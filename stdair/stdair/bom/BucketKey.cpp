// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BucketKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BucketKey_T::BucketKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  BucketKey_T::~BucketKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void BucketKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "BucketKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void BucketKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string BucketKey_T::toString() const {
    std::ostringstream oStr;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string BucketKey_T::describe() const {
    std::ostringstream oStr;
    oStr << _parentKey.describe() << ", " << toString();
    return oStr.str();
  }

}
