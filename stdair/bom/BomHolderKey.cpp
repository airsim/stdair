// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/bom/BomHolderKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomHolderKey::BomHolderKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  BomHolderKey::~BomHolderKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void BomHolderKey::toStream (std::ostream& ioOut) const {
    ioOut << "BomHolderKey: " << toString() << std::endl;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void BomHolderKey::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string BomHolderKey::toString() const {
    std::ostringstream oStr;
    oStr << " -- HOLDER -- ";
    return oStr.str();
  }
  
}
