// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_NESTINGTYPES_HPP
#define __STDAIR_BOM_NESTINGTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
//StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {

  /** Define the nesting node. */
  typedef std::pair<const Yield_T, BookingClassList_T> NestingNode_T;

  /** Define the nesting node map*/
  typedef std::map<const Yield_T, BookingClassList_T> NestingNodeMap_T;
     
}
#endif // __STDAIR_BOM_NESTINGTYPES_HPP

