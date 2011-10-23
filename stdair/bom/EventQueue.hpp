#ifndef __STDAIR_BOM_EVENTQUEUE_HPP
#define __STDAIR_BOM_EVENTQUEUE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/ProgressStatus.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/EventQueueKey.hpp>
#include <stdair/bom/EventQueueTypes.hpp>
#include <stdair/bom/EventTypes.hpp>

namespace stdair {

  /**
   * @brief Class holding event structures.
   * <br>The type of events are for instance booking requests,
   * optimisation notifications, schedule changes.
   */
  struct EventQueue : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // ////////// Type definitions ////////////
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef EventQueueKey Key_T;

    
  public:
    // /////////// Getters ///////////////
    /** Get the event queue key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }
    
    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
    /** Get the overall progress status (for the whole event queue). */
    const ProgressStatus& getStatus() const {
      return _progressStatus;
    }
    /** Get the current number of events (for the whole event queue). */
    const Count_T& getCurrentNbOfEvents() const {
      return _progressStatus.getCurrentNb();
    }
    /** Get the expected total number of events (for the whole event queue). */
    const Count_T& getExpectedTotalNbOfEvents() const {
      return _progressStatus.getExpectedNb();
    }
    /** Get the actual total number of events (for the whole event queue). */
    const Count_T& getActualTotalNbOfEvents() const {
      return _progressStatus.getActualNb();
    }

    // /////////// Setters ///////////////
    /** Set/update the progress status. */
    void setStatus (const ProgressStatus& iProgressStatus) {
      _progressStatus = iProgressStatus;
    }
    /** Set/update the progress status. */
    void setStatus (const Count_T& iCurrentNbOfEvents,
                    const Count_T& iExpectedTotalNbOfEvents,
                    const Count_T& iActualTotalNbOfEvents) {
      _progressStatus.setCurrentNb (iCurrentNbOfEvents);
      _progressStatus.setExpectedNb (iExpectedTotalNbOfEvents);
      _progressStatus.setActualNb (iActualTotalNbOfEvents);
    }
    /** Set/update the progress status. */
    void setStatus (const Count_T& iCurrentNbOfEvents,
                    const Count_T& iActualTotalNbOfEvents) {
      _progressStatus.setCurrentNb (iCurrentNbOfEvents);
      _progressStatus.setActualNb (iActualTotalNbOfEvents);
    }
    /** Set the current number of events (for the whole event queue). */
    void setCurrentNbOfEvents (const Count_T& iCurrentNbOfEvents) {
      _progressStatus.setCurrentNb (iCurrentNbOfEvents);
    }
    /** Set the expected total number of events (for the whole event queue). */
    void setExpectedTotalNbOfEvents (const Count_T& iExpectedTotalNbOfEvents) {
      _progressStatus.setExpectedNb (iExpectedTotalNbOfEvents);
    }
    /** Set the actual total number of events (for the whole event queue). */
    void setActualTotalNbOfEvents (const Count_T& iActualTotalNbOfEvents) {
      _progressStatus.setActualNb (iActualTotalNbOfEvents);
    }

    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << toString();
    }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) {
    }

    /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the  key. */
    const std::string describeKey() const {
      return _key.toString();
    }
    
    /*
     * @brief Display the full content of the event queue, with all
     * its demand streams.
     * <br>That method can be very consuming (in time, CPU and
     * memory) when there are a lot of demand streams (e.g., several
     * hundreds of thousands). Call it only for debug purposes.
    */
    std::string display() const;
    
    
  public:
    // ////////// Business methods /////////
    /**
     * Reset the event queue.
     * <br>The event queue is fully emptied.
     */
    void reset();
    
    /**
     * Pop the next coming (in time) event, and remove it from the
     * event queue.
     * <ul>
     *   <li>The next coming (in time) event corresponds to the event
     *     having the earliest date-time stamp. In other words, it is
     *     the first/front element of the event queue.</li>
     *   <li>That (first) event/element is then removed from the event
     *     queue</li>
     *   <li>The progress status is updated for the corresponding
     *     demand stream.</li>
     * </ul>
     */
    EventStruct popEvent();

    /**
     * Add event.
     * <br>If there already is an event with the same date-time, move
     * the given event one nanosecond forward, and retry the insertion
     * until it succeeds.
     * <br>That method:
     * <ul>
     *   <li>first adds the event structure in the dedicated list,</li>
     *   <li>then retrieves the corresponding demand stream,</li>
     *   <li>and update accordingly the corresponding progress
     *     statuses.</li>
     * </ul>
     * @param stdair::EventStruct& The reference on EventStruct is not
     *   constant, because the EventStruct object can be altered: its
     *   date-time stamp can be changed accordingly to the location
     *   where it has been inserted in the event queue.
     */
    bool addEvent (EventStruct&);

    /**
     * States whether the event queue has reached the end.
     * <br>For now, that method states whether the event queue is empty.
     */
    bool isQueueDone() const;

    /**
     * Initialise the progress statuses for each demand stream.
     * <br>For each demand stream, the progress status is actually
     * a pair of counters:
     * <ul>
     *   <li>The current number of (already generated) events, summed
     *       over all the demand streams. That number is initialised
     *       to 0 (no event has been generated yet) for each demand
     *       stream.</li>
     *   <li>The total number of events (to be generated), also summed
     *       over all the demand streams. That number is calculated
     *       for each demand stream.</li>
     * </ul>
     */
    void addStatus (const DemandStreamKeyStr_T&,
                    const NbOfRequests_T& iExpectedTotalNbOfEvents);

    /**
     * Calculate the progress status.
     * <br>The progress is status is the ratio of:
     * <ul>
     *   <li>the current number of events, summed over all the demand
     *       streams,</li>
     *   <li>over the total number of events, also summed over all the demand
     *       streams.</li>
     * </ul>
     */
    ProgressPercentage_T calculateProgress() const {
      return _progressStatus.progress();
    }

    /**
     * Retrieve the status for a given demand stream.
     * <br>The status is composed of, for the given demand stream:
     * <ul>
     *   <li>the current number of events (already generated),</li>
     *   <li>the total number of events (to be generated).</li>
     * </ul>
     * <br>Normally, that method has not to be used directly, as
     * EventStruct::getStatus() gives the same information, just after
     * a call to EventQueue::popEvent().
     */
    ProgressStatus getStatus (const DemandStreamKeyStr_T&) const;


  public:
    // ////////// Debug methods /////////
    /** Queue size */
    Count_T getQueueSize() const;

    /** Is queue empty */
    bool isQueueEmpty() const;

    
  protected:
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    EventQueue (const Key_T&);
    /** Default copy constructor. */
    EventQueue (const EventQueue&);
    /** Destructor. */
    ~EventQueue ();
  private:
    /** Default constructor. */
    EventQueue ();
    

  protected:
    // ////////// Attributes /////////
    /** Primary key (ID). */
    Key_T _key;

    /** Pointer on the parent class (BomRoot). */
    BomAbstract* _parent;

    /** Map holding the children (DemandStream objects). */
    HolderMap_T _holderMap;

    /** List of events. */
    EventList_T _eventList;

    /**
     * Status (current number of events, total expected and actual
     * number of events) for each demand stream.
     */
    NbOfEventsByDemandStreamMap_T _nbOfEvents;
    
    /**
     * Counters holding the overall progress status.
     */
    ProgressStatus _progressStatus;
  };

}
#endif // __STDAIR_BOM_EVENTQUEUE_HPP
