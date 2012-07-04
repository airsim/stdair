// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_CONFIGHOLDERTYPES_HPP
#define __STDAIR_BOM_CONFIGHOLDERTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
// Boost
#include <boost/shared_ptr.hpp>

namespace stdair {

  // Forward declarations
  struct ConfigHolderStruct;
  
  // ///////////// Type definitions //////////////
  /** Define the smart pointer to a Config Holder structure. */
  typedef boost::shared_ptr<ConfigHolderStruct> ConfigHolderPtr_T;
  
}
#endif // __STDAIR_BOM_CONFIGHOLDERTYPES_HPP

