// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/stdair_types.hpp>
#include <stdair/bom/AirlineFeature.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::AirlineFeature (const Key_T& iKey) : _key (iKey) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature::~AirlineFeature () {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineFeature::init (const ForecasterMode_T& iForecastMode,
                             const HistoricalDataLimit_T& iHistoricalDataLimit,
                             const ControlMode_T& iControlMode) {
    _forecasterMode = iForecastMode;
    _historicalDataLimit = iHistoricalDataLimit;
    _controlMode = iControlMode;
  }

  // ////////////////////////////////////////////////////////////////////
  std::string AirlineFeature::toString() const {
    std::ostringstream ostr;
    ostr << describeKey()
         << ", " << _forecasterMode
         << ", " << _historicalDataLimit
         << ", " << _controlMode;
    return ostr.str();
  }
  
}

