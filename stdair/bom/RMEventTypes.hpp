// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_RMEVENTTYPES_HPP
#define __STDAIR_BOM_RMEVENTTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
// Boost
#include <boost/shared_ptr.hpp>

namespace stdair {

  // Forward declarations
  struct RMEventStruct;
  
  // ///////////// Type definitions //////////////
  /** Define the smart pointer to a RM event . */
  typedef boost::shared_ptr<RMEventStruct> RMEventPtr_T;

  /** Define the list of RM events. */
  typedef std::list<RMEventStruct> RMEventList_T;
  
}
#endif // __STDAIR_BOM_RMEVENTTYPES_HPP

