// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_TRAVELSOLUTIONTYPES_HPP
#define __STDAIR_BOM_TRAVELSOLUTIONTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
// STDAIR
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  struct TravelSolutionStruct;
  
  /** Define the booking class list. */
  typedef std::list<TravelSolutionStruct> TravelSolutionList_T;

  /** Define the segment path key. */
  typedef KeyList_T SegmentPath_T;

  /** Define the list of segment paths. */
  typedef std::list<SegmentPath_T> SegmentPathList_T;

}
#endif // __STDAIR_BOM_TRAVELSOLUTIONTYPES_HPP

