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
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/Bucket.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Bucket::Bucket()
    : _key (DEFAULT_SEAT_INDEX), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  Bucket::Bucket (const Key_T& iKey) : _key (iKey), _parent (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  Bucket::~Bucket() {
  }
    
  // ////////////////////////////////////////////////////////////////////
  std::string Bucket::toString() const {
    std::ostringstream oStr;
    oStr <<  describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void Bucket::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void Bucket::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void Bucket::serialize (Archive& ioArchive, const unsigned int iFileVersion) {
    ioArchive & _key;
  }

}

