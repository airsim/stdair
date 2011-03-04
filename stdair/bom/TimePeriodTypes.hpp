// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_TIMEPERIODTYPES_HPP
#define __STDAIR_BOM_TIMEPERIODTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// STDAIR
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class TimePeriod;
  
  /** Define the time-period list. */
  typedef std::list<TimePeriod*> TimePeriodList_T;

  /** Define the time-period  map. */
  typedef std::map<const MapKey_T, TimePeriod*> TimePeriodMap_T;

  /** Define the list of pair<MapKey_T, TimePeriod>. */
  typedef std::pair<MapKey_T, TimePeriod*> TimePeriodWithKey_T;
  typedef std::list<TimePeriodWithKey_T> TimePeriodDetailedList_T;
}
#endif // __STDAIR_BOM_TIMEPERIODTYPES_HPP

