// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_POLICYTYPES_HPP
#define __STDAIR_BOM_POLICYTYPES_HPP

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
  class Policy;

  /** Define the fare family list. */
  typedef std::list<Policy*> PolicyList_T;

  /** Define the fare family map. */
  typedef std::map<const MapKey_T, Policy*> PolicyMap_T;
  
}
#endif // __STDAIR_BOM_POLICYTYPES_HPP
