// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_AIRLINECLASSLISTTYPES_HPP
#define __STDAIR_BOM_AIRLINECLASSLISTTYPES_HPP

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
  class AirlineClassList;
  
  /** Define the segment-features list. */
  typedef std::list<AirlineClassList*> AirlineClassListList_T;

  /** Define the segment-features map. */
  typedef std::map<const MapKey_T, AirlineClassList*> AirlineClassListMap_T;

  /** Define the list of pair<MapKey_T, AirlineCodeList>. */
  typedef std::pair<MapKey_T, AirlineClassList*> AirlineClassListWithKey_T;
  typedef std::list<AirlineClassListWithKey_T> AirlineClassListDetailedList_T;
}
#endif // __STDAIR_BOM_AIRLINECLASSLISTTYPES_HPP
