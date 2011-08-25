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
#include <stdair/bom/EventQueue.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/service/STDAIR_ServiceContext.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  STDAIR_ServiceContext::STDAIR_ServiceContext()
    : _bomRoot (NULL), _eventQueue (NULL),
      _initType (ServiceInitialisationType::NOT_YET_INITIALISED) {
    // Build the BomRoot object
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_ServiceContext::
  STDAIR_ServiceContext (const STDAIR_ServiceContext& iServiceContext)
    : _bomRoot (iServiceContext._bomRoot),
      _eventQueue (iServiceContext._eventQueue),
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

    //
    initEventQueue();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_ServiceContext::initBomRoot() {
    _bomRoot = &FacBom<BomRoot>::instance().create();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_ServiceContext::initEventQueue() {
    
    // The event queue key is just a string. For now, it is not used.
    const EventQueueKey lKey ("EQ01");

    // Create an EventQueue object instance
    EventQueue& lEventQueue = FacBom<EventQueue>::instance().create (lKey);

    // Store the event queue object
    _eventQueue = &lEventQueue;
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string STDAIR_ServiceContext::shortDisplay() const {
    std::ostringstream oStr;
    oStr << "STDAIR_ServiceContext -- " << _initType
         << " -- DB: " << _dbParams;
    if (_eventQueue != NULL) {
      oStr << " -- Queue: " << _eventQueue->toString();
    }
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

  // //////////////////////////////////////////////////////////////////////
  EventQueue& STDAIR_ServiceContext::getEventQueue() const {
    assert (_eventQueue != NULL);
    return *_eventQueue;
  }

}

/*!
 * \endcode
 */
