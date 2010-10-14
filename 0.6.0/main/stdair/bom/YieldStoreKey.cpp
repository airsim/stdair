// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/YieldStoreKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  YieldStoreKey::YieldStoreKey (const AirlineCode_T& iAirlineCode)
    : _airlineCode (iAirlineCode) {
  }
  // ////////////////////////////////////////////////////////////////////
  YieldStoreKey::YieldStoreKey (const YieldStoreKey& iKey)
    : _airlineCode (iKey._airlineCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldStoreKey::~YieldStoreKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldStoreKey::toStream (std::ostream& ioOut) const {
    ioOut << "YieldStoreKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldStoreKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string YieldStoreKey::toString() const {
    std::ostringstream oStr;
    oStr << _airlineCode;
    return oStr.str();
  }

}
