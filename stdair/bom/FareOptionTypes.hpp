// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_FAREOPTIONTYPES_HPP
#define __STDAIR_BOM_FAREOPTIONTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
#include <map>
// STDAIR
#include <stdair/stdair_types.hpp>
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  struct FareOptionStruct;
  
  /** Define the booking class list. */
  typedef std::list<FareOptionStruct> FareOptionList_T;

}
#endif // __STDAIR_BOM_FAREOPTIONTYPES_HPP

