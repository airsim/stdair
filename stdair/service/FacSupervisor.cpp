// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/factory/FacAbstract.hpp>
#include <stdair/service/FacServiceAbstract.hpp>
#include <stdair/service/FacSupervisor.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/service/DBSessionManager.hpp>

namespace stdair {

  FacSupervisor* FacSupervisor::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacSupervisor& FacSupervisor::instance() {
    if (_instance == NULL) {
      _instance = new FacSupervisor();
    }

    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  FacSupervisor::~FacSupervisor() {
    cleanPersistentBomLayer();
    cleanCloneBomLayer();
    cleanServiceLayer();
  }  

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::registerPersistentBomFactory (FacAbstract* ioFac_ptr) {
    _persistentBomPool.push_back (ioFac_ptr);
  } 

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::registerCloneBomFactory (FacAbstract* ioFac_ptr) {
    _cloneBomPool.push_back (ioFac_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::registerServiceFactory (FacServiceAbstract* ioFac_ptr) {
    _svcPool.push_back (ioFac_ptr);
  } 

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanPersistentBomLayer() { 
    for (PersistentBomFactoryPool_T::const_iterator itFactory = _persistentBomPool.begin();
         itFactory != _persistentBomPool.end(); itFactory++) {
      const FacAbstract* currentFactory_ptr = *itFactory;
      assert (currentFactory_ptr != NULL);

      delete (currentFactory_ptr); currentFactory_ptr = NULL;
    }
    // Empty the pool of BOM factories
    _persistentBomPool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanCloneBomLayer() {
    for (CloneBomFactoryPool_T::const_iterator itFactory = _cloneBomPool.begin();
         itFactory != _cloneBomPool.end(); itFactory++) {
      const FacAbstract* currentFactory_ptr = *itFactory;
      assert (currentFactory_ptr != NULL);

      delete (currentFactory_ptr); currentFactory_ptr = NULL;
    }

    // Empty the pool of BOM factories
    _cloneBomPool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanServiceLayer() {
    for (ServiceFactoryPool_T::const_iterator itFactory = _svcPool.begin();
         itFactory != _svcPool.end(); itFactory++) {
      const FacServiceAbstract* currentFactory_ptr = *itFactory;
      assert (currentFactory_ptr != NULL);
      
      delete (currentFactory_ptr); currentFactory_ptr = NULL;
    }
    
    // Empty the pool of Service Factories
    _svcPool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanLoggerService() {
    // Clean the static instance of the log service
    Logger::clean();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanDBSessionManager() {
    // Clean the static instance of the database service
    DBSessionManager::clean();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanAll() {

    // Clean the static instance of the database session manager
    cleanDBSessionManager();

    // Clean the static instance of the log service
    cleanLoggerService();

    // Clean the static instance of the FacSupervisor.
    // This in turn will invoke the destructor (~FacSupervisor() method)
    // of the static instance, thus cleaning both the BOM and service layers.
    delete _instance; _instance = NULL;
  }

}
