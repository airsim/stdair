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
    { "list", "flight_date", "event_list", "break_point", "run", "reset", "status", "config"};

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
  JSonCommand::getCommand (const std::string& iCommandStr) {
 
    EN_JSonCommand oJSonCommand;
    if (iCommandStr == "list") {
      oJSonCommand = LIST;
    } else if (iCommandStr == "flight_date") {
      oJSonCommand = FLIGHT_DATE; 
    } else if (iCommandStr == "event_list") {
      oJSonCommand = EVENT_LIST; 
    } else if (iCommandStr == "break_point") {
      oJSonCommand = BREAK_POINT; 
    } else if (iCommandStr == "run") {
      oJSonCommand = RUN; 
    } else if (iCommandStr == "reset") {
      oJSonCommand = RESET;  
    } else if (iCommandStr == "status") {
      oJSonCommand = STATUS;  
    } else if (iCommandStr == "config") {
      oJSonCommand = CONFIG; 
    } else {
      oJSonCommand = LAST_VALUE;
    }

    if (oJSonCommand == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The JSON command '" << iCommandStr
               << "' is not known. Known forecasting commands: " << lLabels;
      throw CodeConversionException (oMessage.str());
    }

    return oJSonCommand;
  }

  // //////////////////////////////////////////////////////////////////////
  std::string JSonCommand::getLabel(const EN_JSonCommand& iCommand) {
    return _labels[iCommand];
  }
  
  // //////////////////////////////////////////////////////////////////////
  JSonCommand::JSonCommand (const std::string& iCommandStr) {
    // 
    _command = getCommand (iCommandStr);
  }

  // //////////////////////////////////////////////////////////////////////
  std::string JSonCommand::describeLabels() {
    std::ostringstream ostr;
    for (unsigned short idx = 0; idx != LAST_VALUE; ++idx) {
      if (idx != 0) {
        ostr << ", ";
      }
      ostr << _labels[idx] << " ";//'" << _commandLabels[idx] << "'";
    }
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  JSonCommand::EN_JSonCommand JSonCommand::getCommand() const {
    return _command;
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
