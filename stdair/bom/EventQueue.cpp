// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/make_shared.hpp>
// StdAir
#include <stdair/bom/EventStruct.hpp>
#include <stdair/bom/EventQueue.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  EventQueue::EventQueue () {
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventQueue::EventQueue (const EventQueue& iEventQueue) {
    assert (false);
  }
  
  // //////////////////////////////////////////////////////////////////////
  EventQueue::~EventQueue () {
    _eventList.clear();
    _nbOfEvents.clear();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void EventQueue::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string EventQueue::describe() const {
    std::ostringstream oStr;
    oStr << _eventList.size() << std::endl;

    unsigned int demandStreamIdx = 1;
    for (NbOfEventsByDemandStreamMap_T::const_iterator itNbOfEventsMap =
           _nbOfEvents.begin(); itNbOfEventsMap != _nbOfEvents.end();
         ++itNbOfEventsMap, ++demandStreamIdx) {
      const DemandStreamKeyStr_T& lDemandStreyKeyStr = itNbOfEventsMap->first;
      oStr << "[" << demandStreamIdx << "][" << lDemandStreyKeyStr << "] ";
      const NbOfEventsPair_T& lNbOfEventsPair = itNbOfEventsMap->second;
      const stdair::Count_T& lCurrentNbOfEvents = lNbOfEventsPair.first;
      const stdair::Count_T& lExpectedTotalNbOfEvents = lNbOfEventsPair.second;
      oStr << lCurrentNbOfEvents << " / " << lExpectedTotalNbOfEvents;
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
  void EventQueue::
  initProgressDisplays (ProgressDisplayMap_T& ioProgressDisplayMap) {

    ProgressDisplayMap_T::iterator itProgressDisplayMap =
      ioProgressDisplayMap.begin();
    for (NbOfEventsByDemandStreamMap_T::const_iterator itNbOfEventsMap =
           _nbOfEvents.begin();  itNbOfEventsMap != _nbOfEvents.end();
          ++itProgressDisplayMap, ++itNbOfEventsMap) {
      // Demand stream
      const DemandStreamKeyStr_T& lDemandStreyKeyStr = itNbOfEventsMap->first;
      
      // Expected total number of events for the current demand stream
      const NbOfEventsPair_T& lNbOfEventsPair = itNbOfEventsMap->second;
      const Count_T& lExpectedTotalNbOfEvents = lNbOfEventsPair.second;

      // Initialise the (Boost) progress display object for the
      // current demand stream
      ProgressDisplayPtr lProgressDisplayPtr =
        boost::make_shared<boost::progress_display> (lExpectedTotalNbOfEvents);

      // Insert the (Boost) progress display object into the dedicated map
      const bool hasInsertBeenSuccessful =
        ioProgressDisplayMap.insert (ProgressDisplayMap_T::
                                     value_type (lDemandStreyKeyStr,
                                                 lProgressDisplayPtr)).second;

      if (hasInsertBeenSuccessful == false) {
        STDAIR_LOG_ERROR ("No Boost progress_display can be inserted "
                          << "for the following DemandStream: "
                          << lDemandStreyKeyStr
                          << ". EventQueue: " << describe());
        // TODO: throw an exception?
      }
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  NbOfEventsPair_T EventQueue::
  getStatus (const DemandStreamKeyStr_T& iDemandStreamKey) const {
    Count_T oCurrentNbOfEvents = 0.0;
    Count_T oTotalNbOfEvents = 0.0;
    
    NbOfEventsByDemandStreamMap_T::const_iterator itNbOfEventsMap =
      _nbOfEvents.find (iDemandStreamKey);
    if (itNbOfEventsMap != _nbOfEvents.end()) {
      const NbOfEventsPair_T& lNbOfEventsPair = itNbOfEventsMap->second;
      oCurrentNbOfEvents = lNbOfEventsPair.first;
      oTotalNbOfEvents = lNbOfEventsPair.second;
    }

    return NbOfEventsPair_T (oCurrentNbOfEvents, oTotalNbOfEvents);
  }

  // //////////////////////////////////////////////////////////////////////
  Count_T EventQueue::calculateTotalNbOfEvents() const {
    Count_T oTotalNbOfEvents = 0.0;

    for (NbOfEventsByDemandStreamMap_T::const_iterator itNbOfEventsMap =
           _nbOfEvents.begin(); itNbOfEventsMap != _nbOfEvents.end();
         ++itNbOfEventsMap) {
      const NbOfEventsPair_T& lNbOfEventsPair = itNbOfEventsMap->second;
      const Count_T& lExpectedTotalNbOfEvents = lNbOfEventsPair.second;
      oTotalNbOfEvents += lExpectedTotalNbOfEvents;
    }
    
    return oTotalNbOfEvents;
  }
  
  // //////////////////////////////////////////////////////////////////////
  ProgressPercentage_T EventQueue::calculateProgress() const {
    ProgressPercentage_T oProgress = 0.0;
    Count_T oCurrentNbOfEvents = 0.0;
    Count_T oTotalNbOfEvents = 0.0;
    
    for (NbOfEventsByDemandStreamMap_T::const_iterator itNbOfEventsMap =
           _nbOfEvents.begin(); itNbOfEventsMap != _nbOfEvents.end();
         ++itNbOfEventsMap) {
      const NbOfEventsPair_T& lNbOfEventsPair = itNbOfEventsMap->second;
      
      const Count_T& lCurrentNbOfEvents = lNbOfEventsPair.first;
      oCurrentNbOfEvents += lCurrentNbOfEvents;
      
      const Count_T& lExpectedTotalNbOfEvents = lNbOfEventsPair.second;
      oTotalNbOfEvents += lExpectedTotalNbOfEvents;
    }

    oProgress = oCurrentNbOfEvents / oTotalNbOfEvents;
    return oProgress;
  }

  // //////////////////////////////////////////////////////////////////////
  EventStruct& EventQueue::popEvent() {
    assert (_eventList.empty() == false);

    // Get an iterator on the first event (sorted by date-time stamps)
    EventList_T::iterator itEvent = _eventList.begin();

    // Extract the corresponding Event structure
    EventStruct& lEventStruct = itEvent->second;

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
      ++(lEventTimeStamp);

      // Retry to insert into the event queue
      insertionSucceeded =
        _eventList.insert (EventListElement_T (ioEventStruct._eventTimeStamp,
                                               ioEventStruct)).second;
    }

    // Extract the corresponding demand stream key
    const DemandStreamKeyStr_T& lDemandStreamKeyStr =
      ioEventStruct.getDemandStreamKey();

    NbOfEventsByDemandStreamMap_T::iterator itNbOfEventsMap =
      _nbOfEvents.find (lDemandStreamKeyStr);
    if (itNbOfEventsMap != _nbOfEvents.end()) {
      NbOfEventsPair_T& lNbOfEventsPair = itNbOfEventsMap->second;
      stdair::Count_T& lCurrentNbOfEvents = lNbOfEventsPair.first;
      ++lCurrentNbOfEvents;
    }
    
    return insertionSucceeded;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void EventQueue::eraseLastUsedEvent() {
    assert (isQueueDone () == false);
    _eventList.erase (_eventList.begin());
  }
  
}
