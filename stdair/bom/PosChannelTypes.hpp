// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_POSCHANNELTYPES_HPP
#define __STDAIR_BOM_POSCHANNELTYPES_HPP

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
  class PosChannel;
  
  /** Define the fare-position list. */
  typedef std::list<PosChannel*> PosChannelList_T;

  /** Define the fare-position map. */
  typedef std::map<const MapKey_T, PosChannel*> PosChannelMap_T;

  /** Define the list of pair<MapKey_T, FarePosition>. */
  typedef std::pair<MapKey_T, PosChannel*> PosChannelWithKey_T;
  typedef std::list<PosChannelWithKey_T> PosChannelDetailedList_T;
}
#endif // __STDAIR_BOM_POSCHANNELTYPES_HPP
