// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/service/FacSupervisor.hpp>
#include <stdair/service/FacSTDAIRServiceContext.hpp>
#include <stdair/service/STDAIR_ServiceContext.hpp>

namespace stdair {

  FacSTDAIRServiceContext* FacSTDAIRServiceContext::_instance = NULL;

  // //////////////////////////////////////////////////////////////////////
  FacSTDAIRServiceContext::~FacSTDAIRServiceContext() {
    _instance = NULL;
  }

  // //////////////////////////////////////////////////////////////////////
  FacSTDAIRServiceContext& FacSTDAIRServiceContext::instance() {

    if (_instance == NULL) {
      _instance = new FacSTDAIRServiceContext();
      assert (_instance != NULL);
      
      FacSupervisor::instance().registerServiceFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_ServiceContext& FacSTDAIRServiceContext::create() {
    STDAIR_ServiceContext* aServiceContext_ptr = NULL;

    aServiceContext_ptr = new STDAIR_ServiceContext ();
    assert (aServiceContext_ptr != NULL);

    // The new object is added to the Bom pool
    _pool.push_back (aServiceContext_ptr);

    return *aServiceContext_ptr;
  }

}
