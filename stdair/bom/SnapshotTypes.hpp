// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SNAPSHOTTYPES_HPP
#define __STDAIR_BOM_SNAPSHOTTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>

namespace stdair {

  // Forward declarations
  struct SnapshotStruct;
  
  // ///////////// Type definitions //////////////
  /** Define the smart pointer to a snapshot . */
  typedef boost::shared_ptr<SnapshotStruct> SnapshotPtr_T;
  
}
#endif // __STDAIR_BOM_SNAPSHOTTYPES_HPP

