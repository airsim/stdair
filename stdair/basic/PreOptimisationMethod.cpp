// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/PreOptimisationMethod.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PreOptimisationMethod::_labels[LAST_VALUE] =
    {"None", "Fare Adjustment", "Marginal Revenue Transformation"};

  // //////////////////////////////////////////////////////////////////////
  const char PreOptimisationMethod::
  _methodLabels[LAST_VALUE] = {'N', 'F', 'M'};

  
  // //////////////////////////////////////////////////////////////////////
  PreOptimisationMethod::PreOptimisationMethod()
    : _method (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  PreOptimisationMethod::
  PreOptimisationMethod (const PreOptimisationMethod& iPreOptimisationMethod)
    : _method (iPreOptimisationMethod._method) {
  }

  // //////////////////////////////////////////////////////////////////////
  PreOptimisationMethod::
  PreOptimisationMethod (const EN_PreOptimisationMethod& iPreOptimisationMethod)
    : _method (iPreOptimisationMethod) {
  }

  // //////////////////////////////////////////////////////////////////////
  PreOptimisationMethod::PreOptimisationMethod (const char iMethod) {
    switch (iMethod) {
    case 'N': _method = NONE; break;
    case 'F': _method = FA; break;
    case 'M': _method = MRT; break;
    default: _method = LAST_VALUE; break;
    }

    if (_method == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The pre-optimisation method '" << iMethod
               << "' is not known. Known pre-optimisation methods: " << lLabels;
      throw CodeConversionException (oMessage.str());
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& PreOptimisationMethod::
  getLabel (const EN_PreOptimisationMethod& iMethod) {
    return _labels[iMethod];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char PreOptimisationMethod::getMethodLabel (const EN_PreOptimisationMethod& iMethod) {
    return _methodLabels[iMethod];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string PreOptimisationMethod::
  getMethodLabelAsString (const EN_PreOptimisationMethod& iMethod) {
    std::ostringstream oStr;
    oStr << _methodLabels[iMethod];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string PreOptimisationMethod::describeLabels() {
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
  PreOptimisationMethod::EN_PreOptimisationMethod PreOptimisationMethod::getMethod() const {
    return _method;
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string PreOptimisationMethod::getMethodAsString() const {
    std::ostringstream oStr;
    oStr << _methodLabels[_method];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PreOptimisationMethod::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_method];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool PreOptimisationMethod::
  operator== (const EN_PreOptimisationMethod& iMethod) const {
    return (_method == iMethod);
  }
  
}
