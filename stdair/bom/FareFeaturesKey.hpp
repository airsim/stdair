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
  struct FareFeaturesKey : public KeyAbstract {

  public:
    // /////////// Construction ///////////
    /** Constructors. */
    FareFeaturesKey (const TripType_T&, const DayDuration_T&,
                     const SaturdayStay_T&, const ChangeFees_T&,
                     const NonRefundable_T&, const DayDuration_T&);
    FareFeaturesKey (const FareFeaturesKey&);
    /** Destructor. */
    ~FareFeaturesKey ();

    // /////////// Getters //////////
    /** Get the fare trip type. */
    const TripType_T& getTripType() const {
      return _tripType;
    }

    /** Get the fare day duration. */
    const DayDuration_T& getAdvancePurchase() const {
      return _advancePurchase;
    }

    /** Get the fare saturday stay option. */
    const SaturdayStay_T& getSaturdayStay() const {
      return _saturdayStay;
    }   

    /** Get the change fees criterion. */
    const ChangeFees_T& getChangeFees() const {
      return _changeFees;
    }

    /** Get the refundable option. */
    const NonRefundable_T& getRefundableOption() const {
      return _nonRefundable;
    }

    /** Get the minimum stay. */
    const DayDuration_T& getMinimumStay() const {
      return _minimumStay;
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
    
    /** Number of days that the ticket is sold before the
	flightDate.*/
    DayDuration_T _advancePurchase;
     
    /** Boolean saying whether a saturday is considered
	during the stay .*/
    SaturdayStay_T _saturdayStay;
    
    /** Boolean saying whether the change fees option is
	requested or not.*/
    ChangeFees_T _changeFees;

    /** Boolean saying whether the refundable option is
	requested or not.*/
    NonRefundable_T _nonRefundable;
     
    /** Number of days that the customer spent
	into the destination city.*/
    DayDuration_T _minimumStay;

  };

}
#endif // __STDAIR_BOM_FAREFEATURESKEY_HPP
