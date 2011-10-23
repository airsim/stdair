// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_DATEPERIODTYPES_HPP
#define __STDAIR_BOM_DATEPERIODTYPES_HPP

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
  class DatePeriod;
  
  /** Define the date-period list. */
  typedef std::list<DatePeriod*> DatePeriodList_T;

  /** Define the date-period  map. */
  typedef std::map<const MapKey_T, DatePeriod*> DatePeriodMap_T;

  /** Define the list of pair<MapKey_T, DatePeriod>. */
  typedef std::pair<MapKey_T, DatePeriod*> DatePeriodWithKey_T;
  typedef std::list<DatePeriodWithKey_T> DatePeriodDetailedList_T;
}
#endif // __STDAIR_BOM_DATEPERIODTYPES_HPP

