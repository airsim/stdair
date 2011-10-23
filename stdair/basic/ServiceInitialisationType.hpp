#ifndef __STDAIR_BAS_SERVICEINITIALISATIONTYPE_HPP
#define __STDAIR_BAS_SERVICEINITIALISATIONTYPE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /**
   * @brief Enumeration of service initialisation types.
   */
  struct ServiceInitialisationType : public StructAbstract {
  public:
    typedef enum {
      NOT_YET_INITIALISED = 0,
      FILE_PARSING,
      BUILTIN_SAMPLE,
      LAST_VALUE
    } EN_ServiceInitialisationType;

    /**
     * Get the label as a string (e.g., "Not yet initialised", "File parsing"
     * or "Built-in sample BOM").
     */
    static const std::string& getLabel (const EN_ServiceInitialisationType&);

    /**
     * Get the type value from parsing a single char (e.g., 'N', 'F', 'B').
     */
    static EN_ServiceInitialisationType getType (const char);

    /**
     * Get the label as a single char (e.g., 'N', 'F', 'B').
     */
    static char getTypeLabel (const EN_ServiceInitialisationType&);

    /**
     * Get the label as a string of a single char (e.g., "N", "F", "B").
     */
    static std::string
    getTypeLabelAsString (const EN_ServiceInitialisationType&);

    /**
     * List the labels.
     */
    static std::string describeLabels();

    /**
     * Get the enumerated value.
     */
    EN_ServiceInitialisationType getType() const;

    /**
     * Get the enumerated value as a short string (e.g., 'N', 'F', 'B').
     */
    char getTypeAsChar() const;
    
    /**
     * Get the enumerated value as a short string (e.g., "N", "F", "B").
     */
    std::string getTypeAsString() const;
    
    /**
     * Give a description of the structure (e.g., "Not yet initialised", "File
     * parsing" or "Built-in sample BOM").
     */
    const std::string describe() const;

  public:
    /**
     * Comparison operator.
     */
    bool operator== (const EN_ServiceInitialisationType&) const;
    
  public:
    /**
     * Main constructor.
     */
    ServiceInitialisationType (const EN_ServiceInitialisationType&);
    /**
     * Alternative constructor.
     */
    ServiceInitialisationType (const char iType);
    /**
     * Alternative constructor.
     */
    ServiceInitialisationType (const std::string& iType);
    /**
     * Default copy constructor.
     */
    ServiceInitialisationType (const ServiceInitialisationType&);

  private:
    /**
     * Default constructor.
     */
    ServiceInitialisationType();


  private:
    /**
     * String version of the enumeration.
     */
    static const std::string _labels[LAST_VALUE];
    /**
     * Type version of the enumeration.
     */
    static const char _typeLabels[LAST_VALUE];

  private:
    // //////// Attributes /////////
    /**
     * ServiceInitialisation type.
     */
    EN_ServiceInitialisationType _type;
  };

}
#endif // __STDAIR_BAS_SERVICEINITIALISATIONTYPE_HPP
