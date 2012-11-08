// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/BomKeyManager.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/AirlineFeature.hpp>
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
  Inventory* BomRetriever::
  retrieveInventoryFromLongKey (const Inventory& iInventory,
                                const std::string& iFullKeyStr) {
    Inventory* oInventory_ptr = NULL;
    
    // Extract the inventory key (i.e., airline code)
    const InventoryKey& lInventoryKey =
      BomKeyManager::extractInventoryKey (iFullKeyStr);
    const stdair::AirlineCode_T lAirlineCode = 
      lInventoryKey.getAirlineCode();

    oInventory_ptr =
      BomManager::getObjectPtr<Inventory> (iInventory,
                                           lAirlineCode);
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
  AirlineFeature* BomRetriever::
  retrieveAirlineFeatureFromKey (const BomRoot& iBomRoot,
				 const AirlineCode_T& iAirlineCode) {
    Inventory* oInventory_ptr = NULL;
    AirlineFeature* oAirlineFeature_ptr = NULL;

    //
    oInventory_ptr = retrieveInventoryFromKey (iBomRoot, iAirlineCode);
    if (oInventory_ptr == NULL) {
      return oAirlineFeature_ptr;
    }
    assert (oInventory_ptr != NULL);

    oAirlineFeature_ptr = 
      BomManager::getObjectPtr<AirlineFeature,Inventory> (*oInventory_ptr,
							  iAirlineCode);

    return oAirlineFeature_ptr;
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
  LegDate* BomRetriever::
  retrieveOperatingLegDateFromLongKey (const FlightDate& iFlightDate,
				       const std::string& iFullKeyStr) {
    LegDate* oLegDate_ptr = NULL;

    // Extract the segment-date key (i.e., origin and destination)
    const LegDateKey& lLegDateKey =
      BomKeyManager::extractLegDateKey (iFullKeyStr);

    oLegDate_ptr = iFlightDate.getLegDate (lLegDateKey);

    return oLegDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate* BomRetriever::
  retrievePartnerSegmentDateFromLongKey (const Inventory& iInventory,
                                         const std::string& iFullKeyStr) {
    SegmentDate* oSegmentDate_ptr = NULL;
    Inventory* oInventory_ptr = NULL;

    // Extract the inventory key (i.e., airline code)
    const InventoryKey& lInventoryKey =
      BomKeyManager::extractInventoryKey (iFullKeyStr);
    const stdair::AirlineCode_T lAirlineCode = 
      lInventoryKey.getAirlineCode();

    // Retrieve the inventory
    oInventory_ptr =
      retrieveInventoryFromLongKey (iInventory, lAirlineCode);

    if (oInventory_ptr != NULL) { 
      oSegmentDate_ptr =
        retrieveSegmentDateFromLongKey (*oInventory_ptr, iFullKeyStr);
    }

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
  retrieveAirportPairFromKeySet (const BomRoot& iBomRoot,
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
  retrieveDatePeriodListFromKey (const AirportPair& iAirportPair,
                                 const stdair::Date_T& iDepartureDate,
                                 stdair::DatePeriodList_T& ioDatePeriodList) {

    // Get the list of date-period
    const DatePeriodList_T& lFareDatePeriodList =
      BomManager::getList<DatePeriod> (iAirportPair);

    // Browse the date-period list
    for (DatePeriodList_T::const_iterator itDateRange =
           lFareDatePeriodList.begin();
         itDateRange != lFareDatePeriodList.end(); ++itDateRange) {

      DatePeriod* lCurrentFareDatePeriod_ptr = *itDateRange ;
      assert (lCurrentFareDatePeriod_ptr != NULL);

      // Select the date-period objects having a corresponding date range
      const bool isDepartureDateValid =
        lCurrentFareDatePeriod_ptr->isDepartureDateValid (iDepartureDate);
      
      // Add the date-period objects having a corresponding date range
      // to the list to display
      if (isDepartureDateValid == true) {
        ioDatePeriodList.push_back(lCurrentFareDatePeriod_ptr);
      }
    }

  }

  // ////////////////////////////////////////////////////////////////////
  void BomRetriever::
  retrieveDatePeriodListFromKeySet (const BomRoot& iBomRoot,
                                    const stdair::AirportCode_T& iOrigin,
                                    const stdair::AirportCode_T& iDestination,
                                    const stdair::Date_T& iDepartureDate,
                                    stdair::DatePeriodList_T& ioDatePeriodList) {

    // Retrieve the airport-pair
    AirportPair* oAirportPair_ptr =
      BomRetriever::retrieveAirportPairFromKeySet(iBomRoot, iOrigin,
                                                 iDestination);
    if (oAirportPair_ptr == NULL) {
      return;
    }
    assert (oAirportPair_ptr != NULL);

    // Retrieve the flight date
    BomRetriever::retrieveDatePeriodListFromKey (*oAirportPair_ptr, iDepartureDate,
                                                 ioDatePeriodList);
   
  }
  
  // ////////////////////////////////////////////////////////////////////
  LegCabin& BomRetriever::
  retrieveDummyLegCabin (stdair::BomRoot& iBomRoot,
                         const bool isForFareFamilies) {

    LegCabin* oLegCabin_ptr = NULL;

    // Retrieve the Inventory
    const Inventory* lInventory_ptr = BomRetriever::
      retrieveInventoryFromKey (iBomRoot, DEFAULT_AIRLINE_CODE);

    if (lInventory_ptr == NULL) {
      std::ostringstream oStr;
      oStr << "The inventory corresponding to the '"
           << DEFAULT_AIRLINE_CODE << "' airline can not be found";
      throw ObjectNotFoundException (oStr.str());
    }
    
    // Retrieve the FlightDate
    FlightDate* lFlightDate_ptr = NULL;
    if (isForFareFamilies == true) {
      lFlightDate_ptr = BomRetriever::
        retrieveFlightDateFromKey (*lInventory_ptr, DEFAULT_FLIGHT_NUMBER_FF,
                                   DEFAULT_DEPARTURE_DATE);
      
      if (lFlightDate_ptr == NULL) {
        std::ostringstream oStr;
        oStr << "The flight-date corresponding to ("
             << DEFAULT_FLIGHT_NUMBER_FF << ", "
             << DEFAULT_DEPARTURE_DATE << ") can not be found";
        throw ObjectNotFoundException (oStr.str());
      }
    } else {
      lFlightDate_ptr = BomRetriever::
        retrieveFlightDateFromKey (*lInventory_ptr, DEFAULT_FLIGHT_NUMBER,
                                   DEFAULT_DEPARTURE_DATE);
      
      if (lFlightDate_ptr == NULL) {
        std::ostringstream oStr;
        oStr << "The flight-date corresponding to ("
             << DEFAULT_FLIGHT_NUMBER << ", "
             << DEFAULT_DEPARTURE_DATE << ") can not be found";
        throw ObjectNotFoundException (oStr.str());
      }
    }
    assert(lFlightDate_ptr != NULL);

    // Retrieve the LegDate
    const LegDateKey lLegDateKey (DEFAULT_ORIGIN);
    const LegDate* lLegDate_ptr =
      lFlightDate_ptr->getLegDate (lLegDateKey);

    if (lLegDate_ptr == NULL) {
      std::ostringstream oStr;
      oStr << "The leg-date corresponding to the '"
           << DEFAULT_ORIGIN << "' origin can not be found";
      throw ObjectNotFoundException (oStr.str());
    }
    
    // Retrieve the LegCabin
    const LegCabinKey lLegCabinKey (DEFAULT_CABIN_CODE);
    oLegCabin_ptr = lLegDate_ptr->getLegCabin (lLegCabinKey);

    if (oLegCabin_ptr == NULL) {
      std::ostringstream oStr;
      oStr << "The leg-cabin corresponding to the '"
           << DEFAULT_CABIN_CODE << "' cabin code can not be found";
      throw ObjectNotFoundException (oStr.str());
    }
    
    assert (oLegCabin_ptr != NULL);
    return *oLegCabin_ptr;

  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin& BomRetriever::
  retrieveDummySegmentCabin (stdair::BomRoot& iBomRoot,
                             const bool isForFareFamilies) {

    SegmentCabin* oSegmentCabin_ptr = NULL;

    // Retrieve the Inventory
    const Inventory* lInventory_ptr = BomRetriever::
      retrieveInventoryFromKey (iBomRoot, DEFAULT_AIRLINE_CODE);

    if (lInventory_ptr == NULL) {
      std::ostringstream oStr;
      oStr << "The inventory corresponding to the '"
           << DEFAULT_AIRLINE_CODE << "' airline can not be found";
      throw ObjectNotFoundException (oStr.str());
    }

    // Retrieve the FlightDate
    FlightDate* lFlightDate_ptr = NULL;
    if (isForFareFamilies == true) {
      lFlightDate_ptr = BomRetriever::
        retrieveFlightDateFromKey (*lInventory_ptr, DEFAULT_FLIGHT_NUMBER_FF,
                                   DEFAULT_DEPARTURE_DATE);
      
      if (lFlightDate_ptr == NULL) {
        std::ostringstream oStr;
        oStr << "The flight-date corresponding to ("
             << DEFAULT_FLIGHT_NUMBER_FF << ", "
             << DEFAULT_DEPARTURE_DATE << ") can not be found";
        throw ObjectNotFoundException (oStr.str());
      }
    } else {
      lFlightDate_ptr = BomRetriever::
        retrieveFlightDateFromKey (*lInventory_ptr, DEFAULT_FLIGHT_NUMBER,
                                   DEFAULT_DEPARTURE_DATE);
      
      if (lFlightDate_ptr == NULL) {
        std::ostringstream oStr;
        oStr << "The flight-date corresponding to ("
             << DEFAULT_FLIGHT_NUMBER << ", "
             << DEFAULT_DEPARTURE_DATE << ") can not be found";
        throw ObjectNotFoundException (oStr.str());
      }
    }
    assert(lFlightDate_ptr != NULL);

    // Retrieve the SegmentDate
    const SegmentDateKey lSegmentDateKey (DEFAULT_ORIGIN, DEFAULT_DESTINATION);
    const SegmentDate* lSegmentDate_ptr =
      lFlightDate_ptr->getSegmentDate (lSegmentDateKey);

    if (lSegmentDate_ptr == NULL) {
      std::ostringstream oStr;
      oStr << "The segment-date corresponding to the '"
           << DEFAULT_ORIGIN << "' origin and '"
           << DEFAULT_DESTINATION << "' destination can not be found";
      throw ObjectNotFoundException (oStr.str());
    }
    
    // Retrieve the SegmentCabin
    const SegmentCabinKey lSegmentCabinKey (DEFAULT_CABIN_CODE);
    oSegmentCabin_ptr =
      BomManager::getObjectPtr<SegmentCabin> (*lSegmentDate_ptr, lSegmentCabinKey.toString());

    if (oSegmentCabin_ptr == NULL) {
      std::ostringstream oStr;
      oStr << "The segment-cabin corresponding to the '"
           << DEFAULT_CABIN_CODE << "' cabin code can not be found";
      throw ObjectNotFoundException (oStr.str());
    }

    assert (oSegmentCabin_ptr != NULL);
    return *oSegmentCabin_ptr;
  } 

  // ////////////////////////////////////////////////////////////////////
  std::string BomRetriever::
  retrieveFullKeyFromSegmentDate (const SegmentDate& iSegmentdate) { 

    std::ostringstream lFullKeyStr;
 
    // Get the parent flight date
    FlightDate* lFlightDate_ptr = 
      BomManager::getParentPtr<FlightDate>(iSegmentdate);
    if (lFlightDate_ptr == NULL) { 
      return lFullKeyStr.str();
    }
    assert (lFlightDate_ptr != NULL);

    // Get the parent inventory
    Inventory* lInventory_ptr = 
      BomManager::getParentPtr<Inventory> (*lFlightDate_ptr);  
    if (lInventory_ptr == NULL) { 
      return lFullKeyStr.str();
    }
    assert (lInventory_ptr != NULL);
    
    lFullKeyStr << lInventory_ptr->describeKey() 
		<< DEFAULT_KEY_SUB_FLD_DELIMITER;	
    lFullKeyStr << lFlightDate_ptr->describeKey() 
		<< DEFAULT_KEY_SUB_FLD_DELIMITER;
    lFullKeyStr << iSegmentdate.describeKey();
	
    return lFullKeyStr.str();

  }

}
