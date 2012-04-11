// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/stdair_types.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/AirlineFeature.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::AirlineFeature (const Key_T& iKey) :
    _key (iKey),
    _forecastingMethod(DEFAULT_FORECASTING_METHOD),
    _unconstrainingMethod(DEFAULT_UNCONSTRAINING_METHOD),
    _partnershipTechnique(DEFAULT_PARTNERSHIP_TECHNIQUE) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::~AirlineFeature () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeature::init (const ForecastingMethod& iForecastingMethod,
                             const UnconstrainingMethod& iUnconstrainingMethod,
                             const HistoricalDataLimit_T& iHistoricalDataLimit,
                             const ControlMode_T& iControlMode,
                             const PartnershipTechnique& iPartnershipTechnique) {
    _forecastingMethod = iForecastingMethod;
    _unconstrainingMethod = iUnconstrainingMethod;
    _historicalDataLimit = iHistoricalDataLimit;
    _controlMode = iControlMode;
    _partnershipTechnique = iPartnershipTechnique;
  }

  // ////////////////////////////////////////////////////////////////////
  std::string AirlineFeature::toString() const {
    std::ostringstream ostr;
    ostr << describeKey()
         << ", " << _forecastingMethod
         << ", " << _unconstrainingMethod
         << ", " << _historicalDataLimit
         << ", " << _controlMode
         << ", " << _partnershipTechnique;
    return ostr.str();
  }
  
}

