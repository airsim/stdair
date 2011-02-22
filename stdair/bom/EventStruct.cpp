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
#include <stdair/bom/EventStruct.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct()
    : _eventType (EventType::BKG_REQ), _eventTimeStamp (0),
      _demandStreamKeyStr(), _specificProgressStatus(),
      _overallProgressStatus() {
    assert (false);
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const EventType::EN_EventType& iEventType,
                            const DemandStreamKeyStr_T& iDemandStreamKey,
                            BookingRequestPtr_T ioRequestPtr)
    : _eventType (iEventType), _demandStreamKeyStr (iDemandStreamKey),
      _specificProgressStatus(), _overallProgressStatus() {

    //
    assert (ioRequestPtr != NULL);
    _request = boost::make_shared<BookingRequestStruct> (*ioRequestPtr);
    assert (_request != NULL);
    
    /**
     * Compute and store the number of milliseconds between the
     * date-time of the booking request and DEFAULT_EVENT_OLDEST_DATETIME
     * (as of Feb. 2011, that date is set to Jan. 1, 2010).
     */
    const Duration_T lDuration =
      _request->getRequestDateTime() - DEFAULT_EVENT_OLDEST_DATETIME;
    _eventTimeStamp = lDuration.total_milliseconds();
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct::EventStruct (const EventStruct& iEventStruct)
    : _eventType (iEventStruct._eventType),
      _eventTimeStamp (iEventStruct._eventTimeStamp),
      _demandStreamKeyStr (iEventStruct._demandStreamKeyStr),
      _specificProgressStatus (iEventStruct._specificProgressStatus),
      _overallProgressStatus (iEventStruct._overallProgressStatus) {

    //
    if (iEventStruct._request != NULL) {
      _request =
        boost::make_shared<BookingRequestStruct> (*iEventStruct._request);
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
    oStr << "[" << EventType (_eventType)
         << "][" << _overallProgressStatus.getCurrentNb()
         << "/{" << _overallProgressStatus.getExpectedNb()
         << "," << _overallProgressStatus.getActualNb()
         << "}][" << _specificProgressStatus.getCurrentNb()
         << "/{" << _specificProgressStatus.getExpectedNb()
         << "," << _specificProgressStatus.getActualNb()
         << "}] ";

    const Duration_T lRequestDateDelta =
      boost::posix_time::milliseconds (_eventTimeStamp);
    const DateTime_T lRequestDate (DEFAULT_EVENT_OLDEST_DATETIME
                                   + lRequestDateDelta);
    oStr << lRequestDate;
    
    switch (_eventType) {
    case EventType::BKG_REQ: {
      assert (_request != NULL);
      oStr << ", " << _demandStreamKeyStr << ", " << _request->describe();
    }
    default: {
    }
    }
    
    return oStr.str();
  }

}
