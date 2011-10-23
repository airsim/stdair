#ifndef __STDAIR_BOM_AIRPORTPAIRKEY_HPP
#define __STDAIR_BOM_AIRPORTPAIRKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/KeyAbstract.hpp>
#include <stdair/stdair_basic_types.hpp>

namespace stdair  {
  /** Key of airport-pair. */
  struct AirportPairKey : public KeyAbstract {

  private:
    // /////////// Default constructor //////////
    AirportPairKey () { };
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    AirportPairKey (const stdair::AirportCode_T&, const stdair::AirportCode_T&);
    AirportPairKey (const AirportPairKey&);
    /** Destructor. */
    ~AirportPairKey ();
    
    // /////////// Getters //////////
    /** Get the boarding point. */
    const stdair::AirportCode_T& getBoardingPoint() const {
      return _boardingPoint;
    }

    /** Get the arrival point. */
    const stdair::AirportCode_T& getOffPoint() const {
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
       when among children of a given parent Business Object. */
    const std::string toString() const;

  private:
    // Attributes
    /** Boarding airport. */
    AirportCode_T _boardingPoint;

    /** Arrival airport. */
    AirportCode_T _offPoint;
  };

}
#endif // __SIMFQT_BOM_AIRPORTPAIRKEY_HPP
