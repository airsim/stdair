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
#include <stdair/stdair_json.hpp>
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRetriever.hpp>
#include <stdair/bom/BomJSONExport.hpp>
#include <stdair/bom/BomJSONImport.hpp>
#include <stdair/bom/BomINIImport.hpp>
#include <stdair/bom/BomDisplay.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/EventStruct.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/DatePeriod.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/command/CmdCloneBomManager.hpp>
#include <stdair/service/FacSupervisor.hpp>
#include <stdair/service/FacSTDAIRServiceContext.hpp>
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
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;
    // Return the clone built-in Bom root
    return lSTDAIR_ServiceContext.getCloneBomRoot();
  }  

  // //////////////////////////////////////////////////////////////////////
  BomRoot& STDAIR_Service::getPersistentBomRoot() const {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;
    // Return the persistent built-in Bom root
    return lSTDAIR_ServiceContext.getPersistentBomRoot();
  }

  // //////////////////////////////////////////////////////////////////////
  BasLogParams STDAIR_Service::getLogParams() const {
    return Logger::getLogParams();
  }

  // //////////////////////////////////////////////////////////////////////
  const BasDBParams& STDAIR_Service::getDBParams() const {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;
    return lSTDAIR_ServiceContext.getDBParams();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const ServiceInitialisationType& STDAIR_Service::
  getServiceInitialisationType() const {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;
    return lSTDAIR_ServiceContext.getServiceInitialisationType();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::buildSampleBom() {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lPersistentBomRoot = lSTDAIR_ServiceContext.getPersistentBomRoot();
    
    // Delegate the building process to the dedicated command
    CmdBomManager::buildSampleBom (lPersistentBomRoot);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::
  buildDummyInventory (const CabinCapacity_T& iCabinCapacity) {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the BOM tree root
    BomRoot& lPersistentBomRoot = lSTDAIR_ServiceContext.getPersistentBomRoot();
    
    // Delegate the building process to the dedicated command
    CmdBomManager::buildDummyInventory (lPersistentBomRoot, iCabinCapacity);
    CmdBomManager::buildCompleteDummyInventoryForFareFamilies (lPersistentBomRoot);

  } 

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::
  buildDummyLegSegmentAccesses (BomRoot& iBomRoot) {
    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);

    // Delegate the building process to the dedicated command
    CmdBomManager::buildDummyLegSegmentAccesses (iBomRoot);

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
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the BOM tree root
    const BomRoot& lCloneBomRoot = lSTDAIR_ServiceContext.getCloneBomRoot();

    BomJSONExport::jsonExportFlightDateList (oStr, lCloneBomRoot, 
					     iAirlineCode, iFlightNumber);
    
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
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the BOM tree root
    const BomRoot& lCloneBomRoot = lSTDAIR_ServiceContext.getCloneBomRoot();

    // Retrieve the flight-date object corresponding to the key
    FlightDate* lFlightDate_ptr = 
      BomRetriever::retrieveFlightDateFromKeySet (lCloneBomRoot, iAirlineCode,
                                                  iFlightNumber, 
						  iDepartureDate);

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
  std::string STDAIR_Service::
  jsonExportEventObject (const EventStruct& iEventStruct) const {
    
    std::ostringstream oStr; 

    const EventType::EN_EventType& lEventType = 
      iEventStruct.getEventType();

    switch (lEventType) {
    case EventType::BKG_REQ:{
      BomJSONExport::jsonExportBookingRequestObject (oStr, iEventStruct);
      break;
    }
    case EventType::CX:
    case EventType::OPT_NOT_4_FD:
    case EventType::OPT_NOT_4_NET:
    case EventType::SKD_CHG:
    case EventType::SNAPSHOT:
    case EventType::RM: 
      break;
    case EventType::BRK_PT:
      BomJSONExport::jsonExportBreakPointObject (oStr, iEventStruct);
      break;
    default:
      break;
    }
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool STDAIR_Service::
  jsonImportConfiguration (const JSONString& iJSONString) const {  

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the config holder
    ConfigHolderStruct& lConfigHolder = 
      lSTDAIR_ServiceContext.getConfigHolder();

    // Import the JSON string in the configuration holder
    return BomJSONImport::jsonImportConfig (iJSONString, lConfigHolder);
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::
  jsonExportConfiguration () const {  

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the config holder
    ConfigHolderStruct& lConfigHolder = 
      lSTDAIR_ServiceContext.getConfigHolder();

    // Export the configuration tree in a JSon format
    return lConfigHolder.jsonExport();
  }

  // //////////////////////////////////////////////////////////////////////  
  void STDAIR_Service::importINIConfig (const ConfigINIFile& iConfigINIFile) {  

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the config holder
    ConfigHolderStruct& lConfigHolder = 
      lSTDAIR_ServiceContext.getConfigHolder();

    // Try to import the configuration
    stdair::BomINIImport::importINIConfig (lConfigHolder, iConfigINIFile);
  } 

  // //////////////////////////////////////////////////////////////////////  
  void STDAIR_Service::importConfigValue (const std::string& iValue,
					  const std::string& iPath) {  

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the config holder
    ConfigHolderStruct& lConfigHolder = 
      lSTDAIR_ServiceContext.getConfigHolder();

    // Add the given value to the configuration
    lConfigHolder.addValue (iValue, iPath);
  }

  // //////////////////////////////////////////////////////////////////////  
  void STDAIR_Service::updateAirlineFeatures () { 

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the config holder
    ConfigHolderStruct& lConfigHolder = 
      lSTDAIR_ServiceContext.getConfigHolder();

    // Retrieve the persistent BOM tree root
    BomRoot& lPersistentBomRoot = 
      lSTDAIR_ServiceContext.getPersistentBomRoot(); 

    // Add the given value to the configuration
    lConfigHolder.updateAirlineFeatures (lPersistentBomRoot);
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::list (const AirlineCode_T& iAirlineCode,
                                    const FlightNumber_T& iFlightNumber) const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    const BomRoot& lCloneBomRoot = lSTDAIR_ServiceContext.getCloneBomRoot();
    
    // Dump the content of the whole BOM tree into the string
    BomDisplay::list (oStr, lCloneBomRoot, iAirlineCode, iFlightNumber);
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::listAirportPairDateRange () const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext;

    // Retrieve the BOM tree root
    const BomRoot& lCloneBomRoot = lSTDAIR_ServiceContext.getCloneBomRoot();
    
    // Dump the content of the whole BOM tree into the string
    BomDisplay::listAirportPairDateRange (oStr, lCloneBomRoot);
    
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
    const BomRoot& lCloneBomRoot = lSTDAIR_ServiceContext.getCloneBomRoot();
    
    // Dump the content of the whole BOM tree into the string
    const FlightDate* lFlightDate_ptr =
      BomRetriever::retrieveFlightDateFromKeySet (lCloneBomRoot, iAirlineCode,
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
    const BomRoot& lCloneBomRoot = lSTDAIR_ServiceContext.getCloneBomRoot();
    
    // Dump the content of the whole BOM tree into the string
    stdair::DatePeriodList_T lDatePeriodList;
    BomRetriever::retrieveDatePeriodListFromKeySet  (lCloneBomRoot, ioOrigin,
                                                     ioDestination,
                                                     ioDepartureDate,
                                                     lDatePeriodList);    
    
    return (lDatePeriodList.size() != 0);
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::configDisplay () const {

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);    
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the config holder
    ConfigHolderStruct& lConfigHolder = 
      lSTDAIR_ServiceContext.getConfigHolder();

    // Display (dump in the returned string) the configuration.
    return lConfigHolder.describe();

  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::csvDisplay () const {

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);    
    const STDAIR_ServiceContext& lSTDAIR_ServiceContext = 
      *_stdairServiceContext;

    // Retrieve the persistent BOM tree root
    const BomRoot& lPersistentBomRoot = 
      lSTDAIR_ServiceContext.getPersistentBomRoot();
    
    // Call the dedicated service
    return csvDisplay (lPersistentBomRoot);
  }

  // //////////////////////////////////////////////////////////////////////
  std::string STDAIR_Service::csvDisplay (const BomRoot& iBomRoot) const {
    std::ostringstream oStr;

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    
    // Dump the content of the whole BOM tree into the string
    BomDisplay::csvDisplay (oStr, iBomRoot);
    
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
    const BomRoot& lCloneBomRoot = lSTDAIR_ServiceContext.getCloneBomRoot();

    // Retrieve the flight-date object corresponding to the key
    FlightDate* lFlightDate_ptr = 
      BomRetriever::retrieveFlightDateFromKeySet (lCloneBomRoot, iAirlineCode,
                                                  iFlightNumber, 
						  iDepartureDate);

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
    const BomRoot& lCloneBomRoot = lSTDAIR_ServiceContext.getCloneBomRoot();

    // Retrieve the flight-date object corresponding to the key
    DatePeriodList_T lDatePeriodList;
    BomRetriever::retrieveDatePeriodListFromKeySet (lCloneBomRoot, iOrigin,
                                                    iDestination, 
						    iDepartureDate,
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

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::clonePersistentBom () {  

    // Retrieve the StdAir service context
    assert (_stdairServiceContext != NULL);
    STDAIR_ServiceContext& lSTDAIR_ServiceContext = *_stdairServiceContext; 

    // Clean all the cloned objects
    FacSupervisor::instance().cleanCloneBomLayer();

    // Init the root of the clone BOM tree
    lSTDAIR_ServiceContext.initCloneBomRoot();

    // Retrieve the persistent BOM tree root and the clone BOM tree root
    const BomRoot& lPersistentBomRoot = 
      lSTDAIR_ServiceContext.getPersistentBomRoot(); 
    BomRoot& lCloneBomRoot = lSTDAIR_ServiceContext.getCloneBomRoot(); 
   
    // Call the dedicated service to clone the whole BOM
    CmdCloneBomManager::cloneBomRoot (lPersistentBomRoot, lCloneBomRoot);
    
  }

}
