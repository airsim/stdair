#ifndef __STDAIR_SVC_LOGGER_HPP
#define __STDAIR_SVC_LOGGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#include <string>
// StdAir
#include <stdair/stdair_log.hpp>
#include <stdair/basic/BasLogParams.hpp>

// /////////////// LOG MACROS /////////////////
#define STDAIR_LOG_CORE(iLevel, iToBeLogged) \
  { std::ostringstream ostr; ostr << iToBeLogged; \
    stdair::Logger::instance().log (iLevel, __LINE__, __FILE__, ostr.str()); }

#define STDAIR_LOG_CRITICAL(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::CRITICAL, iToBeLogged)

#define STDAIR_LOG_ERROR(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::ERROR, iToBeLogged)

#define STDAIR_LOG_NOTIFICATION(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::NOTIFICATION, iToBeLogged)

#define STDAIR_LOG_WARNING(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::WARNING, iToBeLogged)

#define STDAIR_LOG_DEBUG(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::DEBUG, iToBeLogged)

#define STDAIR_LOG_VERBOSE(iToBeLogged) \
  STDAIR_LOG_CORE (stdair::LOG::VERBOSE, iToBeLogged)
// /////////// (END OF) LOG MACROS /////////////


namespace stdair {

  /**
   * Class holding the stream for logs.
   *
   * Note that the error logs are seen as standard output logs, 
   * but with a higher level of visibility.
   */
  class Logger {
    /// Friend classes
    friend class FacSupervisor;
    friend class STDAIR_Service;

  public:
    
    /**
     * Main log entry.
     */
    template <typename T>
    void log (const LOG::EN_LogLevel iLevel, const int iLineNumber,
              const std::string& iFileName, const T& iToBeLogged) {
      assert (_logStream != NULL);
      if (iLevel <= _level) {
        *_logStream << "[" << LOG::_logLevels[iLevel] << "]" << iFileName << ":"
                    << iLineNumber << ": " << iToBeLogged << std::endl;
      }
    }
    
    /**
     * Return the static Logger instance.
     */
    static Logger& instance();
    

  private:
    // /////////////////// Initialisation and finalisation ////////////////
    /**
     * Record the fact that the static instance has been initialised.
     */
    bool getStatus() const {
      return _hasBeenInitialised;
    }

    /**
     * Set the log level (e.g., Debug, Notification, Error, etc.).
     */
    void setLevel (const LOG::EN_LogLevel& iLevel) {
      _level = iLevel;
    }

    /**
     * Set the log stream (e.g., a file or std::cout).
     */
    void setStream (std::ostream& ioStream) {
      _logStream = &ioStream;
    }

    /**
     * Record the fact that the static instance has been initialised.
     */
    void setStatus (const bool iStatus) {
      _hasBeenInitialised = iStatus;
    }

    /**
     * Default constructors are private so that only the required 
     * constructor can be used.
     */
    Logger();
    /**
     * Default copy constructor. It must not be used.
     */
    Logger (const Logger&);
    /**
     * Destructor.
     */
    ~Logger();

    /**
     * Initialise the static Logger instance.
     *
     * @param const BasLogParams&
     */
    static void init (const BasLogParams&);

    /**
     * Get the log parameters.
     */
    static BasLogParams getLogParams();

    /**
     * Delete the static Logger instance.
     */
    static void clean();


  private:
    // /////////////////// Attributes ////////////////
    /**
     * Log level.
     */
    LOG::EN_LogLevel _level;
    
    /**
     * Stream dedicated to the logs.
     */
    std::ostream* _logStream;

    /**
     * State whether the Logger instance has alredy been initialised.
     */
    bool _hasBeenInitialised;
  };
  
}
#endif // __STDAIR_SVC_LOGGER_HPP

