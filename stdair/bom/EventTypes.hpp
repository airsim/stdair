// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_EVENTTYPES_HPP
#define __STDAIR_BOM_EVENTTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// Boost Smart Pointers
#include <boost/shared_ptr.hpp>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/basic/ProgressStatus.hpp>
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations
  struct EventStruct;
  
  /** Define an element of a event list */
  typedef std::pair<const LongDuration_T, EventStruct> EventListElement_T;
  
  /** Define a list of events */
  typedef std::map<const LongDuration_T, EventStruct> EventList_T;

  /** Define a map allowing tracking the progress status for each
      demand stream. */
  typedef std::map<const DemandStreamKeyStr_T,
                   ProgressStatus> NbOfEventsByDemandStreamMap_T;
  
}
#endif // __STDAIR_BOM_EVENTTYPES_HPP

