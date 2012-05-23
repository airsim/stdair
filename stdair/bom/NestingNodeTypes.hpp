// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_NESTINGNODETYPES_HPP
#define __STDAIR_BOM_NESTINGNODETYPES_HPP

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
  class NestingNode;

  /** Define the fare family list. */
  typedef std::list<NestingNode*> NestingNodeList_T;

  /** Define the fare family map. */
  typedef std::map<const MapKey_T, NestingNode*> NestingNodeMap_T;
  
}
#endif // __STDAIR_BOM_NESTINGNODETYPES_HPP
