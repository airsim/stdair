// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// STDAIR
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/AirportPairKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirportPairKey::AirportPairKey ()
    : _boardingPoint (DEFAULT_ORIGIN), 
      _offPoint (DEFAULT_DESTINATION) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AirportPairKey::AirportPairKey (const AirportCode_T& iBoardingPoint,
                                  const AirportCode_T& iOffPoint)
    : _boardingPoint (iBoardingPoint), _offPoint (iOffPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirportPairKey::AirportPairKey (const AirportPairKey& iKey)
    : _boardingPoint (iKey._boardingPoint),
      _offPoint (iKey._offPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirportPairKey::~AirportPairKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirportPairKey::toStream (std::ostream& ioOut) const {
    ioOut << "AirportPairKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void AirportPairKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string AirportPairKey::toString() const {
    std::ostringstream oStr;
    oStr << _boardingPoint << DEFAULT_KEY_SUB_FLD_DELIMITER
         << " " << _offPoint; 
    return oStr.str();
  }

}
