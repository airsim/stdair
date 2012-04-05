// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/UnconstrainingMethod.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string UnconstrainingMethod::_labels[LAST_VALUE] =
    { "ByTimeFrame", "BookingCurve" };

  // //////////////////////////////////////////////////////////////////////
  const char UnconstrainingMethod::
  _methodLabels[LAST_VALUE] = { 'T', 'B' };

  
  // //////////////////////////////////////////////////////////////////////
  UnconstrainingMethod::UnconstrainingMethod()
    : _method (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  UnconstrainingMethod::
  UnconstrainingMethod (const UnconstrainingMethod& iUnconstrainingMethod)
    : _method (iUnconstrainingMethod._method) {
  }

  // //////////////////////////////////////////////////////////////////////
  UnconstrainingMethod::
  UnconstrainingMethod (const EN_UnconstrainingMethod& iUnconstrainingMethod)
    : _method (iUnconstrainingMethod) {
  }

  // //////////////////////////////////////////////////////////////////////
  UnconstrainingMethod::UnconstrainingMethod (const char iMethod) {
    switch (iMethod) {
    case 'T': _method = TIME_FRAME; break;
    case 'B': _method = BOOKING_CURVE; break;
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
  const std::string& UnconstrainingMethod::
  getLabel (const EN_UnconstrainingMethod& iMethod) {
    return _labels[iMethod];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char UnconstrainingMethod::getMethodLabel (const EN_UnconstrainingMethod& iMethod) {
    return _methodLabels[iMethod];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string UnconstrainingMethod::
  getMethodLabelAsString (const EN_UnconstrainingMethod& iMethod) {
    std::ostringstream oStr;
    oStr << _methodLabels[iMethod];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string UnconstrainingMethod::describeLabels() {
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
  UnconstrainingMethod::EN_UnconstrainingMethod UnconstrainingMethod::getMethod() const {
    return _method;
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string UnconstrainingMethod::getMethodAsString() const {
    std::ostringstream oStr;
    oStr << _methodLabels[_method];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string UnconstrainingMethod::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_method];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool UnconstrainingMethod::
  operator== (const EN_UnconstrainingMethod& iMethod) const {
    return (_method == iMethod);
  }
  
}
