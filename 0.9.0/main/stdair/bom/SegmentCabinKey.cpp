// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/bom/SegmentCabinKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey::SegmentCabinKey (const CabinCode_T& iCabinCode)
    : _cabinCode (iCabinCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey::SegmentCabinKey (const SegmentCabinKey& iKey)
    : _cabinCode (iKey._cabinCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey::~SegmentCabinKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabinKey::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentCabinKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabinKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentCabinKey::toString() const {
    std::ostringstream oStr;
    oStr << _cabinCode;
    return oStr.str();
  }

}
