// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Yield.hpp>
#include <stdair/bom/BookingClassContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClassContent::BookingClassContent (const Key_T& iKey) : _key (iKey) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassContent::~BookingClassContent () {
  }
  
}
