#ifndef __SIMFQT_BOM_DATEPERIODKEY_HPP
#define __SIMFQT_BOM_DATEPERIODKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/KeyAbstract.hpp>
#include <stdair/stdair_date_time_types.hpp>

namespace stdair  {
  /** Key of date-period. */
  struct DatePeriodKey : public KeyAbstract {

  public:
    // /////////// Construction ///////////
    /** Constructors. */
    DatePeriodKey (const DatePeriod_T&);
    DatePeriodKey (const DatePeriodKey&);
    /** Destructor. */
    ~DatePeriodKey ();
    
    // /////////// Getter //////////
    /** Get the date period. */
    const DatePeriod_T& getDatePeriod() const {
      return _datePeriod;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object. */
    const std::string toString() const;

  private:
    // Attributes
    /** Fare date period */
    DatePeriod_T _datePeriod;

  };

}
#endif // __SIMFQT_BOM_DATEPERIODKEY_HPP
