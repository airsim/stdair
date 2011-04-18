#ifndef __STDAIR_BOM_SNAPSHOTSTRUCT_HPP
#define __STDAIR_BOM_SNAPSHOTSTRUCT_HPP

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
#include <stdair/bom/SnapshotTypes.hpp>

namespace stdair {

  /** Structure holding the elements of a snapshot . */
  struct SnapshotStruct : public StructAbstract {
  public:
    // /////////////// Getters /////////////////
    /** Get the airline code. */
    const AirlineCode_T& getAirlineCode() const {
      return _airlineCode;
    }

    /** Get the snapshot action time. */
    const DateTime_T& getSnapshotTime() const {
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
    SnapshotStruct (const AirlineCode_T&, const DateTime_T&);

    /** Copy constructor. */
    SnapshotStruct (const SnapshotStruct&);
    
  private:
    /** Default constructor.
        <br>It is private so that it can not be used. */
    SnapshotStruct ();

  public:
    /** Destructor. */
    ~SnapshotStruct();
    

  private:
    // /////////////// Attributes /////////////////
    /** Airline code. */
    const AirlineCode_T _airlineCode;

    /** Snapshot time. */
    const DateTime_T _snapshotTime;
  };

}
#endif // __STDAIR_BOM_SNAPSHOTSTRUCT_HPP
