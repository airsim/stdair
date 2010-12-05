// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/LegDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegDateKey_T::LegDateKey_T (const AirportCode_T& iBoardingPoint) 
    : _boardingPoint (iBoardingPoint) {
  }
  // ////////////////////////////////////////////////////////////////////
  LegDateKey_T::LegDateKey_T (const LegDateKey_T& iKey)
    : _boardingPoint (iKey._boardingPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateKey_T::~LegDateKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void LegDateKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "LegDateKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void LegDateKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string LegDateKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _boardingPoint;
    return oStr.str();
  }

}