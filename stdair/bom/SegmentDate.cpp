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
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate()
    : _key (DEFAULT_ORIGIN, DEFAULT_DESTINATION), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const SegmentDate&)
    : _key (DEFAULT_ORIGIN, DEFAULT_DESTINATION), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const Key_T& iKey) : _key (iKey), _parent (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::~SegmentDate() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentDate::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const Duration_T SegmentDate::getTimeOffset() const {
    // TimeOffset = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
    //              - ElapsedTime
    Duration_T oTimeOffset = (_offTime - _boardingTime);
    const DateOffset_T& lDateOffset = getDateOffset();
    const Duration_T lDateOffsetInHours (lDateOffset.days() * 24, 0, 0);
    oTimeOffset += lDateOffsetInHours - _elapsedTime;
    return oTimeOffset;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin* SegmentDate::
  getSegmentCabin (const std::string& iSegmentCabinKeyStr) const {
    SegmentCabin* oSegmentCabin_ptr = NULL;
    BomManager::getObjectPtr<SegmentCabin> (*this, iSegmentCabinKeyStr);
    return oSegmentCabin_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin* SegmentDate::
  getSegmentCabin (const SegmentCabinKey& iSegmentCabinKey) const {
    return getSegmentCabin (iSegmentCabinKey.toString());
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDate::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void SegmentDate::serialize (Archive& ioArchive,
                             const unsigned int iFileVersion) {
    ioArchive & _key;
  }

}

