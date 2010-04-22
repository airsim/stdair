// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/AirportDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirportDateKey_T::AirportDateKey_T () : _origin ("ZZZ") {
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirportDateKey_T::AirportDateKey_T (const AirportCode_T& iAirportCode)
    : _origin (iAirportCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirportDateKey_T::AirportDateKey_T (const AirportDateKey_T& iKey)
    : _origin (iKey._origin) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirportDateKey_T::~AirportDateKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirportDateKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "AirportDateKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void AirportDateKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string AirportDateKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _origin;
    return oStr.str();
  }
  
}
