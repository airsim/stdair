#ifndef __STDAIR_BOM_FLIGHTDATEKEY_HPP
#define __STDAIR_BOM_FLIGHTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace stdair {
  /** Key of flight-date. */
  struct FlightDateKey_T : public BomKey_T {

  public:
    // /////////// Construction ///////////
    /** Constructor. */
    FlightDateKey_T (const FlightNumber_T&, const Date_T&);

    /** Destructor. */
    ~FlightDateKey_T ();
    
    // /////////// Getters //////////
    /** Get the flight number. */
    const FlightNumber_T& getFlightNumber() const {
      return _flightNumber;
    }

    /** Get the departure date of the (first leg of the) flight. */
    const Date_T& getFlightDate() const {
      return _flightDate;
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
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-date. */
    std::string toString() const;
    
  private:
    // Attributes
    /** Flight number. */
    FlightNumber_T _flightNumber;

    /** Departure date of the (first leg of the) flight. */
    Date_T _flightDate;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATEKEY_HPP
