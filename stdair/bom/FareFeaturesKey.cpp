// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_DefaultObject.hpp>
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/bom/FareFeaturesKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FareFeaturesKey::FareFeaturesKey()
    : _tripType (TRIP_TYPE_ONE_WAY),
      _advancePurchase (NO_ADVANCE_PURCHASE), 
      _saturdayStay (SATURDAY_STAY),
      _changeFees (CHANGE_FEES), 
      _nonRefundable (NON_REFUNDABLE),
      _minimumStay (NO_STAY_DURATION) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  FareFeaturesKey::FareFeaturesKey (const TripType_T& iTripType,
                                    const DayDuration_T& iAdvancePurchase,
                                    const SaturdayStay_T& iSaturdayStay,
                                    const ChangeFees_T& iChangeFees,
                                    const NonRefundable_T& iNonRefundable,
                                    const DayDuration_T& iMinimumStay)
    : _tripType (iTripType), _advancePurchase (iAdvancePurchase),
      _saturdayStay (iSaturdayStay), _changeFees (iChangeFees),
      _nonRefundable (iNonRefundable), _minimumStay (iMinimumStay) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFeaturesKey::FareFeaturesKey (const FareFeaturesKey& iKey)
    : _tripType (iKey.getTripType()),
      _advancePurchase (iKey.getAdvancePurchase()), 
      _saturdayStay (iKey.getSaturdayStay()),
      _changeFees (iKey.getChangeFees()), 
      _nonRefundable (iKey.getRefundableOption()),
      _minimumStay (iKey.getMinimumStay()) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFeaturesKey::~FareFeaturesKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFeaturesKey::toStream (std::ostream& ioOut) const {
    ioOut << "FareFeaturesKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFeaturesKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string FareFeaturesKey::toString() const {
    std::ostringstream oStr;
    oStr << _tripType << " -- " << _advancePurchase << "-"
         << _saturdayStay << "-" << _changeFees << "-"
         << _nonRefundable << "-" << _minimumStay;
    return oStr.str();
  }

}
