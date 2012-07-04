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
      Q_FORECASTING = 0,
      HYBRID_FORECASTING,
      OLD_QFF,
      NEW_QFF,
      BASED_FORECASTING,
      LAST_VALUE
    } EN_ForecastingMethod;

    /** Get the label as a string (e.g., "Q Forecasting", "Hybrid Forecasting",
        "Old QFF" or "New QFF"). */
    static const std::string& getLabel (const EN_ForecastingMethod&);

    /** Get the label as a single char (e.g., 'Q', 'H', 'O', 'N' or 'B'). */
    static char getMethodLabel (const EN_ForecastingMethod&);

    /** Get the label as a string of a single char (e.g., "Q", "H", "O", "N"
        or "B"). */
    static std::string getMethodLabelAsString (const EN_ForecastingMethod&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_ForecastingMethod getMethod() const;

    /** Get the enumerated value as a short string (e.g., "Q", "H", "O", 
        "N" or "B"). */
    std::string getMethodAsString() const;
    
    /** Give a description of the structure (e.g., "Q Forecasting",
        "Hybrid Forecasting, "Old QFF", "New QFF" or "Based Forecasting"). */
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
