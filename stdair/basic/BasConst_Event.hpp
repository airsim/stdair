#ifndef __STDAIR_BAS_BASCONST_EVENT_HPP
#define __STDAIR_BAS_BASCONST_EVENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/stdair_event_types.hpp>

namespace stdair {
  
  /** Default progress status. */
  extern const Count_T DEFAULT_PROGRESS_STATUS;
  
  /** Default reference (oldest) date for the events. No event can
      occur before that date. */
  extern const Date_T DEFAULT_EVENT_OLDEST_DATE;

  /** Default reference (oldest) date-time for the events. No event can
      occur before that date-time. */
  extern const DateTime_T DEFAULT_EVENT_OLDEST_DATETIME;  

  /** Maximum progress status. */
  extern const Percentage_T MAXIMUM_PROGRESS_STATUS;

}
#endif // __STDAIR_BAS_BASCONST_EVENT_HPP
