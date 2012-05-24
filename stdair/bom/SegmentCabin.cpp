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
  SegmentCabin::SegmentCabin (const SegmentCabin& iSegmentCabin)
    : _key (iSegmentCabin._key), _parent (NULL),
      _capacity (iSegmentCabin._capacity),
      _blockSpace (iSegmentCabin._blockSpace),
      _bookingCounter (iSegmentCabin._bookingCounter),
      _committedSpace (iSegmentCabin._committedSpace),
      _availabilityPool (iSegmentCabin._availabilityPool),
      _currentBidPrice (iSegmentCabin._currentBidPrice),
      _fareFamilyActivation (iSegmentCabin._fareFamilyActivation) {
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
  void SegmentCabin::initNestingStruct() {
    _nestingStruct.clear();
    const BookingClassList_T& lBookingClassList = 
      BomManager::getList<BookingClass>(*this);
    //Browse the booking class list
    for (BookingClassList_T::const_iterator itBC = lBookingClassList.begin();
         itBC != lBookingClassList.end(); ++itBC) {
      BookingClass* lBC_ptr = *itBC;
      assert (lBC_ptr != NULL);
      const Yield_T& lYield = lBC_ptr->getYield();
      BookingClassList_T lBCList;
      lBCList.push_back(lBC_ptr);
      const bool insertionSucceeded = 
        _nestingStruct.insertBookingClassList(lYield, lBCList);
      assert (insertionSucceeded == true);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabin::fillNestingStruct() {
    // Find the remaining booking classes.
    // Create a copy of the booking class list of the segment cabin and remove 
    // from the copy the booking classes of the nesting structure.
    BookingClassList_T lBookingClass = BomManager::getList<BookingClass>(*this);
    const NestingNodeMap_T& lNestingNodeMap = _nestingStruct.getNestingNodeMap();
    for (NestingNodeMap_T::const_iterator itNestingStruct = lNestingNodeMap.begin();
         itNestingStruct != lNestingNodeMap.end(); ++itNestingStruct) {
      const NestingNode_T& lNestingNode = (*itNestingStruct);
      const BookingClassList_T& lBCList = lNestingNode.second;
      // Browse the nesting structure...
      for (BookingClassList_T::const_iterator itNestedBC = lBCList.begin();
           itNestedBC != lBCList.end(); ++itNestedBC) {
        assert(itNestedBC != lBCList.end());
        const BookingClass* lNestedBC_ptr = *itNestedBC;
        assert(lNestedBC_ptr != NULL);
        // ...and remove its booking classes from the list.  
        for (BookingClassList_T::iterator itBC = lBookingClass.begin();
             itBC != lBookingClass.end(); ++itBC){
          assert(itBC != lBookingClass.end());
          const BookingClass* lBC_ptr = *itBC;
          assert(lBC_ptr != NULL);
          if (lBC_ptr == lNestedBC_ptr) {
            lBookingClass.erase(itBC);
            break;
          }
        }
      }
    }
    // Add the remaining booking classes in the nesting structure with a 
    // yield of 0.
    const bool isBookingClassEmpty = lBookingClass.empty();
    if (isBookingClassEmpty == false) {
      const bool insertionSucceeded = 
        _nestingStruct.insertBookingClassList(DEFAULT_YIELD_VALUE,
                                              lBookingClass);
      assert (insertionSucceeded == true);
    }
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

}

