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
#include <stdair/bom/EventStruct.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct()
    : _eventType (EventType::BKG_REQ), _eventTimeStamp (0),
      _typeSpecificProgressStatus(), _keySpecificProgressStatus(),
      _overallProgressStatus() {
    assert (false);
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const EventType::EN_EventType& iEventType,
                            BookingRequestPtr_T ioRequestPtr)
    : _eventType (iEventType), _typeSpecificProgressStatus(), 
      _keySpecificProgressStatus(), _overallProgressStatus() {

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
    : _eventType (iEventType), _typeSpecificProgressStatus(), 
      _keySpecificProgressStatus(), _overallProgressStatus() {

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
    : _eventType (iEventType), _typeSpecificProgressStatus(),
      _keySpecificProgressStatus(), _overallProgressStatus() {

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
  EventStruct::EventStruct (const EventStruct& iEventStruct)
    : _eventType (iEventStruct._eventType),
      _eventTimeStamp (iEventStruct._eventTimeStamp),
      _typeSpecificProgressStatus (iEventStruct._typeSpecificProgressStatus),
      _keySpecificProgressStatus (iEventStruct._keySpecificProgressStatus),
      _overallProgressStatus (iEventStruct._overallProgressStatus) {

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
    oStr << "[" << EventType (_eventType) << "]"
         << "[" << _typeSpecificProgressStatus.getCurrentNb()
         << "/{" << _typeSpecificProgressStatus.getExpectedNb()
         << "," << _typeSpecificProgressStatus.getActualNb()
         << "}]";

    oStr << "-[Overall]"
         << "[" << _overallProgressStatus.getCurrentNb()
         << "/{" << _overallProgressStatus.getExpectedNb()
         << "," << _overallProgressStatus.getActualNb()
         << "}] ";

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
    default: {
      oStr << ", " << _eventType << " (not yet recognised)";
      break;
    }
    }

    return oStr.str();
  }

}
