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
    { "PoissonProcess", "SatisticsOrder" };

  // //////////////////////////////////////////////////////////////////////
  const char DemandGenerationMethod::
  _methodLabels[LAST_VALUE] = { 'P', 'S' };

  
  // //////////////////////////////////////////////////////////////////////
  DemandGenerationMethod::DemandGenerationMethod()
    : _method (LAST_VALUE) {
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
  DemandGenerationMethod::DemandGenerationMethod (const char iMethod) {
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
  const std::string& DemandGenerationMethod::
  getLabel (const EN_DemandGenerationMethod& iMethod) {
    return _labels[iMethod];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char DemandGenerationMethod::getMethodLabel (const EN_DemandGenerationMethod& iMethod) {
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
  DemandGenerationMethod::EN_DemandGenerationMethod DemandGenerationMethod::getMethod() const {
    return _method;
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
