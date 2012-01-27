// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/BasConst_Event.hpp>
#include <stdair/bom/EventStruct.hpp>
#include <stdair/bom/EventQueue.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  EventQueue::EventQueue()
    : _key (DEFAULT_EVENT_QUEUE_ID), _parent (NULL),
      _progressStatus (stdair::DEFAULT_PROGRESS_STATUS,
                       stdair::DEFAULT_PROGRESS_STATUS) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventQueue::EventQueue (const Key_T& iKey)
    : _key (iKey), _parent (NULL),
      _progressStatus (stdair::DEFAULT_PROGRESS_STATUS,
                       stdair::DEFAULT_PROGRESS_STATUS) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventQueue::EventQueue (const EventQueue& iEventQueue)
    : _key (DEFAULT_EVENT_QUEUE_ID), _parent (NULL),
      _progressStatus (stdair::DEFAULT_PROGRESS_STATUS,
                       stdair::DEFAULT_PROGRESS_STATUS) {
    assert (false);
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventQueue::~EventQueue() {
    _eventList.clear();
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string EventQueue::toString() const {
    std::ostringstream oStr;
    oStr << "(" << _eventList.size() << ") "
         << _progressStatus.getCurrentNb() << "/{"
         << _progressStatus.getExpectedNb() << ","
         << _progressStatus.getActualNb() << "}";
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string EventQueue::display() const {
    std::ostringstream oStr;

    oStr << toString();
    
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  Count_T EventQueue::getQueueSize() const {
    return _eventList.size();
  }
  
  // //////////////////////////////////////////////////////////////////////
  bool EventQueue::isQueueEmpty() const {
    return _eventList.empty();
  }
  
  // //////////////////////////////////////////////////////////////////////
  bool EventQueue::isQueueDone() const {
    const bool isQueueEmpty = _eventList.empty();
    return isQueueEmpty;
  }

  // //////////////////////////////////////////////////////////////////////
  void EventQueue::reset() {
    // Reset only the current number of events, not the expected one
    _progressStatus.reset();
    
    // Empty the list of events
    _eventList.clear();

    // Reset the progress statuses for all the event types
    for (ProgressStatusMap_T::iterator itProgressStatus =
           _progressStatusMap.begin();
         itProgressStatus != _progressStatusMap.end(); ++itProgressStatus) {
      ProgressStatus& lProgressStatus = itProgressStatus->second;
      lProgressStatus.reset();
    }

  }
  
  // //////////////////////////////////////////////////////////////////////
  const Count_T& EventQueue::
  getCurrentNbOfEvents (const EventType::EN_EventType& iType) const {

    // Retrieve the ProgressStatus structure corresponding to the
    // given event type
    ProgressStatusMap_T::const_iterator itProgressStatus =
      _progressStatusMap.find (iType);
    if (itProgressStatus == _progressStatusMap.end()) {
      //
      STDAIR_LOG_ERROR ("No ProgressStatus structure can be retrieved in the "
                        << "EventQueue: " << display());
      assert (false);
    }
    
    const ProgressStatus& lProgressStatus = itProgressStatus->second;
    return lProgressStatus.getCurrentNb();
  }

  // //////////////////////////////////////////////////////////////////////
  const Count_T& EventQueue::
  getExpectedTotalNbOfEvents (const EventType::EN_EventType& iType) const {

    // Retrieve the ProgressStatus structure corresponding to the
    // given event type
    ProgressStatusMap_T::const_iterator itProgressStatus =
      _progressStatusMap.find (iType);
    if (itProgressStatus == _progressStatusMap.end()) {
      std::ostringstream oStr;
      oStr << "No ProgressStatus structure can be retrieved in the EventQueue '"
           << display() << "'. The EventQueue should be initialised, e.g., by "
           << "calling a buildSampleBom() method.";
      //
      STDAIR_LOG_ERROR (oStr.str());
      throw EventQueueException (oStr.str());
    }
    
    const ProgressStatus& lProgressStatus = itProgressStatus->second;
    return lProgressStatus.getExpectedNb();
  }

  // //////////////////////////////////////////////////////////////////////
  const Count_T& EventQueue::
  getActualTotalNbOfEvents (const EventType::EN_EventType& iType) const {

    // Retrieve the ProgressStatus structure corresponding to the
    // given event type
    ProgressStatusMap_T::const_iterator itProgressStatus =
      _progressStatusMap.find (iType);
    if (itProgressStatus == _progressStatusMap.end()) {
      //
      STDAIR_LOG_ERROR ("No ProgressStatus structure can be retrieved in the "
                        << "EventQueue: " << display());
      assert (false);
    }
    
    const ProgressStatus& lProgressStatus = itProgressStatus->second;
    return lProgressStatus.getActualNb();
  }

  // //////////////////////////////////////////////////////////////////////
  void EventQueue::updateStatus (const EventType::EN_EventType& iType,
                                 const ProgressStatus& iProgressStatus) {

    // Retrieve, if existing, the ProgressStatus structure
    // corresponding to the given event type
    ProgressStatusMap_T::iterator itProgressStatus =
      _progressStatusMap.find (iType);
    if (itProgressStatus == _progressStatusMap.end()) {
      const bool hasInsertBeenSuccessful =
        _progressStatusMap.insert (ProgressStatusMap_T::
                                   value_type (iType, iProgressStatus)).second;
      
      if (hasInsertBeenSuccessful == false) {
        STDAIR_LOG_ERROR ("No progress_status can be inserted "
                          << "for the following event type: "
                          << EventType::getLabel(iType)
                          << ". EventQueue: " << toString());
        throw EventException ("No progress_status can be inserted for the "
                              "following event type: "
                              + EventType::getLabel(iType)
                              + ". EventQueue: " + toString());
      }

      return;
    }
    
    ProgressStatus& lProgressStatus = itProgressStatus->second;

    // Update the progress status
    const Count_T& lCurrentNb = iProgressStatus.getCurrentNb();
    lProgressStatus.setCurrentNb (lCurrentNb);

    const Count_T& lExpectedNb = iProgressStatus.getExpectedNb();
    lProgressStatus.setExpectedNb(lProgressStatus.getExpectedNb() + lExpectedNb);

    const Count_T& lActualNb = iProgressStatus.getActualNb();
    lProgressStatus.setActualNb (lProgressStatus.getActualNb() + lActualNb);
  }

  // //////////////////////////////////////////////////////////////////////
  void EventQueue::
  addStatus (const EventType::EN_EventType& iType,
             const NbOfEvents_T& iExpectedTotalNbOfEvents) {
    
    // Initialise the progress status object
    const Count_T lExpectedTotalNbOfEventsInt =
      static_cast<const Count_T> (std::floor (iExpectedTotalNbOfEvents));
    const ProgressStatus lProgressStatus (lExpectedTotalNbOfEventsInt);
      
    // Update the progress status for the given event type
    updateStatus (iType, lProgressStatus);
    
    // Update the overall progress status
    const Count_T lExpectedNb = 
      static_cast<const Count_T> (_progressStatus.getExpectedNb()
				  + iExpectedTotalNbOfEvents);
    _progressStatus.setExpectedNb (lExpectedNb);

    const Count_T lActualNb = 
      static_cast<const Count_T> (_progressStatus.getActualNb()
				  + iExpectedTotalNbOfEvents);
    _progressStatus.setActualNb (lActualNb);
  }

  // //////////////////////////////////////////////////////////////////////
  void EventQueue::updateStatus (const EventType::EN_EventType& iType,
                                 const NbOfEvents_T& iActualNbOfEvents) {

    // Initialise the progress status object for the type key
    Count_T lActualNbOfEventsInt =
      static_cast<const Count_T> (std::floor (iActualNbOfEvents));
      
    // Update the progress status for the corresponding content type key
    ProgressStatusMap_T::iterator itProgressStatus =
      _progressStatusMap.find (iType);
    if (itProgressStatus != _progressStatusMap.end()) {
      ProgressStatus& lProgressStatus = itProgressStatus->second;
      //
      lActualNbOfEventsInt += lProgressStatus.getActualNb();
      //
      lProgressStatus.setActualNb (lActualNbOfEventsInt);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void EventQueue::setStatus (const EventType::EN_EventType& iType,
                              const ProgressStatus& iProgressStatus) {

    // Retrieve the ProgressStatus structure corresponding to the
    // given event type
    ProgressStatusMap_T::iterator itProgressStatus =
      _progressStatusMap.find (iType);
    // assert (itProgressStatus != _progressStatusMap.end());
    if (itProgressStatus != _progressStatusMap.end()) {
      // Update the ProgressStatus structure
      itProgressStatus->second = iProgressStatus;
    }
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressStatus EventQueue::
  getStatus (const EventType::EN_EventType& iType) const {

    // Retrieve the ProgressStatus structure corresponding to the
    // given event type
    ProgressStatusMap_T::const_iterator itProgressStatus =
      _progressStatusMap.find (iType);
    if (itProgressStatus != _progressStatusMap.end()) {
      const ProgressStatus& oProgressStatus = itProgressStatus->second;
      return oProgressStatus;
    }

    return ProgressStatus();
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressPercentage_T EventQueue::
  calculateProgress (const EventType::EN_EventType& iType) const {

    // Retrieve the ProgressStatus structure corresponding to the
    // given event type
    ProgressStatusMap_T::const_iterator itProgressStatus =
      _progressStatusMap.find (iType);
    if (itProgressStatus == _progressStatusMap.end()) {
      //
      STDAIR_LOG_ERROR ("No ProgressStatus structure can be retrieved in the "
                        << "EventQueue: " << display());
      assert (false);
    }
    
    const ProgressStatus& lProgressStatus = itProgressStatus->second;
    return lProgressStatus.progress();
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressStatusSet EventQueue::popEvent (EventStruct& ioEventStruct) {

    if (_eventList.empty() == true) {  
      std::ostringstream oStr;
      oStr << "The event queue '" << describeKey() << "' is empty. "
	   << "No event can be popped.";
      //
      STDAIR_LOG_ERROR (oStr.str());
      throw EventQueueException (oStr.str());
    }

    /**
     * 1. Update the event queue itself.
     */
    // Get an iterator on the first event (sorted by date-time stamps)
    EventList_T::iterator itEvent = _eventList.begin();

    /**
     * Extract (a copy of) the corresponding Event structure. We make
     * a copy here, as the original EventStruct structure is removed
     * from the list (and erased). Moreover, the resulting EventStruct
     * structure will be returned by this method.
     */
    ioEventStruct = itEvent->second;
    // Retrieve the event type
    const EventType::EN_EventType& lEventType = ioEventStruct.getEventType();
    ProgressStatusSet oProgressStatusSet (lEventType);
  
    // Update the (current number part of the) overall progress status,
    // to account for the event that is being popped out of the event
    // queue.
    ++_progressStatus;
    
    // Remove the event, which has just been retrieved
    _eventList.erase (itEvent);


    /**
     * 2. Update the progress statuses held by the EventStruct structure.
     *
     * 2.1. Update the progress status specific to the event type (e.g.,
     *      booking request, optimisation notification).
     */

    // Retrieve the progress status specific to that event type
    ProgressStatus lEventTypeProgressStatus = getStatus (lEventType);

    // Increase the current number of events
    ++lEventTypeProgressStatus;

    // Store back the progress status
    setStatus (lEventType, lEventTypeProgressStatus);

    // Update the progress status of the progress status set, specific to
    // the event type.
    oProgressStatusSet.setTypeSpecificStatus (lEventTypeProgressStatus);

    /**
     * 2.2. Update the overall progress status.
     */
    // Update the overall progress status of the progress status set.
    oProgressStatusSet.setOverallStatus (_progressStatus);

    //
    return oProgressStatusSet;
  }

  // //////////////////////////////////////////////////////////////////////
  bool EventQueue::addEvent (EventStruct& ioEventStruct) {
    bool insertionSucceeded =
      _eventList.insert (EventListElement_T (ioEventStruct._eventTimeStamp,
                                             ioEventStruct)).second;

    /**
     * If the insertion has not been successful, try repeatedly until
     * the insertion becomes successful.
     *
     * The date-time is counted in milliseconds (1e-3 second). Hence,
     * one thousand (1e3) of attempts correspond to 1 second.
     *     
     * The check on one thousand (1e3) is made in order to avoid
     * potential infinite loops. In such case, however, an assertion
     * will fail: it is always better that an assertion fails rather
     * than entering an infinite loop.
     */
    const unsigned int idx = 0;
    while (insertionSucceeded == false && idx != 1e3) {
      // Retrieve the date-time stamp (expressed in milliseconds)
      LongDuration_T& lEventTimeStamp (ioEventStruct._eventTimeStamp);
      ++lEventTimeStamp;

      // Retry to insert into the event queue
      insertionSucceeded =
        _eventList.insert (EventListElement_T (ioEventStruct._eventTimeStamp,
                                               ioEventStruct)).second;
    }
    assert (idx != 1e3);

    return insertionSucceeded;
  }

}
