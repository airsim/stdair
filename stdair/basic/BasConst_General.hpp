#ifndef __STDAIR_BAS_BASCONST_GENERAL_HPP
#define __STDAIR_BAS_BASCONST_GENERAL_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_types.hpp>

namespace stdair {

  /** Default value for the BOM tree root key (" -- ROOT -- "). */
  extern const std::string DEFAULT_BOM_ROOT_KEY;

  /** Default epsilon value (1e-4). */
  extern const double DEFAULT_EPSILON_VALUE;

  /** Default cabin capacity for Leg cabins. */
  extern const CabinCapacity_T DEFAULT_CABIN_CAPACITY;

  /** Default number of generated flight dates (0). */
  extern const NbOfFlightDates_T DEFAULT_NB_OF_FLIGHTDATES;

  /** Default number of bookings for BookingClass. */
  extern const NbOfBookings_T DEFAULT_CLASS_NB_OF_BOOKINGS;

  /** Default distance value (kilometers). */
  extern const Distance_T DEFAULT_DISTANCE_VALUE;

  /** Default flight speed (number of kilometers per hour). */
  extern const unsigned int DEFAULT_FLIGHT_SPEED;

  /** Default value of Fare. */
  extern const Fare_T DEFAULT_FARE_VALUE;

  /** Default currency (euro). */
  extern const PriceCurrency_T DEFAULT_CURRENCY;

  /** Default revenue value. */
  extern const Revenue_T DEFAULT_REVENUE_VALUE;

  /** Default booking rate for OnD bookings over overall class bookings. */
  extern const BookingRatio_T DEFAULT_OND_BOOKING_RATE;

  /** Number of seconds in one day (86400). */
  extern const Count_T SECONDS_IN_ONE_DAY;
  
  /** Number of milliseconds in one second (1000). */
  extern const Count_T MILLISECONDS_IN_ONE_SECOND;

  /** Default date for the General (1-Jan-2010). */
  extern const Date_T DEFAULT_DATE;
  
  /** Default date-time (1-Jan-2010). */
  extern const DateTime_T DEFAULT_DATETIME;

  /** Default epsilon duration (1 nanosecond). */
  extern const Duration_T DEFAULT_EPSILON_DURATION;

  /** Default random seed (120765987). */
  extern const RandomSeed_T DEFAULT_RANDOM_SEED;
    
  /** Null time duration (in boost::time_duration unit).*/
  extern const Duration_T NULL_BOOST_TIME_DURATION;
    
  /** Default value of Availability. */
  extern const Fare_T DEFAULT_CLASS_FARE_VALUE;

  /** Default number of airlines (0). */
  extern const NbOfAirlines_T DEFAULT_NBOFAIRLINES;
  
  /** Default number of days in a year (365). */
  extern const unsigned int DEFAULT_NB_OF_DAYS_IN_A_YEAR;
  
  /** Default number of bookings (0). */
  extern const NbOfBookings_T DEFAULT_CLASS_NB_OF_BOOKINGS;

  /** Default channel. */
  extern const ChannelLabel_T DEFAULT_CHANNEL;
}
#endif // __STDAIR_BAS_BASCONST_GENERAL_HPP
