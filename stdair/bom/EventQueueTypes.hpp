// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_EVENTQUEUETYPES_HPP
#define __STDAIR_BOM_EVENTQUEUETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// Stdair
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class EventQueue;

  /** Define the EventQueue list. */
  typedef std::list<EventQueue*> EventQueueList_T;

  /** Define the EventQueue map. */
  typedef std::map<const MapKey_T, EventQueue*> EventQueueMap_T;
  
}
#endif // __STDAIR_BOM_EVENTQUEUETYPES_HPP
