// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BOOKINGREQUESTTYPES_HPP
#define __STDAIR_BOM_BOOKINGREQUESTTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost
#include <boost/shared_ptr.hpp>

namespace stdair {

  // Forward declarations
  struct BookingRequestStruct;
  
  // ///////////// Type definitions //////////////
  /** Define the smart pointer to a booking request. */
  typedef boost::shared_ptr<BookingRequestStruct> BookingRequestPtr_T;
  
  /** Define the hash key for the demand generator. */
  typedef std::string DemandGeneratorKey_T;

  
}
#endif // __STDAIR_BOM_BOOKINGREQUESTTYPES_HPP

