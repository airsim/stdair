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
   * Structure holding parameters for logging.
   */
  struct BasLogParams : public StructAbstract {
    friend class Logger;
  public:
    // ///////// Getters ////////
    /** Get the log level. */
    const LOG::EN_LogLevel& getLogLevel() const {
      return _logLevel;
    }
    
    /** Get the log output stream. */
    std::ostream& getLogStream() const {
      return _logStream;
    }
    
    
    // ///////// Setters //////////
    // No setters
    
    
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
     */
    BasLogParams (const LOG::EN_LogLevel iLogLevel,
                  std::ostream& ioLogOutputStream);

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
    /** Log level (e.g., LOG::DEBUG). */
    const LOG::EN_LogLevel _logLevel;

    /** Log output stream (e.g., std::cout). */
    std::ostream& _logStream;
  };

}
#endif // __STDAIR_BAS_BASLOGPARAMS_HPP
