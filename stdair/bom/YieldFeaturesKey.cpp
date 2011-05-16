// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// STDAIR
#include <stdair/bom/YieldFeaturesKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  YieldFeaturesKey::YieldFeaturesKey (const stdair::CabinCode_T& iCabin)
    : _cabinCode (iCabin) {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldFeaturesKey::YieldFeaturesKey (const YieldFeaturesKey& iKey)
    : _cabinCode (iKey._cabinCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldFeaturesKey::~YieldFeaturesKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldFeaturesKey::toStream (std::ostream& ioOut) const {
    ioOut << "YieldFeaturesKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldFeaturesKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string YieldFeaturesKey::toString() const {
    std::ostringstream oStr;
    oStr << _cabinCode;
    return oStr.str();
  }

}
