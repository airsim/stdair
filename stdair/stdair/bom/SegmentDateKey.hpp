#ifndef __STDAIR_BOM_SEGMENTDATEKEY_HPP
#define __STDAIR_BOM_SEGMENTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

namespace stdair {

  /** Key of segment-date. */
  struct SegmentDateKey : public KeyAbstract {

  private:
    // /////////// Default constructor //////////
    SegmentDateKey () { };
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    SegmentDateKey (const AirportCode_T&, const AirportCode_T&);
    SegmentDateKey (const SegmentDateKey&);
    /** Destructor. */
    ~SegmentDateKey ();
    
    // /////////// Getters //////////
    /** Get the boardinging point. */
    const AirportCode_T& getBoardingPoint() const {
      return _boardingPoint;
    }

    /** Get the arrival point. */
    const AirportCode_T& getOffPoint() const {
      return _offPoint;
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
    const std::string toString() const;

  private:
    // Attributes
    /** Boardinging airport. */
    AirportCode_T _boardingPoint;

    /** Arrival airport. */
    AirportCode_T _offPoint;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATEKEY_HPP
