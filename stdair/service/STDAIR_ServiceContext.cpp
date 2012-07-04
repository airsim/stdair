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
// Boost
#if BOOST_VERSION >= 103900
#include <boost/make_shared.hpp>
#else  // BOOST_VERSION >= 103900
#include <boost/shared_ptr.hpp>
#endif // BOOST_VERSION >= 103900
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/factory/FacCloneBom.hpp>
#include <stdair/service/STDAIR_ServiceContext.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  STDAIR_ServiceContext::STDAIR_ServiceContext()
    : _cloneBomRoot (NULL), 
      _persistentBomRoot (NULL),
      _initType (ServiceInitialisationType::NOT_YET_INITIALISED) {
    // Build the BomRoot object
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_ServiceContext::
  STDAIR_ServiceContext (const STDAIR_ServiceContext& iServiceContext)
    : _cloneBomRoot (iServiceContext._cloneBomRoot),
      _persistentBomRoot (iServiceContext._persistentBomRoot),
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
    initConfigHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_ServiceContext::initBomRoot() {
    _persistentBomRoot = &FacBom<BomRoot>::instance().create();
    initCloneBomRoot();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_ServiceContext::initCloneBomRoot() {
    _cloneBomRoot = 
      &FacCloneBom<BomRoot>::instance().clone(*_persistentBomRoot);
  } 

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_ServiceContext::initConfigHolder() {
    _configHolderPtr = boost::make_shared<ConfigHolderStruct> ();
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
  BomRoot& STDAIR_ServiceContext::getPersistentBomRoot() const {
    assert (_persistentBomRoot != NULL);
    return *_persistentBomRoot;
  }  
  
  // //////////////////////////////////////////////////////////////////////
  BomRoot& STDAIR_ServiceContext::getCloneBomRoot() const {
    assert (_cloneBomRoot != NULL);
    return *_cloneBomRoot;
  }  

  // //////////////////////////////////////////////////////////////////////
  ConfigHolderStruct& STDAIR_ServiceContext::getConfigHolder() const { 
    assert (_configHolderPtr != NULL);
    return *_configHolderPtr;
  } 
}

/*!
 * \endcode
 */
