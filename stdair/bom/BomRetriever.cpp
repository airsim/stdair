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
  Inventory* BomRetriever::
  retrieveInventoryFromShortKey (const BomRoot& iBomRoot,
                                 const std::string& iKeyStr) {
    Inventory* oInventory_ptr = NULL;

    // Extract the inventory key (i.e., airline code)
    const InventoryKey& lInventoryKey =
      BomKeyManager::extractInventoryKey (iKeyStr);

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
  retrieveFlightDateFromShortKey (const Inventory& iInventory,
                                  const std::string& iKeyStr) {
    FlightDate* oFlightDate_ptr = NULL;

    // Extract the flight-date key (i.e., flight number and date)
    const FlightDateKey& lFlightDateKey =
      BomKeyManager::extractFlightDateKey (iKeyStr);

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

    // Retrieve the flight-date
    FlightDate* oFlightDate_ptr =
      BomRetriever::retrieveFlightDateFromLongKey (iInventory, iFullKeyStr);
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
  retrieveSegmentDateFromShortKey (const FlightDate& iFlightDate,
                                   const std::string& iKeyStr) {
    SegmentDate* oSegmentDate_ptr = NULL;

    // Extract the segment-date key (i.e., origin and destination)
    const SegmentDateKey& lSegmentDateKey =
      BomKeyManager::extractSegmentDateKey (iKeyStr);

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
  retrieveBookingClassFromLongKey (const BomRoot& iBomRoot,
                                   const std::string& iFullKeyStr) {
    BookingClass* oBookingClass_ptr = NULL;

    // Retrieve the segment-date
    SegmentDate* lSegmentDate_ptr =
      BomRetriever::retrieveSegmentDateFromLongKey (iBomRoot, iFullKeyStr);
    if (lSegmentDate_ptr == NULL) {
      return oBookingClass_ptr;
    }
    assert (lSegmentDate_ptr != NULL);

    // Extract the booking class key (i.e., booking class code)
    const BookingClassKey& lBookingClassKey =
      BomKeyManager::extractBookingClassKey (iFullKeyStr);

    // Browse the segment-cabins
    const SegmentCabinList_T& lSegmentCabinList =
      BomManager::getList<SegmentCabin> (*lSegmentDate_ptr);
    for (SegmentCabinList_T::const_iterator itCabin =
           lSegmentCabinList.begin();
         itCabin != lSegmentCabinList.end(); ++itCabin) {
      SegmentCabin* lSegmentCabin_ptr = *itCabin;
      assert (lSegmentCabin_ptr != NULL);

      oBookingClass_ptr =
        BomManager::getObjectPtr<BookingClass> (*lSegmentCabin_ptr,
                                                lBookingClassKey.toString());
    }

    return oBookingClass_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClass* BomRetriever::
  retrieveBookingClassFromLongKey (const Inventory& iInventory,
                                   const std::string& iFullKeyStr) {
    BookingClass* oBookingClass_ptr = NULL;

    // Retrieve the segment-date
    SegmentDate* lSegmentDate_ptr =
      BomRetriever::retrieveSegmentDateFromLongKey (iInventory, iFullKeyStr);
    if (lSegmentDate_ptr == NULL) {
      return oBookingClass_ptr;
    }
    assert (lSegmentDate_ptr != NULL);

    // Extract the booking class key (i.e., booking class code)
    const BookingClassKey& lBookingClassKey =
      BomKeyManager::extractBookingClassKey (iFullKeyStr);

    // Browse the segment-cabins
    const SegmentCabinList_T& lSegmentCabinList =
      BomManager::getList<SegmentCabin> (*lSegmentDate_ptr);
    for (SegmentCabinList_T::const_iterator itCabin =
           lSegmentCabinList.begin();
         itCabin != lSegmentCabinList.end(); ++itCabin) {
      SegmentCabin* lSegmentCabin_ptr = *itCabin;
      assert (lSegmentCabin_ptr != NULL);

      oBookingClass_ptr =
        BomManager::getObjectPtr<BookingClass> (*lSegmentCabin_ptr,
                                                lBookingClassKey.toString());
      if (oBookingClass_ptr != NULL) {
        break;
      }
    }

    return oBookingClass_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClass* BomRetriever::
  retrieveBookingClassFromLongKey (const Inventory& iInventory,
                                   const std::string& iFullKeyStr,
                                   const ClassCode_T& iClassCode) {
    BookingClass* oBookingClass_ptr = NULL;

    // Retrieve the segment-date
    SegmentDate* lSegmentDate_ptr =
      BomRetriever::retrieveSegmentDateFromLongKey (iInventory, iFullKeyStr);
    if (lSegmentDate_ptr == NULL) {
      return oBookingClass_ptr;
    }
    assert (lSegmentDate_ptr != NULL);

    // Browse the segment-cabins
    const SegmentCabinList_T& lSegmentCabinList =
      BomManager::getList<SegmentCabin> (*lSegmentDate_ptr);
    for (SegmentCabinList_T::const_iterator itCabin =
           lSegmentCabinList.begin();
         itCabin != lSegmentCabinList.end(); ++itCabin) {
      SegmentCabin* lSegmentCabin_ptr = *itCabin;
      assert (lSegmentCabin_ptr != NULL);

      oBookingClass_ptr =
        BomManager::getObjectPtr<BookingClass> (*lSegmentCabin_ptr, iClassCode);
      if (oBookingClass_ptr != NULL) {
        break;
      }
    }

    return oBookingClass_ptr;
  }

}
