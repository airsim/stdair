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
#include <stdair/bom/BomRootKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomRootKey::BomRootKey()
    : _id (DEFAULT_BOM_ROOT_KEY) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRootKey::BomRootKey (const BomRootKey& iBomRootKey)
    : _id (iBomRootKey._id) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRootKey::BomRootKey (const std::string& iIdentification)
    : _id (iIdentification) {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRootKey::~BomRootKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void BomRootKey::toStream (std::ostream& ioOut) const {
    ioOut << "BomRootKey: " << toString() << std::endl;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void BomRootKey::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string BomRootKey::toString() const {
    std::ostringstream oStr;
    oStr << _id;
    return oStr.str();
  }
  
  // ////////////////////////////////////////////////////////////////////
  void BomRootKey::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void BomRootKey::serialize (Archive& ioArchive,
                              const unsigned int iFileVersion) {
    ioArchive & _id;
  }

  // ////////////////////////////////////////////////////////////////////
  // Explicit template instantiation
  namespace ba = boost::archive;
  template void BomRootKey::serialize<ba::text_oarchive> (ba::text_oarchive&,
                                                          unsigned int);
  template void BomRootKey::serialize<ba::text_iarchive> (ba::text_iarchive&,
                                                          unsigned int);
  // ////////////////////////////////////////////////////////////////////

}
