// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/bom/YieldFeaturesKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  YieldFeaturesKey::YieldFeaturesKey()
    : _tripType (TRIP_TYPE_ONE_WAY),
      _cabinCode (DEFAULT_PREFERRED_CABIN) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  YieldFeaturesKey::YieldFeaturesKey (const stdair::TripType_T& iTripType,
                                      const stdair::CabinCode_T& iCabin)
    : _tripType (iTripType), _cabinCode (iCabin) {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldFeaturesKey::YieldFeaturesKey (const YieldFeaturesKey& iKey)
    : _tripType (iKey.getTripType()), _cabinCode (iKey.getCabinCode()) {
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
    oStr << _tripType << " -- " << _cabinCode;
    return oStr.str();
  }

}
