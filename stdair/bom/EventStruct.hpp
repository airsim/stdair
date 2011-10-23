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
    /** Constructor for events corresponding to optimisation requests. */
    EventStruct (const EventType::EN_EventType&, const DateTime_T& iDCPDate,
                 OptimisationNotificationPtr_T);
    /** Constructor for events corresponding to snapshot requests. */
    EventStruct (const EventType::EN_EventType&, SnapshotPtr_T);
    /** Copy constructor. */
    EventStruct (const EventStruct&);

    /** Destructor. */
    ~EventStruct();

    
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
  };

}
#endif // __STDAIR_BAS_EVENTSTRUCT_HPP
