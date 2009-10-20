// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_LEGCABINTYPES_HPP
#define __STDAIR_BOM_LEGCABINTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename BOM_CONTENT> class LegCabinStructure;
  class LegCabin;
  
  /** Define the LegCabin structure. */
  typedef LegCabinStructure<LegCabin> LegCabinStructure_T;
  
  /** Define the leg-cabin structure list. */
  typedef std::vector<LegCabinStructure_T*> LegCabinStructureList_T;

  /** Define the leg-cabin structure map. */
  typedef std::map<const std::string, LegCabinStructure_T*> LegCabinStructureMap_T;

}
#endif // __STDAIR_BOM_LEGCABINTYPES_HPP

