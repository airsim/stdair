#ifndef __STDAIR_BAS_BASCONST_REQUEST_HPP
#define __STDAIR_BAS_BASCONST_REQUEST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/stdair_date_time_types.hpp>

namespace stdair {

  /** Default party size in a request (e.g., 1). */
  extern const PartySize_T DEFAULT_PARTY_SIZE;
  
  /** Default duration for a stay (e.g., 7 days). */
  extern const DayDuration_T DEFAULT_STAY_DURATION;

  /** Default Willingness-to-Pay (WTP, as expressed as a monetary unit). */
  extern const WTP_T DEFAULT_WTP;

  /** Default Point-Of-Sale (POS, e.g., "ROW"). */
  extern const AirportCode_T DEFAULT_POS;
    
  /** Default departure date (e.g., 01-Jan-2011). */
  extern const Date_T DEFAULT_PREFERRED_DEPARTURE_DATE;

  /** Default preferred departure time (e.g., 08:00). */
  extern const Duration_T DEFAULT_PREFERRED_DEPARTURE_TIME;
    
  /** Default advance purchase (e.g., 22 days). */
  extern const DateOffset_T DEFAULT_ADVANCE_PURCHASE;

  /** Default request date (e.g., 10-Jan-2011). */
  extern const Date_T DEFAULT_REQUEST_DATE;

  /** Default preferred departure time (e.g., 08:00). */
  extern const Duration_T DEFAULT_REQUEST_TIME;
    
  /** Default request date-time (e.g., 08:00). */
  extern const DateTime_T DEFAULT_REQUEST_DATE_TIME;

  /** Default preferred cabin (e.g., 'M'). */
  extern const CabinCode_T DEFAULT_PREFERRED_CABIN;

  /** Default channel (e.g., direct on-line). */
  extern const ChannelLabel_T DEFAULT_CHANNEL;

  /** Default trip type (e.g., one-way). */
  extern const TripType_T DEFAULT_TRIP_TYPE;

  /** Default frequent flyer tier (e.g., non member). */
  extern const FrequentFlyer_T DEFAULT_FF_TIER;

  /** Default value of time (expressed as a monetary unit per hour). */
  extern const PriceValue_T DEFAULT_VALUE_OF_TIME;

}
#endif // __STDAIR_BAS_BASCONST_REQUEST_HPP
