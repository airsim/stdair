#ifndef __STDAIR_SVC_STDAIRSERVICECONTEXT_HPP
#define __STDAIR_SVC_STDAIRSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/basic/ServiceInitialisationType.hpp>
#include <stdair/service/ServiceAbstract.hpp>

namespace stdair {

  /// Forward declarations
  class BomRoot;
  class EventQueue;

  /**
   * @brief Class holding the context of the Stdair services.
   */
  class STDAIR_ServiceContext : public ServiceAbstract {
    /** The STDAIR_Service class should be the sole class to get access to
        ServiceContext content: general users do not want to bother
        with a context interface. */
    friend class STDAIR_Service;
    friend class FacSTDAIRServiceContext;
    
  private:
    // ///////// Getters //////////
    /**
     * Get the pointer on the EventQueue instance.
     */
    BomRoot& getBomRoot() const;

    /**
     * Get the pointer on the EventQueue instance.
     */
    EventQueue& getEventQueue() const;

    /**
     * Get the database parameters.
     */
    const BasDBParams& getDBParams() const {
      return _dbParams;
    }

    /**
     * Get the type of initialisation (e.g., not yet, file parsing, sample BOM).
     */
    const ServiceInitialisationType& getServiceInitialisationType() const {
      return _initType;
    }


  private:
    // ///////// Setters //////////
    /**
     * Set the database parameters.
     */
    void setDBParams (const BasDBParams& iDBParams) {
      _dbParams = iDBParams;
    }

    /**
     * Set the type of initialisation (e.g., not yet, file parsing, sample BOM).
     */
    void setServiceInitialisationType (const ServiceInitialisationType& iSIT) {
      _initType = iSIT;
    }

    
  private:
    // ///////// Display Methods //////////
    /**
     * Display the short STDAIR_ServiceContext content.
     */
    const std::string shortDisplay() const;
    
    /**
     * Display the full STDAIR_ServiceContext content.
     */
    const std::string display() const;

    /**
     * Display of the structure.
     */
    const std::string describe() const;
    

  private:
    // /////// Construction / initialisation ////////
    /**
     * Default Constructor.
     */
    STDAIR_ServiceContext();

    /**
     * Default copy constructor.
     *
     * The copy constructor must not be used. An failing assertion
     * would be thrown otherwise.
     */
    STDAIR_ServiceContext (const STDAIR_ServiceContext&);

    /**
     * Destructor.
     */
    ~STDAIR_ServiceContext();

    /**
     * Initialisation.
     *
     * That method is invoked from the constructors. It triggers, in
     * turn, the initialisation of the BOM tree root and of the event
     * queue.
     */
    void init();

    /**
     * Initialisation.
     *
     * The root of the BOM tree, on which all of the other BOM objects
     * will be attached, is being created by that method.
     */
    void initBomRoot();
    
    /**
     * Initialisation.
     *
     * The EventQueue object is created by that method, and then
     * stored within the service context.
     */
    void initEventQueue();
    

  private:
    // ///////////// Children ////////////
    /**
     * @brief Root of the BOM tree.
     */
    BomRoot* _bomRoot;

    /**
     * @brief EventQueue.
     */
    EventQueue* _eventQueue;

    /**
     * @brief Database parameters.
     */
    BasDBParams _dbParams;

    /**
     * @brief State how the component services have been initialised.
     *
     * Currently, the component services may either be:
     * <ul>
     *   <li>Not initialised yet.</li>
     *   <li>Initialised by parsing (CSV) input files (e.g., schedules,
     *       fares), i.e., by calling the parseAndLoad() method of
     *       the corresponding components.</li>
     *   <li>Initialised by loading built-in sample BOM trees (i.e., by
     *       calling the STDAIR_Service::buildSampleBom() method.</li>
     * </ul>
     */
    ServiceInitialisationType _initType;
  };

}
#endif // __STDAIR_SVC_STDAIRSERVICECONTEXT_HPP
