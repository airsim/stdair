// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/SegmentDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey::SegmentDateKey()
    : _boardingPoint (DEFAULT_ORIGIN), _offPoint (DEFAULT_DESTINATION) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey::SegmentDateKey (const AirportCode_T& iBoardingPoint,
                                  const AirportCode_T& iOffPoint)
    : _boardingPoint (iBoardingPoint), _offPoint (iOffPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey::SegmentDateKey (const SegmentDateKey& iKey)
    : _boardingPoint (iKey._boardingPoint), _offPoint (iKey._offPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey::~SegmentDateKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDateKey::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentDateKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDateKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentDateKey::toString() const {
    std::ostringstream oStr;
    oStr << _boardingPoint << "-" << _offPoint;
    return oStr.str();
  }

}
