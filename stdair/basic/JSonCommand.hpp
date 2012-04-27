#ifndef __STDAIR_BAS_JSONCOMMAND_HPP
#define __STDAIR_BAS_JSONCOMMAND_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /**
   * @brief Enumeration of json commands.
   */
  struct JSonCommand : public StructAbstract {
  public:
    typedef enum { 
      LIST = 0,
      FLIGHT_DATE,
      EVENT_LIST,
      BREAK_POINT,
      RUN,
      RESET,
      STATUS,	
      LAST_VALUE
    } EN_JSonCommand;

    /**
     * Get the command value from parsing a single char (e.g., "list", "flight_date", "event_list", "break_point", "run", "reset or "status").
     */
    static EN_JSonCommand getCommand (const std::string& iCommandStr);

    /**
     * Get a label of a command
     */
    static std::string getLabel(const EN_JSonCommand&);

    /**
     * List the labels.
     */
    static std::string describeLabels();

    /**
     * Get the enumerated value.
     */
    EN_JSonCommand getCommand() const;
    
    /**
     * Give a description of the structure (e.g., "list", "flight_date", "event_list", "break_point" "run", "reset or "status").
     */
    const std::string describe() const;

  public:
    /**
     * Comparison operator.
     */
    bool operator== (const EN_JSonCommand&) const;
    
  public:
    /**
     * Main Constructor.
     */
    JSonCommand (const EN_JSonCommand&);
    
    /**
     * Constructor.
     */
    //JSonCommand (const char);
    
    /**
     * Alternative constructor.
     */
    JSonCommand (const std::string&);
    
    /**
     * Default copy constructor.
     */
    JSonCommand (const JSonCommand&);

  private:
    /**
     * Default constructor.
     */
    JSonCommand();

    
  private:
    /**
     * String version of the enumeration.
     */    
    static const std::string _labels[LAST_VALUE];

  private:
    // //////// Attributes /////////
    /**
     * JSon command.
     */
    EN_JSonCommand _command;
  };

}
#endif // __STDAIR_BAS_JSONCOMMAND_HPP
