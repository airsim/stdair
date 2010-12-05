#ifndef __STDAIR_BOM_REACHABLEUNIVERSEKEY_HPP
#define __STDAIR_BOM_REACHABLEUNIVERSEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomKey.hpp>

namespace stdair {
  /** Key of airport-date. */
  struct ReachableUniverseKey_T : public BomKey_T {

  private:
    // /////////// Default constructor //////////
    ReachableUniverseKey_T ();
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    ReachableUniverseKey_T (const AirportCode_T& iAirportCode);
    ReachableUniverseKey_T (const ReachableUniverseKey_T&);
    /** Destructor. */
    ~ReachableUniverseKey_T ();
    
    // /////////// Getters //////////
    /** Get boarding airport. */
    const AirportCode_T& getBoardingPoint() const {
      return _origin;
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
    /** The boarding airport. */
    AirportCode_T _origin;
  };

}

#endif // __STDAIR_BOM_REACHABLEUNIVERSEKEY_HPP