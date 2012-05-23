// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_Yield.hpp>
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::SegmentCabin() : _key (DEFAULT_CABIN_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::SegmentCabin (const SegmentCabin&)
    : _key (DEFAULT_CABIN_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::SegmentCabin (const Key_T& iKey)
    : _key (iKey), _parent (NULL),
      _capacity (DEFAULT_CABIN_CAPACITY),
      _blockSpace (DEFAULT_BLOCK_SPACE),
      _bookingCounter (DEFAULT_CLASS_NB_OF_BOOKINGS),
      _committedSpace (DEFAULT_COMMITTED_SPACE),
      _availabilityPool (DEFAULT_AVAILABILITY),
      _bidPriceVector (DEFAULT_BID_PRICE_VECTOR),
      _currentBidPrice (DEFAULT_BID_PRICE),
      _fareFamilyActivation (false) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::~SegmentCabin() {
  }

  // ////////////////////////////////////////////////////////////////////
  const MapKey_T SegmentCabin::getFullerKey() const {
    const SegmentDate& lSegmentDate = BomManager::getParent<SegmentDate>(*this);

    const MapKey_T oFullKey =
      lSegmentDate.describeKey() + DEFAULT_KEY_FLD_DELIMITER + getCabinCode();
    return oFullKey;
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentCabin::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabin::
  updateFromReservation (const NbOfBookings_T& iNbOfBookings) {
    _committedSpace += iNbOfBookings;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabin::addPolicy (Policy& ioPolicy) {
    _convexHull.push_back (&ioPolicy);
  }
}

