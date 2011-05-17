// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// StdAir Logger
#include <stdair/stdair_exceptions.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  Logger::Logger()
    : _level (LOG::DEBUG), _logStream (&std::cout),
      _hasBeenInitialised (false) {
  }

  // //////////////////////////////////////////////////////////////////////
  Logger::Logger (const Logger&)
    : _level (LOG::DEBUG), _logStream (&std::cout),
      _hasBeenInitialised (false) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  Logger::~Logger() {
    // std::cout << "In Logger destructor" << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void Logger::init (const BasLogParams& iLogParams) {

    //
    Logger& lInstance = instance();
    const bool hasBeenInitialised = lInstance.getStatus();
    if (hasBeenInitialised == true
        && iLogParams.getForcedInitialisationFlag() == false) {
      STDAIR_LOG_ERROR ("Error: the log stream has already been initialised");
      assert (false);
    }

    lInstance.setLevel (iLogParams._logLevel);
    lInstance.setStream (iLogParams._logStream);
    lInstance.setStatus (true);
  }

  // //////////////////////////////////////////////////////////////////////
  Logger& Logger::instance() {
    static Logger _instance;
    return _instance;
  }
  
  // //////////////////////////////////////////////////////////////////////
  BasLogParams Logger::getLogParams() {
    std::ostream* oStream_ptr = instance()._logStream;
    assert (oStream_ptr != NULL);
    return BasLogParams (instance()._level, *oStream_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  void Logger::clean() {
    Logger& lInstance = instance();
    lInstance.setStatus (false);
  }
  
}
