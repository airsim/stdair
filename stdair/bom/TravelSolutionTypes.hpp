// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_TRAVELSOLUTIONTYPES_HPP
#define __STDAIR_BOM_TRAVELSOLUTIONTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
#include <map>
// STDAIR
#include <stdair/stdair_types.hpp>
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

  /** Define booking class - availability map. */
  typedef std::map<const ClassCode_T, Availability_T> ClassAvailabilityMap_T;

  /** Define list of booking class - availability maps. */
  typedef std::list<ClassAvailabilityMap_T> ClassAvailabilityMapHolder_T;

}
#endif // __STDAIR_BOM_TRAVELSOLUTIONTYPES_HPP

