// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#if BOOST_VERSION >= 103900
#include <boost/make_shared.hpp>
#else  // BOOST_VERSION >= 103900
#include <boost/shared_ptr.hpp>
#endif // BOOST_VERSION >= 103900
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_Event.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/OptimisationNotificationStruct.hpp>
#include <stdair/bom/SnapshotStruct.hpp>
#include <stdair/bom/CancellationStruct.hpp>
#include <stdair/bom/RMEventStruct.hpp>
#include <stdair/bom/BreakPointStruct.hpp>
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
#if BOOST_VERSION >= 103900
    _bookingRequest = boost::make_shared<BookingRequestStruct> (*ioRequestPtr);
#else  // BOOST_VERSION >= 103900
    _bookingRequest = ioRequestPtr;
#endif // BOOST_VERSION >= 103900
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
                            CancellationPtr_T ioCancellationPtr)
    : _eventType (iEventType) {

    //
    assert (ioCancellationPtr != NULL);
#if BOOST_VERSION >= 103900
    _cancellation = boost::make_shared<CancellationStruct> (*ioCancellationPtr);
#else  // BOOST_VERSION >= 103900
    _cancellation = ioCancellationPtr;
#endif // BOOST_VERSION >= 103900
    assert (_cancellation != NULL);
    
    /**
     * Compute and store the number of milliseconds between the
     * date-time of the cancellation and DEFAULT_EVENT_OLDEST_DATETIME
     * (as of Feb. 2011, that date is set to Jan. 1, 2010).
     */
    const Duration_T lDuration =
      _cancellation->getCancellationDateTime() - DEFAULT_EVENT_OLDEST_DATETIME;
    _eventTimeStamp = lDuration.total_milliseconds();
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct::
  EventStruct (const EventType::EN_EventType& iEventType,
	       const DateTime_T& iDCPDate,
	       OptimisationNotificationPtr_T ioOptimisationNotificationPtr)
    : _eventType (iEventType) {

    //
    assert (ioOptimisationNotificationPtr != NULL);
#if BOOST_VERSION >= 103900
    _optimisationNotification =
      boost::make_shared<OptimisationNotificationStruct> (*ioOptimisationNotificationPtr);
#else  // BOOST_VERSION >= 103900
    _optimisationNotification = ioOptimisationNotificationPtr;
#endif // BOOST_VERSION >= 103900
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

#if BOOST_VERSION >= 103900
    _snapshot = boost::make_shared<SnapshotStruct> (*ioSnapshotPtr);
#else  // BOOST_VERSION >= 103900
    _snapshot = ioSnapshotPtr;
#endif // BOOST_VERSION >= 103900
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

#if BOOST_VERSION >= 103900
    _rmEvent = boost::make_shared<RMEventStruct> (*ioRMEventPtr);
#else  // BOOST_VERSION >= 103900
    _rmEvent = ioRMEventPtr;
#endif // BOOST_VERSION >= 103900
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
  EventStruct::EventStruct (const EventType::EN_EventType& iEventType,
                            BreakPointPtr_T ioBreakPointPtr)
    : _eventType (iEventType) {

    //
    assert (ioBreakPointPtr != NULL);

#if BOOST_VERSION >= 103900
    _breakPoint = boost::make_shared<BreakPointStruct> (*ioBreakPointPtr);
#else  // BOOST_VERSION >= 103900
    _breakPoint = ioBreakPointPtr;
#endif // BOOST_VERSION >= 103900
    assert (_breakPoint != NULL);
    
    /**
     * Compute and store the number of milliseconds between the
     * date-time of the RM event and DEFAULT_EVENT_OLDEST_DATETIME
     * (as of Feb. 2011, that date is set to Jan. 1, 2010).
     */
    const Duration_T lDuration =
      _breakPoint->getBreakPointTime() - DEFAULT_EVENT_OLDEST_DATETIME;
    _eventTimeStamp = lDuration.total_milliseconds();
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const EventStruct& iEventStruct)
    : _eventType (iEventStruct._eventType),
      _eventTimeStamp (iEventStruct._eventTimeStamp) {

    //
    if (iEventStruct._bookingRequest != NULL) {
#if BOOST_VERSION >= 103900
      _bookingRequest =
        boost::make_shared<BookingRequestStruct>(*iEventStruct._bookingRequest);
#else  // BOOST_VERSION >= 103900
      _bookingRequest = iEventStruct._bookingRequest;
#endif // BOOST_VERSION >= 103900
    }

    //
    if (iEventStruct._cancellation != NULL) {
#if BOOST_VERSION >= 103900
      _cancellation =
        boost::make_shared<CancellationStruct>(*iEventStruct._cancellation);
#else  // BOOST_VERSION >= 103900
      _cancellation = iEventStruct._cancellation;
#endif // BOOST_VERSION >= 103900
    }

    //
    if (iEventStruct._optimisationNotification != NULL) {
#if BOOST_VERSION >= 103900
      _optimisationNotification =
        boost::make_shared<OptimisationNotificationStruct> (*iEventStruct._optimisationNotification);
#else  // BOOST_VERSION >= 103900
      _optimisationNotification = iEventStruct._optimisationNotification;
#endif // BOOST_VERSION >= 103900
    }

    //
    if (iEventStruct._snapshot != NULL) {
#if BOOST_VERSION >= 103900
      _snapshot = boost::make_shared<SnapshotStruct> (*iEventStruct._snapshot);
#else  // BOOST_VERSION >= 103900
      _snapshot = iEventStruct._snapshot;
#endif // BOOST_VERSION >= 103900
    }

    //
    if (iEventStruct._rmEvent != NULL) {
#if BOOST_VERSION >= 103900
      _rmEvent = boost::make_shared<RMEventStruct> (*iEventStruct._rmEvent);
#else  // BOOST_VERSION >= 103900
      _rmEvent = iEventStruct._rmEvent;
#endif // BOOST_VERSION >= 103900
    } 

    //
    if (iEventStruct._breakPoint != NULL) {
#if BOOST_VERSION >= 103900
      _breakPoint = boost::make_shared<BreakPointStruct> (*iEventStruct._breakPoint);
#else  // BOOST_VERSION >= 103900
      _breakPoint = iEventStruct._breakPoint;
#endif // BOOST_VERSION >= 103900
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

    //
    switch (_eventType) {
    case EventType::BKG_REQ: {
      assert (_bookingRequest != NULL);
      oStr << lEventDateTime;
      oStr << ", " << EventType::getLabel(_eventType)
	   << ", " << _bookingRequest->describe();
      break;
    }
    case EventType::CX: {
      assert (_cancellation != NULL);
      oStr << lEventDateTime;
      oStr << ", " << EventType::getLabel(_eventType)
	   << ", " << _cancellation->describe();
      break;
    }
    case EventType::OPT_NOT_4_FD: {
      assert (_optimisationNotification != NULL);
      oStr << lEventDateTime;
      oStr << ", " << EventType::getLabel(_eventType)
           << ", " << _optimisationNotification->describe();
      break;
    }
    case EventType::SNAPSHOT: {
      assert (_snapshot != NULL);
      /**oStr << ", " << EventType::getLabel(_eventType)
         << ", " << _snapshot->describe();*/
      break;
    }
    case EventType::RM: {
      assert (_rmEvent != NULL);
      /**oStr << ", " << EventType::getLabel(_eventType)
         << ", " << _rmEvent->describe();*/
      break;
    } 
    case EventType::BRK_PT: {
      assert (_breakPoint != NULL);
      oStr << lEventDateTime;
      oStr << ", " << EventType::getLabel(_eventType)
           << ", " << _breakPoint->describe(); 
      break;
    }
    default: {
      oStr << ", " << _eventType << " (not yet recognised)";
      break;
    }
    }
    
    oStr << "\n";
    return oStr.str();
  }   

  // //////////////////////////////////////////////////////////////////////
  const DateTime_T& EventStruct::getEventTime() const {
    const DateTime_T& lDateTime (DEFAULT_EVENT_OLDEST_DATETIME);

    //
    switch (_eventType) {
    case EventType::BKG_REQ: {
      assert (_bookingRequest != NULL);
      return _bookingRequest->getRequestDateTime();
      break;
    }
    case EventType::CX: {
      assert (_cancellation != NULL);
      return _cancellation->getCancellationDateTime() ;
      break;
    }
    case EventType::OPT_NOT_4_FD: {
      assert (_optimisationNotification != NULL);
      return _optimisationNotification->getNotificationDateTime();
      break;
    }
    case EventType::SNAPSHOT: {
      assert (_snapshot != NULL);
      return _snapshot->getSnapshotTime();
      break;
    }
    case EventType::RM: {
      assert (_rmEvent != NULL);
      return _rmEvent->getRMEventTime();
      break;
    } 
    case EventType::BRK_PT: {
      assert (_breakPoint != NULL);
      return _breakPoint->getBreakPointTime();
      break;
    }
    default: {
      assert(false); 
      return lDateTime;
      break;
    }
    }

    return lDateTime;
  } 

  // //////////////////////////////////////////////////////////////////////
  void EventStruct::incrementEventTimeStamp() {
    // The date-time is counted in milliseconds (1e-3 second). Hence,
    // one thousand (1e3) of attempts correspond to 1 second.
    // Increment the time stamp of one millisecond.
    ++_eventTimeStamp;
  }

}
