// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabin.hpp>


namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegCabin::LegCabin() : _key (DEFAULT_CABIN_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabin::LegCabin (const LegCabin&)
    : _key (DEFAULT_CABIN_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabin::LegCabin (const Key_T& iKey)
    : _key (iKey), _parent (NULL),
      _offeredCapacity (DEFAULT_CABIN_CAPACITY),
      _physicalCapacity (DEFAULT_CABIN_CAPACITY),
      _soldSeat (DEFAULT_CLASS_NB_OF_BOOKINGS),
      _committedSpace (DEFAULT_COMMITTED_SPACE),
      _availabilityPool (DEFAULT_AVAILABILITY),
      _availability (DEFAULT_AVAILABILITY),
      _currentBidPrice (DEFAULT_BID_PRICE),
      _bidPriceVector (DEFAULT_BID_PRICE_VECTOR),
      _dcsRegrade (DEFAULT_NULL_CAPACITY_ADJUSTMENT),
      _au (DEFAULT_CLASS_AUTHORIZATION_LEVEL),
      _upr (DEFAULT_NULL_UPR),
      _nav (DEFAULT_AVAILABILITY),
      _gav (DEFAULT_AVAILABILITY),
      _acp (DEFAULT_CLASS_OVERBOOKING_RATE),
      _etb (DEFAULT_NULL_BOOKING_NUMBER),
      _staffNbOfBookings (DEFAULT_NULL_BOOKING_NUMBER),
      _wlNbOfBookings (DEFAULT_NULL_BOOKING_NUMBER),
      _groupNbOfBookings (DEFAULT_NULL_BOOKING_NUMBER) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabin::~LegCabin() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void LegCabin::setCapacities (const CabinCapacity_T& iCapacity) {
    _offeredCapacity = iCapacity;
    _physicalCapacity = iCapacity;
    setAvailabilityPool (iCapacity - _committedSpace);
  }

  // ////////////////////////////////////////////////////////////////////
  const MapKey_T LegCabin::getFullerKey() const {
    const LegDate& lLegDate = BomManager::getParent<LegDate> (*this);

    const MapKey_T oFullKey =
      lLegDate.describeKey() + DEFAULT_KEY_FLD_DELIMITER + getCabinCode();
    return oFullKey;
  }

  // ////////////////////////////////////////////////////////////////////
  std::string LegCabin::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string LegCabin::displayVirtualClassList () const {
    std::ostringstream oStr;
    
    for (VirtualClassList_T::const_iterator itVC = _virtualClassList.begin();
         itVC != _virtualClassList.end(); ++itVC) {
      const VirtualClassStruct& lVC = *itVC;
      oStr << std::endl << "Yield: " << std::fixed << std::setprecision (2)
           << lVC.getYield()
           << ", Protection: " << std::fixed << std::setprecision (2)
           << lVC.getCumulatedProtection()
           << ", Booking limit: " << std::fixed << std::setprecision (2)
           << lVC.getCumulatedBookingLimit();
    }
    
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void LegCabin::updateFromReservation (const NbOfBookings_T& iNbOfBookings) {
    _committedSpace += iNbOfBookings;
    _availabilityPool = _offeredCapacity - _committedSpace;
  }

  // ////////////////////////////////////////////////////////////////////
  void LegCabin::updateCurrentBidPrice() {
    const unsigned short lAvailabilityPool =
      static_cast<unsigned short> (std::floor (_availabilityPool));

    if (lAvailabilityPool >= 1) {
      const unsigned short lBidPriceVectorSize = _bidPriceVector.size();
      if (lBidPriceVectorSize >= lAvailabilityPool) {
        _currentBidPrice = _bidPriceVector.at (lAvailabilityPool - 1);
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void LegCabin::addDemandInformation (const YieldValue_T& iYield,
                                       const MeanValue_T& iMeanValue,
                                       const StdDevValue_T& iStdDevValue) {
    //
    const int lYieldLevel =
      static_cast<int> (std::floor (iYield + 0.5));

    //
    YieldLevelDemandMap_T::iterator itDemand =
      _yieldLevelDemandMap.find (lYieldLevel);

    if (itDemand == _yieldLevelDemandMap.end()) {
      MeanStdDevPair_T lMeanStdDevPair (iMeanValue,iStdDevValue);
      const bool hasInsertBeenSuccessful = _yieldLevelDemandMap.
        insert (YieldLevelDemandMap_T::value_type (lYieldLevel,
                                                   lMeanStdDevPair)).second;
      assert (hasInsertBeenSuccessful == true);
      
    } else {
      //
      MeanStdDevPair_T& lMeanStdDevPair = itDemand->second;
      MeanValue_T lMeanValue = iMeanValue + lMeanStdDevPair.first;
      StdDevValue_T lStdDevValue = iStdDevValue * iStdDevValue + lMeanStdDevPair.second * lMeanStdDevPair.second;
      lStdDevValue = std::sqrt (lStdDevValue);

      //
      lMeanStdDevPair = MeanStdDevPair_T (lMeanValue, lStdDevValue);
    }
  }  

}

