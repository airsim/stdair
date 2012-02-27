// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/JSonCommand.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string JSonCommand::_labels[LAST_VALUE] =
    { "list", "flight_date", "event_list"};

  // //////////////////////////////////////////////////////////////////////
  const char JSonCommand::_commandLabels[LAST_VALUE] = { 'l', 'f', 'e' };

  // //////////////////////////////////////////////////////////////////////
  JSonCommand::JSonCommand()
    : _command (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  JSonCommand::
  JSonCommand (const JSonCommand& iJSonCommand)
    : _command (iJSonCommand._command) {
  }

  // //////////////////////////////////////////////////////////////////////
  JSonCommand::EN_JSonCommand
  JSonCommand::getCommand (const char iCommandChar) {
 
    EN_JSonCommand oJSonCommand;
    switch (iCommandChar) {
    case 'l': oJSonCommand = LIST; break;
    case 'f': oJSonCommand = FLIGHT_DATE; break;
    case 'e': oJSonCommand = EVENT_LIST; break;
    default: oJSonCommand = LAST_VALUE; break;
    }

    if (oJSonCommand == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The JSON command '" << iCommandChar
               << "' is not known. Known forecasting commands: " << lLabels;
      throw CodeConversionException (oMessage.str());
    }

    return oJSonCommand;
  }

  
  // //////////////////////////////////////////////////////////////////////
  JSonCommand::JSonCommand (const char iCommandChar) 
    : _command (getCommand (iCommandChar)) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  JSonCommand::JSonCommand (const std::string& iCommandStr) {
    // 
    const size_t lSize = iCommandStr.size();
    assert (lSize == 1);
    const char lCommandChar = iCommandStr[0];
    _command = getCommand (lCommandChar);
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string& JSonCommand::
  getLabel (const EN_JSonCommand& iCommand) {
    return _labels[iCommand];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char JSonCommand::getCommandLabel (const EN_JSonCommand& iCommand) {
    return _commandLabels[iCommand];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string JSonCommand::
  getCommandLabelAsString (const EN_JSonCommand& iCommand) {
    std::ostringstream oStr;
    oStr << _commandLabels[iCommand];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string JSonCommand::describeLabels() {
    std::ostringstream ostr;
    for (unsigned short idx = 0; idx != LAST_VALUE; ++idx) {
      if (idx != 0) {
        ostr << ", ";
      }
      ostr << _labels[idx] << " '" << _commandLabels[idx] << "'";
    }
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  JSonCommand::EN_JSonCommand JSonCommand::getCommand() const {
    return _command;
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string JSonCommand::getCommandAsString() const {
    std::ostringstream oStr;
    oStr << _commandLabels[_command];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  char JSonCommand::getCommandAsChar() const {
    const char oCommandChar = _commandLabels[_command];
    return oCommandChar;
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string JSonCommand::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_command];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool JSonCommand::
  operator== (const EN_JSonCommand& iCommand) const {
    return (_command == iCommand);
  }
  
}
