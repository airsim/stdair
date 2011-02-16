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
  EventQueue::EventQueue ()
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
  EventQueue::~EventQueue () {
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
    for (NbOfEventsByDemandStreamMap_T::const_iterator itNbOfEventsMap =
           _nbOfEvents.begin(); itNbOfEventsMap != _nbOfEvents.end();
         ++itNbOfEventsMap, ++demandStreamIdx) {

      const DemandStreamKeyStr_T& lDemandStreyKeyStr = itNbOfEventsMap->first;
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
    _progressStatus.setCurrentNb (DEFAULT_PROGRESS_STATUS);
    
    //
    _holderMap.clear();
    _eventList.clear();
    _nbOfEvents.clear();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void EventQueue::
  addStatus (const DemandStreamKeyStr_T& iDemandStreamKeyStr,
             const NbOfRequests_T& iExpectedTotalNbOfEvents) {

    /**
     * \note After the initialisation of the event queue (e.g., by a
     * call to the TRADEMGEN_Service::generateFirstRequests() method),
     * there are, by construction, exactly as many events as distinct
     * demand streams. Indeed, the event queue contains a single event
     * structure for every demand stream.
     */
    
    // Initialise the progress status object for the current demand stream
    const Count_T lExpectedTotalNbOfEventsInt =
      std::floor (iExpectedTotalNbOfEvents);
    const ProgressStatus lProgressStatus (1, lExpectedTotalNbOfEventsInt,
                                          lExpectedTotalNbOfEventsInt);
      
    // Insert the (Boost) progress display object into the dedicated map
    const bool hasInsertBeenSuccessful =
      _nbOfEvents.insert (NbOfEventsByDemandStreamMap_T::
                          value_type (iDemandStreamKeyStr,
                                      lProgressStatus)).second;

    if (hasInsertBeenSuccessful == false) {
      STDAIR_LOG_ERROR ("No progress_status can be inserted "
                        << "for the following DemandStream: "
                        << iDemandStreamKeyStr
                        << ". EventQueue: " << toString());
      throw EventException ("No progress_status can be inserted for the "
                            "following DemandStream: " + iDemandStreamKeyStr
                            + ". EventQueue: " + toString());
    }

    // Update the overall progress status
    _progressStatus.setExpectedNb (_progressStatus.getExpectedNb()
                                   + iExpectedTotalNbOfEvents);

    _progressStatus.setActualNb (_progressStatus.getActualNb()
                                   + iExpectedTotalNbOfEvents);
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressStatus EventQueue::
  getStatus (const DemandStreamKeyStr_T& iDemandStreamKey) const {
    
    NbOfEventsByDemandStreamMap_T::const_iterator itNbOfEventsMap =
      _nbOfEvents.find (iDemandStreamKey);
    if (itNbOfEventsMap != _nbOfEvents.end()) {
      const ProgressStatus& oProgressStatus = itNbOfEventsMap->second;
      return oProgressStatus;
    }

    return ProgressStatus();
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct EventQueue::popEvent() {
    assert (_eventList.empty() == false);

    // Get an iterator on the first event (sorted by date-time stamps)
    EventList_T::iterator itEvent = _eventList.begin();

    // Extract the corresponding Event structure
    EventStruct lEventStruct = itEvent->second;

    // Extract the key of the demand stream
    const DemandStreamKeyStr_T& lDemandStreamKeyStr =
      lEventStruct.getDemandStreamKey();

    // Retrieve the progress status specific to that demand stream
    const ProgressStatus& lProgressStatus = getStatus (lDemandStreamKeyStr);

    // Update the progress status of the event structure, specific to
    // the demand stream
    lEventStruct.setSpecificStatus (lProgressStatus);

    // Update the (current number part of the) overall progress
    // status, to account for the event that is being popped out of
    // the event queue
    ++_progressStatus;
    
    // Update the overall progress status of the event structure
    lEventStruct.setOverallStatus (_progressStatus);

    // Remove the event, which has just been retrieved
    _eventList.erase (itEvent);

    //
    return lEventStruct;
  }

  // //////////////////////////////////////////////////////////////////////
  bool EventQueue::addEvent (EventStruct& ioEventStruct) {
    bool insertionSucceeded =
      _eventList.insert (EventListElement_T (ioEventStruct._eventTimeStamp,
                                             ioEventStruct)).second;

    /**
       If the insertion has not been successful, try repeatedly until the
       insertion becomes successful.
       <br>The date-time is counted in milliseconds (1e-3 second). Hence,
       one thousand (1e3) of attempts correspond to 1 second.
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

    // Extract the corresponding demand stream key
    const DemandStreamKeyStr_T& lDemandStreamKeyStr =
      ioEventStruct.getDemandStreamKey();

    // Update the progress status for the corresponding demand stream
    NbOfEventsByDemandStreamMap_T::iterator itNbOfEventsMap =
      _nbOfEvents.find (lDemandStreamKeyStr);
    if (itNbOfEventsMap != _nbOfEvents.end()) {
      ProgressStatus& lProgressStatus = itNbOfEventsMap->second;
      ++lProgressStatus;
    }

    return insertionSucceeded;
  }

}
