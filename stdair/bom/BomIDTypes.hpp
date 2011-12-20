// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BOMIDTYPES_HPP
#define __STDAIR_BOM_BOMIDTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>
#include <stdair/bom/BomID.hpp>

namespace stdair {

  // Forward declarations.
  class BookingClass;

  /** Define the booking class ID. */
  typedef struct BomID<BookingClass> BookingClassID_T;

  /** Define the list of booking class ID's. */
  typedef std::list<BookingClassID_T> BookingClassIDList_T;
}
#endif // __STDAIR_BOM_BOMIDTYPES_HPP

