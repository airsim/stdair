// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost.Serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
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
  BomRoot::BomRoot (const BomRoot& iBomRoot) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::BomRoot (const Key_T& iKey) : _key (iKey) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRoot::~BomRoot () {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string BomRoot::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory* BomRoot::
  getInventory (const std::string& iInventoryKeyStr) const {
    Inventory* oInventory_ptr = NULL;
    BomManager::getObjectPtr<Inventory> (*this, iInventoryKeyStr);
    return oInventory_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory* BomRoot::
  getInventory (const InventoryKey& iInventoryKey) const {
    return getInventory (iInventoryKey.toString());
  }

  // ////////////////////////////////////////////////////////////////////
  void BomRoot::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void BomRoot::serialize (Archive& ioArchive,
                             const unsigned int iFileVersion) {
    ioArchive & _key;
  }

}
