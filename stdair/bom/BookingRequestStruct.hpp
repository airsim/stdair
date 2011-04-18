#ifndef __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
#define __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP

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
#include <stdair/bom/BookingRequestTypes.hpp>

namespace stdair {

  /**
   * @brief Structure holding the elements of a booking request.
   */
  struct BookingRequestStruct : public StructAbstract {
  public:
    // /////////////// Getters /////////////////
    /** Get the demand generator key. */
    const DemandGeneratorKey_T& getDemandGeneratorKey () const {
      return _generatorKey;
    }
    
    /** Get the requested origin. */
    const AirportCode_T& getOrigin() const {
      return _origin;
    }

    /** Get the requested destination. */
    const AirportCode_T& getDestination() const {
      return _destination;
    }

    /** Get the point-of-sale. */
    const AirportCode_T& getPOS() const {
      return _pos;
    }

    /** Get the requested departure date. */
    const Date_T& getPreferedDepartureDate() const {
      return _preferredDepartureDate;
    }

    /** Get the preferred departure time. */
    const Duration_T& getPreferredDepartureTime() const {
      return _preferredDepartureTime;
    }

    /** Get the request datetime. */
    const DateTime_T& getRequestDateTime() const {
      return _requestDateTime;
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
    const ChannelLabel_T& getBookingChannel() const {
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

    /** Get the willingness-to-pay. */
    const WTP_T& getWTP() const {
      return _wtp;
    }

    /** Get the value of time. */
    const PriceValue_T& getValueOfTime () const {
      return _valueOfTime;
    }
      

  public:
    // /////////// Display support method /////////////
    /**
     * Dump a Business Object into an output stream.
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;

    /**
     * Read a Business Object from an input stream.
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn);

    /**
     * Display of the structure.
     */
    const std::string describe() const;

    /**
     * Display of the structure.
     *
     * <ul>
     *  <li>#id,</li>
     *  <li>request_date (YYMMDD),</li>
     *  <li>request_time (HHMMSS),</li>
     *  <li>POS (three-letter code),</li>
     *  <li>Channel (two-letter code):</li>
     *  <ul>
     *   <li>'D' for direct or 'I' for indirect,</li>
     *   <li>'N' for oNline or 'F' for oFfline,</li>
     *  </ul>
     *  <li>Origin (three-letter code),</li>
     *  <li>Destination (three-letter code),</li>
     *  <li>Preferred departure date (YYMMDD),</li>
     *  <li>Preferred departure time (HHMM),</li>
     *  <li>Min departure time (HHMM),</li>
     *  <li>Max departure time (HHMM),</li>
     *  <li>Preferred arrival date (YYMMDD),</li>
     *  <li>Preferred arrival time (HHMM),</li>
     *  <li>Preferred cabin:</li>
     *  <ul>
     *   <li>'F' for first,</li>
     *   <li>'C' for club/business,</li>
     *   <li>'W' for economy plus,</li>
     *   <li>'M' for economy,</li>
     *  </ul>
     *  <li>Trip type:</li>
     *  <ul>
     *   <li>'OW' for a one-way trip,</li>
     *   <li>'RO' for the outbound part of a rount-trip,</li>
     *   <li>'RI' for the inbound part of a rount-trip,</li>
     *  </ul>
     *  <li>Duration of stay (expressed as a number of days),</li>
     *  <li>Frequent flyer tier:</li>
     *  <ul>
     *   <li>'G' for gold,</li>
     *   <li>'S' for silver,</li>
     *   <li>'K' for basic,</li>
     *   <li>'N' for none,</li>
     *  </ul>
     *  <li>Willingness-to-pay (WTP, expressed as a monetary unit,
     *      e.g., EUR),</li>
     *  <li>Disutility per stop (expressed as a monetary unit, e.g., EUR),</li>
     *  <li>Value of time (EUR per hour),</li>
     * </ul>
     *
     * @return const std::string The output of the booking request structure.
     */
    const std::string display() const;

    
  public:
    // /////////////// Constructors and Destructors /////////////////
    /**
     * Default constructor.
     */
    BookingRequestStruct (const DemandGeneratorKey_T& iGeneratorKey,
                          const AirportCode_T& iOrigin,
                          const AirportCode_T& iDestination,
                          const AirportCode_T& iPOS,
                          const Date_T& iDepartureDate,
                          const DateTime_T& iRequestDateTime,
                          const CabinCode_T& iPreferredCabin,
                          const NbOfSeats_T& iPartySize,
                          const ChannelLabel_T& iChannel,
                          const TripType_T& iTripType,
                          const DayDuration_T& iStayDuration,
                          const FrequentFlyer_T& iFrequentFlyerType,
                          const Duration_T& iPreferredDepartureTime,
                          const WTP_T& iWTP,
                          const PriceValue_T& iValueOfTime);

    /**
     * Constructor without the demand generator key, used for batches.
     */
    BookingRequestStruct (const AirportCode_T& iOrigin,
                          const AirportCode_T& iDestination,
                          const AirportCode_T& iPOS,
                          const Date_T& iDepartureDate,
                          const DateTime_T& iRequestDateTime,
                          const CabinCode_T& iPreferredCabin,
                          const NbOfSeats_T& iPartySize,
                          const ChannelLabel_T& iChannel,
                          const TripType_T& iTripType,
                          const DayDuration_T& iStayDuration,
                          const FrequentFlyer_T& iFrequentFlyerType,
                          const Duration_T& iPreferredDepartureTime,
                          const WTP_T& iWTP,
                          const PriceValue_T& iValueOfTime);
    /**
     * Copy constructor.
     */
    BookingRequestStruct (const BookingRequestStruct&);
    
    /**
     * Destructor.
     */
    ~BookingRequestStruct();
    

  private:
    /**
     * Default constructor.
     *
     * It is private so that it can not be used.
     */
    BookingRequestStruct();


  private:
    // /////////////// Attributes /////////////////
    /** Demand generator key. */
    const DemandGeneratorKey_T _generatorKey;
    
    /** Origin. */
    const AirportCode_T _origin;

    /** Destination. */
    const AirportCode_T _destination;

    /** Point-Of-Sale. */
    const AirportCode_T _pos;
    
    /** Departure date. */
    const Date_T _preferredDepartureDate;

    /** Preferred departure time. */
    const Duration_T _preferredDepartureTime;
    
    /** Request date-time */
    const DateTime_T _requestDateTime;

    /** Preferred cabin. */
    const CabinCode_T _preferredCabin;

    /** Party size. */
    const NbOfSeats_T _partySize;

    /** Booking channel (D=direct, I=indirect, N=oNline, F=oFfline). */
    const ChannelLabel_T _channel;

    /** Trip type (RO=outbound of round-trip, RI=inbound of round-trip, 
        OW=one way). */
    const TripType_T _tripType;

    /** Stay duration (number of days). */
    const DayDuration_T _stayDuration;

    /** Frequent flyer type (P=Platinum, G=Gold, S=Silver, M=Member, N=None). */
    const FrequentFlyer_T _frequentFlyerType;

    /** Willingness-To-Pay. */
    const WTP_T _wtp;

    /** Value of time. */
    const PriceValue_T _valueOfTime;
  };

}
#endif // __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
