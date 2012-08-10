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
    _preOptimisationMethod(DEFAULT_PREOPTIMISATION_METHOD),
    _optimisationMethod(DEFAULT_OPTIMISATION_METHOD),
    _partnershipTechnique(DEFAULT_PARTNERSHIP_TECHNIQUE) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::AirlineFeature (const AirlineFeature& iAirlineFeature) :
    _key (iAirlineFeature._key),
    _forecastingMethod (iAirlineFeature._forecastingMethod),
    _unconstrainingMethod (iAirlineFeature._unconstrainingMethod),
    _preOptimisationMethod (iAirlineFeature._preOptimisationMethod),
    _optimisationMethod (iAirlineFeature._optimisationMethod),
    _partnershipTechnique (iAirlineFeature._partnershipTechnique) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::~AirlineFeature () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeature::init(const ForecastingMethod& iForecastingMethod,
                            const UnconstrainingMethod& iUnconstrainingMethod,
                            const PreOptimisationMethod& iPreOptimisationMethod,
                            const OptimisationMethod& iOptimisationMethod,
                            const HistoricalDataLimit_T& iHistoricalDataLimit,
                            const ControlMode_T& iControlMode,
                            const PartnershipTechnique& iPartnershipTechnique) {
    _forecastingMethod = iForecastingMethod;
    _unconstrainingMethod = iUnconstrainingMethod;
    _preOptimisationMethod = iPreOptimisationMethod;
    _optimisationMethod = iOptimisationMethod;
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
	 << ", " << _preOptimisationMethod
      	 << ", " << _optimisationMethod
         << ", " << _historicalDataLimit
      //<< ", " << _controlMode
         << ", " << _partnershipTechnique;
    return ostr.str();
  }
  
}

