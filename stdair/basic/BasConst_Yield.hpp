#ifndef __STDAIR_BAS_BASCONST_YIELD_HPP
#define __STDAIR_BAS_BASCONST_YIELD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_types.hpp>

namespace stdair {

  // //////// Yield-related BOM ///////
  /** Default yield value. */
  extern const Yield_T DEFAULT_YIELD_VALUE;
  
  /** Default yield max value. */
  extern const Yield_T DEFAULT_YIELD_MAX_VALUE;

  /** Default yield value for a virtual class. */
  extern const Yield_T DEFAULT_CLASS_YIELD_VALUE;
  
  /** Default number of bookings for YieldRangeStruct_T. */
  extern const NbOfBookings_T DEFAULT_YIELD_NB_OF_BOOKINGS;

  /** Default booking number. */
  extern const Identity_T DEFAULT_BOOKING_NUMBER;

  /** Default cancellation number for YieldRangeStruct_T. */
  extern const NbOfCancellations_T DEFAULT_YIELD_NB_OF_CANCELLATIONS;

  /** Default no-shows number for YieldRangeStruct_T. */
  extern const NbOfNoShows_T DEFAULT_YIELD_NB_OF_NOSHOWS;

  /** Default availability for YieldRangeStruct_T. */
  extern const Availability_T DEFAULT_YIELD_AVAILABILITY;

  /** Default boolean for booking limit availability for
      YieldRangeStruct_T. */
  extern const CensorshipFlag_T DEFAULT_YIELD_CENSORSHIPFLAG;
  
  /** Default booking limit value for YieldRangeStruct_T. */
  extern const BookingLimit_T DEFAULT_YIELD_BOOKING_LIMIT;
  
  /** Default over-booking rate for YieldRangeStruct_T. */
  extern const OverbookingRate_T DEFAULT_YIELD_OVERBOOKING_RATE;

}
#endif // __STDAIR_BAS_BASCONST_YIELD_HPP
