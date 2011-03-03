#ifndef __STDAIR_SVC_STDAIRSERVICECONTEXT_HPP
#define __STDAIR_SVC_STDAIRSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
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
     * @brief Get the pointer on the EventQueue instance.
     */
    BomRoot& getBomRoot() const;

    /**
     * @brief Get the pointer on the EventQueue instance.
     */
    EventQueue& getEventQueue() const;


  private:
    // ///////// Setters //////////

    
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
  };

}
#endif // __STDAIR_SVC_STDAIRSERVICECONTEXT_HPP
