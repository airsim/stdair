#ifndef __STDAIR_BAS_EVENTSTRUCT_HPP
#define __STDAIR_BAS_EVENTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/basic/EventType.hpp>
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
  };

}
#endif // __STDAIR_BAS_EVENTSTRUCT_HPP
