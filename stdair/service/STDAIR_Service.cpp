// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#if BOOST_VERSION >= 104100
// Boost Property Tree
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#endif // BOOST_VERSION >= 104100
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

#if BOOST_VERSION >= 104100
namespace bpt = boost::property_tree;
#else // BOOST_VERSION >= 104100
namespace bpt {
  typedef char ptree;
}
#endif // BOOST_VERSION >= 104100

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
  const ServiceInitialisationType& STDAIR_Service::
  getServiceInitialisationType() const {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;
    return lSTDAIR_ServiceContext.getServiceInitialisationType();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::buildSampleBom() {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Delegate the building process to the dedicated command
    CmdBomManager::buildSampleBom (lBomRoot);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::
  buildDummyInventory (const CabinCapacity_T& iCabinCapacity) {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Delegate the building process to the dedicated command
    CmdBomManager::buildDummyInventory (lBomRoot, iCabinCapacity);
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
  jsonExportFlightDateList (const AirlineCode_T& iAirlineCode,
			    const FlightNumber_T& iFlightNumber) const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();

    BomJSONExport::jsonExportFlightDateList (oStr, lBomRoot, iAirlineCode, iFlightNumber);
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::
  jsonExportFlightDateObjects (const stdair::AirlineCode_T& iAirlineCode,
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
      BomJSONExport::jsonExportFlightDateObjects (oStr, *lFlightDate_ptr);
      
    } else {
#if BOOST_VERSION >= 104100
      //
      bpt::ptree lPropertyTree;
      
      // Build the appropriate message, so that the client may know that
      // no flight-date can be found for that given key.
      std::ostringstream oNoFlightDateStream;
      oNoFlightDateStream << "No flight-date found for the given key: '"
                          << iAirlineCode << iFlightNumber
                          << " - " << iDepartureDate << "'";
      const std::string oNoFlightDateString (oNoFlightDateStream.str());

      // Put in the property tree the fact that no flight-date has been found.
      // \note That is not (necessary) an error.
      lPropertyTree.put ("error", oNoFlightDateString.c_str());

      // Write the property tree into the JSON stream.
      write_json (oStr, lPropertyTree);
#endif // BOOST_VERSION >= 104100
    }
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::jsonExportBookingRequestObjects () const {
    std::ostringstream oStr; 

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the event queue object instance
    const EventQueue& lQueue = lSTDAIR_ServiceContext.getEventQueue();

    BomJSONExport::jsonExportBookingRequestObjects (oStr, lQueue);
    
    return oStr.str();
  }


  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::list (const AirlineCode_T& iAirlineCode,
                                    const FlightNumber_T& iFlightNumber) const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Dump the content of the whole BOM tree into the string
    BomDisplay::list (oStr, lBomRoot, iAirlineCode, iFlightNumber);
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::listAirportPairDateRange () const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Dump the content of the whole BOM tree into the string
    BomDisplay::listAirportPairDateRange (oStr, lBomRoot);
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool STDAIR_Service::check (const AirlineCode_T& iAirlineCode,
                              const FlightNumber_T& iFlightNumber,
                              const stdair::Date_T& iDepartureDate) const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Dump the content of the whole BOM tree into the string
    const FlightDate* lFlightDate_ptr =
      BomRetriever::retrieveFlightDateFromKeySet (lBomRoot, iAirlineCode,
                                                  iFlightNumber,
                                                  iDepartureDate);    
    
    return (lFlightDate_ptr != NULL);
  }

  // //////////////////////////////////////////////////////////////////////
  bool STDAIR_Service::check (const stdair::AirportCode_T& ioOrigin,
                              const stdair::AirportCode_T& ioDestination,
                              const stdair::Date_T& ioDepartureDate) const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lBomRoot = lSTDAIR_ServiceContext.getBomRoot();
    
    // Dump the content of the whole BOM tree into the string
    stdair::DatePeriodList_T lDatePeriodList;
    BomRetriever::retrieveDatePeriodListFromKeySet  (lBomRoot, ioOrigin,
                                                     ioDestination,
                                                     ioDepartureDate,
                                                     lDatePeriodList);    
    
    return (lDatePeriodList.size() != 0);
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
