#ifndef __STDAIR_BOM_YIELDSTOREKEY_HPP
#define __STDAIR_BOM_YIELDSTOREKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomKey.hpp>

namespace stdair {

  /** Key of YieldStore. */
  struct YieldStoreKey_T : public BomKey_T {
    
  private:
    // /////////// Default constructor //////////
    YieldStoreKey_T () { };
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    YieldStoreKey_T (const AirlineCode_T& iAirlineCode);
    YieldStoreKey_T (const YieldStoreKey_T&);
    /** Destructor. */
    ~YieldStoreKey_T ();
    
    // /////////// Getters //////////
    /** Get the airline code. */
    const AirlineCode_T& getAirlineCode() const {
      return _airlineCode;
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
    /** Airline code. */
    AirlineCode_T _airlineCode;
  };

}
#endif // __STDAIR_BOM_YIELDSTOREKEY_HPP
