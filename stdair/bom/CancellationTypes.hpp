// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_CANCELLATIONTYPES_HPP
#define __STDAIR_BOM_CANCELLATIONTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>

namespace stdair {

  // Forward declarations
  struct CancellationStruct;
  
  // ///////////// Type definitions //////////////
  /** Define the smart pointer to a cancellation . */
  typedef boost::shared_ptr<CancellationStruct> CancellationPtr_T;
  
}
#endif // __STDAIR_BOM_CANCELLATIONTYPES_HPP

