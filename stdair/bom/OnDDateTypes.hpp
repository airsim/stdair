// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_ONDDATETYPES_HPP
#define __STDAIR_BOM_ONDDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// Stdair
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class OnDDate;

  /** Define the O&D date list. */
  typedef std::list<OnDDate*> OnDDateList_T;

  /** Define the OnD date map. */
  typedef std::map<const MapKey_T, OnDDate*> OnDDateMap_T;
  
}
#endif // __STDAIR_BOM_ONDDATETYPES_HPP
