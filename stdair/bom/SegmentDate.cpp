// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate()
    : _key (DEFAULT_ORIGIN, DEFAULT_DESTINATION), _parent (NULL),
      _operatingSegmentDate (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const SegmentDate& iSegmentDate)
    : _key (iSegmentDate._key),
      _parent (NULL),
      _operatingSegmentDate (NULL),
      _boardingDate (iSegmentDate._boardingDate),
      _boardingTime (iSegmentDate._boardingTime),
      _offDate (iSegmentDate._offDate),
      _offTime (iSegmentDate._offTime),
      _elapsedTime (iSegmentDate._elapsedTime),
      _distance (iSegmentDate._distance) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const Key_T& iKey)
    : _key (iKey), _parent (NULL) ,
      _operatingSegmentDate (NULL) {
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
}

