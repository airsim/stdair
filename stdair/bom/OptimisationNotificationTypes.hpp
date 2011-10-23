// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_OPTIMISATIONNOTIFICATIONTYPES_HPP
#define __STDAIR_BOM_OPTIMISATIONNOTIFICATIONTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>

namespace stdair {

  // Forward declarations
  struct OptimisationNotificationStruct;
  
  // ///////////// Type definitions //////////////
  /** Define the smart pointer to a optimisation notification. */
  typedef boost::
  shared_ptr<OptimisationNotificationStruct> OptimisationNotificationStructPtr_T;
  
}
#endif // __STDAIR_BOM_OPTIMISATIONNOTIFICATIONTYPES_HPP

