/*!
 * \page stdair_service_context_cpp C++ Class Storing the StdAir Context
 * \code
 */
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/service/STDAIR_ServiceContext.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  STDAIR_ServiceContext::STDAIR_ServiceContext()
    : _bomRoot (NULL), 
      _initType (ServiceInitialisationType::NOT_YET_INITIALISED) {
    // Build the BomRoot object
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_ServiceContext::
  STDAIR_ServiceContext (const STDAIR_ServiceContext& iServiceContext)
    : _bomRoot (iServiceContext._bomRoot),
      _initType (ServiceInitialisationType::NOT_YET_INITIALISED) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_ServiceContext::~STDAIR_ServiceContext() {
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_ServiceContext::init() {
    //
    initBomRoot();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_ServiceContext::initBomRoot() {
    _bomRoot = &FacBom<BomRoot>::instance().create();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string STDAIR_ServiceContext::shortDisplay() const {
    std::ostringstream oStr;
    oStr << "STDAIR_ServiceContext -- " << _initType
         << " -- DB: " << _dbParams;
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string STDAIR_ServiceContext::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string STDAIR_ServiceContext::describe() const {
    return shortDisplay();
  }

  // //////////////////////////////////////////////////////////////////////
  BomRoot& STDAIR_ServiceContext::getBomRoot() const {
    assert (_bomRoot != NULL);
    return *_bomRoot;
  }
}

/*!
 * \endcode
 */
