#ifndef __STDAIR_BOM_OPTIMISATIONNOTIFICATIONSTRUCT_HPP
#define __STDAIR_BOM_OPTIMISATIONNOTIFICATIONSTRUCT_HPP

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
#include <stdair/bom/OptimisationNotificationTypes.hpp>

namespace stdair {

  /** Structure holding the elements of a optimisation notification. */
  struct OptimisationNotificationStruct : public StructAbstract {
  public:
    // /////////////// Getters /////////////////
    /** Get the notificationed origin. */
    const AirportCode_T& getOrigin() const {
      return _origin;
    }

    /** Get the notificationed destination. */
    const AirportCode_T& getDestination() const {
      return _destination;
    }

    /** Get the point-of-sale. */
    const CityCode_T& getPOS() const {
      return _pos;
    }

    /** Get the notificationed departure date. */
    const Date_T& getPreferedDepartureDate() const {
      return _preferredDepartureDate;
    }

    /** Get the notification datetime. */
    const DateTime_T& getNotificationDateTime() const {
      return _notificationDateTime;
    }

    /** Get the preferred cabin. */
    const CabinCode_T& getPreferredCabin() const {
      return _preferredCabin;
    }

    /** Get the party size. */
    const NbOfSeats_T& getPartySize() const {
      return _partySize;
    }

    /** Get the reservation channel. */
    const ChannelLabel_T& getOptimisationChannel() const {
      return _channel;
    }

    /** Get the trip type. */
    const TripType_T& getTripType() const {
      return _tripType;
    }

    /** Get the duration of stay. */
    const DayDuration_T& getStayDuration() const {
      return _stayDuration;
    }

    /** Get the frequent flyer type. */
    const FrequentFlyer_T& getFrequentFlyerType() const {
      return _frequentFlyerType;
    }

    /** Get the preferred departure time. */
    const Duration_T& getPreferredDepartureTime() const {
      return _preferredDepartureTime;
    }

    /** Get the willingness-to-pay. */
    const WTP_T& getWTP() const {
      return _wtp;
    }

    /** Get the value of time. */
    const PriceValue_T& getValueOfTime () const {
      return _valueOfTime;
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
    OptimisationNotificationStruct (const AirportCode_T& iOrigin,
                          const AirportCode_T& iDestination,
                          const CityCode_T& iPOS,
                          const Date_T& iDepartureDate,
                          const DateTime_T& iNotificationDateTime,
                          const CabinCode_T& iPreferredCabin,
                          const NbOfSeats_T& iPartySize,
                          const ChannelLabel_T& iChannel,
                          const TripType_T& iTripType,
                          const DayDuration_T& iStayDuration,
                          const FrequentFlyer_T& iFrequentFlyerType,
                          const Duration_T& iPreferredDepartureTime,
                          const WTP_T& iWTP,
                          const PriceValue_T& iValueOfTime);

    /** Copy constructor. */
    OptimisationNotificationStruct (const OptimisationNotificationStruct&);
    
  private:
    /** Default constructor.
        <br>It is private so that it can not be used. */
    OptimisationNotificationStruct ();

  public:
    /** Destructor. */
    ~OptimisationNotificationStruct();
    

  private:
    // /////////////// Attributes /////////////////
    /** Origin. */
    const AirportCode_T _origin;

    /** Destination. */
    const AirportCode_T _destination;

    /** Point-Of-Sale. */
    const CityCode_T _pos;
    
    /** Departure date. */
    const Date_T _preferredDepartureDate;

    /** Notification date-time */
    const DateTime_T _notificationDateTime;

    /** Preferred cabin. */
    const CabinCode_T _preferredCabin;

    /** Party size. */
    const NbOfSeats_T _partySize;

    /** Optimisation channel (D=direct, I=indirect, N=oNline, F=oFfline). */
    const ChannelLabel_T _channel;

    /** Trip type (RO=outbound of round-trip, RI=inbound of round-trip, 
        OW=one way). */
    const TripType_T _tripType;

    /** Stay duration (number of days). */
    const DayDuration_T _stayDuration;

    /** Frequent flyer type (P=Platinum, G=Gold, S=Silver, M=Member, N=None). */
    const FrequentFlyer_T _frequentFlyerType;

    /** Preferred departure time. */
    const Duration_T _preferredDepartureTime;
    
    /** Willingness-To-Pay. */
    const WTP_T _wtp;

    /** Value of time. */
    const PriceValue_T _valueOfTime;
  };

}
#endif // __STDAIR_BOM_OPTIMISATIONNOTIFICATIONSTRUCT_HPP
