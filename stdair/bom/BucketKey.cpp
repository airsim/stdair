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
#include <stdair/bom/BucketKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BucketKey::BucketKey() {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  BucketKey::BucketKey (const SeatIndex_T& iSeatIndex)
    : _seatIndex (iSeatIndex) {
  }

  // ////////////////////////////////////////////////////////////////////
  BucketKey::BucketKey (const BucketKey& iBucketKey)
    : _seatIndex (iBucketKey._seatIndex) {
  }

  // ////////////////////////////////////////////////////////////////////
  BucketKey::~BucketKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void BucketKey::toStream (std::ostream& ioOut) const {
    ioOut << "BucketKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void BucketKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string BucketKey::toString() const {
    std::ostringstream oStr;
    oStr << _seatIndex;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void BucketKey::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void BucketKey::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void BucketKey::serialize (Archive& ioArchive,
                                 const unsigned int iFileVersion) {
    ioArchive & _seatIndex;
  }

  // ////////////////////////////////////////////////////////////////////
  // Explicit template instantiation
  namespace ba = boost::archive;
  template void BucketKey::serialize<ba::text_oarchive> (ba::text_oarchive&,
                                                         unsigned int);
  template void BucketKey::serialize<ba::text_iarchive> (ba::text_iarchive&,
                                                         unsigned int);
  // ////////////////////////////////////////////////////////////////////

}
