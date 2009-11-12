// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentCabinKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey_T::SegmentCabinKey_T (const CabinCode_T& iCabinCode)
    : _cabinCode (iCabinCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey_T::SegmentCabinKey_T (const SegmentCabinKey_T& iKey)
    : _parentKey (iKey._parentKey), _cabinCode (iKey._cabinCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey_T::~SegmentCabinKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabinKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentCabinKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabinKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentCabinKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _cabinCode;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentCabinKey_T::describe() const {
    std::ostringstream oStr;
    oStr << _parentKey.describe() << ", " << toString();
    return oStr.str();
  }

}
