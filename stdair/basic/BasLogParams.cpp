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
    : _logLevel (LOG::DEBUG), _logStream (std::cout),
      _forceMultipleInit (false) {
    assert (false);
  }
  
  // //////////////////////////////////////////////////////////////////////
  BasLogParams::BasLogParams (const BasLogParams& iLogParams)
    : _logLevel (iLogParams._logLevel), _logStream (iLogParams._logStream),
      _forceMultipleInit (iLogParams._forceMultipleInit) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BasLogParams::BasLogParams (const LOG::EN_LogLevel iLogLevel,
                              std::ostream& ioLogOutputStream,
                              const bool iForceMultipleInstance)
    : _logLevel (iLogLevel), _logStream (ioLogOutputStream),
      _forceMultipleInit (iForceMultipleInstance) {
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
    const std::string isForcedStr = (_forceMultipleInit == true)?" (forced)":"";
    std::ostringstream oStr;
    oStr << LOG::_logLevels[_logLevel] << isForcedStr;
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  std::string BasLogParams::toString() const {
    std::ostringstream oStr;
    oStr << LOG::_logLevels[_logLevel];
    return oStr.str();
  }
    
}
