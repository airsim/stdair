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
  
  /** Define the fare-point_of_sale list. */
  typedef std::list<PosChannel*> PosChannelList_T;

  /** Define the fare-point_of_sale map. */
  typedef std::map<const MapKey_T, PosChannel*> PosChannelMap_T;

  /** Define the list of pair<MapKey_T, PosChannel>. */
  typedef std::pair<MapKey_T, PosChannel*> PosChannelWithKey_T;
  typedef std::list<PosChannelWithKey_T> PosChannelDetailedList_T;
}
#endif // __STDAIR_BOM_POSCHANNELTYPES_HPP
