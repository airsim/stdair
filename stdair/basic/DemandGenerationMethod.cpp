// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/DemandGenerationMethod.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string DemandGenerationMethod::_labels[LAST_VALUE] =
    { "PoissonProcess", "StatisticsOrder" };

  // //////////////////////////////////////////////////////////////////////
  const char DemandGenerationMethod::_methodLabels[LAST_VALUE] = { 'P', 'S' };

  
  // //////////////////////////////////////////////////////////////////////
  DemandGenerationMethod::DemandGenerationMethod() : _method (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  DemandGenerationMethod::
  DemandGenerationMethod (const DemandGenerationMethod& iDemandGenerationMethod)
    : _method (iDemandGenerationMethod._method) {
  }

  // //////////////////////////////////////////////////////////////////////
  DemandGenerationMethod::
  DemandGenerationMethod (const EN_DemandGenerationMethod& iDemandGenerationMethod)
    : _method (iDemandGenerationMethod) {
  }

  // //////////////////////////////////////////////////////////////////////
  DemandGenerationMethod::EN_DemandGenerationMethod
  DemandGenerationMethod::getMethod (const char iMethodChar) {
    EN_DemandGenerationMethod oMethod;
    switch (iMethodChar) {
    case 'P': oMethod = POI_PRO; break;
    case 'S': oMethod = STA_ORD; break;
    default: oMethod = LAST_VALUE; break;
    }

    if (oMethod == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The demand (booking request) generation method '"
               << iMethodChar
               << "' is not known. Known demand (booking request) generation "
               << "methods: " << lLabels;
      throw CodeConversionException (oMessage.str());
    }

    return oMethod;
  }
  
  // //////////////////////////////////////////////////////////////////////
  DemandGenerationMethod::DemandGenerationMethod (const char iMethodChar)
    : _method (getMethod (iMethodChar)) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  DemandGenerationMethod::
  DemandGenerationMethod (const std::string& iMethodStr) {
    // 
    const size_t lSize = iMethodStr.size();
    assert (lSize == 1);
    const char lMethodChar = iMethodStr[0];
    _method = getMethod (lMethodChar);
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& DemandGenerationMethod::
  getLabel (const EN_DemandGenerationMethod& iMethod) {
    return _labels[iMethod];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char DemandGenerationMethod::
  getMethodLabel (const EN_DemandGenerationMethod& iMethod) {
    return _methodLabels[iMethod];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string DemandGenerationMethod::
  getMethodLabelAsString (const EN_DemandGenerationMethod& iMethod) {
    std::ostringstream oStr;
    oStr << _methodLabels[iMethod];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string DemandGenerationMethod::describeLabels() {
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
  DemandGenerationMethod::EN_DemandGenerationMethod
  DemandGenerationMethod::getMethod() const {
    return _method;
  }
  
  // //////////////////////////////////////////////////////////////////////
  char DemandGenerationMethod::getMethodAsChar() const {
    const char oMethodChar = _methodLabels[_method];
    return oMethodChar;
  }

  // //////////////////////////////////////////////////////////////////////
  std::string DemandGenerationMethod::getMethodAsString() const {
    std::ostringstream oStr;
    oStr << _methodLabels[_method];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string DemandGenerationMethod::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_method];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool DemandGenerationMethod::
  operator== (const EN_DemandGenerationMethod& iMethod) const {
    return (_method == iMethod);
  }
  
}
