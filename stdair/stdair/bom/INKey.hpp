#ifndef __STDAIR_BOM_INKEY_HPP
#define __STDAIR_BOM_INKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>


namespace stdair {
  struct INKey_T : public BomKey_T {

    // /////////// Display support methods /////////
    void toStream (std::ostream& ioOut) const {
      ioOut << "INKey: " << toString() << std::endl;
    }

    void fromStream (std::istream& ioIn) {
    }

    const std::string toString() const {
      std::ostringstream oStr;
      oStr << _airlineCode;
      return oStr.str();
    }
    
    const std::string describe() const {
      return toString();
    }

  public:
    // /////////// Construction ///////////
    /** Constructors. */
    INKey_T (const AirlineCode_T& iAirlineCode) : _airlineCode (iAirlineCode) { }
    INKey_T (const INKey_T& iKey)
      : _airlineCode (iKey._airlineCode) { }
    /** Destructor. */
    ~INKey_T () { }

  private:
    // Attributes
    /** Airline code. */
    AirlineCode_T _airlineCode;

  };
}

#endif // __STDAIR_BOM_INKEY_HPP