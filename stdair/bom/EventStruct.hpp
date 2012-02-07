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
#include <stdair/bom/CancellationTypes.hpp>
#include <stdair/bom/RMEventTypes.hpp>
#include <stdair/bom/BreakPointTypes.hpp>

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

    // ///////////// Getters ///////////
  public:
    /** Get the event type */
    const EventType::EN_EventType& getEventType() const {
      return _eventType;
    }  

    /** Get the event time stamp */
    const LongDuration_T& getEventTimeStamp() const {
      return _eventTimeStamp;
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
     * Get a reference on the cancellation referred to by event.
     *
     * \note When that event is not of type cancellation
     *       (EventType::CX), an assertion fails.
     */
    const CancellationStruct& getCancellation() const {
      assert (_cancellation != NULL);
      return *_cancellation;
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
     * Get a reference on the RM event referred to by the generic event.
     *
     * \note When that event is not of type RM event
     * for snapshot (EventType::OPT_NOT_4_FD), an
     * assertion fails.
     */
    const RMEventStruct& getRMEvent() const {
      assert (_rmEvent != NULL);
      return *_rmEvent;
    }   

    /**
     * Get a reference on the break point referred to by event.
     *
     * \note When that event is not of type booking break point
     *       (EventType::BRK_PT), an assertion fails.
     */
    const BreakPointStruct& getBreakPoint() const {
      assert (_breakPoint != NULL);
      return *_breakPoint;
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
    /** Default constructor. */
    EventStruct();
    /** Constructor for events corresponding to booking requests. */
    EventStruct (const EventType::EN_EventType&, BookingRequestPtr_T);
    /** Constructor for events corresponding to cancellations. */
    EventStruct (const EventType::EN_EventType&, CancellationPtr_T);
    /** Constructor for events corresponding to optimisation requests. */
    EventStruct (const EventType::EN_EventType&, const DateTime_T& iDCPDate,
                 OptimisationNotificationPtr_T);
    /** Constructor for events corresponding to snapshot requests. */
    EventStruct (const EventType::EN_EventType&, SnapshotPtr_T);
    /** Constructor for events corresponding to RM events. */
    EventStruct (const EventType::EN_EventType&, RMEventPtr_T);   
    /** Constructor for events corresponding to Break Point events. */
    EventStruct (const EventType::EN_EventType&, BreakPointPtr_T);
    /** Copy constructor. */
    EventStruct (const EventStruct&);

    /** Destructor. */
    ~EventStruct();    

    // ////////// Modifiers /////////
  public:
    /**
     * Increment the date-time stamp which is counted in milliseconds.
     * 
     * This incrementation of one millisecond is needed when the
     * insertion in the event queue failed, that is to say when an
     * event with the exact same time stamp has already been inserted
     * in the queue.
     */
    void incrementEventTimeStamp();
    
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
     * Pointer to the cancellation referred to by the event.
     */
    CancellationPtr_T _cancellation;

    /**
     * Pointer to the optimisation notification referred to by the event.
     */
    OptimisationNotificationPtr_T _optimisationNotification;

    /**
     * Pointer to the snapshot referred to by the event.
     */
    SnapshotPtr_T _snapshot;

    /**
     * Pointer to the RM event referred to by the event.
     */
    RMEventPtr_T _rmEvent; 

    /**
     * Pointer to the break point referred to by the event.
     */
    BreakPointPtr_T _breakPoint;
  };

}
#endif // __STDAIR_BAS_EVENTSTRUCT_HPP
