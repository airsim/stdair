// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/InventoryKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  InventoryKey_T::InventoryKey_T (const AirlineCode_T& iAirlineCode)
    : _airlineCode (iAirlineCode) {
  }
  // ////////////////////////////////////////////////////////////////////
  InventoryKey_T::InventoryKey_T (const InventoryKey_T& iKey)
    : _airlineCode (iKey._airlineCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryKey_T::~InventoryKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void InventoryKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "InventoryKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void InventoryKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string InventoryKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _airlineCode;
    return oStr.str();
  }

}