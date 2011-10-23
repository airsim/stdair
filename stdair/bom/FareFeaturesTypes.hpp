// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_FAREFEATURESTYPES_HPP
#define __STDAIR_BOM_FAREFEATURESTYPES_HPP

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
  class FareFeatures;
  
  /** Define the date-period list. */
  typedef std::list<FareFeatures*> FareFeaturesList_T;

  /** Define the date-period  map. */
  typedef std::map<const MapKey_T, FareFeatures*> FareFeaturesMap_T;

  /** Define the list of pair<MapKey_T, FareFeatures>. */
  typedef std::pair<MapKey_T, FareFeatures*> FareFeaturesWithKey_T;
  typedef std::list<FareFeaturesWithKey_T> FareFeaturesDetailedList_T;
}
#endif // __STDAIR_BOM_FAREFEATURESTYPES_HPP

