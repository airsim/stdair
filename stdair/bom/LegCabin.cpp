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
      _bidPriceVector (DEFAULT_BID_PRICE_VECTOR) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabin::~LegCabin() {
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
  void LegCabin::addDemandInformation (const YieldValue_T& iYield,
                                       const MeanValue_T& iMeanValue,
                                       const StdDevValue_T& iStdDevValue) {
    int lYieldLevel = std::floor (iYield + 0.5);
    std::map<int,MeanStdDevPair_T>::iterator it =
      _yieldDemandMap.find(lYieldLevel);
    if (it == _yieldDemandMap.end()) {
      MeanStdDevPair_T lMeanStdDevPair (iMeanValue,iStdDevValue);
      _yieldDemandMap.insert(std::pair<int,MeanStdDevPair_T> (lYieldLevel,lMeanStdDevPair));
    } else {
      MeanStdDevPair_T lMeanStdDevPair = _yieldDemandMap [lYieldLevel];
      MeanValue_T lMeanValue = iMeanValue + lMeanStdDevPair.first;
      StdDevValue_T lStdDevValue2 = pow(iStdDevValue,2) + pow(lMeanStdDevPair.second,2);
      StdDevValue_T lStdDevValue = sqrt (lStdDevValue2);
      _yieldDemandMap [lYieldLevel]= MeanStdDevPair_T (lMeanValue, lStdDevValue);
    }
  }  

}

