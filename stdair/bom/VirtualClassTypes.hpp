// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_VIRTUALCLASSTYPES_HPP
#define __STDAIR_BOM_VIRTUALCLASSTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
#include <map>
// STDAIR
#include <stdair/stdair_basic_types.hpp>

namespace stdair {

  // Forward declarations.
  struct VirtualClassStruct;
  
  /** Define the booking class list. */
  typedef std::list<VirtualClassStruct> VirtualClassList_T;
  
  /** Define the booking class map. */
  typedef std::map<const YieldLevel_T, VirtualClassStruct> VirtualClassMap_T;
}
#endif // __STDAIR_BOM_VIRTUALCLASSTYPES_HPP

