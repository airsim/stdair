// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/bom/BookingRequestStruct.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::BookingRequestStruct ()
    :  _partySize (0), _stayDuration (0), _wtp (0.0), _valueOfTime (0.0) {
    assert (false);
  }
    
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::
  BookingRequestStruct (const BookingRequestStruct& iBookingRequest)
    : _origin (iBookingRequest._origin),
      _destination (iBookingRequest._destination),
      _pos (iBookingRequest._pos),
      _preferredDepartureDate (iBookingRequest._preferredDepartureDate), 
      _requestDateTime (iBookingRequest._requestDateTime),
      _preferredCabin (iBookingRequest._preferredCabin),
      _partySize (iBookingRequest._partySize),
      _channel (iBookingRequest._channel),
      _tripType (iBookingRequest._tripType),
      _stayDuration (iBookingRequest._stayDuration),
      _frequentFlyerType (iBookingRequest._frequentFlyerType),
      _preferredDepartureTime (iBookingRequest._preferredDepartureTime),
      _wtp (iBookingRequest._wtp),
      _valueOfTime (iBookingRequest._valueOfTime) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::
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
                        const PriceValue_T& iValueOfTime)
    : _origin (iOrigin), _destination (iDestination),
      _pos (iPOS), _preferredDepartureDate (iDepartureDate), 
      _requestDateTime (iRequestDateTime),
      _preferredCabin (iPreferredCabin), _partySize (iPartySize),
      _channel (iChannel), _tripType (iTripType),
      _stayDuration (iStayDuration), _frequentFlyerType (iFrequentFlyerType),
      _preferredDepartureTime (iPreferredDepartureTime), _wtp (iWTP),
      _valueOfTime (iValueOfTime) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct::~BookingRequestStruct () {
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
    oStr << _origin << " - " << _destination
         << " " << _pos << " " << _preferredDepartureDate
         << " " << _requestDateTime << " " << _preferredCabin
         << " " << _partySize << " " << _channel << " " << _tripType 
         << " " << _stayDuration << " " << _frequentFlyerType
         << " " << _preferredDepartureTime << " " << _wtp
         << " " << _valueOfTime;
    return oStr.str();
  }

}
