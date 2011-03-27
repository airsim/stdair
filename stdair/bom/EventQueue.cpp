// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/make_shared.hpp>
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
    _nbOfEvents.clear();
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
    
    /*
     * \note The following can be very consuming (in time, CPU and
     * memory) when there are a lot of demand streams (e.g., several
     * hundreds of thousands). Uncomment it only for debug purposes.
    */
    unsigned int demandStreamIdx = 1;
    for (NbOfEventsByContentKeyMap_T::const_iterator itNbOfEventsMap =
           _nbOfEvents.begin(); itNbOfEventsMap != _nbOfEvents.end();
         ++itNbOfEventsMap, ++demandStreamIdx) {

      const EventContentKey_T& lDemandStreyKeyStr = itNbOfEventsMap->first;
      oStr << ", [" << demandStreamIdx << "][" << lDemandStreyKeyStr << "] ";

      const ProgressStatus& lProgressStatus = itNbOfEventsMap->second;
      oStr << lProgressStatus;
    }
    
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

    // Reset the progress statuses for all the content keys
    for (NbOfEventsByContentKeyMap_T::iterator itNbOfEvents =
           _nbOfEvents.begin();
         itNbOfEvents != _nbOfEvents.end(); ++itNbOfEvents) {
      ProgressStatus& lProgressStatus = itNbOfEvents->second;
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
  }

  // //////////////////////////////////////////////////////////////////////
  void EventQueue::
  addStatus (const EventType::EN_EventType& iType,
             const EventContentKey_T& iEventContentKey,
             const NbOfRequests_T& iExpectedTotalNbOfEvents) {

    /**
     * \note After the initialisation of the DemandStream objects
     * attached to the event queue, there are, by construction,
     * exactly as many events as there are distinct demand
     * streams. Indeed, the event queue contains a single event
     * structure for every demand stream.
     */

    // Initialise the progress status object
    const Count_T lExpectedTotalNbOfEventsInt =
      std::floor (iExpectedTotalNbOfEvents);
    const ProgressStatus lProgressStatus (lExpectedTotalNbOfEventsInt);
      
    // Insert the (Boost) progress display object into the dedicated map
    const bool hasInsertBeenSuccessful =
      _nbOfEvents.insert (NbOfEventsByContentKeyMap_T::
                          value_type (iEventContentKey,
                                      lProgressStatus)).second;

    if (hasInsertBeenSuccessful == false) {
      STDAIR_LOG_ERROR ("No progress_status can be inserted "
                        << "for the following event content key: "
                        << iEventContentKey
                        << ". EventQueue: " << toString());
      throw EventException ("No progress_status can be inserted for the "
                            "following event content key: " + iEventContentKey
                            + ". EventQueue: " + toString());
    }

    // Update the progress status for the given event type
    updateStatus (iType, lProgressStatus);
    
    // Update the overall progress status
    _progressStatus.setExpectedNb (_progressStatus.getExpectedNb()
                                   + iExpectedTotalNbOfEvents);

    _progressStatus.setActualNb (_progressStatus.getActualNb()
                                 + iExpectedTotalNbOfEvents);
  }

  // //////////////////////////////////////////////////////////////////////
  void EventQueue::
  updateStatus (const EventType::EN_EventType& iType,
                const NbOfRequests_T& iExpectedTotalNbOfEvents) {

    // Initialise the progress status object for the current content type key
    Count_T lExpectedTotalNbOfEventsInt = std::floor (iExpectedTotalNbOfEvents);
      
    // Update the progress status for the corresponding content type key
    ProgressStatusMap_T::iterator itProgressStatus =
      _progressStatusMap.find (iType);
    if (itProgressStatus != _progressStatusMap.end()) {
      ProgressStatus& lProgressStatus = itProgressStatus->second;
      //
      lExpectedTotalNbOfEventsInt += lProgressStatus.getActualNb();
      //
      lProgressStatus.setActualNb (lExpectedTotalNbOfEventsInt);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void EventQueue::
  updateStatus (const EventContentKey_T& iEventContentKey,
                const NbOfRequests_T& iExpectedTotalNbOfEvents) {

    // Initialise the progress status object for the current content type key
    const Count_T lExpectedTotalNbOfEventsInt =
      std::floor (iExpectedTotalNbOfEvents);
      
    // Update the progress status for the corresponding content type key
    NbOfEventsByContentKeyMap_T::iterator itNbOfEvents =
      _nbOfEvents.find (iEventContentKey);
    if (itNbOfEvents != _nbOfEvents.end()) {
      ProgressStatus& lProgressStatus = itNbOfEvents->second;
      lProgressStatus.setActualNb (lExpectedTotalNbOfEventsInt);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  const ProgressStatus& EventQueue::
  getStatus (const EventType::EN_EventType& iType) const {

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

    const ProgressStatus& oProgressStatus = itProgressStatus->second;
    return oProgressStatus;
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressStatus EventQueue::
  getStatus (const EventContentKey_T& iEventContentKey) const {
    
    NbOfEventsByContentKeyMap_T::const_iterator itNbOfEventsMap =
      _nbOfEvents.find (iEventContentKey);
    if (itNbOfEventsMap != _nbOfEvents.end()) {
      const ProgressStatus& oProgressStatus = itNbOfEventsMap->second;
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
  EventStruct EventQueue::popEvent() {
    assert (_eventList.empty() == false);

    /**
     * 1. Update the event queue itself.
     */
    // Get an iterator on the first event (sorted by date-time stamps)
    EventList_T::iterator itEvent = _eventList.begin();

    /**
     * Extract (a copy of) the corresponding Event structure. We make
     * a copy here, as the resulting EventStruct structure will be
     * returned by this method.
     */
    EventStruct lEventStruct = itEvent->second;

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
    // Retrieve the event type
    const EventType::EN_EventType& lEventType = lEventStruct.getEventType();

    // Retrieve the progress status specific to that event type
    const ProgressStatus& lEventTypeProgressStatus = getStatus (lEventType);

    // Update the progress status of the event structure, specific to
    // the content type key.
    lEventStruct.setTypeSpecificStatus (lEventTypeProgressStatus);

    /**
     * 2.2. Update the progress status specific to the content key (e.g.,
     *      demand stream key, DCP rule key).
     */
    // Extract the key of the event content
    const EventContentKey_T& lEventContentKey =
      lEventStruct.getEventContentKey();

    // Retrieve the progress status specific to that event content key
    const ProgressStatus& lEventContentKeyProgressStatus =
      getStatus (lEventContentKey);

    // Update the progress status of the event structure, specific to
    // the content type key.
    lEventStruct.setKeySpecificStatus (lEventContentKeyProgressStatus);

    /**
     * 2.3. Update the overall progress status.
     */
    // Update the overall progress status of the event structure
    lEventStruct.setOverallStatus (_progressStatus);

    //
    return lEventStruct;
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

    // Update the progress status for the corresponding event type
    const EventType::EN_EventType& lEventType = ioEventStruct.getEventType();
    ProgressStatusMap_T::iterator itProgressStatus =
      _progressStatusMap.find (lEventType);
    if (itProgressStatus != _progressStatusMap.end()) {
      ProgressStatus& lProgressStatus = itProgressStatus->second;
      ++lProgressStatus;
    }

    // Update the progress status for the corresponding event content key
    const EventContentKey_T& lEventContentKey =
      ioEventStruct.getEventContentKey();
    NbOfEventsByContentKeyMap_T::iterator itNbOfEventsMap =
      _nbOfEvents.find (lEventContentKey);
    if (itNbOfEventsMap != _nbOfEvents.end()) {
      ProgressStatus& lProgressStatus = itNbOfEventsMap->second;
      ++lProgressStatus;
    }

    return insertionSucceeded;
  }

}
