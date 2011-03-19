#ifndef __STDAIR_BAS_BASCONST_INVENTORY_HPP
#define __STDAIR_BAS_BASCONST_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_date_time_types.hpp>

namespace stdair {

  // //////// Inventory-related BOM ///////
  /** Default airline code value ("XX"). */
  extern const AirlineCode_T DEFAULT_AIRLINE_CODE;

  /** Default airline code value (""). */
  extern const AirlineCode_T DEFAULT_NULL_AIRLINE_CODE;
  
  /** Default airline code list value (empty vector). */
  extern const AirlineCodeList_T DEFAULT_AIRLINE_CODE_LIST;

  /** Default flight number (9999). */
  extern const FlightNumber_T DEFAULT_FLIGHT_NUMBER;
  
  /** Default flight departure date (01/01/1900). */
  extern const Date_T DEFAULT_DEPARTURE_DATE;
  
  /** Default airport code value ("XXX"). */
  extern const AirportCode_T DEFAULT_AIRPORT_CODE;

  /** Default airport code value ("").. */
  extern const AirportCode_T DEFAULT_NULL_AIRPORT_CODE;
  
  /** Default Origin. */
  extern const AirportCode_T DEFAULT_ORIGIN;
  
  /** Default Destination. */
  extern const AirportCode_T DEFAULT_DESTINATION;
  
  /** Default Cabin Code. */
  extern const CabinCode_T DEFAULT_CABIN_CODE;

  /** Default Fare Family Code. */
  extern const FamilyCode_T DEFAULT_FARE_FAMILY_CODE;

  /** Default class code value ("X"). */
  extern const ClassCode_T DEFAULT_CLASS_CODE;

  /** Default null class code value (""). */
  extern const ClassCode_T DEFAULT_NULL_CLASS_CODE;

  /** Default class code list value (empty vector). */
  extern const ClassList_StringList_T DEFAULT_CLASS_CODE_LIST;

  /** Default Bid-Price. */
  extern const BidPrice_T DEFAULT_BID_PRICE;

  /** Default Bid-Price Vector. */
  extern const BidPriceVector_T DEFAULT_BID_PRICE_VECTOR;

  /** Maximal number of legs linked to a single flight-date.
      <br>Note that the number of derived segments is n*(n+1)/2 if n
      is the number of legs. */
  extern const unsigned short MAXIMAL_NUMBER_OF_LEGS_IN_FLIGHT;
  
  /** Maximal number of segments linked to a single O&D
      (Origin & Destination). */
  extern const unsigned short MAXIMAL_NUMBER_OF_SEGMENTS_IN_OND;

  /** Maximal offered capacity in a cabin. */
  extern const Availability_T MAXIMAL_AVAILABILITY;

  /** Default seat index (for a bucket and/or Bid-Price Vector slot). */
  extern const SeatIndex_T DEFAULT_SEAT_INDEX;

}
#endif // __STDAIR_BAS_BASCONST_INVENTORY_HPP
