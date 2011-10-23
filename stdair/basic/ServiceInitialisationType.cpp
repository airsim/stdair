// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/ServiceInitialisationType.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string ServiceInitialisationType::_labels[LAST_VALUE] =
    { "Not yet initialised", "File parsing",  "Built-in sample BOM" };

  // //////////////////////////////////////////////////////////////////////
  const char ServiceInitialisationType::_typeLabels[LAST_VALUE] =
    { 'N', 'F', 'B' };

  
  // //////////////////////////////////////////////////////////////////////
  ServiceInitialisationType::ServiceInitialisationType()
    : _type (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  ServiceInitialisationType::
  ServiceInitialisationType (const ServiceInitialisationType& iServiceInitialisationType)
    : _type (iServiceInitialisationType._type) {
  }

  // //////////////////////////////////////////////////////////////////////
  ServiceInitialisationType::
  ServiceInitialisationType (const EN_ServiceInitialisationType& iServiceInitialisationType)
    : _type (iServiceInitialisationType) {
  }

  // //////////////////////////////////////////////////////////////////////
  ServiceInitialisationType::EN_ServiceInitialisationType
  ServiceInitialisationType::getType (const char iTypeChar) {
    EN_ServiceInitialisationType oType;
    switch (iTypeChar) {
    case 'N': oType = NOT_YET_INITIALISED; break;
    case 'F': oType = FILE_PARSING; break;
    case 'B': oType = BUILTIN_SAMPLE; break;
    default: oType = LAST_VALUE; break;
    }

    if (oType == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The service initialisation type '" << iTypeChar
               << "' is not known. "
               << "Known service initialisation types: " << lLabels;
      throw CodeConversionException (oMessage.str());
    }

    return oType;
  }
  
  // //////////////////////////////////////////////////////////////////////
  ServiceInitialisationType::
  ServiceInitialisationType (const char iTypeChar)
    : _type (getType (iTypeChar)) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  ServiceInitialisationType::
  ServiceInitialisationType (const std::string& iTypeStr) {
    // 
    const size_t lSize = iTypeStr.size();
    assert (lSize == 1);
    const char lTypeChar = iTypeStr[0];
    _type = getType (lTypeChar);
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& ServiceInitialisationType::
  getLabel (const EN_ServiceInitialisationType& iType) {
    return _labels[iType];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char ServiceInitialisationType::
  getTypeLabel (const EN_ServiceInitialisationType& iType) {
    return _typeLabels[iType];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string ServiceInitialisationType::
  getTypeLabelAsString (const EN_ServiceInitialisationType& iType) {
    std::ostringstream oStr;
    oStr << _typeLabels[iType];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string ServiceInitialisationType::describeLabels() {
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
  ServiceInitialisationType::EN_ServiceInitialisationType
  ServiceInitialisationType::getType() const {
    return _type;
  }
  
  // //////////////////////////////////////////////////////////////////////
  char ServiceInitialisationType::getTypeAsChar() const {
    const char oTypeChar = _typeLabels[_type];
    return oTypeChar;
  }

  // //////////////////////////////////////////////////////////////////////
  std::string ServiceInitialisationType::getTypeAsString() const {
    std::ostringstream oStr;
    oStr << _typeLabels[_type];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string ServiceInitialisationType::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_type];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool ServiceInitialisationType::
  operator== (const EN_ServiceInitialisationType& iType) const {
    return (_type == iType);
  }
  
}
