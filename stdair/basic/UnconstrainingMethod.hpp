#ifndef __STDAIR_BAS_UNCONSTRAININGMETHOD_HPP
#define __STDAIR_BAS_UNCONSTRAININGMETHOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /** Enumeration of unconstraining methods. */
  struct UnconstrainingMethod : public StructAbstract {
  public:
    typedef enum { 
      TIME_FRAME = 0,
      BOOKING_CURVE,
      LAST_VALUE
    } EN_UnconstrainingMethod;

    /** Get the label as a string (e.g., "ByTimeFrame or
        "BookingCurve"). */
    static const std::string& getLabel (const EN_UnconstrainingMethod&);

    /** Get the label as a single char (e.g., 'T' or 'B'). */
    static char getMethodLabel (const EN_UnconstrainingMethod&);

    /** Get the label as a string of a single char (e.g., "T" or "B"). */
    static std::string getMethodLabelAsString (const EN_UnconstrainingMethod&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_UnconstrainingMethod getMethod() const;

    /** Get the enumerated value as a short string (e.g., "T" or "B"). */
    std::string getMethodAsString() const;
    
    /** Give a description of the structure (e.g., "ByTimeFrame" or
        "BookingCurve"). */
    const std::string describe() const;

  public:
    /** Comparison operator. */
    bool operator== (const EN_UnconstrainingMethod&) const;
    
  public:
    /** Constructor. */
    UnconstrainingMethod (const EN_UnconstrainingMethod&);
    /** Constructor. */
    UnconstrainingMethod (const char iMethod);
    /** Default copy constructor. */
    UnconstrainingMethod (const UnconstrainingMethod&);

  private:
    /** Default constructor. */
    UnconstrainingMethod();
  

  private:
    /** String version of the enumeration. */    
    static const std::string _labels[LAST_VALUE];
    /** Method version of the enumeration. */    
    static const char _methodLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /** Unconstraining method. */
    EN_UnconstrainingMethod _method;
  };

}
#endif // __STDAIR_BAS_UNCONSTRAININGMETHOD_HPP
