// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// STDAIR
#include <stdair/bom/FareFeaturesKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FareFeaturesKey::FareFeaturesKey (const stdair::DayDuration_T& iAdvancePurchase,
                                    const stdair::SaturdayStay_T& iSaturdayStay,
                                    const stdair::ChangeFees_T& iChangeFees,
                                    const stdair::NonRefundable_T& iNonRefundable,
                                    const stdair::DayDuration_T& iMinimumStay,
                                    const stdair::Fare_T& iFare)
    : _advancePurchase(iAdvancePurchase),_saturdayStay(iSaturdayStay),
      _changeFees(iChangeFees), _nonRefundable(iNonRefundable),
      _minimumStay(iMinimumStay), _fare(iFare) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFeaturesKey::FareFeaturesKey (const FareFeaturesKey& iKey)
    : _advancePurchase(iKey.getAdvancePurchase()), 
      _saturdayStay(iKey.getSaturdayStay()),
      _changeFees(iKey.getChangeFees()), 
      _nonRefundable(iKey.getRefundableOption()),
      _minimumStay(iKey.getMinimumStay()), 
      _fare(iKey.getFare()) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFeaturesKey::~FareFeaturesKey () {
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
    oStr << _advancePurchase << "-"<< _saturdayStay << "-"
         << _changeFees << "-" << _nonRefundable << "-"
         << _minimumStay << "-" << _fare;
    return oStr.str();
  }

}
