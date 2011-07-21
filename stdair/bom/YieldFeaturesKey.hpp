#ifndef __STDAIR_BOM_YIELDFEATURESKEY_HPP
#define __STDAIR_BOM_YIELDFEATURESKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/KeyAbstract.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/stdair_inventory_types.hpp>

namespace stdair  {
  /** Key of date-period. */
  struct YieldFeaturesKey : public KeyAbstract {

  public:
    // /////////// Construction ///////////
    /** Constructors. */
    YieldFeaturesKey (const stdair::TripType_T&,
                      const stdair::CabinCode_T&);
    YieldFeaturesKey (const YieldFeaturesKey&);
    /** Destructor. */
    ~YieldFeaturesKey ();

    // /////////// Getters //////////
    /** Get the fare trip type. */
    const TripType_T& getTripType() const {
      return _tripType;
    }

    /** Get the cabin. */
    const stdair::CabinCode_T& getCabinCode() const {
      return _cabinCode;
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
    
    /** Type of trip type (RT=round-trip, OW=one way). */
    TripType_T _tripType;
    
    /** Cabin code. */
    stdair::CabinCode_T _cabinCode;

  };

}
#endif // __STDAIR_BOM_YIELDFEATURESKEY_HPP
