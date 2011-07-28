// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/bom/OptimisationNotificationStruct.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  OptimisationNotificationStruct::OptimisationNotificationStruct()
    :  _partySize (0), _stayDuration (0), _wtp (0.0), _valueOfTime (0.0) {
    assert (false);
  }
    
  // //////////////////////////////////////////////////////////////////////
  OptimisationNotificationStruct::
  OptimisationNotificationStruct (const OptimisationNotificationStruct& iOptimisationNotification)
    : _origin (iOptimisationNotification._origin),
      _destination (iOptimisationNotification._destination),
      _pos (iOptimisationNotification._pos),
      _preferredDepartureDate (iOptimisationNotification._preferredDepartureDate), 
      _notificationDateTime (iOptimisationNotification._notificationDateTime),
      _preferredCabin (iOptimisationNotification._preferredCabin),
      _partySize (iOptimisationNotification._partySize),
      _channel (iOptimisationNotification._channel),
      _tripType (iOptimisationNotification._tripType),
      _stayDuration (iOptimisationNotification._stayDuration),
      _frequentFlyerType (iOptimisationNotification._frequentFlyerType),
      _preferredDepartureTime (iOptimisationNotification._preferredDepartureTime),
      _wtp (iOptimisationNotification._wtp),
      _valueOfTime (iOptimisationNotification._valueOfTime) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  OptimisationNotificationStruct::
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
                        const PriceValue_T& iValueOfTime)
    : _origin (iOrigin), _destination (iDestination),
      _pos (iPOS), _preferredDepartureDate (iDepartureDate), 
      _notificationDateTime (iNotificationDateTime),
      _preferredCabin (iPreferredCabin), _partySize (iPartySize),
      _channel (iChannel), _tripType (iTripType),
      _stayDuration (iStayDuration), _frequentFlyerType (iFrequentFlyerType),
      _preferredDepartureTime (iPreferredDepartureTime), _wtp (iWTP),
      _valueOfTime (iValueOfTime) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  OptimisationNotificationStruct::~OptimisationNotificationStruct() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void OptimisationNotificationStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // //////////////////////////////////////////////////////////////////////
  void OptimisationNotificationStruct::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string OptimisationNotificationStruct::describe() const {
    std::ostringstream oStr;
    oStr << "At " << _notificationDateTime
         << ", for (" << _pos << ") " << _origin << "-" << _destination
         << " " << _preferredDepartureDate << " " << _preferredCabin
         << " " << _partySize << " " << _channel << " " << _tripType 
         << " " << _stayDuration << " " << _frequentFlyerType
         << " " << _preferredDepartureTime << " " << _wtp
         << " " << _valueOfTime;
    return oStr.str();
  }

}
