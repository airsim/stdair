// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost
#include <boost/date_time/gregorian/formatters.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::BookingRequestStruct()
    : _origin (DEFAULT_ORIGIN), _destination (DEFAULT_DESTINATION), 
      _pos (DEFAULT_POS),
      _preferredDepartureDate (DEFAULT_PREFERRED_DEPARTURE_DATE),
      _preferredDepartureTime (DEFAULT_PREFERRED_DEPARTURE_TIME),
      _requestDateTime (DEFAULT_REQUEST_DATE_TIME),
      _preferredCabin (DEFAULT_PREFERRED_CABIN),
      _partySize (DEFAULT_PARTY_SIZE),
      _channel (DEFAULT_CHANNEL),
      _tripType (TRIP_TYPE_ONE_WAY),
      _stayDuration (DEFAULT_STAY_DURATION),
      _frequentFlyerType (DEFAULT_FF_TIER),
      _wtp (DEFAULT_WTP),
      _valueOfTime (DEFAULT_VALUE_OF_TIME),
      _changeFees (false), _nonRefundable (false) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::
  BookingRequestStruct (const BookingRequestStruct& iBookingRequest)
    : _generatorKey (iBookingRequest._generatorKey),
      _origin (iBookingRequest._origin),
      _destination (iBookingRequest._destination),
      _pos (iBookingRequest._pos),
      _preferredDepartureDate (iBookingRequest._preferredDepartureDate), 
      _preferredDepartureTime (iBookingRequest._preferredDepartureTime),
      _requestDateTime (iBookingRequest._requestDateTime),
      _preferredCabin (iBookingRequest._preferredCabin),
      _partySize (iBookingRequest._partySize),
      _channel (iBookingRequest._channel),
      _tripType (iBookingRequest._tripType),
      _stayDuration (iBookingRequest._stayDuration),
      _frequentFlyerType (iBookingRequest._frequentFlyerType),
      _wtp (iBookingRequest._wtp),
      _valueOfTime (iBookingRequest._valueOfTime),
      _changeFees (iBookingRequest._changeFees),
      _nonRefundable (iBookingRequest._nonRefundable) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::
  BookingRequestStruct (const DemandGeneratorKey_T& iGeneratorKey,
                        const AirportCode_T& iOrigin,
                        const AirportCode_T& iDestination,
                        const CityCode_T& iPOS,
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
                        const PriceValue_T& iValueOfTime,
                        const ChangeFees_T& iChangeFees,
                        const NonRefundable_T& iNonRefundable)
    : _generatorKey (iGeneratorKey), _origin (iOrigin),
      _destination (iDestination), _pos (iPOS), 
      _preferredDepartureDate (iDepartureDate), 
      _preferredDepartureTime (iPreferredDepartureTime),
      _requestDateTime (iRequestDateTime),
      _preferredCabin (iPreferredCabin), _partySize (iPartySize),
      _channel (iChannel), _tripType (iTripType),
      _stayDuration (iStayDuration), _frequentFlyerType (iFrequentFlyerType),
      _wtp (iWTP), _valueOfTime (iValueOfTime),
      _changeFees (iChangeFees), _nonRefundable (iNonRefundable) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::
  BookingRequestStruct (const AirportCode_T& iOrigin,
                        const AirportCode_T& iDestination,
                        const CityCode_T& iPOS,
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
                        const PriceValue_T& iValueOfTime,
                        const ChangeFees_T& iChangeFees,
                        const NonRefundable_T& iNonRefundable)
    : _generatorKey (""), _origin (iOrigin),
      _destination (iDestination), _pos (iPOS), 
      _preferredDepartureDate (iDepartureDate), 
      _preferredDepartureTime (iPreferredDepartureTime),
      _requestDateTime (iRequestDateTime),
      _preferredCabin (iPreferredCabin), _partySize (iPartySize),
      _channel (iChannel), _tripType (iTripType),
      _stayDuration (iStayDuration), _frequentFlyerType (iFrequentFlyerType),
      _wtp (iWTP), _valueOfTime (iValueOfTime),
      _changeFees (iChangeFees), _nonRefundable (iNonRefundable) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::~BookingRequestStruct() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BookingRequestStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // //////////////////////////////////////////////////////////////////////
  void BookingRequestStruct::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string BookingRequestStruct::describe() const {
    std::ostringstream oStr;
    oStr << "At " << _requestDateTime
         << ", for (" << _pos << ", " << _channel << ")"
         << " " << _origin << "-" << _destination << " (" << _tripType << ")"
         << " " << _preferredDepartureDate << " (" << _stayDuration << " days)"
         << " " << _preferredDepartureTime
         << " " << _preferredCabin << " " << _partySize
         << " " << _frequentFlyerType << " " << _wtp << " " << _valueOfTime
         << " " << _changeFees << " " << _nonRefundable;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void intDisplay (std::ostream& oStream, const int& iInt) {
    const int dInt = iInt - static_cast<int> (iInt / 100) * 100;
    if (dInt < 10) {
      oStream << "0" << dInt;
    } else {
      oStream << dInt;
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string BookingRequestStruct::display() const {
    std::ostringstream oStr;

    // Request date and time
    const Date_T& lRequestDate = _requestDateTime.date();
    oStr << boost::gregorian::to_iso_extended_string (lRequestDate);

    const Duration_T& lRequestTime = _requestDateTime.time_of_day();
    oStr << ", " << boost::posix_time::to_simple_string (lRequestTime);

    // POS
    oStr << ", " << _pos;

    // Channel
    oStr << ", " << _channel;

    // Origin
    oStr << ", " << _origin;

    // Destination
    oStr << ", " << _destination;

    // Preferred departure date
    oStr << ", "
         << boost::gregorian::to_iso_extended_string (_preferredDepartureDate);

    // Preferred departure time
    oStr << ", "
         << boost::posix_time::to_simple_string (_preferredDepartureTime);

    // MIN & MAX preferred departure time (hardcode)
    oStr << ", " << "00:00-23:59";

    // Preferred arrival date (hardcode to the preferred departure date)
    oStr << ", "
         << boost::gregorian::to_iso_extended_string (_preferredDepartureDate);

    // Preferred arrival time (hard-coded to 23:55)
    oStr << ", " << "23:55";

    // Preferred cabin
    oStr << ", " << _preferredCabin;

    // Trip type
    oStr << ", " << _tripType;

    // Duration of stay
    oStr << ", ";
    if (_tripType == TRIP_TYPE_ONE_WAY) {
      oStr << "0";
    } else {
      oStr << _stayDuration;
    }

    // Frequent flyer tier
    oStr << ", " << _frequentFlyerType;

    // Willingness-to-pay
    oStr << ", " << _wtp;

    // Disutility per stop (hardcode to 100, expressed as a monetary
    // unit per hour)
    oStr << ", " << "100";

    // Value of time
    oStr << ", " << _valueOfTime;

    // Change fees
    oStr << ", " << _changeFees;

    // Non refundable
    oStr << ", " << _nonRefundable;

    return oStr.str();
  }

}
