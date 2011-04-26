// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_GUILLOTINEBLOCKTYPES_HPP
#define __STDAIR_BOM_GUILLOTINEBLOCKTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// BOOST
#include <boost/multi_array.hpp>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations
  class GuillotineBlock;
  class SegmentCabin;

  // //////////////////////// Type definitions /////////////////////////
  /** Define the guillotine-block list. */
  typedef std::list<GuillotineBlock*> GuillotineBlockList_T;

  /** Define the guillotine-block map. */
  typedef std::map<const MapKey_T, GuillotineBlock*> GuillotineBlockMap_T;

  /** Define the map between the segment-cabins and the block number. */
  typedef std::map<const SegmentCabin*, BlockNumber_T> SegmentCabinIndexMap_T;

  /** Define the map between the value type of the snapshots and their index. */
  typedef std::map<const MapKey_T, BlockIndex_T> ValueTypeIndexMap_T;

}
#endif // __STDAIR_BOM_GUILLOTINEBLOCKTYPES_HPP

