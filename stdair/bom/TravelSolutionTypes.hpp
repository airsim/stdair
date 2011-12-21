// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_TRAVELSOLUTIONTYPES_HPP
#define __STDAIR_BOM_TRAVELSOLUTIONTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
#include <map>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/bom/key_types.hpp>
#include <stdair/stdair_inventory_types.hpp> // bid price related types.
#include <stdair/bom/BomIDTypes.hpp>

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

  /** Define booking class - object ID map. */
  typedef std::map<const ClassCode_T, BookingClassID_T> ClassObjectIDMap_T;

  /** Define list of boking class - object ID maps.*/
  typedef std::list<ClassObjectIDMap_T> ClassObjectIDMapHolder_T;
  
  /** Define booking class - yield map. */
  typedef std::map<const ClassCode_T, YieldValue_T> ClassYieldMap_T;

  /** Define list of booking class - yield maps. */
  typedef std::list<ClassYieldMap_T> ClassYieldMapHolder_T;

  /** Define list of bid price vectors. */
  typedef std::list<BidPriceVector_T> BidPriceVectorHolder_T;

  /** Define booking class - bid price reference map. */
  typedef std::map<const ClassCode_T, const BidPriceVector_T*> ClassBpvMap_T;

  /** Define list of booking class - bid price reference maps. */
  typedef std::list<ClassBpvMap_T> ClassBpvMapHolder_T;
}
#endif // __STDAIR_BOM_TRAVELSOLUTIONTYPES_HPP

