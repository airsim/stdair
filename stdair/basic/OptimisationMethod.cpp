// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/OptimisationMethod.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string OptimisationMethod::_labels[LAST_VALUE] =
    { "Leg based Monte Carlo", "Leg based EMSRb"};

  // //////////////////////////////////////////////////////////////////////
  const char OptimisationMethod::
  _methodLabels[LAST_VALUE] = { 'M', 'E'};

  
  // //////////////////////////////////////////////////////////////////////
  OptimisationMethod::OptimisationMethod()
    : _method (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  OptimisationMethod::
  OptimisationMethod (const OptimisationMethod& iOptimisationMethod)
    : _method (iOptimisationMethod._method) {
  }

  // //////////////////////////////////////////////////////////////////////
  OptimisationMethod::
  OptimisationMethod (const EN_OptimisationMethod& iOptimisationMethod)
    : _method (iOptimisationMethod) {
  }

  // //////////////////////////////////////////////////////////////////////
  OptimisationMethod::OptimisationMethod (const char iMethod) {
    switch (iMethod) {
    case 'M': _method = LEG_BASED_MC; break;
    case 'E': _method = LEG_BASED_EMSR_B; break;
    default: _method = LAST_VALUE; break;
    }

    if (_method == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The optimisation method '" << iMethod
               << "' is not known. Known optimisation methods: " << lLabels;
      throw CodeConversionException (oMessage.str());
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& OptimisationMethod::
  getLabel (const EN_OptimisationMethod& iMethod) {
    return _labels[iMethod];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char OptimisationMethod::getMethodLabel (const EN_OptimisationMethod& iMethod) {
    return _methodLabels[iMethod];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string OptimisationMethod::
  getMethodLabelAsString (const EN_OptimisationMethod& iMethod) {
    std::ostringstream oStr;
    oStr << _methodLabels[iMethod];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string OptimisationMethod::describeLabels() {
    std::ostringstream ostr;
    for (unsigned short idx = 0; idx != LAST_VALUE; ++idx) {
      if (idx != 0) {
        ostr << ", ";
      }
      ostr << _labels[idx] << " (" << _methodLabels[idx] << ")";
    }
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  OptimisationMethod::EN_OptimisationMethod OptimisationMethod::getMethod() const {
    return _method;
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string OptimisationMethod::getMethodAsString() const {
    std::ostringstream oStr;
    oStr << _methodLabels[_method];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string OptimisationMethod::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_method];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool OptimisationMethod::
  operator== (const EN_OptimisationMethod& iMethod) const {
    return (_method == iMethod);
  }
  
}
