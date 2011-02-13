#ifndef __STDAIR_BOM_EVENTQUEUE_HPP
#define __STDAIR_BOM_EVENTQUEUE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_basic_types.hpp>
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
     * Initialise the (Boost) progress display objects, passed as parameter.
     * <br>The maximum, for each progress display object, is set to
     * be the expected total number of events.
     */
    void initProgressDisplays (ProgressDisplayMap_T&);

    /**
     * Retrieve the status for a given demand stream.
     * <br>The status is composed of, for the given demand stream:
     * <ul>
     *   <li>the current number of events (already generated),</li>
     *   <li>the total number of events (to be generated).</li>
     * </ul>
     */
    NbOfEventsPair_T getStatus (const DemandStreamKeyStr_T&) const;

    /**
     * Calculate the expected total number of events to be generated.
     * <br>The total number is the sum, for all the demand streams,
     * of the expected number of events.
    */
    Count_T calculateTotalNbOfEvents() const;

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
    ProgressPercentage_T calculateProgress() const;


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
     * Status (current number of events, total number of events) for
     * each demand stream.
     */
    NbOfEventsByDemandStreamMap_T _nbOfEvents;
  };

}
#endif // __STDAIR_BOM_EVENTQUEUE_HPP
