#ifndef __STDAIR_BAS_PREOPTIMISATIONMETHOD_HPP
#define __STDAIR_BAS_PREOPTIMISATIONMETHOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /** Enumeration of PreOptimisation methods. */
  struct PreOptimisationMethod : public StructAbstract {
  public:
    typedef enum {
      NONE = 0,
      FA,
      MRT,
      LAST_VALUE
    } EN_PreOptimisationMethod;

    /** Get the label as a string (e.g., MRT or FA). */
    static const std::string& getLabel (const EN_PreOptimisationMethod&);

    /** Get the label as a single char (e.g., 'M' or 'E'). */
    static char getMethodLabel (const EN_PreOptimisationMethod&);

    /** Get the label as a string of a single char (e.g., "M" or "E"). */
    static std::string getMethodLabelAsString (const EN_PreOptimisationMethod&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_PreOptimisationMethod getMethod() const;

    /** Get the enumerated value as a short string (e.g., "M" or "E"). */
    std::string getMethodAsString() const;
    
    /** Give a description of the structure (e.g., MRT or FA). */
    const std::string describe() const;

  public:
    /** Comparaison operator. */
    bool operator== (const EN_PreOptimisationMethod&) const;
    
  public:
    /** Constructor. */
    PreOptimisationMethod (const EN_PreOptimisationMethod&);
    /** Constructor. */
    PreOptimisationMethod (const char iMethod);
    /** Default copy constructor. */
    PreOptimisationMethod (const PreOptimisationMethod&);

  private:
    /** Default constructor. */
    PreOptimisationMethod();
  

  private:
    /** String version of the enumeration. */    
    static const std::string _labels[LAST_VALUE];
    /** Method version of the enumeration. */    
    static const char _methodLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /** PreOptimisation Method. */
    EN_PreOptimisationMethod _method;
  };

}
#endif // __STDAIR_BAS_PREOPTIMISATIONMETHOD_HPP
