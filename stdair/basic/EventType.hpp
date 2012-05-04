#ifndef __STDAIR_BAS_EVENTTYPE_HPP
#define __STDAIR_BAS_EVENTTYPE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /** Enumeration of event types. */
  struct EventType : public StructAbstract {
  public:
    typedef enum { 
      BKG_REQ = 0,
      CX,
      OPT_NOT_4_FD,
      OPT_NOT_4_NET,
      SKD_CHG,
      SNAPSHOT,
      RM,
      BRK_PT,
      LAST_VALUE
    } EN_EventType;

    /** Get the label as a string (e.g., "BookingRequest", "Cancellation", 
     * "OptimisationNotificationForFlightDate",
     * "OptimisationNotificationForNetwork", "ScheduleChange", "Snapshot",
     * "RevenueManagement", "BreakPoint" or "BookingRequest").
     */
    static const std::string& getLabel (const EN_EventType&);

    /** Get the label as a single char 
     * (e.g., 'B', 'X', 'F', 'N', 'C', 'S', 'R' or 'P'). 
     */
    static char getTypeLabel (const EN_EventType&);

    /** Get the label as a string of a single char 
     * (e.g., "B", "X", "F", "N", "C", "S", "R" or "P"). 
     */
    static std::string getTypeLabelAsString (const EN_EventType&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_EventType getType() const;

    /** Get the enumerated value as a short string 
     * (e.g., "B", "X", "F", "N", "C", "S", "R" or "P").
     */
    std::string getTypeAsString() const;
    
    /** Give a description of the structure (e.g., "BookingRequest", "Cancellation", 
     * "OptimisationNotificationForFlightDate",
     * "OptimisationNotificationForNetwork", "ScheduleChange", "Snapshot",
     * "RevenueManagement", "BreakPoint" or "BookingRequest").
     */
    const std::string describe() const;

  public:
    /** Comparison operator. */
    bool operator== (const EN_EventType&) const;
    
  public:
    /** Constructor. */
    EventType (const EN_EventType&);
    /** Constructor using a char. */
    EventType (const char iType);  
    /** Constructor using a string. */
    EventType (const std::string iTypeStr);
    /** Default copy constructor. */
    EventType (const EventType&);

  private:
    /** Default constructor. */
    EventType();
  

  private:
    /** String version of the enumeration. */    
    static const std::string _labels[LAST_VALUE];
    /** Type version of the enumeration. */    
    static const char _typeLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /** Event type. */
    EN_EventType _type;
  };

}
#endif // __STDAIR_BAS_EVENTTYPE_HPP
