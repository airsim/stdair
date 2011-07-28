#ifndef __STDAIR_BAS_BASCONST_DEFAULTOBJECT_HPP
#define __STDAIR_BAS_BASCONST_DEFAULTOBJECT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_types.hpp>

namespace stdair {

  // //////// Fare and Yield related BOM Tree///////
  /** London Heathrow airport (e.g., "LHR"). */
  extern const AirportCode_T AIRPORT_LHR;

  /** Sydney airport (e.g., "SYD"). */
  extern const AirportCode_T AIRPORT_SYD;

  /** London city code (e.g., "LHR"). */
  extern const CityCode_T POS_LHR;

  /** Advance purchase 0 day. */ 
  extern const DayDuration_T NO_ADVANCE_PURCHASE;
  
  /** Default saturdayStay value (true). */
  extern const SaturdayStay_T SATURDAY_STAY;

  /** Default saturdayStay value (false). */
  extern const SaturdayStay_T NO_SATURDAY_STAY;
  
  /** Default change fees value (true). */
  extern const ChangeFees_T CHANGE_FEES;
  
  /** Default change fees value (false). */
  extern const ChangeFees_T NO_CHANGE_FEES;
  
  /** Default non refundable value (true). */
  extern const NonRefundable_T NON_REFUNDABLE;

  /** Default refundable value (false). */
  extern const NonRefundable_T NO_NON_REFUNDABLE;

  /** Stay duration 0 day. */
  extern const DayDuration_T NO_STAY_DURATION;

  /** Cabin 'Y'. */
  extern const CabinCode_T CABIN_Y;

  /** Airline code "BA". */
  extern const AirlineCode_T AIRLINE_CODE_BA;

  /** Class code 'Y'. */
  extern const ClassCode_T CLASS_CODE_Y;

  // //////// Travel Solution related objects///////
  /** Class code 'Q'. */
  extern const ClassCode_T CLASS_CODE_Q;

  // //////// Booking request related objects///////
  /** Singapour airport (e.g., "SIN"). */
  extern const AirportCode_T AIRPORT_SIN;

  /** Bangkok airport (e.g., "BKK"). */
  extern const AirportCode_T AIRPORT_BKK;

  /** Singapour city code (e.g., "SIN"). */
  extern const CityCode_T POS_SIN;

  /** Economic cabin (e.g., "Eco"). */
  extern const CabinCode_T CABIN_ECO;

  /** Frequent flyer tier (e.g., "M" meaning member). */
  extern const FrequentFlyer_T FREQUENT_FLYER_MEMBER;
  
}
#endif // __STDAIR_BAS_BASCONST_DEFAULTOBJECT_HPP
