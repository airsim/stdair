// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/AirlineFeatureKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureKey_T::AirlineFeatureKey_T (const AirlineCode_T& iAirlineCode)
    : _airlineCode (iAirlineCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureKey_T::~AirlineFeatureKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeatureKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "AirlineFeatureKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeatureKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string AirlineFeatureKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _airlineCode;
    return oStr.str();
  }

}
