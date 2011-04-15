#ifndef __STDAIR_BAS_EVENTSTRUCT_HPP
#define __STDAIR_BAS_EVENTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/stdair_event_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/basic/EventType.hpp>
#include <stdair/bom/EventTypes.hpp>
#include <stdair/bom/BookingRequestTypes.hpp>
#include <stdair/bom/OptimisationNotificationTypes.hpp>
#include <stdair/bom/SnapshotTypes.hpp>

namespace stdair {

  /**
   * Structure holding the details of an event.
   *
   * \note No event should be scheduled before the date-time
   *       corresponding to the DEFAULT_EVENT_OLDEST_DATETIME constant
   *       (as of Feb. 2011, that date is set to Jan. 1, 2010). That
   *       constant is specified in the stdair/basic/BasConst.cpp
   *       file. In other words, the simulation should not specified
   *       to start before that date-time.
   */
  struct EventStruct : public StructAbstract {
    // Friend classes and structures
    friend struct EventQueue;

    // ///////////// Getters ///////////
  public:
    /** Get the event type */
    const EventType::EN_EventType& getEventType() const {
      return _eventType;
    }

    /**
     * Get a reference on the booking request referred to by event.
     *
     * \note When that event is not of type booking request
     *       (EventType::BKG_REQ), an assertion fails.
     */
    const BookingRequestStruct& getBookingRequest() const {
      assert (_bookingRequest != NULL);
      return *_bookingRequest;
    }

    /**
     * Get a reference on the optimisation notification referred to by event.
     *
     * \note When that event is not of type optimisation notification
     * for optimisation notification (EventType::OPT_NOT_4_FD), an
     * assertion fails.
     */
    const OptimisationNotificationStruct&
    getOptimisationNotificationStruct() const {
      assert (_optimisationNotification != NULL);
      return *_optimisationNotification;
    }
    
    /**
     * Get a reference on the snapshot referred to by event.
     *
     * \note When that event is not of type snapshot 
     * for snapshot (EventType::OPT_NOT_4_FD), an
     * assertion fails.
     */
    const SnapshotStruct& getSnapshotStruct() const {
      assert (_snapshot != NULL);
      return *_snapshot;
    }

    /**
     * Get the progress status specific to that event type.
     *
     * Note that that progress status may not be up-to-date. That
     * attribute is up-to-date only after a call to the
     * EventQueue::popEvent() method.
     */
    const ProgressStatus& getTypeSpecificStatus() const {
      return _typeSpecificProgressStatus;
    }
    /** Get the current number of events. See the getTypeSpecificStatus()
        method for details. */
    const Count_T& getTypeSpecificCurrentNbOfEvents() const {
      return _typeSpecificProgressStatus.getCurrentNb();
    }
    /** Get the expected total number of events. See the
        getTypeSpecificStatus() method for details. */
    const Count_T& getTypeSpecificExpectedTotalNbOfEvents() const {
      return _typeSpecificProgressStatus.getExpectedNb();
    }
    /** Get the actual total number of events. See the
        getTypeSpecificStatus() method for details. */
    const Count_T& getTypeSpecificActualTotalNbOfEvents() const {
      return _typeSpecificProgressStatus.getActualNb();
    }

    /**
     * Get the progress status specific to the content key for
     * that event.
     *
     * Note that that progress status may not be up-to-date. That
     * attribute is up-to-date only after a call to the
     * EventQueue::popEvent() method.
     */
    const ProgressStatus& getKeySpecificStatus() const {
      return _keySpecificProgressStatus;
    }
    /** Get the current number of events. See the getKeySpecificStatus()
        method for details. */
    const Count_T& getKeySpecificCurrentNbOfEvents() const {
      return _keySpecificProgressStatus.getCurrentNb();
    }
    /** Get the expected total number of events. See the
        getKeySpecificStatus() method for details. */
    const Count_T& getKeySpecificExpectedTotalNbOfEvents() const {
      return _keySpecificProgressStatus.getExpectedNb();
    }
    /** Get the actual total number of events. See the
        getKeySpecificStatus() method for details. */
    const Count_T& getKeySpecificActualTotalNbOfEvents() const {
      return _keySpecificProgressStatus.getActualNb();
    }

    /**
     * Get the overall progress status (absolute, for all the events).
     *
     * Note that that progress status may not be up-to-date. That
     * attribute is up-to-date only after a call to the
     * EventQueue::popEvent() method.
     */
    const ProgressStatus& getOverallStatus() const {
      return _overallProgressStatus;
    }
    /** Get the current number of events. See the getOverallStatus()
        method for details. */
    const Count_T& getOverallCurrentNbOfEvents() const {
      return _overallProgressStatus.getCurrentNb();
    }
    /** Get the expected total number of events. See the
        getOverallStatus() method for details. */
    const Count_T& getOverallExpectedTotalNbOfEvents() const {
      return _overallProgressStatus.getExpectedNb();
    }
    /** Get the expected total number of events. See the
        getOverallStatus() method for details. */
    const Count_T& getOverallActualTotalNbOfEvents() const {
      return _overallProgressStatus.getActualNb();
    }

    
    // ///////////// Setters ///////////
  public:
    /** Set/update the progress status specific to that event type. */
    void setTypeSpecificStatus (const ProgressStatus& iProgressStatus) {
      _typeSpecificProgressStatus = iProgressStatus;
    }
    /** Set/update the progress status specific to that event type. */
    void setTypeSpecificStatus (const Count_T& iCurrentNbOfEvents,
                                const Count_T& iExpectedTotalNbOfEvents,
                                const Count_T& iActualTotalNbOfEvents) {
      _typeSpecificProgressStatus.setCurrentNb (iCurrentNbOfEvents);
      _typeSpecificProgressStatus.setExpectedNb (iExpectedTotalNbOfEvents);
      _typeSpecificProgressStatus.setActualNb (iActualTotalNbOfEvents);
    }
    /** Set/update the progress status specific to that event type. */
    void setTypeSpecificStatus (const Count_T& iCurrentNbOfEvents,
                                const Count_T& iActualTotalNbOfEvents) {
      _typeSpecificProgressStatus.setCurrentNb (iCurrentNbOfEvents);
      _typeSpecificProgressStatus.setExpectedNb (iActualTotalNbOfEvents);
      _typeSpecificProgressStatus.setActualNb (iActualTotalNbOfEvents);
    }

    /** Set/update the progress status specific to the content key
        for that event. */
    void setKeySpecificStatus (const ProgressStatus& iProgressStatus) {
      _keySpecificProgressStatus = iProgressStatus;
    }
    /** Set/update the progress status specific to the content key
        for that event. */
    void setKeySpecificStatus (const Count_T& iCurrentNbOfEvents,
                               const Count_T& iExpectedTotalNbOfEvents,
                               const Count_T& iActualTotalNbOfEvents) {
      _keySpecificProgressStatus.setCurrentNb (iCurrentNbOfEvents);
      _keySpecificProgressStatus.setExpectedNb (iExpectedTotalNbOfEvents);
      _keySpecificProgressStatus.setActualNb (iActualTotalNbOfEvents);
    }
    /** Set/update the progress status specific to the demand stream
        for that event. */
    void setKeySpecificStatus (const Count_T& iCurrentNbOfEvents,
                               const Count_T& iActualTotalNbOfEvents) {
      _keySpecificProgressStatus.setCurrentNb (iCurrentNbOfEvents);
      _keySpecificProgressStatus.setExpectedNb (iActualTotalNbOfEvents);
      _keySpecificProgressStatus.setActualNb (iActualTotalNbOfEvents);
    }


    /** Set/update the overall progress status (absolute, for all the
        events). */
    void setOverallStatus (const ProgressStatus& iProgressStatus) {
      _overallProgressStatus = iProgressStatus;
    }
    /** Set/update the overall progress status (absolute, for all the
        events). */
    void setOverallStatus (const Count_T& iCurrentNbOfEvents,
                           const Count_T& iExpectedTotalNbOfEvents,
                           const Count_T& iActualTotalNbOfEvents) {
      _overallProgressStatus.setCurrentNb (iCurrentNbOfEvents);
      _overallProgressStatus.setExpectedNb (iExpectedTotalNbOfEvents);
      _overallProgressStatus.setActualNb (iActualTotalNbOfEvents);
    }
    /** Set/update the overall progress status (absolute, for all the
        events). */
    void setOverallStatus (const Count_T& iCurrentNbOfEvents,
                           const Count_T& iActualTotalNbOfEvents) {
      _overallProgressStatus.setCurrentNb (iCurrentNbOfEvents);
      _overallProgressStatus.setExpectedNb (iActualTotalNbOfEvents);
      _overallProgressStatus.setActualNb (iActualTotalNbOfEvents);
    }


    // ////////// Display methods //////////
  public:
    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;

    
    // ////////// Constructors and destructors /////////
  public:
    /** Constructor for events corresponding to booking requests. */
    EventStruct (const EventType::EN_EventType&, BookingRequestPtr_T);
    /** Constructor for events corresponding to optimisation requests. */
    EventStruct (const EventType::EN_EventType&, const DateTime_T& iDCPDate,
                 OptimisationNotificationPtr_T);
    /** Constructor for events corresponding to snapshot requests. */
    EventStruct (const EventType::EN_EventType&, SnapshotPtr_T);
    /** Copy constructor. */
    EventStruct (const EventStruct&);

    /** Destructor. */
    ~EventStruct();
    
  private:
    /** Default constructor. */
    EventStruct();

    
    // ////////////////// Attributes //////////////////
  private:
    /**
     * Event type.
     */
    EventType::EN_EventType _eventType;

    /**
     * Reprentative timestamp of the event, which is the number of
     * milliseconds between the event date-time and the default
     * event date-time (2010-01-01 00:00:00).
     */
    LongDuration_T _eventTimeStamp;
    
    /**
     * Pointer to the booking request referred to by the event.
     */
    BookingRequestPtr_T _bookingRequest;

    /**
     * Pointer to the optimisation notification referred to by the event.
     */
    OptimisationNotificationPtr_T _optimisationNotification;

    /**
     * Pointer to the snapshot referred to by the event.
     */
    SnapshotPtr_T _snapshot;

    /**
     * Counters holding the progress status.
     *
     * That attribute is altered only for the EventStruct instance
     * returned by the popEvent() method. For all the EventStruct
     * instances held by the EventQueue object, that attribute is not
     * set (and not up-to-date).
     *
     * Indeed, the progress statuses are kept up-to-date in parallel
     * (i.e., independently) of the EventStruct instances. They are
     * kept in a dedicated map, stored within the EventQueue object.
     */
    ProgressStatus _typeSpecificProgressStatus;

    /**
     * Counters holding the progress status.
     *
     * That attribute is altered only for the EventStruct instance
     * returned by the popEvent() method. For all the EventStruct
     * instances held by the EventQueue object, that attribute is not
     * set (and not up-to-date).
     *
     * Indeed, the progress statuses are kept up-to-date in parallel
     * (i.e., independently) of the EventStruct instances. They are
     * kept in a dedicated map, stored within the EventQueue object.
     */
    ProgressStatus _keySpecificProgressStatus;

    /**
     * Counters holding the progress status.
     *
     * That attribute is altered only for the EventStruct instance
     * returned by the popEvent() method. For all the EventStruct
     * instances held by the EventQueue object, that attribute is not
     * set (and not up-to-date).
     *
     * Indeed, the progress statuses are kept up-to-date in parallel
     * (i.e., independently) of the EventStruct instances. They are
     * kept in a dedicated map, stored within the EventQueue object.
     */
    ProgressStatus _overallProgressStatus;
  };

}
#endif // __STDAIR_BAS_EVENTSTRUCT_HPP
