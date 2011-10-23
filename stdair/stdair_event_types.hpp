#ifndef __STDAIR_STDAIR_EVENT_TYPES_HPP
#define __STDAIR_STDAIR_EVENT_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace stdair {

  // //////// Type definitions /////////
  /** Type definition for the hashed key of the content of an event. */
  typedef std::string EventContentKey_T;

  /** Define the name of an event. */
  typedef std::string EventName_T;

  /** Define a number of events. */
  typedef double NbOfEvents_T;

  /** Define an ID for an EventQueue object. */
  typedef std::string EventQueueID_T;

}
#endif // __STDAIR_STDAIR_EVENT_TYPES_HPP
