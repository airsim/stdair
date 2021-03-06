#ifndef __STDAIR_BAS_BASCONST_INVENTORY_HPP
#define __STDAIR_BAS_BASCONST_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/basic/ForecastingMethod.hpp>
#include <stdair/basic/UnconstrainingMethod.hpp>
#include <stdair/basic/PreOptimisationMethod.hpp>
#include <stdair/basic/OptimisationMethod.hpp>
#include <stdair/basic/PartnershipTechnique.hpp>

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

  /** Default flight number for fare families (255). */
  extern const FlightNumber_T DEFAULT_FLIGHT_NUMBER_FF;

  /** Default data table ID (9999). */
  extern const TableID_T DEFAULT_TABLE_ID;
  
  /** Default flight departure date (01/01/1900). */
  extern const Date_T DEFAULT_DEPARTURE_DATE;
  
  /** Default airport code value ("XXX"). */
  extern const AirportCode_T DEFAULT_AIRPORT_CODE;

  /** Default airport code value ("").. */
  extern const AirportCode_T DEFAULT_NULL_AIRPORT_CODE;
  
  /** Default Origin ("XXX"). */
  extern const AirportCode_T DEFAULT_ORIGIN;
  
  /** Default Destination ("XXX"). */
  extern const AirportCode_T DEFAULT_DESTINATION;
  
  /** Default Cabin Code ("X"). */
  extern const CabinCode_T DEFAULT_CABIN_CODE;

  /** Default Fare Family Code ("EcoSaver"). */
  extern const FamilyCode_T DEFAULT_FARE_FAMILY_CODE;

  /** Default null fare family Code ("NoFF"). */
  extern const FamilyCode_T DEFAULT_NULL_FARE_FAMILY_CODE;

  /** Default Policy Code ("0"). */
  extern const PolicyCode_T DEFAULT_POLICY_CODE;

  /** Default Nesting Structure Code ("DEFAULT"). */
  extern const NestingStructureCode_T DEFAULT_NESTING_STRUCTURE_CODE;

  /** Display Nesting Structure Code ("Display Nesting"). */
  extern const NestingStructureCode_T DISPLAY_NESTING_STRUCTURE_CODE;

  /** Display Nesting Structure Code ("Yield-Based Nesting"). */
  extern const NestingStructureCode_T YIELD_BASED_NESTING_STRUCTURE_CODE;

  /** Default Nesting Node Code ("0"). */
  extern const NestingNodeCode_T DEFAULT_NESTING_NODE_CODE;

  /** Default class code value ("X"). */
  extern const ClassCode_T DEFAULT_CLASS_CODE;

  /** Default null class code value (""). */
  extern const ClassCode_T DEFAULT_NULL_CLASS_CODE;

  /** Default class code list value (empty vector). */
  extern const ClassList_StringList_T DEFAULT_CLASS_CODE_LIST;

  /** Default Bid-Price (0.0). */
  extern const BidPrice_T DEFAULT_BID_PRICE;

  /** Default Bid-Price Vector (empty vector). */
  extern const BidPriceVector_T DEFAULT_BID_PRICE_VECTOR;

  /** Maximal number of legs linked to a single flight-date (e.g., 7).
      <br>Note that the number of derived segments is n*(n+1)/2 if n
      is the number of legs. */
  extern const unsigned short MAXIMAL_NUMBER_OF_LEGS_IN_FLIGHT;
  
  /** Maximal number of segments linked to a single O&D
      (Origin & Destination)(e.g., 3). */
  extern const unsigned short MAXIMAL_NUMBER_OF_SEGMENTS_IN_OND;

  /** Maximal offered capacity in a cabin. */
  extern const Availability_T MAXIMAL_AVAILABILITY;

  /** Default seat index (for a bucket and/or Bid-Price Vector slot)(e.g., 1). */
  extern const SeatIndex_T DEFAULT_SEAT_INDEX;

  /** Default number of bookings. */
  extern const NbOfSeats_T DEFAULT_NULL_BOOKING_NUMBER;

  /** Default capacity adjustment of the cabin. */
  extern const CapacityAdjustment_T DEFAULT_NULL_CAPACITY_ADJUSTMENT;
  
  /** Default unsold Protection (UPR). */
  extern const UPR_T DEFAULT_NULL_UPR;

  /** Default value type (within a guillotine block) for fare family. */
  extern const std::string DEFAULT_FARE_FAMILY_VALUE_TYPE;

  /** Default value type (within a guillotine block) for segment-cabin. */
  extern const std::string DEFAULT_SEGMENT_CABIN_VALUE_TYPE;

  /** Default value for max day-to-departure (365). */
  extern const int DEFAULT_MAX_DTD;

  /** Defaut data collection point list. */
  extern const DCPList_T DEFAULT_DCP_LIST;
  struct DefaultDCPList { static DCPList_T init(); };

  /** Default frat5 coef map. */
  extern const DTDFratMap_T DEFAULT_DTD_FRAT5COEF_MAP;
  struct DefaultDtdFratMap { static DTDFratMap_T init();};

  /** Default arrival pattern map. */
  extern const DTDProbMap_T DEFAULT_DTD_PROB_MAP;
  struct DefaultDtdProbMap { static DTDProbMap_T init();};

  /** Default Forecasting Method (Q Forecasting). */
  extern const ForecastingMethod DEFAULT_FORECASTING_METHOD;

  /** Default Unconstraining Method (By Time Frame). */
  extern const UnconstrainingMethod DEFAULT_UNCONSTRAINING_METHOD; 

  /** Default Pre-Optimisation Method (NONE). */
  extern const PreOptimisationMethod DEFAULT_PREOPTIMISATION_METHOD;

  /** Default Optimisation Method (Leg Based EMSRb). */
  extern const OptimisationMethod DEFAULT_OPTIMISATION_METHOD;

  /** Default Partnership Technique (None). */
  extern const PartnershipTechnique DEFAULT_PARTNERSHIP_TECHNIQUE;

}
#endif // __STDAIR_BAS_BASCONST_INVENTORY_HPP
