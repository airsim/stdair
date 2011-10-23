/**
 * @brief Handle on the StdAir library context
 * @author Anh Quan Nguyen <quannaus@users.sourceforge.net>
 * @date 20/01/2010
 * @detail StdAir aims at providing a clean API, and the corresponding
 *         C++ implementation, for the basis of Airline IT Business Object
 *         Model (BOM), that is, to be used by several other Open Source
 *         projects, such as RMOL and OpenTREP.
 *
 *         Install the StdAir library for Airline IT Standard C++ fundaments.
 */
#ifndef __STDAIR_STDAIR_HPP
#define __STDAIR_STDAIR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_service_types.hpp>
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/basic/EventType.hpp>

namespace stdair {

  /// Forward declarations
  class BomRoot;
  class EventQueue;
  class EventStruct;
  class STDAIR_ServiceContext;
  

  /**
   * @brief Interface for the STDAIR Services
   */
  class STDAIR_Service {
  public:
    // ////////// Constructors and destructors //////////
    /**
     * @brief Default constructor.
     */
    STDAIR_Service();

    /**
     * @brief Constructor.
     *
     * The init() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, a reference on an output stream is given, so
     * that log outputs can be directed onto that stream.
     *
     * @param[in] const BasLogParams& Parameters for the output log stream.
     */
    STDAIR_Service (const BasLogParams&);

    /**
     * @brief Constructor.
     *
     * The init() method is called; see the corresponding
     * documentation for more details.
     *
     * A reference on an output stream is given, so
     * that log outputs can be directed onto that stream.
     *
     * Moreover, database connection parameters are given, so
     * that database events can use the corresponding access.
     *
     * @param[in] const BasLogParams& Parameters for the output log stream.
     * @param[in] const BasDBParams& Parameters for the database session.
     */
    STDAIR_Service (const BasLogParams&, const BasDBParams&);

    /**
     * @brief Destructor.
     */
    ~STDAIR_Service();
    

  public:
    // ////////////////// Business support methods //////////////////    
    /**
     * Build a sample BOM tree, and attach it to the BomRoot instance.
     *
     * As for now, two sample BOM trees can be built.
     * <ul>
     *   <li>One BOM tree is based on two actual inventories (one for BA,
     *     another for AF). Each inventory contains one flight. One of
     *     those flights has two legs (and therefore three segments).</li>
     *   <li>The other BOM tree is fake, as a hook for RMOL to work.</li>
     * </ul>
     *
     * @param const bool isForRMOL Whether the sample BOM tree is for RMOL.
     * @param const CabinCapacity_T Capacity of the cabin for RMOL optimisation.
     */
    void buildSampleBom (const bool isForRMOL = false,
                         const CabinCapacity_T iCabinCapacity = 0);

    /**
     * Get the expected number of events to be generated.
     *
     * The getExpectedTotalNbOfEvents() method is called on the
     * underlying EventQueue object, which keeps track of that number.
     *
     * \note That number usually corresponds to an expectation (i.e.,
     *       the mean value of a random distribution), and may not be
     *       accurate. The actual number will be known after calling
     *       the generateFirstEvents() method for each event type
     *       (e.g., booking request, optimisation notification, etc).
     *
     * @return const Count_T& Expected number of events to be generated.
     */
    const Count_T& getExpectedTotalNumberOfEventsToBeGenerated() const;

    /**
     * Get the expected number of events to be generated for the given
     * event type.
     *
     * The getExpectedTotalNbOfEvents() method is called on the
     * underlying EventQueue object, which keeps track of that number.
     *
     * \note That number usually corresponds to an expectation (i.e.,
     *       the mean value of a random distribution), and may not be
     *       accurate. The actual number will be known after calling
     *       the generateFirstEvents() method for each event type
     *       (e.g., booking request, optimisation notification, etc).
     *
     * @param const EventType_T& Event type for which the number is calculated.
     * @return const Count_T& Expected number of events to be generated.
     */
    const Count_T&
    getExpectedTotalNumberOfEventsToBeGenerated (const EventType::EN_EventType&) const;

    /**
     * Get the actual number of events to be generated for all the
     * demand streams.
     *
     * The getActualTotalNbOfEvents() method is called on the
     * underlying EventQueue object, which keeps track of that number.
     *
     * \note That number is being known after calling the
     *       generateFirstEvents() method.
     *
     * @return const Count_T& Expected number of events to be generated.
     */
    const Count_T& getActualTotalNumberOfEventsToBeGenerated() const;

    /**
     * Get the actual number of events to be generated for the given
     * event type.
     *
     * The getActualTotalNbOfEvents() method is called on the
     * underlying EventQueue object, which keeps track of that number.
     *
     * \note That number is being known after calling the
     *       generateFirstEvents() method.
     *
     * @param const EventType_T& Event type for which the number is calculated.
     * @return const Count_T& Expected number of events to be generated.
     */
    const Count_T&
    getActualTotalNumberOfEventsToBeGenerated (const EventType::EN_EventType&) const;

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
     *     event type.</li>
     * </ul>
     *
     * @return EventStruct A copy of the event structure,
     *   which comes first in time from within the event queue.
     */
    EventStruct popEvent() const;

    /**
     * States whether the event queue has reached the end.
     *
     * For now, that method states whether or not the event queue is empty.
     */
    bool isQueueDone() const;

    /**
     * Reset the context of the demand streams for another demand generation
     * without having to reparse the demand input file.
     */
    void reset() const;


  public:
    // //////////////// Display support methods /////////////////
    /**
     * Recursively display (dump in the returned string) the objects
     * of the BOM tree.
     *
     * @return std::string Output string in which the BOM tree is
     *        logged/dumped.
     */
    std::string csvDisplay() const;


  public:
    // ///////////////// Getters ///////////////////
    /**
     * @brief Get a reference on the BomRoot object.
     *
     * If the service context has not been initialised, that
     * method throws an exception (failing assertion).
     *
     * @param[out] BomRoot& Reference on the BomRoot.
     */
    BomRoot& getBomRoot() const;
    
    /**
     * @brief Get a reference on the EventQueue object.
     *
     * If the service context has not been initialised, that
     * method throws an exception (failing assertion).
     *
     * @param[out] EventQueue& Reference on the EventQueue.
     */
    EventQueue& getEventQueue() const;
    

  private:
    // /////// Construction and Destruction helper methods ///////
    /**
     * @brief Default copy constructor.
     *
     * @param[in] const STDAIR_Service& Reference on the
     *            STDAIR_Service handler to be copied.
     */
    STDAIR_Service (const STDAIR_Service&);
    
    /**
     * @brief Initialise the (TRADEMGEN) service context (i.e., the
     * STDAIR_ServiceContext object).
     */
    void initServiceContext();

    /**
     * @brief Initialise the log.
     *
     * @param[in] const BasLogParams& Parameters for the output log stream.
     */
    void logInit (const BasLogParams&);
    
    /**
     * @brief Initialise the database session.
     *
     * @param[in] const BasDBParams& Parameters for the database session.
     */
    void dbInit (const BasDBParams&);
    
    /**
     * @brief Initialise.
     *
     * The static instance of the log service (Logger object) is created.
     *
     * The static instance of the database session manager
     * (DBSessionManager object) is created.
     *
     * The static instance of the FacSupervisor object, itself referencing
     * all the other objects (factories and BOM), is created.
     *
     * As those three objects are static, there is no need to store them
     * in any service context. However, some lock mechanism may be needed
     * in order to secure the access to the corresponding resources.
     */
    void init();
    
    /**
     * @brief Finalise.
     */
    void finalise();
    

  private:
    // ///////// Service Context /////////
    /**
     * Stdair context.
     */
    STDAIR_ServiceContext* _stdairServiceContext;
  };
}
#endif // __STDAIR_STDAIR_HPP
