// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BREAKPOINTTYPES_HPP
#define __STDAIR_BOM_BREAKPOINTTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
// Boost
#include <boost/shared_ptr.hpp>

namespace stdair {

  // Forward declarations
  struct BreakPointStruct;
  
  // ///////////// Type definitions //////////////
  /** Define the smart pointer to a Break Point event . */
  typedef boost::shared_ptr<BreakPointStruct> BreakPointPtr_T;

  /** Define the list of Break Points. */
  typedef std::list<BreakPointStruct> BreakPointList_T;
  
}
#endif // __STDAIR_BOM_BREAKPOINTTYPES_HPP

