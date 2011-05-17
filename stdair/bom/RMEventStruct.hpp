#ifndef __STDAIR_BOM_RMEVENTSTRUCT_HPP
#define __STDAIR_BOM_RMEVENTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/RMEventTypes.hpp>

namespace stdair {

  /** Structure holding the elements of a snapshot . */
  struct RMEventStruct : public StructAbstract {
  public:
    // /////////////// Getters /////////////////
    /** Get the airline code. */
    const AirlineCode_T& getAirlineCode() const {
      return _airlineCode;
    }

    /** Get the string describing the flight-date key. */
    const KeyDescription_T& getFlightDateDescription() const {
      return _flightDateDescription;
    }

    /** Get the snapshot action time. */
    const DateTime_T& getRMEventTime() const {
      return _snapshotTime;
    }
    
    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;

    
    // /////////////// Constructors and Destructors /////////////////
  public:
    /** Constructor. */
    RMEventStruct (const AirlineCode_T&, const KeyDescription_T&,
                   const DateTime_T&);

    /** Copy constructor. */
    RMEventStruct (const RMEventStruct&);
    
    /** Default constructor.
        <br>It is private so that it can not be used. */
    RMEventStruct ();

  public:
    /** Destructor. */
    ~RMEventStruct();
    

  private:
    // /////////////// Attributes /////////////////
    /** Airline code. */
    const AirlineCode_T _airlineCode;

    /** Flight-date key description. */
    const KeyDescription_T _flightDateDescription;
    
    /** RMEvent time. */
    const DateTime_T _snapshotTime;
  };

}
#endif // __STDAIR_BOM_RMEVENTSTRUCT_HPP
