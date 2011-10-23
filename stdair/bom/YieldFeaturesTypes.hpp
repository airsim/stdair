// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_YIELDFEATURESTYPES_HPP
#define __STDAIR_BOM_YIELDFEATURESTYPES_HPP

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
  class YieldFeatures;
  
  /** Define the date-period list. */
  typedef std::list<YieldFeatures*> YieldFeaturesList_T;

  /** Define the date-period  map. */
  typedef std::map<const MapKey_T, YieldFeatures*> YieldFeaturesMap_T;

  /** Define the list of pair<MapKey_T, YieldFeatures>. */
  typedef std::pair<MapKey_T, YieldFeatures*> YieldFeaturesWithKey_T;
  typedef std::list<YieldFeaturesWithKey_T> YieldFeaturesDetailedList_T;
}
#endif // __STDAIR_BOM_YIELDFEATURESTYPES_HPP

