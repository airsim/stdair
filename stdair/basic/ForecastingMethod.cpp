// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/ForecastingMethod.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string ForecastingMethod::_labels[LAST_VALUE] =
    { "Q Forecasting", "Hybrid Forecasting", "Old QFF", "New QFF",
      "Based Forecasting" };

  // //////////////////////////////////////////////////////////////////////
  const char ForecastingMethod::
  _methodLabels[LAST_VALUE] = { 'Q', 'H', 'O' , 'N', 'B'};

  
  // //////////////////////////////////////////////////////////////////////
  ForecastingMethod::ForecastingMethod()
    : _method (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  ForecastingMethod::
  ForecastingMethod (const ForecastingMethod& iForecastingMethod)
    : _method (iForecastingMethod._method) {
  }

  // //////////////////////////////////////////////////////////////////////
  ForecastingMethod::
  ForecastingMethod (const EN_ForecastingMethod& iForecastingMethod)
    : _method (iForecastingMethod) {
  }

  // //////////////////////////////////////////////////////////////////////
  ForecastingMethod::ForecastingMethod (const char iMethod) {
    switch (iMethod) {
    case 'Q': _method = Q_FORECASTING; break;
    case 'H': _method = HYBRID_FORECASTING; break;
    case 'O': _method = OLD_QFF; break;
    case 'N': _method = NEW_QFF; break;
    case 'B': _method = BASED_FORECASTING; break;
    default: _method = LAST_VALUE; break;
    }

    if (_method == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The forecasting method '" << iMethod
               << "' is not known. Known forecasting methods: " << lLabels;
      throw CodeConversionException (oMessage.str());
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& ForecastingMethod::
  getLabel (const EN_ForecastingMethod& iMethod) {
    return _labels[iMethod];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char ForecastingMethod::getMethodLabel (const EN_ForecastingMethod& iMethod) {
    return _methodLabels[iMethod];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string ForecastingMethod::
  getMethodLabelAsString (const EN_ForecastingMethod& iMethod) {
    std::ostringstream oStr;
    oStr << _methodLabels[iMethod];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string ForecastingMethod::describeLabels() {
    std::ostringstream ostr;
    for (unsigned short idx = 0; idx != LAST_VALUE; ++idx) {
      if (idx != 0) {
        ostr << ", ";
      }
      ostr << _labels[idx];
    }
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  ForecastingMethod::EN_ForecastingMethod ForecastingMethod::getMethod() const {
    return _method;
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string ForecastingMethod::getMethodAsString() const {
    std::ostringstream oStr;
    oStr << _methodLabels[_method];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string ForecastingMethod::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_method];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool ForecastingMethod::
  operator== (const EN_ForecastingMethod& iMethod) const {
    return (_method == iMethod);
  }
  
}
