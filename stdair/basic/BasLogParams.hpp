#ifndef __STDAIR_BAS_BASLOGPARAMS_HPP
#define __STDAIR_BAS_BASLOGPARAMS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// Stdair
#include <stdair/stdair_log.hpp>
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /**
   * @brief Structure holding parameters for logging.
   */
  struct BasLogParams : public StructAbstract {
    friend class Logger;
  public:
    // ///////// Getters ////////
    /**
     * Get the log level.
     */
    const LOG::EN_LogLevel& getLogLevel() const {
      return _logLevel;
    }
    
    /**
     * Get the log output stream.
     */
    std::ostream& getLogStream() const {
      return _logStream;
    }
    
    /**
     * State whether or not multiple initialisations are to be forced.
     */
    const bool getForcedInitialisationFlag() const {
      return _forceMultipleInit;
    }
    
    
    // ///////// Setters //////////
    /**
     * State whether or not multiple initialisations are to be forced.
     */
    void setForcedInitialisationFlag (const bool iForceMultipleInstance) {
      _forceMultipleInit = iForceMultipleInstance;
    }
    
    
  public:
    // ///////// Busines methods ////////
    /**
     * Check that all the parameters are fine.
     */
    bool check() const;

    
  public:
    // ///////// Display methods ////////
    /**
     * Get the serialised version of the DBParams structure.
     */
    const std::string describe() const;

    /**
     * Get a short display of the LOGParams structure.
     */
    std::string toShortString() const;
    
    /**
     * Get the serialised version of the LOGParams structure.
     */
    std::string toString() const;

    
  public:
    /**
     * Main Constructor.
     *
     * @param[in] const LOG::EN_LogLevel Level of the log (e.g., DEBUG)
     * @param[in,out] std::ostream& (STL) Stream to log into.
     * @param[in] const bool Whether or not multiple initialisation
     *            should be forced.
     */
    BasLogParams (const LOG::EN_LogLevel iLogLevel,
                  std::ostream& ioLogOutputStream,
                  const bool iForceMultipleInstance = false);

    /**
     * Copy constructor.
     */
    BasLogParams (const BasLogParams&);

    /**
     * Destructor.
     */
    ~BasLogParams();

  private:
    /**
     * Default Constructor.
     */
    BasLogParams();
    
    
  private:
    // /////// Attributes /////////
    /**
     * Log level (e.g., LOG::DEBUG).
     */
    const LOG::EN_LogLevel _logLevel;

    /**
     * Log output stream (e.g., std::cout).
     */
    std::ostream& _logStream;

    /**
     * The log service must not be initialised twice, unless explicitly
     * forced to.
     *
     * As of March 2011, the only known case is when AIRINV_Service is
     * invoked from AIRINV_Master_Service. Indeed, those two should live
     * in two different processes, connected through the network (MPI).
     *
     * But, for test reason, it is easier to deploy those two services
     * within the same process. So, when testing, the same static instance
     * of the Logger service is initialised twice, once for
     * AIRINV_Master_Service, and the other one for AIRINV_Service.
     */
    bool _forceMultipleInit;
  };

}
#endif // __STDAIR_BAS_BASLOGPARAMS_HPP
