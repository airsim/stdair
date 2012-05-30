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
#include <stdair/bom/FareFamily.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FareFamily::FareFamily() : _key (DEFAULT_FARE_FAMILY_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  FareFamily::FareFamily (const FareFamily& iFareFamily)
    : _key (iFareFamily._key),
      _parent (NULL),
      _frat5Curve (iFareFamily._frat5Curve),
      _disutilityCurve (iFareFamily._disutilityCurve),
      _meanStdDev (iFareFamily._meanStdDev) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFamily::FareFamily (const Key_T& iKey) : _key (iKey), _parent (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFamily::~FareFamily() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string FareFamily::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFamily::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFamily::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void FareFamily::serialize (Archive& ioArchive,
                              const unsigned int iFileVersion) {
    ioArchive & _key;
  }

}


