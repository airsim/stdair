// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost.Serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/access.hpp>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/Inventory.hpp>
// StdAir serialisation (should be moved elsewhere, as bom should not
// depend on factory)
#include <stdair/factory/FacBom.hpp>

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
  BomRoot::~BomRoot() {
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
    Inventory* oInventory_ptr =
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
    // Serialise the key (by default, equal to " -- ROOT -- ")
    ioArchive & _key;

    /**
     * Retrieve the list of children (Inventory objects).
     *
     * \note That list does not exist when the back-up file/stream is
     *       parsed (in order to re-built a new BOM tree from the
     *       stored data), and must be (re-)created in memory. Of
     *       course, when the BOM tree is dumped within the backup
     *       file/stream, the list (and map) of children
     *       exist. However, as of now, I have found no way to know in
     *       which mode we are (either BOM tree dump into the backup
     *       file OR backup file parsing to re-instance the BOM tree
     *       into memory).
     */
    BomHolder<Inventory>* lBomHolder_ptr = NULL;
    HolderMap_T::const_iterator itHolder= _holderMap.find (&typeid (Inventory));

    if (itHolder == _holderMap.end()) {
      lBomHolder_ptr = &FacBom<BomHolder<Inventory> >::instance().create();
      _holderMap.insert (typename HolderMap_T::value_type (&typeid (Inventory),
                                                           lBomHolder_ptr));

    } else {
      lBomHolder_ptr = static_cast<BomHolder<Inventory>*> (itHolder->second);
    }
    assert (lBomHolder_ptr != NULL);

    // Serialise the children (Inventory objects)
    //ioArchive.register_type (static_cast<Inventory*> (NULL));
    ioArchive & lBomHolder_ptr->_bomList;
    ioArchive & lBomHolder_ptr->_bomMap;
  }

}
