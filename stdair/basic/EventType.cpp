// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/EventType.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string EventType::_labels[LAST_VALUE] =
    { "BookingRequest", "OptimisationNotificationForFlightDate",
      "OptimisationNotificationForNetwork", "ScheduleChange", "Snapshot",
      "BreakPoint" };

  // //////////////////////////////////////////////////////////////////////
  const char EventType::
  _typeLabels[LAST_VALUE] = { 'B', 'F', 'N', 'C', 'S', 'P' };

  
  // //////////////////////////////////////////////////////////////////////
  EventType::EventType()
    : _type (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  EventType::EventType (const EventType& iEventType)
    : _type (iEventType._type) {
  }

  // //////////////////////////////////////////////////////////////////////
  EventType::EventType (const EN_EventType& iEventType)
    : _type (iEventType) {
  }

  // //////////////////////////////////////////////////////////////////////
  EventType::EventType (const char iType) {
    switch (iType) {
    case 'B': _type = BKG_REQ; break;
    case 'F': _type = OPT_NOT_4_FD; break;
    case 'N': _type = OPT_NOT_4_NET; break;
    case 'C': _type = SKD_CHG; break;
    case 'S': _type = SNAPSHOT; break;
    case 'P': _type = BRK_PT; break;
    default: _type = LAST_VALUE; break;
    }

    if (_type == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The event type '" << iType
               << "' is not known. Known event types: " << lLabels;
      throw CodeConversionException (oMessage.str());
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& EventType::getLabel (const EN_EventType& iType) {
    return _labels[iType];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char EventType::getTypeLabel (const EN_EventType& iType) {
    return _typeLabels[iType];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string EventType::getTypeLabelAsString (const EN_EventType& iType) {
    std::ostringstream oStr;
    oStr << _typeLabels[iType];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string EventType::describeLabels() {
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
  EventType::EN_EventType EventType::getType() const {
    return _type;
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string EventType::getTypeAsString() const {
    std::ostringstream oStr;
    oStr << _typeLabels[_type];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string EventType::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_type];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool EventType::operator== (const EN_EventType& iType) const {
    return (_type == iType);
  }
  
}
