// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/service/Logger.hpp>
// Stdair
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/PassengerType.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PassengerType::_labels[LAST_VALUE] =
    { "Leisure", "Business", "First" };

  const char PassengerType::_typeLabels[LAST_VALUE] = { 'L', 'B', 'F' };

  
  // //////////////////////////////////////////////////////////////////////
  PassengerType::PassengerType (const EN_PassengerType& iPassengerType)
    : _type (iPassengerType) {
  }

  // //////////////////////////////////////////////////////////////////////
  PassengerType::PassengerType (const char iType) {
    switch (iType) {
    case 'L': _type = LEISURE; break;
    case 'B': _type = BUSINESS; break;
    case 'F': _type = FIRST; break;
    default: _type = LAST_VALUE; break;
    }

    if (_type == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      STDAIR_LOG_ERROR ("The passenger type '" << iType
                        << "' is not known. Known passenger types: " << lLabels);
      throw CodeConversionException();
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& PassengerType::getLabel (const EN_PassengerType& iType) {
    return _labels[iType];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char PassengerType::getTypeLabel(const EN_PassengerType& iType) {
    return _typeLabels[iType];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string PassengerType::describeLabels() {
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
  PassengerType::EN_PassengerType PassengerType::getType() const {
    return _type;
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PassengerType::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_type];
    return ostr.str();
  }

}
