// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/YieldStoreKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  YieldStoreKey_T::YieldStoreKey_T (const AirlineCode_T& iAirlineCode)
    : _airlineCode (iAirlineCode) {
  }
  // ////////////////////////////////////////////////////////////////////
  YieldStoreKey_T::YieldStoreKey_T (const YieldStoreKey_T& iKey)
    : _airlineCode (iKey._airlineCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldStoreKey_T::~YieldStoreKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldStoreKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "YieldStoreKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldStoreKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string YieldStoreKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _airlineCode;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string YieldStoreKey_T::describe() const {
    return toString();
  }

}
