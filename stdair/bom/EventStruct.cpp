// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/make_shared.hpp>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_Event.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/OptimisationNotificationStruct.hpp>
#include <stdair/bom/SnapshotStruct.hpp>
#include <stdair/bom/RMEventStruct.hpp>
#include <stdair/bom/EventStruct.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct()
    : _eventType (EventType::BKG_REQ), _eventTimeStamp (0) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const EventType::EN_EventType& iEventType,
                            BookingRequestPtr_T ioRequestPtr)
    : _eventType (iEventType) {

    //
    assert (ioRequestPtr != NULL);
    _bookingRequest = boost::make_shared<BookingRequestStruct> (*ioRequestPtr);
    assert (_bookingRequest != NULL);
    
    /**
     * Compute and store the number of milliseconds between the
     * date-time of the booking request and DEFAULT_EVENT_OLDEST_DATETIME
     * (as of Feb. 2011, that date is set to Jan. 1, 2010).
     */
    const Duration_T lDuration =
      _bookingRequest->getRequestDateTime() - DEFAULT_EVENT_OLDEST_DATETIME;
    _eventTimeStamp = lDuration.total_milliseconds();
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const EventType::EN_EventType& iEventType,
                            const DateTime_T& iDCPDate,
                            OptimisationNotificationPtr_T ioOptimisationNotificationPtr)
    : _eventType (iEventType) {

    //
    assert (ioOptimisationNotificationPtr != NULL);
    _optimisationNotification =
      boost::make_shared<OptimisationNotificationStruct> (*ioOptimisationNotificationPtr);
    assert (_optimisationNotification != NULL);
    
    /**
     * Compute and store the number of milliseconds between the
     * date-time of the booking request and DEFAULT_EVENT_OLDEST_DATETIME
     * (as of Feb. 2011, that date is set to Jan. 1, 2010).
     */
    const Duration_T lDuration = iDCPDate - DEFAULT_EVENT_OLDEST_DATETIME;
    _eventTimeStamp = lDuration.total_milliseconds();
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const EventType::EN_EventType& iEventType,
                            SnapshotPtr_T ioSnapshotPtr)
    : _eventType (iEventType) {

    //
    assert (ioSnapshotPtr != NULL);
    _snapshot = boost::make_shared<SnapshotStruct> (*ioSnapshotPtr);
    assert (_snapshot != NULL);
    
    /**
     * Compute and store the number of milliseconds between the
     * date-time of the snapshot and DEFAULT_EVENT_OLDEST_DATETIME
     * (as of Feb. 2011, that date is set to Jan. 1, 2010).
     */
    const Duration_T lDuration =
      _snapshot->getSnapshotTime() - DEFAULT_EVENT_OLDEST_DATETIME;
    _eventTimeStamp = lDuration.total_milliseconds();
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const EventType::EN_EventType& iEventType,
                            RMEventPtr_T ioRMEventPtr)
    : _eventType (iEventType) {

    //
    assert (ioRMEventPtr != NULL);
    _rmEvent = boost::make_shared<RMEventStruct> (*ioRMEventPtr);
    assert (_rmEvent != NULL);
    
    /**
     * Compute and store the number of milliseconds between the
     * date-time of the RM event and DEFAULT_EVENT_OLDEST_DATETIME
     * (as of Feb. 2011, that date is set to Jan. 1, 2010).
     */
    const Duration_T lDuration =
      _rmEvent->getRMEventTime() - DEFAULT_EVENT_OLDEST_DATETIME;
    _eventTimeStamp = lDuration.total_milliseconds();
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const EventStruct& iEventStruct)
    : _eventType (iEventStruct._eventType),
      _eventTimeStamp (iEventStruct._eventTimeStamp) {

    //
    if (iEventStruct._bookingRequest != NULL) {
      _bookingRequest =
        boost::make_shared<BookingRequestStruct>(*iEventStruct._bookingRequest);
    }

    //
    if (iEventStruct._optimisationNotification != NULL) {
      _optimisationNotification =
        boost::make_shared<OptimisationNotificationStruct> (*iEventStruct._optimisationNotification);
    }

    //
    if (iEventStruct._snapshot != NULL) {
      _snapshot =
        boost::make_shared<SnapshotStruct>(*iEventStruct._snapshot);
    }

    //
    if (iEventStruct._rmEvent != NULL) {
      _rmEvent =
        boost::make_shared<RMEventStruct>(*iEventStruct._rmEvent);
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::~EventStruct() {
  }

  // //////////////////////////////////////////////////////////////////////
  void EventStruct::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string EventStruct::describe() const {
    std::ostringstream oStr;

    //
    const Duration_T lEventDateTimeDelta =
      boost::posix_time::milliseconds (_eventTimeStamp);
    const DateTime_T lEventDateTime (DEFAULT_EVENT_OLDEST_DATETIME
                                   + lEventDateTimeDelta);
    oStr << lEventDateTime;

    //
    switch (_eventType) {
    case EventType::BKG_REQ: {
      assert (_bookingRequest != NULL);
      oStr << ", " << _eventType << ", " << _bookingRequest->describe();
      break;
    }
    case EventType::OPT_NOT_4_FD: {
      assert (_optimisationNotification != NULL);
      oStr << ", " << _eventType
           << ", " << _optimisationNotification->describe();
      break;
    }
    case EventType::SNAPSHOT: {
      assert (_snapshot != NULL);
      oStr << ", " << _eventType
           << ", " << _snapshot->describe();
      break;
    }
    case EventType::RM: {
      assert (_rmEvent != NULL);
      oStr << ", " << _eventType
           << ", " << _rmEvent->describe();
      break;
    }
    default: {
      oStr << ", " << _eventType << " (not yet recognised)";
      break;
    }
    }

    return oStr.str();
  }

}
