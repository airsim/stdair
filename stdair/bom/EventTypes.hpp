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
// Boost Progress
#include <boost/progress.hpp>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations
  struct EventStruct;
  
  /** Define an element of a event list */
  typedef std::pair<const LongDuration_T, EventStruct> EventListElement_T;
  
  /** Define a list of events */
  typedef std::map<const LongDuration_T, EventStruct> EventList_T;

  /**
     Define a pair of counters associated to a given demand stream:
     <ul>
     <li>one for the current number of events already generated,</li>
     <li>one for the total number of events to be generated</li>
     </ul>
  */
  typedef std::pair<stdair::Count_T, stdair::Count_T> NbOfEventsPair_T;

  /** Define a map allowing tracking the progress status for each
      demand stream. */
  typedef std::map<const stdair::DemandStreamKeyStr_T,
                   NbOfEventsPair_T> NbOfEventsByDemandStreamMap_T;

  /** */
  typedef boost::shared_ptr<boost::progress_display> ProgressDisplayPtr;
  
  /** Define a map holding the progress display object for each demand
      stream. */
  typedef std::map<const stdair::DemandStreamKeyStr_T,
                   ProgressDisplayPtr> ProgressDisplayMap_T;
  
}
#endif // __STDAIR_BOM_EVENTTYPES_HPP

