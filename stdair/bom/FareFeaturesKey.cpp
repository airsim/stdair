// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/bom/FareFeaturesKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  // TODO (gsabatier): replace the hard-coded constants by BasConst ones.
  FareFeaturesKey::FareFeaturesKey()
    : _tripType ("RT"),
      _advancePurchase (7), 
      _saturdayStay (true),
      _changeFees (true), 
      _nonRefundable (true),
      _minimumStay (3) {
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
