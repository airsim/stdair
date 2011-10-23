#ifndef __STDAIR_BOM_TIMEPERIODKEY_HPP
#define __STDAIR_BOM_TIMEPERIODKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/KeyAbstract.hpp>
#include <stdair/stdair_date_time_types.hpp>

namespace stdair {
  /** Key of time-period. */
  struct TimePeriodKey : public KeyAbstract {

  public:
    // /////////// Construction ///////////
    /** Constructors. */
    TimePeriodKey (const Time_T&,
                   const Time_T&);
    TimePeriodKey (const TimePeriodKey&);
    /** Destructor. */
    ~TimePeriodKey ();
    
    // /////////// Getter //////////
    /** Get the time period. */
    const Time_T& getTimeRangeStart() const {
      return _timeRangeStart;
    }

    /** Get the time period. */
    const Time_T& getTimeRangeEnd() const {
      return _timeRangeEnd;
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
    /** Fare time range start */
    Time_T _timeRangeStart;

    /** Fare time range end */
    Time_T _timeRangeEnd;

  };

}
#endif // __STDAIR_BOM_TIMEPERIODKEY_HPP
