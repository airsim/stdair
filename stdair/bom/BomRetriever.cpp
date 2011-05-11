// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/bom/BomKeyManager.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BomRetriever.hpp>
#include <stdair/bom/ParsedKey.hpp>
#include <stdair/bom/AirportPair.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Inventory* BomRetriever::
  retrieveInventoryFromLongKey (const BomRoot& iBomRoot,
                                const std::string& iFullKeyStr) {
    Inventory* oInventory_ptr = NULL;

    // Extract the inventory key (i.e., airline code)
    const InventoryKey& lInventoryKey =
      BomKeyManager::extractInventoryKey (iFullKeyStr);

    oInventory_ptr = iBomRoot.getInventory (lInventoryKey);

    return oInventory_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory* BomRetriever::retrieveInventoryFromKey (const BomRoot& iBomRoot,
                                                     const InventoryKey& iKey) {
    Inventory* oInventory_ptr = NULL;

    //
    oInventory_ptr = iBomRoot.getInventory (iKey);

    return oInventory_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory* BomRetriever::
  retrieveInventoryFromKey (const BomRoot& iBomRoot,
                            const AirlineCode_T& iAirlineCode) {
    Inventory* oInventory_ptr = NULL;

    //
    const InventoryKey lKey (iAirlineCode);
    oInventory_ptr = iBomRoot.getInventory (lKey);

    return oInventory_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* BomRetriever::
  retrieveFlightDateFromLongKey (const BomRoot& iBomRoot,
                                 const std::string& iFullKeyStr) {
    FlightDate* oFlightDate_ptr = NULL;

    // Retrieve the inventory
    Inventory* oInventory_ptr =
      BomRetriever::retrieveInventoryFromLongKey (iBomRoot, iFullKeyStr);
    if (oInventory_ptr == NULL) {
      return oFlightDate_ptr;
    }
    assert (oInventory_ptr != NULL);

    // Extract the flight-date key (i.e., flight number and date)
    const FlightDateKey& lFlightDateKey =
      BomKeyManager::extractFlightDateKey (iFullKeyStr);

    oFlightDate_ptr = oInventory_ptr->getFlightDate (lFlightDateKey);

    return oFlightDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* BomRetriever::
  retrieveFlightDateFromKeySet (const BomRoot& iBomRoot,
                                const AirlineCode_T& iAirlineCode,
                                const FlightNumber_T& iFlightNumber,
                                const Date_T& iFlightDateDate) {
    FlightDate* oFlightDate_ptr = NULL;

    // Retrieve the inventory
    Inventory* oInventory_ptr =
      BomRetriever::retrieveInventoryFromKey (iBomRoot, iAirlineCode);
    if (oInventory_ptr == NULL) {
      return oFlightDate_ptr;
    }
    assert (oInventory_ptr != NULL);

    //
    oFlightDate_ptr = retrieveFlightDateFromKey (*oInventory_ptr,
                                                 iFlightNumber, iFlightDateDate);

    return oFlightDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* BomRetriever::
  retrieveFlightDateFromLongKey (const Inventory& iInventory,
                                 const std::string& iFullKeyStr) {
    FlightDate* oFlightDate_ptr = NULL;

    // Extract the flight-date key (i.e., flight number and date)
    const FlightDateKey& lFlightDateKey =
      BomKeyManager::extractFlightDateKey (iFullKeyStr);

    oFlightDate_ptr = iInventory.getFlightDate (lFlightDateKey);

    return oFlightDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* BomRetriever::
  retrieveFlightDateFromKey (const Inventory& iInventory,
                             const FlightDateKey& iKey) {
    FlightDate* oFlightDate_ptr = NULL;

    //
    oFlightDate_ptr = iInventory.getFlightDate (iKey);

    return oFlightDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* BomRetriever::
  retrieveFlightDateFromKey (const Inventory& iInventory,
                             const FlightNumber_T& iFlightNumber,
                             const Date_T& iFlightDateDate) {
    FlightDate* oFlightDate_ptr = NULL;

    //
    const FlightDateKey lKey (iFlightNumber, iFlightDateDate);
    oFlightDate_ptr = iInventory.getFlightDate (lKey);

    return oFlightDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate* BomRetriever::
  retrieveSegmentDateFromLongKey (const BomRoot& iBomRoot,
                                  const std::string& iFullKeyStr) {
    SegmentDate* oSegmentDate_ptr = NULL;

    // Retrieve the flight-date
    FlightDate* oFlightDate_ptr =
      BomRetriever::retrieveFlightDateFromLongKey (iBomRoot, iFullKeyStr);
    if (oFlightDate_ptr == NULL) {
      return oSegmentDate_ptr;
    }
    assert (oFlightDate_ptr != NULL);

    // Extract the segment-date key (i.e., origin and destination)
    const SegmentDateKey& lSegmentDateKey =
      BomKeyManager::extractSegmentDateKey (iFullKeyStr);

    oSegmentDate_ptr = oFlightDate_ptr->getSegmentDate (lSegmentDateKey);

    return oSegmentDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate* BomRetriever::
  retrieveSegmentDateFromLongKey (const Inventory& iInventory,
                                  const std::string& iFullKeyStr) {
    SegmentDate* oSegmentDate_ptr = NULL;

    ParsedKey lParsedKey = BomKeyManager::extractKeys (iFullKeyStr);

    if (iInventory.getAirlineCode() != lParsedKey._airlineCode) {
      STDAIR_LOG_DEBUG ("Airline code: " << lParsedKey._airlineCode);
      return oSegmentDate_ptr;
    }

    FlightDate* lFlightDate_ptr =
      retrieveFlightDateFromKey (iInventory, lParsedKey.getFlightDateKey());
    if (lFlightDate_ptr == NULL) {
      STDAIR_LOG_DEBUG ("Flight-date key: "
                        << lParsedKey.getFlightDateKey().toString());
      return oSegmentDate_ptr;
    }

    oSegmentDate_ptr =
      retrieveSegmentDateFromKey (*lFlightDate_ptr, lParsedKey.getSegmentKey());
    if (oSegmentDate_ptr == NULL) {
      STDAIR_LOG_DEBUG ("Segment-date key: "
                        << lParsedKey.getSegmentKey().toString());
      return oSegmentDate_ptr;
    }
    
    return oSegmentDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate* BomRetriever::
  retrieveSegmentDateFromLongKey (const FlightDate& iFlightDate,
                                  const std::string& iFullKeyStr) {
    SegmentDate* oSegmentDate_ptr = NULL;

    // Extract the segment-date key (i.e., origin and destination)
    const SegmentDateKey& lSegmentDateKey =
      BomKeyManager::extractSegmentDateKey (iFullKeyStr);

    oSegmentDate_ptr = iFlightDate.getSegmentDate (lSegmentDateKey);

    return oSegmentDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate* BomRetriever::
  retrieveSegmentDateFromKey (const FlightDate& iFlightDate,
                              const SegmentDateKey& iKey) {
    SegmentDate* oSegmentDate_ptr = NULL;

    //
    oSegmentDate_ptr = iFlightDate.getSegmentDate (iKey);

    return oSegmentDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate* BomRetriever::
  retrieveSegmentDateFromKey (const FlightDate& iFlightDate,
                              const AirportCode_T& iOrigin,
                              const AirportCode_T& iDestination) {
    SegmentDate* oSegmentDate_ptr = NULL;

    //
    const SegmentDateKey lKey (iOrigin, iDestination);
    oSegmentDate_ptr = iFlightDate.getSegmentDate (lKey);

    return oSegmentDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClass* BomRetriever::
  retrieveBookingClassFromLongKey (const Inventory& iInventory,
                                   const std::string& iFullKeyStr,
                                   const ClassCode_T& iClassCode) {
    BookingClass* oBookingClass_ptr = NULL;

    SegmentDate* lSegmentDate_ptr = retrieveSegmentDateFromLongKey (iInventory,
                                                                    iFullKeyStr);

    if (lSegmentDate_ptr == NULL) {
      return oBookingClass_ptr;
    }
    assert (lSegmentDate_ptr != NULL);

    // 
    oBookingClass_ptr =
      BomManager::getObjectPtr<BookingClass> (*lSegmentDate_ptr, iClassCode);

    return oBookingClass_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  AirportPair* BomRetriever::
  retrieveFareRuleFromKeySet (const BomRoot& iBomRoot,
                              const stdair::AirportCode_T& iOrigin,
                              const stdair::AirportCode_T& iDestination) {

    // Get the Airport pair stream of the segment path.
    const AirportPairKey lAirportPairKey (iOrigin, iDestination);
    
    // Search for the fare rules having the same origin and
    // destination airport as the travel solution
    AirportPair* oAirportPair_ptr = BomManager::
      getObjectPtr<AirportPair> (iBomRoot, lAirportPairKey.toString());  

    return oAirportPair_ptr;
   
  }

  // ////////////////////////////////////////////////////////////////////
  void BomRetriever::
  retrieveFareRuleFromKeySet (const BomRoot& iBomRoot,
                              const stdair::AirportCode_T& iOrigin,
                              const stdair::AirportCode_T& iDestination,
                              const stdair::Date_T& iDepartureDate,
                              stdair::DatePeriodList_T& ioDatePeriodList) {

    /** // Retrieve the airport-pair
    AirportPair* oAirportPair_ptr =
      BomRetriever::retrieveFareRuleFromKeySet (iBomRoot, iOrigin,
                                                iDestination);
    if (oAirportPair_ptr == NULL) {
      return oDatePeriod_ptr;
    }
    assert (oAirportPair_ptr != NULL);

    //
    // oDatePeriod_ptr = retrieveFlightDateFromKey (*oAirportPair_ptr,
    //                                   iDepartureDate);
 */ 
   
  }

}
