#ifndef __STDAIR_BAS_FORECASTINGMETHOD_HPP
#define __STDAIR_BAS_FORECASTINGMETHOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /** Enumeration of forecasting methods. */
  struct ForecastingMethod : public StructAbstract {
  public:
    typedef enum { 
      ADD_PK = 0,
      MUL_PK,
      LAST_VALUE
    } EN_ForecastingMethod;

    /** Get the label as a string (e.g., "BookingRequest" or
        "ScheduleChange"). */
    static const std::string& getLabel (const EN_ForecastingMethod&);

    /** Get the label as a single char (e.g., 'B' or 'S'). */
    static char getMethodLabel (const EN_ForecastingMethod&);

    /** Get the label as a string of a single char (e.g., "B" or "S"). */
    static std::string getMethodLabelAsString (const EN_ForecastingMethod&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_ForecastingMethod getMethod() const;

    /** Get the enumerated value as a short string (e.g., "B" or "S"). */
    std::string getMethodAsString() const;
    
    /** Give a description of the structure (e.g., "BookingRequest" or
        "ScheduleChange"). */
    const std::string describe() const;

  public:
    /** Comparison operator. */
    bool operator== (const EN_ForecastingMethod&) const;
    
  public:
    /** Constructor. */
    ForecastingMethod (const EN_ForecastingMethod&);
    /** Constructor. */
    ForecastingMethod (const char iMethod);
    /** Default copy constructor. */
    ForecastingMethod (const ForecastingMethod&);

  private:
    /** Default constructor. */
    ForecastingMethod();
  

  private:
    /** String version of the enumeration. */    
    static const std::string _labels[LAST_VALUE];
    /** Method version of the enumeration. */    
    static const char _methodLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /** Forecasting method. */
    EN_ForecastingMethod _method;
  };

}
#endif // __STDAIR_BAS_FORECASTINGMETHOD_HPP
