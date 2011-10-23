// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// Boost.Serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
// StdAir
#include <stdair/bom/BomRootKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BomRootKey::BomRootKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  BomRootKey::BomRootKey (const BomRootKey& iBomRootKey) {
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
    oStr << " -- ROOT -- ";
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
  }

}
