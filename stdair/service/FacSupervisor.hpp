#ifndef __STDAIR_SVC_FACSUPERVISOR_HPP
#define __STDAIR_SVC_FACSUPERVISOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <list>

namespace stdair {

  /// Forward declarations
  class FacAbstract;
  class FacServiceAbstract;

  /**
   * Singleton class to register and clean all Factories.
   */
  class FacSupervisor {
  public:
    /**
     * Define the pool (list) of factories.
     */
    typedef std::list<FacAbstract*> BomFactoryPool_T;
    typedef std::list<FacServiceAbstract*> ServiceFactoryPool_T;

    /**
     * Provide the unique (static) instance of the FacSupervisor object.
     *
     * The singleton is instantiated when first used.
     * @return FacSupervisor&
     */
    static FacSupervisor& instance();

    /**
     * Register a newly instantiated concrete factory for the Bom layer.
     *
     * When a concrete Factory is firstly instantiated
     * this factory have to register itself to the FacSupervisor
     * @param FacBom* The concrete Factory to register.
     */
    void registerBomFactory (FacAbstract*);

    /**
     * Register a newly instantiated concrete factory for the Service layer.
     *
     * When a concrete Factory is firstly instantiated
     * this factory have to register itself to the FacSupervisor.
     * @param FacServiceAbstract& the concrete Factory to register.
     */
    void registerServiceFactory (FacServiceAbstract*);

    /**
     * Clean all registered object.
     *
     * Call the clean method of all the instantiated factories
     * for the BomStructure layer.
     */
    void cleanBomLayer();

    /**
     * Clean all Service created object.
     *
     * Call the clean method of all the instantiated  factories
     * for the Service layer.
     */
    void cleanServiceLayer();

    /**
     * Delete the static instance of the Logger object.
     */
    static void cleanLoggerService();

    /**
     * Delete the static instance of the DBSessionManager object.
     */
    static void cleanDBSessionManager();

    /**
     * Clean the static instance.
     * As the static instance (singleton) is deleted, all the other
     * registered objects will be deleted in turn.
     */
    static void cleanAll();

    /**
     * Destructor.
     *
     * That destructors is applied on the static instance. It then
     * deletes in turn all the other registered objects.
     */
    ~FacSupervisor();


  protected:
    /**
     * Default Constructor.
     *
     * This constructor is protected to ensure the singleton pattern.
     */
    FacSupervisor() {}
    FacSupervisor (const FacSupervisor&) {}

  private:
    /**
     * The unique instance.
     */
    static FacSupervisor* _instance;

    /**
     * List of instantiated factories for the BOM layer.
     */
    BomFactoryPool_T _bomPool;

    /**
     * List of instantiated factories for the Service layer.
     */
    ServiceFactoryPool_T _svcPool;
  };
}  
#endif // __STDAIR_SVC_FACSUPERVISOR_HPP
