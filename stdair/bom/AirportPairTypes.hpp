// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_AIRPORTPAIRTYPES_HPP
#define __STDAIR_BOM_AIRPORTPAIRTYPES_HPP

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
  class AirportPair;
  
  /** Define the airport-pair list. */
  typedef std::list<AirportPair*> AirportPairList_T;

  /** Define the airport-pair map. */
  typedef std::map<const MapKey_T, AirportPair*> AirportPairMap_T;

  /** Define the list of pair<MapKey_T, AirportPair>. */
  typedef std::pair<MapKey_T, AirportPair*> AirportPairWithKey_T;
  typedef std::list<AirportPairWithKey_T> AirportPairDetailedList_T;
}
#endif // __STDAIR_BOM_AIRPORTPAIRTYPES_HPP

