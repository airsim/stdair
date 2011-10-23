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
#include <stdair/bom/SegmentCabinKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey::SegmentCabinKey() : _cabinCode (DEFAULT_CABIN_CODE) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey::SegmentCabinKey (const CabinCode_T& iCabinCode)
    : _cabinCode (iCabinCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey::SegmentCabinKey (const SegmentCabinKey& iKey)
    : _cabinCode (iKey._cabinCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinKey::~SegmentCabinKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabinKey::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentCabinKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabinKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentCabinKey::toString() const {
    std::ostringstream oStr;
    oStr << _cabinCode;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabinKey::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void SegmentCabinKey::serialize (Archive& ioArchive,
                                   const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    ioArchive & _cabinCode;
  }

}
