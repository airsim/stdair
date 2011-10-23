#ifndef __STDAIR_BOM_FAREFEATURESKEY_HPP
#define __STDAIR_BOM_FAREFEATURESKEY_HPP

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
    YieldFeaturesKey (const stdair::CabinCode_T&, const stdair::Yield_T&);
    YieldFeaturesKey (const YieldFeaturesKey&);
    /** Destructor. */
    ~YieldFeaturesKey ();

    // /////////// Getters //////////

    /** Get the cabin. */
    const stdair::CabinCode_T& getCabinCode() const {
      return _cabinCode;
    }  

    /** Get the yield. */
    const stdair::Yield_T& getYield() const {
      return _yield;
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
    /** Cabin code. */
    stdair::CabinCode_T _cabinCode;
 
    /** Yield value.*/
    stdair::Yield_T _yield;

  };

}
#endif // __STDAIR_BOM_YIELDFEATURESKEY_HPP
