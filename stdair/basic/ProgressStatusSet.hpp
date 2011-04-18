#ifndef __STDAIR_BAS_PROGRESSSTATUSSET_HPP
#define __STDAIR_BAS_PROGRESSSTATUSSET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/basic/EventType.hpp>
#include <stdair/basic/ProgressStatus.hpp>

namespace stdair {

  /**
   * Structrure holding a set of progress status. 
   */
  struct ProgressStatusSet : public StructAbstract {
    // ///////////// Getters ///////////
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
    
    /**
     * Get the progress status specific to the content key for
     * that event.
     *
     * Note that that progress status may not be up-to-date. That
     * attribute is up-to-date only after a call to the
     * EventQueue::popEvent() method.
     */
    const ProgressStatus& getSpecificGeneratorStatus() const {
      return _generatorProgressStatus;
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

    
    // ///////////// Setters ///////////
  public:
    /** Set/update the progress status specific to that event type. */
    void setTypeSpecificStatus (const ProgressStatus& iProgressStatus) {
      _typeSpecificProgressStatus = iProgressStatus;
    }

    /** Set/update the progress status specific to the content key
        for that event. */
    void setSpecificGeneratorStatus (const ProgressStatus& iProgressStatus) {
      _generatorProgressStatus = iProgressStatus;
    }

    /** Set/update the overall progress status (absolute, for all the
        events). */
    void setOverallStatus (const ProgressStatus& iProgressStatus) {
      _overallProgressStatus = iProgressStatus;
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
    /** Constructor . */
    ProgressStatusSet (const EventType::EN_EventType&);
    /** Copy constructor. */
    ProgressStatusSet (const ProgressStatusSet&);
    /** Destructor. */
    ~ProgressStatusSet();
    
  private:
    /** Default constructor . */
    ProgressStatusSet ();
    
    // ////////////////// Attributes //////////////////
  private:
    /**
     * Event type.
     */
    const EventType::EN_EventType _eventType;

    /**
     * Counters holding the progress status of a specific type of event.
     */
    ProgressStatus _typeSpecificProgressStatus;

    /**
     * Counters holding the progress status of a specific event generator.
     */
    ProgressStatus _generatorProgressStatus;

    /**
     * Counters holding the progress status of all events altogether
     */
    ProgressStatus _overallProgressStatus;
  };

}
#endif // __STDAIR_BAS_PROGRESSSTATUSSET_HPP
