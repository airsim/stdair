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
      LAST_VALUE
    } EN_JSonCommand;

    /**
     * Get the label as a string (e.g., "list" or "flight_date").
     */
    static const std::string& getLabel (const EN_JSonCommand&);

    /**
     * Get the command value from parsing a single char (e.g., 'l' or 'f').
     */
    static EN_JSonCommand getCommand (const char);

    /**
     * Get the label as a single char (e.g., 'l' or 'f').
     */
    static char getCommandLabel (const EN_JSonCommand&);

    /**
     * Get the label as a string of a single char (e.g., "l" or "f").
     */
    static std::string getCommandLabelAsString (const EN_JSonCommand&);

    /**
     * List the labels.
     */
    static std::string describeLabels();

    /**
     * Get the enumerated value.
     */
    EN_JSonCommand getCommand() const;

    /**
     * Get the enumerated value as a char (e.g., 'l' or 'f').
     */
    char getCommandAsChar() const;

    /**
     * Get the enumerated value as a short string (e.g., "l" or "f").
     */
    std::string getCommandAsString() const;
    
    /**
     * Give a description of the structure (e.g., "list" or "flight_date").
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
    JSonCommand (const char);
    
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
    
    /**
     * Method version of the enumeration.
     */    
    static const char _commandLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /**
     * JSon command.
     */
    EN_JSonCommand _command;
  };

}
#endif // __STDAIR_BAS_JSONCOMMAND_HPP
