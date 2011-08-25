// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/SampleType.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  const std::string SampleType::_labels[LAST_VALUE] =
    { "All", "AllForPartnerships", "RevenueManagement", "Inventory", "Schedule",
      "RevenueAccounting", "FareQuote", "CRS", "DemandGeneration", "EventManagement",
      "CustomerChoice" };

  // //////////////////////////////////////////////////////////////////////
  const char SampleType::
  _typeLabels[LAST_VALUE] = { 'A', 'P', 'R', 'I', 'S', 'T', 'F', 'C', 'D', 'E', 'M' };

  
  // //////////////////////////////////////////////////////////////////////
  SampleType::SampleType()
    : _type (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  SampleType::SampleType (const SampleType& iSampleType)
    : _type (iSampleType._type) {
  }

  // //////////////////////////////////////////////////////////////////////
  SampleType::SampleType (const EN_SampleType& iSampleType)
    : _type (iSampleType) {
  }

  // //////////////////////////////////////////////////////////////////////
  SampleType::SampleType (const char iType) {
    switch (iType) {
    case 'A': _type = ALL; break;
    case 'P': _type = A4P; break;
    case 'R': _type = RMS; break;
    case 'I': _type = INV; break;
    case 'S': _type = SCH; break;
    case 'T': _type = RAC; break;
    case 'F': _type = FQT; break;
    case 'C': _type = CRS; break;
    case 'D': _type = DEM; break;
    case 'E': _type = EVT; break;
    case 'M': _type = CCM; break;
    default: _type = LAST_VALUE; break;
    }

    if (_type == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The sample type '" << iType
               << "' is not known. Known sample types: " << lLabels;
      throw CodeConversionException (oMessage.str());
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& SampleType::getLabel (const EN_SampleType& iType) {
    return _labels[iType];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char SampleType::getTypeLabel (const EN_SampleType& iType) {
    return _typeLabels[iType];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SampleType::getTypeLabelAsString (const EN_SampleType& iType) {
    std::ostringstream oStr;
    oStr << _typeLabels[iType];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SampleType::describeLabels() {
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
  SampleType::EN_SampleType SampleType::getType() const {
    return _type;
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string SampleType::getTypeAsString() const {
    std::ostringstream oStr;
    oStr << _typeLabels[_type];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string SampleType::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_type];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool SampleType::operator== (const EN_SampleType& iType) const {
    return (_type == iType);
  }
  
}
