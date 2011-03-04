// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <sstream>
// StdAir
#include <stdair/basic/BasLogParams.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  BasLogParams::BasLogParams()
    : _logLevel (LOG::DEBUG), _logStream (std::cout) {
    assert (false);
  }
  
  // //////////////////////////////////////////////////////////////////////
  BasLogParams::BasLogParams (const BasLogParams& iLogParams)
    : _logLevel (iLogParams._logLevel), _logStream (iLogParams._logStream) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BasLogParams::BasLogParams (const LOG::EN_LogLevel iLogLevel,
                              std::ostream& ioLogOutputStream)
    : _logLevel (iLogLevel), _logStream (ioLogOutputStream) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BasLogParams::~BasLogParams() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string BasLogParams::describe() const {
    return toString();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string BasLogParams::toShortString() const {
    std::ostringstream oStr;
    oStr << LOG::_logLevels[_logLevel];
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  std::string BasLogParams::toString() const {
    std::ostringstream oStr;
    oStr << LOG::_logLevels[_logLevel];
    return oStr.str();
  }
    
}
