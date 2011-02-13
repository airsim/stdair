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
#include <stdair/stdair_demand_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/basic/EventType.hpp>
#include <stdair/bom/EventTypes.hpp>
#include <stdair/bom/BookingRequestTypes.hpp>

namespace stdair {

  /** Structure holding the details of an event. */
  struct EventStruct : public StructAbstract {
    // Friend classes and structures
    friend struct EventQueue;

    // ///////////// Getters ///////////
  public:
    /** Get the event type */
    const EventType::EN_EventType& getEventType () const {
      return _eventType;
    }
    
    /** Get the Request event. */
    const BookingRequestStruct& getBookingRequest () const {
      assert (_request != NULL);
      return *_request;
    }

    /** Get the demand stream of the event. */
    const DemandStreamKeyStr_T& getDemandStreamKey () const {
      return _demandStreamKeyStr;
    }

    /**
     * Get the progress status specific to the demand stream for that event.
     * <br>Note that that progress status may not be up-to-date. That
     * attribute is up-to-date only after a call to the
     * EventQueue::popEvent() method.
     */
    const NbOfEventsPair_T& getSpecificStatus() const {
      return _specificProgressStatus;
    }
    /** Get the current number of events. See the getSpecificStatus()
        method for details. */
    const Count_T& getSpecificCurrentNbOfEvents() const {
      return _specificProgressStatus.first;
    }
    /** Get the expected total number of events. See the
        getSpecificStatus() method for details. */
    const Count_T& getSpecificExpectedTotalNbOfEvents() const {
      return _specificProgressStatus.second;
    }

    /**
     * Get the overall progress status (absolute, for all the events).
     * <br>Note that that progress status may not be up-to-date. That
     * attribute is up-to-date only after a call to the
     * EventQueue::popEvent() method.
     */
    const NbOfEventsPair_T& getOverallStatus() const {
      return _overallProgressStatus;
    }
    /** Get the current number of events. See the getOverallStatus()
        method for details. */
    const Count_T& getOverallCurrentNbOfEvents() const {
      return _overallProgressStatus.first;
    }
    /** Get the expected total number of events. See the
        getOverallStatus() method for details. */
    const Count_T& getOverallExpectedTotalNbOfEvents() const {
      return _overallProgressStatus.second;
    }

    
    // ///////////// Setters ///////////
  public:
    /** Set/update the progress status specific to the demand stream
        for that event. */
    void setSpecificStatus (const NbOfEventsPair_T& iNbOfEventsPair) {
      _specificProgressStatus = iNbOfEventsPair;
    }
    /** Set/update the progress status specific to the demand stream
        for that event. */
    void setSpecificStatus (const Count_T& iCurrentNbOfEvents,
                            const Count_T& iExpectedTotalNbOfEvents) {
      _specificProgressStatus.first = iCurrentNbOfEvents;
      _specificProgressStatus.second = iExpectedTotalNbOfEvents;
    }

    /** Set/update the overall progress status (absolute, for all the
        events). */
    void setOverallStatus (const NbOfEventsPair_T& iNbOfEventsPair) {
      _overallProgressStatus = iNbOfEventsPair;
    }
    /** Set/update the overall progress status (absolute, for all the
        events). */
    void setOverallStatus (const Count_T& iCurrentNbOfEvents,
                           const Count_T& iExpectedTotalNbOfEvents) {
      _overallProgressStatus.first = iCurrentNbOfEvents;
      _overallProgressStatus.second = iExpectedTotalNbOfEvents;
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
    /** Constructor. */
    EventStruct (const EventType::EN_EventType&, const DemandStreamKeyStr_T&, 
                 BookingRequestPtr_T);
    /** Copy constructor. */
    EventStruct (const EventStruct&);

    /** Destructor. */
    ~EventStruct ();
    
  private:
    /** Default constructors. */
    EventStruct ();

    
    // ////////// Attributes //////////
  private:
    /** Event type */
    EventType::EN_EventType _eventType;

    /** Reprentative timestamp of the event, which is the number of
        milliseconds between the event date-time and the default
        date-time (2010-01-01 00:00:00) */
    LongDuration_T _eventTimeStamp;
    
    /** When the event is a booking request, the following attribute
        contains the key of the corresponding demand stream. */
    DemandStreamKeyStr_T _demandStreamKeyStr;
    
    /** Pointer to the booking request event */
    BookingRequestPtr_T _request;

    /**
     * Pair of counters holding the progress status.
     * <br>That attribute is altered only for the EventStruct instance
     * returned by the popEvent() method. For all the EventStruct
     * instances held by the EventQueue object, that attribute is not
     * set (and not up-to-date).
     * <br>Indeed, the progress statuses are kept up-to-date in
     * parallel (i.e., independently) of the EventStruct
     * instances. They are kept in a dedicated map, stored within the
     * EventQueue object.
     */
    NbOfEventsPair_T _specificProgressStatus;

    /**
     * Pair of counters holding the progress status.
     * <br>That attribute is altered only for the EventStruct instance
     * returned by the popEvent() method. For all the EventStruct
     * instances held by the EventQueue object, that attribute is not
     * set (and not up-to-date).
     * <br>Indeed, the progress statuses are kept up-to-date in
     * parallel (i.e., independently) of the EventStruct
     * instances. They are kept in a dedicated map, stored within the
     * EventQueue object.
     */
    NbOfEventsPair_T _overallProgressStatus;
  };

}
#endif // __STDAIR_BAS_EVENTSTRUCT_HPP
