// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/EventStruct.hpp>
#include <stdair/bom/EventQueue.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  EventQueue::EventQueue () {
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventQueue::~EventQueue () {
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventStruct& EventQueue::popEvent () {
    assert (isQueueDone() == false);
    return _eventList.begin()->second;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void EventQueue::addEvent (EventStruct& ioEventStruct) {
    const DateTime_T& lEventDateTime = ioEventStruct.getEventDateTime ();
    const bool insertionSucceeded =
      _eventList.insert (EventListElement_T (lEventDateTime, ioEventStruct)).second;

    // If the insertion is not succeded.
    if (insertionSucceeded == false) {
      ioEventStruct.moveForwardInTime();
      addEvent (ioEventStruct);
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void EventQueue::eraseLastUsedEvent () {
    assert (isQueueDone () == false);
    _eventList.erase (_eventList.begin());
  }
  
  // //////////////////////////////////////////////////////////////////////
  const bool EventQueue::isQueueDone () const {
    return _eventList.begin() == _eventList.end();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const Count_T EventQueue::getQueueSize () const {
    if (_eventList.empty ()) {
      return 0;
    } else {
      return _eventList.size ();
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  const bool EventQueue::isQueueEmpty () const {
    return _eventList.empty ();
  }
  
}
