#ifndef __STDAIR_BAS_DEMANDGENERATIONMETHOD_HPP
#define __STDAIR_BAS_DEMANDGENERATIONMETHOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /**
   * @brief Enumeration of demand (booking request) generation methods.
   */
  struct DemandGenerationMethod : public StructAbstract {
  public:
    typedef enum {
      POI_PRO = 0,
      STA_ORD,
      LAST_VALUE
    } EN_DemandGenerationMethod;

    /**
     * Get the label as a string (e.g., "PoissonProcess" or "StatisticsOrder").
     */
    static const std::string& getLabel (const EN_DemandGenerationMethod&);

    /**
     * Get the method value from parsing a single char (e.g., 'P' or 'S').
     */
    static EN_DemandGenerationMethod getMethod (const char);

    /**
     * Get the label as a single char (e.g., 'P' or 'S').
     */
    static char getMethodLabel (const EN_DemandGenerationMethod&);

    /**
     * Get the label as a string of a single char (e.g., "P" or "S").
     */
    static std::string getMethodLabelAsString (const EN_DemandGenerationMethod&);

    /**
     * List the labels.
     */
    static std::string describeLabels();

    /**
     * Get the enumerated value.
     */
    EN_DemandGenerationMethod getMethod() const;

    /**
     * Get the enumerated value as a short string (e.g., 'P' or 'S').
     */
    char getMethodAsChar() const;
    
    /**
     * Get the enumerated value as a short string (e.g., "P" or "S").
     */
    std::string getMethodAsString() const;
    
    /**
     * Give a description of the structure (e.g., "PoissonProcess" or
     * "SatisticsOrder").
     */
    const std::string describe() const;

  public:
    /**
     * Comparison operator.
     */
    bool operator== (const EN_DemandGenerationMethod&) const;
    
  public:
    /**
     * Main constructor.
     */
    DemandGenerationMethod (const EN_DemandGenerationMethod&);
    /**
     * Alternative constructor.
     */
    DemandGenerationMethod (const char iMethod);
    /**
     * Alternative constructor.
     */
    DemandGenerationMethod (const std::string& iMethod);
    /**
     * Default copy constructor.
     */
    DemandGenerationMethod (const DemandGenerationMethod&);

  private:
    /**
     * Default constructor.
     */
    DemandGenerationMethod();


  private:
    /**
     * String version of the enumeration.
     */
    static const std::string _labels[LAST_VALUE];
    /**
     * Method version of the enumeration.
     */
    static const char _methodLabels[LAST_VALUE];

  private:
    // //////// Attributes /////////
    /**
     * DemandGeneration method.
     */
    EN_DemandGenerationMethod _method;
  };

}
#endif // __STDAIR_BAS_DEMANDGENERATIONMETHOD_HPP
