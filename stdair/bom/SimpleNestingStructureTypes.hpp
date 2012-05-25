// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SIMPLENESTINGSTRUCTURETYPES_HPP
#define __STDAIR_BOM_SIMPLENESTINGSTRUCTURETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class SimpleNestingStructure;

  /** Define the fare family list. */
  typedef std::list<SimpleNestingStructure*> SimpleNestingStructureList_T;

  /** Define the fare family map. */
  typedef std::map<const MapKey_T, SimpleNestingStructure*> SimpleNestingStructureMap_T;
  
}
#endif // __STDAIR_BOM_SIMPLENESTINGSTRUCTURETYPES_HPP
