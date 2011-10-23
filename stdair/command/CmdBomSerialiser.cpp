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
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/command/CmdBomSerialiser.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  template <class Archive, class BOM_OBJECT1, class BOM_OBJECT2>
  void serialiseHelper (BOM_OBJECT1& ioObject1, Archive& ioArchive,
                        const unsigned int iFileVersion) {

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
    BomHolder<BOM_OBJECT2>* lBomHolder_ptr =
      FacBomManager::getBomHolderPtr<BOM_OBJECT2> (ioObject1);

    if (lBomHolder_ptr == NULL) {
      lBomHolder_ptr = &FacBomManager::addBomHolder<BOM_OBJECT2> (ioObject1);
    }
    assert (lBomHolder_ptr != NULL);

    /**
     * Serialise the children (Inventory objects).
     *
     * \note As for now, when re-instantiated, the parent pointer is
     *       no longer set correctly (it remains NULL). When the
     *       _bomList is recreated, the link with the parent has to be
     *       reset.
     * \todo Find a way to recreate the link to the parent.
     */
    //ioArchive.register_type (static_cast<Inventory*> (NULL));
    ioArchive & lBomHolder_ptr->_bomList;
    ioArchive & lBomHolder_ptr->_bomMap;
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

    // Serialise the children of the BomRoot object, i.e., the
    // Inventory children
    stdair::serialiseHelper<Archive, BomRoot, Inventory> (*this, ioArchive,
                                                          iFileVersion);
  }

  // ////////////////////////////////////////////////////////////////////
  void Inventory::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void Inventory::serialize (Archive& ioArchive,
                             const unsigned int iFileVersion) {
    // Serialise the key (airline code)
    ioArchive & _key;

    // Serialise the children of the Inventory object, i.e., the
    // FlightDate children
    /*
    stdair::serialiseHelper<Archive, Inventory, FlightDate> (*this, ioArchive,
                                                             iFileVersion);
    */
  }

}
