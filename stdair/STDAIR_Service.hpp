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
#include <stdair/basic/ServiceInitialisationType.hpp>
#include <stdair/basic/EventType.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>

namespace stdair {

  /// Forward declarations
  class BomRoot;
  class EventQueue;
  class EventStruct;
  struct ProgressStatusSet;
  struct BookingRequestStruct;
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
     * As for now, a single sample BOM tree is built, with objects
     * for all the simulator-related components, i.e.:
     * <ul>
     *   <li>schedule (e.g., AirSched),</li>
     *   <li>inventory (e.g., AirInv),</li>
     *   <li>revenue management (e.g., RMOL),</li>
     *   <li>pricing (e.g., SimFQT),</li>
     *   <li>revenue accounting (e.g., AirRAC),</li>
     *   <li>demand generation (e.g., TraDemGen),</li>
     *   <li>customer choice (e.g., TravelCCM),</li>
     *   <li>event manager (e.g., SEvMgr)</li>
     * </ul>
     *
     * Most of the inventories just contain one flight. One of those flights
     * has two legs (and therefore three segments).
     */
    void buildSampleBom();
    
    /**
     * Build a dummy inventory, containing a dummy flight-date with a single
     * leg-cabin and some virtual booking classes. That structure is the bare
     * minimum required to perform an optimisation on a leg-cabin.
     *
     * As for now, that method is called only by RMOL. Indeed, the
     * revenue management component (RMOL) needs very basic set up in
     * order to perform optimisation at leg-level. Hence, there are:
     * <ul>
     *    <li>a dedicated inventory ('XX'),</li>
     *    <li>the corresponding flight-date (#9999, departing 01/01/1900),</li>
     *    <li>a leg-date (departing and arriving from/to 'XXX' airport),<li>
     *    <li>a leg-cabin ('X').<li>
     * </ul>
     *
     * Most of the data is dummy because RMOL uses only the cabin capacity
     * from that part of the BOM tree.
     *
     * @param const CabinCapacity_T& Cabin capacity for revenue management
     *        optimisation.
     */
    void buildDummyInventory (const CabinCapacity_T& iCabinCapacity);
    
    /**
     * Build a sample list of travel solutions.
     *
     * As of now (March 2011), that list is made of the following
     * travel solutions:
     * <ul>
     *  <li>BA9</li>
     *  <li>LHR-SYD</li>
     *  <li>2011-06-10</li>
     * </ul>
     *
     * @param TravelSolutionList_T& Sample list of travel solution structures.
     *        It should be given empty. It is altered with the returned sample.
     */
    void buildSampleTravelSolutionForPricing (TravelSolutionList_T&);

    /**
     * Build a sample list of travel solutions.
     *
     * As of now (March 2011), that list is made of the following
     * travel solutions:
     * <ul>
     *  <li>BA9</li>
     *  <li>LHR-SYD</li>
     *  <li>2011-06-10</li>
     *  <li>Q</li>
     *  <li>WTP: 900</li>
     *  <li>Change fee: 20; Non refundable; Saturday night stay</li>
     * </ul>
     *
     * @param TravelSolutionList_T& Sample list of travel solution structures.
     *        It should be given empty. It is altered with the returned sample.
     */
    void buildSampleTravelSolutions (TravelSolutionList_T&);

    /**
     * Build a sample booking request structure.
     *
     * As of now (March 2011), the sample booking request is made of the
     * following parameters:
     * <ul>
     *  <li>Return trip (inbound): LHR-SYD (POS: LHR, Channel: DN), </li>
     *  <li>Departing 10-JUN-2011 around 8:00, staying 7 days</li>
     *  <li>Requested on 15-MAY-2011 at 10:00</li>
     *  <li>Economy cabin, 3 persons, FF member</li>
     *  <li>WTP: 1000.0 EUR</li>
     *  <li>Dis-utility: 100.0 EUR/hour</li>
     * </ul>
     *
     * As of now (March 2011), the CRS-related booking request is made
     * of the following parameters:
     * <ul>
     *  <li>Return trip (inbound): SIN-BKK (POS: SIN, Channel: IN), </li>
     *  <li>Departing 30-JAN-2010 around 10:00, staying 7 days</li>
     *  <li>Requested on 22-JAN-2010 at 10:00</li>
     *  <li>Economy cabin, 3 persons, FF member</li>
     *  <li>WTP: 1000.0 EUR</li>
     *  <li>Dis-utility: 100.0 EUR/hour</li>
     * </ul>
     *
     * @param const bool isForCRS Whether the sample booking request is for CRS.
     * @return BookingRequestStruct& Sample booking request structure.
     */
    BookingRequestStruct buildSampleBookingRequest (const bool isForCRS = false);

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
    ProgressStatusSet popEvent (EventStruct&) const;

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

    // //////////////// Export support methods /////////////////
    /**
     * Recursively dump, in the returned string and in JSON format,
     * the flight-date list corresponding to the parameters given as 
     * input.
     *
     * @param const AirlineCode& Airline for which the flight-dates should be
     *        displayed. If set to "all" (default), all the inventories will
     *        be displayed. 
     * @param const FlightNumber_T& Flight number for which all the departure
     *        dates should be displayed. If set to 0 (the default),
     *        all the flight numbers will be displayed.
     */
    std::string jsonExportFlightDateList (const AirlineCode_T& iAirlineCode = "all",
					  const FlightNumber_T& iFlightNumber = 0) const;

    /**
     * Recursively dump, in the returned string and in JSON format,
     * the detailed flight-date (leg, segments, cabins, classes, ...) 
     * corresponding to the parameters given as input.
     *
     * @param const AirlineCode_T& Airline code of the flight to dump.
     * @param const FlightNumber_T& Flight number of the flight to dump.
     * @param const Date_T& Departure date of the flight to dump.
     * @return std::string Output string in which the BOM tree is JSON-ified.
     */
    std::string jsonExportFlightDateObjects (const AirlineCode_T&, 
					     const FlightNumber_T&,
					     const Date_T& iDepartureDate) const;  

    /**
     * Recursively dump, in the returned string and in JSON format,
     * the booking request events.
     *
     * @return std::string Output string in which the booking-requests are 
     * JSON-ified.
     */
    std::string jsonExportBookingRequestObjects () const;


  public:
    // //////////////// Display support methods /////////////////
    /**
     * Display the list of flight-dates (contained within the BOM tree)
     * corresponding to the parameters given as input.
     *
     * @param const AirlineCode& Airline for which the flight-dates should be
     *        displayed. If set to "all" (the default), all the inventories
     *        will be displayed.
     * @param const FlightNumber_T& Flight number for which all the departure
     *        dates should be displayed. If set to 0 (the default),
     *        all the flight numbers will be displayed.
     * @return std::string Output string in which the BOM tree is
     *        logged/dumped.
     */
    std::string list (const AirlineCode_T& iAirlineCode = "all",
                      const FlightNumber_T& iFlightNumber = 0) const;
    
    /** Display the list of aiports pairs and date ranges
     * (contained within the BOM tree)
     *
     * @param std::ostream& Output stream in which the airport pairs and
     * date ranges are logged/dumped.
     */
    std::string listAirportPairDateRange () const;

    /**
     * Check whether the given flight-date is a valid one.
     *
     * @param const stdair::AirlineCode_T& Airline code of the flight to check.
     * @param const stdair::FlightNumber_T& Flight number of the
     *        flight to check.
     * @param const stdair::Date_T& Departure date of the flight to check.
     * @return bool Whether or not the given flight date is valid.
     */
    bool check (const AirlineCode_T&, const FlightNumber_T&,
                const Date_T& iDepartureDate) const;

    /**
     * Check whether the given couple airportpair-date is a valid one.
     *
     * @param const stdair::AirportCode_T& Origin airport of the fare
     *        rule to check.
     * @param const stdair::AirportCode_T& Destination airport of the
     *        fare rule to check.
     * @param const stdair::Date_T& Departure date of the fare rule
     *        to check. 
     * @return bool Whether or not the given airportpair-date couple
     *        is a valid one.
     */
    bool check (const AirportCode_T&, const AirportCode_T&,
                const Date_T& iDepartureDate) const;

    /**
     * Recursively display (dump in the returned string) the objects
     * of the BOM tree.
     *
     * @return std::string Output string in which the BOM tree is
     *        logged/dumped.
     */
    std::string csvDisplay() const;

    /**
     * Recursively display (dump in the returned string) the flight-date
     * corresponding to the parameters given as input.
     *
     * @param const AirlineCode_T& Airline code of the flight to display.
     * @param const FlightNumber_T& Flight number of the flight to display.
     * @param const Date_T& Departure date of the flight to display.
     * @return std::string Output string in which the BOM tree is logged/dumped.
     */
    std::string csvDisplay (const AirlineCode_T&, const FlightNumber_T&,
                            const Date_T& iDepartureDate) const;

    /**
     * Display (dump in the returned string) the full list of travel
     * solution structures.
     *
     * @return std::string Output string in which the list of travel
     *        solutions is logged/dumped.
     */
    std::string csvDisplay (const TravelSolutionList_T&) const;
    
    /**
     * Recursively display (dump in the returned string) the fare-rules
     * corresponding to the parameters given as input.
     *
     * @param const AirportCode_T& Origin airport of the fare-rules to display
     * @param const AirportCode_T& Destination airport of the fare-rules
     *        to display.
     * @param const Date_T& Departure date of the fare-rules to display.
     * @return std::string Output string in which the BOM tree is logged/dumped.
     */
    std::string csvDisplay (const AirportCode_T&, const AirportCode_T&,
                            const Date_T& iDepartureDate) const;


  public:
    // ///////////////// Getters ///////////////////
    /**
     * @brief Get a reference on the BomRoot object.
     *
     * If the service context has not been initialised, that
     * method throws an exception (failing assertion).
     *
     * @return BomRoot& Reference on the BomRoot.
     */
    BomRoot& getBomRoot() const;
    
    /**
     * @brief Get a reference on the EventQueue object.
     *
     * If the service context has not been initialised, that
     * method throws an exception (failing assertion).
     *
     * @return EventQueue& Reference on the EventQueue.
     */
    EventQueue& getEventQueue() const;
    
    /**
     * Get the log parameters.
     *
     * @return BasLogParams Copy of the structure holding the log parameters.
     */
    BasLogParams getLogParams() const;

    /**
     * Get the database parameters.
     *
     * @return const BasDBParams& Reference on the structure holding
     *         the database parameters.
     */
    const BasDBParams& getDBParams() const;

    /**
     * Get the type of initialisation (e.g., not yet, file parsing,
     * sample BOM) which the component (owner of the current
     * STDAIR_Service instance) has gone through.
     *
     * @return const ServiceInitialisationType& Reference on the type of
     *         initialisation (enumeration structure).
     */
    const ServiceInitialisationType& getServiceInitialisationType() const;


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
     * The log service must not be initialised twice, unless explicitly
     * forced to.
     *
     * As of March 2011, the only known case is when AIRINV_Service is
     * invoked from AIRINV_Master_Service. Indeed, those two should live
     * in two different processes, connected through the network (MPI).
     *
     * But, for test reason, it is easier to deploy those two services
     * within the same process. So, when testing, the same static instance
     * of the Logger service is initialised twice, once for
     * AIRINV_Master_Service, and the other one for AIRINV_Service.
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
