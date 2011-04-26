// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/ProgressStatusSet.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  ProgressStatusSet::ProgressStatusSet()
    : _eventType (EventType::LAST_VALUE), _typeSpecificProgressStatus(), 
      _generatorProgressStatus(), _overallProgressStatus(), _generatorKey ("") {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressStatusSet::ProgressStatusSet (const EventType::EN_EventType& iType)
    : _eventType (iType), _typeSpecificProgressStatus(), 
      _generatorProgressStatus(), _overallProgressStatus(), _generatorKey ("") {
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressStatusSet::
    ProgressStatusSet (const ProgressStatusSet& iProgressStatusSet)
      : _eventType (iProgressStatusSet._eventType),
        _typeSpecificProgressStatus(iProgressStatusSet._typeSpecificProgressStatus),
        _generatorProgressStatus (iProgressStatusSet._generatorProgressStatus),
        _overallProgressStatus (iProgressStatusSet._overallProgressStatus),
        _generatorKey (iProgressStatusSet._generatorKey) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  ProgressStatusSet::~ProgressStatusSet() {
  }

  // //////////////////////////////////////////////////////////////////////
  void ProgressStatusSet::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string ProgressStatusSet::describe() const {
    std::ostringstream oStr;

    oStr << "-[Overall]"
         << "[" << _overallProgressStatus.getCurrentNb()
         << "/{" << _overallProgressStatus.getExpectedNb()
         << "," << _overallProgressStatus.getActualNb()
         << "}] ";

    oStr << "[" << EventType (_eventType) << "]"
         << "[" << _typeSpecificProgressStatus.getCurrentNb()
         << "/{" << _typeSpecificProgressStatus.getExpectedNb()
         << "," << _typeSpecificProgressStatus.getActualNb()
         << "}]";

    oStr << " [Specific generator: " << _generatorKey << "]"
         << "[" << _generatorProgressStatus.getCurrentNb()
         << "/{" << _generatorProgressStatus.getExpectedNb()
         << "," << _generatorProgressStatus.getActualNb()
         << "}]";

    return oStr.str();
  }

}
