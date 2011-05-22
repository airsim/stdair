// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_types.hpp>
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRetriever.hpp>
#include <stdair/bom/BomJSONExport.hpp>
#include <stdair/bom/BomDisplay.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/EventQueue.hpp>
#include <stdair/bom/EventStruct.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/DatePeriod.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/FacSupervisor.hpp>
#include <stdair/service/FacSTDAIRServiceContext.hpp>
#include <stdair/service/STDAIR_ServiceContext.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/service/DBSessionManager.hpp>
#include <stdair/STDAIR_Service.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service() : _stdairServiceContext (NULL) {

    // Initialise the service context
    initServiceContext();
    
    // Initialise the (remaining of the) context
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const STDAIR_Service& iService) 
    : _stdairServiceContext (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const BasLogParams& iLogParams)  
    : _stdairServiceContext (NULL) {

    // Initialise the service context
    initServiceContext();
    
    // Set the log file
    logInit (iLogParams);

    // Initialise the (remaining of the) context
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const BasLogParams& iLogParams,
                                  const BasDBParams& iDBParams) 
    : _stdairServiceContext (NULL) { 

    // Initialise the service context
    initServiceContext();

    // Set the log file
    logInit (iLogParams);

    // Create a database session
    dbInit (iDBParams);

    // Initialise the (remaining of the) context
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::~STDAIR_Service() {
    // Delete/Clean all the objects from memory
    finalise();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::initServiceContext() {
    // Initialise the service context
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      FacSTDAIRServiceContext::instance().create();

    // Store the stdair service context
    _stdairServiceContext = &lSTDAIR_ServiceContext;
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::logInit (const BasLogParams& iLogParams) {
    Logger::init (iLogParams);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::dbInit (const BasDBParams& iDBParams) {
    DBSessionManager::init (iDBParams);

    // Store the database parameters into the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;
    lSTDAIR_ServiceContext.setDBParams (iDBParams);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::init() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BomRoot& STDAIR_Service::getBomRoot() const {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;
    return lSTDAIR_ServiceContext.getBomRoot();
  }

  // //////////////////////////////////////////////////////////////////////
  EventQueue& STDAIR_Service::getEventQueue() const {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;
    return lSTDAIR_ServiceContext.getEventQueue();
  }

  // //////////////////////////////////////////////////////////////////////
  BasLogParams STDAIR_Service::getLogParams() const {
    return Logger::getLogParams();
  }

  // //////////////////////////////////////////////////////////////////////
  const BasDBParams& STDAIR_Service::getDBParams() const {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;
    return lSTDAIR_ServiceContext.getDBParams();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::buildSampleBom (const bool isForRMOL,
                                       const CabinCapacity_T iCabinCapacity ) {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Build a sample BOM tree
    if (isForRMOL == true) {
      CmdBomManager::buildSampleBomForRMOL (lBomRoot, iCabinCapacity);
    } else {
      CmdBomManager::buildSampleBom (lBomRoot);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::buildSampleBomForFareQuoter () {
    
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Build a sample BOM tree
    CmdBomManager::buildSampleBomForFareQuoter (lBomRoot);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::buildSampleBomForAirRAC () {
    
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Build a sample BOM tree
    CmdBomManager::buildSampleBomForAirRAC (lBomRoot);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::
  buildSampleTravelSolutionForPricing (TravelSolutionList_T& ioTravelSolutionList) {
    // Build a sample list of travel solution structures
    CmdBomManager::buildSampleTravelSolutionForPricing (ioTravelSolutionList);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::
  buildSampleTravelSolutions (TravelSolutionList_T& ioTravelSolutionList) {
    // Build a sample list of travel solution structures
    CmdBomManager::buildSampleTravelSolutions (ioTravelSolutionList);
  }

  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct STDAIR_Service::
  buildSampleBookingRequest (const bool isForCRS) {

    // Build a sample booking request structure
    if (isForCRS == true) {
      return CmdBomManager::buildSampleBookingRequestForCRS();
    }

    return CmdBomManager::buildSampleBookingRequest();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::
  jsonExport (const stdair::AirlineCode_T& iAirlineCode,
              const stdair::FlightNumber_T& iFlightNumber,
              const stdair::Date_T& iDepartureDate) const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();

    // Retrieve the flight-date object corresponding to the key
    FlightDate* lFlightDate_ptr = 
      BomRetriever::retrieveFlightDateFromKeySet (lBomRoot, iAirlineCode,
                                                  iFlightNumber, iDepartureDate);

    // Dump the content of the whole BOM tree into the string
    if (lFlightDate_ptr != NULL) {
      BomJSONExport::jsonExport (oStr, *lFlightDate_ptr);
      
    } else {
      oStr << "error - No flight-date found for the given key: '"
           << iAirlineCode << iFlightNumber << " - " << iDepartureDate << "'";
    }
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::csvDisplay() const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Dump the content of the whole BOM tree into the string
    BomDisplay::csvDisplay (oStr, lBomRoot);
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::
  csvDisplay (const stdair::AirlineCode_T& iAirlineCode,
              const stdair::FlightNumber_T& iFlightNumber,
              const stdair::Date_T& iDepartureDate) const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();

    // Retrieve the flight-date object corresponding to the key
    FlightDate* lFlightDate_ptr = 
      BomRetriever::retrieveFlightDateFromKeySet (lBomRoot, iAirlineCode,
                                                  iFlightNumber, iDepartureDate);

    // Dump the content of the whole BOM tree into the string
    if (lFlightDate_ptr != NULL) {
      BomDisplay::csvDisplay (oStr, *lFlightDate_ptr);
      
    } else {
      oStr << "   No flight-date found for the given key: '"
           << iAirlineCode << iFlightNumber << " - " << iDepartureDate << "'";
    }
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::
  csvDisplay (const TravelSolutionList_T& iTravelSolutionList) const {

    // Dump the content of the whole list of travel solutions into the string
    std::ostringstream oStr;
    BomDisplay::csvDisplay (oStr, iTravelSolutionList);
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::
  csvDisplay (const stdair::AirportCode_T& iOrigin,
              const stdair::AirportCode_T& iDestination,
              const stdair::Date_T& iDepartureDate) const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();

    // Retrieve the flight-date object corresponding to the key
    DatePeriodList_T lDatePeriodList;
    BomRetriever::retrieveDatePeriodListFromKeySet (lBomRoot, iOrigin,
                                                    iDestination, iDepartureDate,
                                                    lDatePeriodList);

    // Dump the content of the whole BOM tree into the string
    if (lDatePeriodList.empty()) {
      oStr << "   No fare-rule found for the given key: '"
            << iOrigin << "-" << iDestination << " - " << iDepartureDate << "'";
    } else {
      BomDisplay::csvDisplay (oStr, lDatePeriodList);
    }
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::finalise() {
    // Clean all the objects
    FacSupervisor::cleanAll();
  }

  // ////////////////////////////////////////////////////////////////////
  const Count_T& STDAIR_Service::
  getExpectedTotalNumberOfEventsToBeGenerated() const {
    
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the event queue object instance
    const EventQueue& lQueue = lSTDAIR_ServiceContext.getEventQueue();
    
    // Delegate the call to the dedicated command
    const Count_T& oExpectedTotalNumberOfEventsToBeGenerated =
      lQueue.getExpectedTotalNbOfEvents();

    //
    return oExpectedTotalNumberOfEventsToBeGenerated;
  }

  // ////////////////////////////////////////////////////////////////////
  const Count_T& STDAIR_Service::
  getExpectedTotalNumberOfEventsToBeGenerated (const EventType::EN_EventType& iType) const {
    
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the event queue object instance
    const EventQueue& lQueue = lSTDAIR_ServiceContext.getEventQueue();
    
    // Delegate the call to the dedicated command
    const Count_T& oExpectedTotalNumberOfEventsToBeGenerated =
      lQueue.getExpectedTotalNbOfEvents (iType);

    //
    return oExpectedTotalNumberOfEventsToBeGenerated;
  }

  // ////////////////////////////////////////////////////////////////////
  const Count_T& STDAIR_Service::
  getActualTotalNumberOfEventsToBeGenerated() const {
    
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the event queue object instance
    const EventQueue& lQueue = lSTDAIR_ServiceContext.getEventQueue();
    
    // Delegate the call to the dedicated command
    const Count_T& oActualTotalNumberOfEventsToBeGenerated =
      lQueue.getActualTotalNbOfEvents();

    //
    return oActualTotalNumberOfEventsToBeGenerated;
  }

  // ////////////////////////////////////////////////////////////////////
  const Count_T& STDAIR_Service::
  getActualTotalNumberOfEventsToBeGenerated (const EventType::EN_EventType& iType) const {
    
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the event queue object instance
    const EventQueue& lQueue = lSTDAIR_ServiceContext.getEventQueue();
    
    // Delegate the call to the dedicated command
    const Count_T& oActualTotalNumberOfEventsToBeGenerated =
      lQueue.getActualTotalNbOfEvents (iType);

    //
    return oActualTotalNumberOfEventsToBeGenerated;
  }

  // ////////////////////////////////////////////////////////////////////
  ProgressStatusSet STDAIR_Service::popEvent (EventStruct& ioEventStruct) const {

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the event queue object instance
    EventQueue& lQueue = lSTDAIR_ServiceContext.getEventQueue();
    
    // Extract the next event from the queue
    return lQueue.popEvent (ioEventStruct);
  }

  // ////////////////////////////////////////////////////////////////////
  bool STDAIR_Service::isQueueDone() const {

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the event queue object instance
    const EventQueue& lQueue = lSTDAIR_ServiceContext.getEventQueue();
    
    // Calculates whether the event queue has been fully emptied
    const bool isQueueDone = lQueue.isQueueDone();

    //
    return isQueueDone;
  }

  // ////////////////////////////////////////////////////////////////////
  void STDAIR_Service::reset() const {

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the event queue object instance
    EventQueue& lQueue = lSTDAIR_ServiceContext.getEventQueue();
    
    // Delegate the call to the event queue object
    lQueue.reset();
  }

}
