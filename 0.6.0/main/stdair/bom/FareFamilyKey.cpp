// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/FareFamilyKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FareFamilyKey::FareFamilyKey (const FamilyCode_T& iFamilyCode)
    : _familyCode (iFamilyCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFamilyKey::~FareFamilyKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFamilyKey::toStream (std::ostream& ioOut) const {
    ioOut << "FareFamilyKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFamilyKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string FareFamilyKey::toString() const {
    std::ostringstream oStr;
    oStr << _familyCode;
    return oStr.str();
  }

}
