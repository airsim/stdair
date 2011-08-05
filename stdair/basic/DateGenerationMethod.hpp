#ifndef __STDAIR_BAS_DATEGENERATIONMETHOD_HPP
#define __STDAIR_BAS_DATEGENERATIONMETHOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /** Enumeration of Date-time booking request generation methods. */
  struct DateGenerationMethod : public StructAbstract {
  public:
    typedef enum {
      POI_PRO = 0,
      STA_ORD,
      LAST_VALUE
    } EN_DateGenerationMethod;

    /** Get the label as a string (e.g., "PoissonProcess" or
        "SatisticsOrder"). */
    static const std::string& getLabel (const EN_DateGenerationMethod&);

    /** Get the label as a single char (e.g., 'P' or 'S'). */
    static char getMethodLabel (const EN_DateGenerationMethod&);

    /** Get the label as a string of a single char (e.g., "P" or "S"). */
    static std::string getMethodLabelAsString (const EN_DateGenerationMethod&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_DateGenerationMethod getMethod() const;

    /** Get the enumerated value as a short string (e.g., "P" or "S"). */
    std::string getMethodAsString() const;
    
    /** Give a description of the structure (e.g., "PoissonProcess" or
        "SatisticsOrder"). */
    const std::string describe() const;

  public:
    /** Comparison operator. */
    bool operator== (const EN_DateGenerationMethod&) const;
    
  public:
    /** Constructor. */
    DateGenerationMethod (const EN_DateGenerationMethod&);
    /** Constructor. */
    DateGenerationMethod (const char iMethod);
    /** Default copy constructor. */
    DateGenerationMethod (const DateGenerationMethod&);

  private:
    /** Default constructor. */
    DateGenerationMethod();
  

  private:
    /** String version of the enumeration. */    
    static const std::string _labels[LAST_VALUE];
    /** Method version of the enumeration. */    
    static const char _methodLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /** DateGeneration method. */
    EN_DateGenerationMethod _method;
  };

}
#endif // __STDAIR_BAS_DATEGENERATIONMETHOD_HPP
