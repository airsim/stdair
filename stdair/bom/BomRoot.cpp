// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/Inventory.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot() {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (const BomRoot& iBomRoot) :
    _key (iBomRoot._key), _frat5CurveHolder (iBomRoot._frat5CurveHolder),
    _ffDisutilityCurveHolder (iBomRoot._ffDisutilityCurveHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (const Key_T& iKey) : _key (iKey) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::~BomRoot() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string BomRoot::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory* BomRoot::getInventory (const std::string& iInventoryKeyStr) const {
    Inventory* oInventory_ptr =
      BomManager::getObjectPtr<Inventory> (*this, iInventoryKeyStr);
    return oInventory_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory* BomRoot::getInventory (const InventoryKey& iInventoryKey) const {
    return getInventory (iInventoryKey.toString());
  }

}
