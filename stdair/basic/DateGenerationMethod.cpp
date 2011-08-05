// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/DateGenerationMethod.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string DateGenerationMethod::_labels[LAST_VALUE] =
    { "PoissonProcess", "SatisticsOrder" };

  // //////////////////////////////////////////////////////////////////////
  const char DateGenerationMethod::
  _methodLabels[LAST_VALUE] = { 'P', 'S' };

  
  // //////////////////////////////////////////////////////////////////////
  DateGenerationMethod::DateGenerationMethod()
    : _method (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  DateGenerationMethod::
  DateGenerationMethod (const DateGenerationMethod& iDateGenerationMethod)
    : _method (iDateGenerationMethod._method) {
  }

  // //////////////////////////////////////////////////////////////////////
  DateGenerationMethod::
  DateGenerationMethod (const EN_DateGenerationMethod& iDateGenerationMethod)
    : _method (iDateGenerationMethod) {
  }

  // //////////////////////////////////////////////////////////////////////
  DateGenerationMethod::DateGenerationMethod (const char iMethod) {
    switch (iMethod) {
    case 'P': _method = POI_PRO; break;
    case 'S': _method = STA_ORD; break;
    default: _method = LAST_VALUE; break;
    }

    if (_method == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The date-time booking request generation method '" << iMethod
               << "' is not known. Known date-time booking request generation methods: "
               << lLabels;
      throw CodeConversionException (oMessage.str());
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& DateGenerationMethod::
  getLabel (const EN_DateGenerationMethod& iMethod) {
    return _labels[iMethod];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char DateGenerationMethod::getMethodLabel (const EN_DateGenerationMethod& iMethod) {
    return _methodLabels[iMethod];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string DateGenerationMethod::
  getMethodLabelAsString (const EN_DateGenerationMethod& iMethod) {
    std::ostringstream oStr;
    oStr << _methodLabels[iMethod];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string DateGenerationMethod::describeLabels() {
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
  DateGenerationMethod::EN_DateGenerationMethod DateGenerationMethod::getMethod() const {
    return _method;
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string DateGenerationMethod::getMethodAsString() const {
    std::ostringstream oStr;
    oStr << _methodLabels[_method];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string DateGenerationMethod::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_method];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool DateGenerationMethod::
  operator== (const EN_DateGenerationMethod& iMethod) const {
    return (_method == iMethod);
  }
  
}
