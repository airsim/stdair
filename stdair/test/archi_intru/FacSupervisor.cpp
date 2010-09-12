// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Local
#include <test/archi_intru/FacRelationShipRootAbstract.hpp>
#include <test/archi_intru/FacSupervisor.hpp>

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
    cleanFacRelationShipRoots();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::
  registerFacRelationShipRoot (FacRelationShipRootAbstract* ioFacRelationShipRoot_ptr) {
    _facRelationShipRootPool.push_back (ioFacRelationShipRoot_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanFacRelationShipRoots() {
    for (FacRelationShipRootPool_T::const_iterator itRS =
           _facRelationShipRootPool.begin();
         itRS != _facRelationShipRootPool.end(); ++itRS) {
      const FacRelationShipRootAbstract* currentFacRelationShipRoot_ptr = *itRS;
      assert (currentFacRelationShipRoot_ptr != NULL);

      delete currentFacRelationShipRoot_ptr; currentFacRelationShipRoot_ptr = NULL;
    }

    // Empty the pool of relations ships
    _facRelationShipRootPool.clear();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacSupervisor::cleanAll () {
    // Clean the static instance of the FacSupervisor.
    // This in turn will invoke the destructor (~FacSupervisor() method)
    // of the static instance.
    delete _instance; _instance = NULL;
  }

}
