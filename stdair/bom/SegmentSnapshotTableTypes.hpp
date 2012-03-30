// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SEGMENTSNAPSHOTTABLETYPES_HPP
#define __STDAIR_BOM_SEGMENTSNAPSHOTTABLETYPES_HPP

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
  class SegmentSnapshotTable;
  class SegmentCabin;

  // //////////////////////// Type definitions /////////////////////////
  /** Define the guillotine-block list. */
  typedef std::list<SegmentSnapshotTable*> SegmentSnapshotTableList_T;

  /** Define the guillotine-block map. */
  typedef std::map<const MapKey_T, SegmentSnapshotTable*> SegmentSnapshotTableMap_T;

  /** Define the map between the segment-cabins and the segment data ID. */
  typedef std::map<const SegmentCabin*, SegmentDataID_T> SegmentCabinIndexMap_T;

  /** Define the map between the class and their index. */
  typedef std::map<const MapKey_T, ClassIndex_T> ClassIndexMap_T;

}
#endif // __STDAIR_BOM_SEGMENTSNAPSHOTTABLETYPES_HPP

