// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory() :
    _key (DEFAULT_AIRLINE_CODE),
    _parent (NULL),
    _airlineFeature (NULL) {
    // That constructor is used by the serialisation process
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const Inventory&)
    : _key (DEFAULT_AIRLINE_CODE),
      _parent (NULL),
      _airlineFeature (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const Key_T& iKey) :
    _key (iKey),
    _parent (NULL),
    _airlineFeature (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::~Inventory() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string Inventory::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* Inventory::
  getFlightDate (const std::string& iFlightDateKeyStr) const {
    FlightDate* oFlightDate_ptr =
      BomManager::getObjectPtr<FlightDate> (*this, iFlightDateKeyStr);
    return oFlightDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* Inventory::
  getFlightDate (const FlightDateKey& iFlightDateKey) const {
    return getFlightDate (iFlightDateKey.toString());
  }

}

