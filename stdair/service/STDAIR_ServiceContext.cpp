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
    : _bomRoot (NULL), _eventQueue (NULL) {
    // Build the BomRoot object
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_ServiceContext::
  STDAIR_ServiceContext (const STDAIR_ServiceContext& iServiceContext)
    : _bomRoot (iServiceContext._bomRoot),
      _eventQueue (iServiceContext._eventQueue) {
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

    // Link the EventQueue to its parent (BomRoot)
    // assert (_bomRoot != NULL);
    //FacBomManager::instance().linkWithParent (*_bomRoot, lEventQueue);
    
    // Add the EventQueue to the dedicated list
    //FacBomManager::instance().addToList (*_bomRoot, lEventQueue);

    // Store the event queue object
    _eventQueue = &lEventQueue;
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string STDAIR_ServiceContext::shortDisplay() const {
    std::ostringstream oStr;
    oStr << "STDAIR_ServiceContext ";
    if (_eventQueue != NULL) {
      oStr << " - Queue: " << _eventQueue->toString();
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
