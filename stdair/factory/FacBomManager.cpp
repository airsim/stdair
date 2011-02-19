// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/FacSupervisor.hpp>

namespace stdair {

  FacBomManager* FacBomManager::_instance = NULL;
  
  // ////////////////////////////////////////////////////////////////////
  FacBomManager& FacBomManager::instance () {
    if (_instance == NULL) {
      _instance = new FacBomManager ();
      assert (_instance != NULL);

      FacSupervisor::instance().registerFacBom (_instance);
    }
    return *_instance;
  }
  
}
