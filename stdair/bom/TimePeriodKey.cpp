// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// STDAIR
#include <stdair/bom/TimePeriodKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  TimePeriodKey::TimePeriodKey (const Time_T& iTimeRangeStart,
                                const Time_T& iTimeRangeEnd)
    : _timeRangeStart(iTimeRangeStart), _timeRangeEnd(iTimeRangeEnd) {
  }

  // ////////////////////////////////////////////////////////////////////
  TimePeriodKey::TimePeriodKey (const TimePeriodKey& iKey)
    : _timeRangeStart(iKey.getTimeRangeStart()),
      _timeRangeEnd(iKey.getTimeRangeEnd())  {
  }

  // ////////////////////////////////////////////////////////////////////
  TimePeriodKey::~TimePeriodKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void TimePeriodKey::toStream (std::ostream& ioOut) const {
    ioOut << "TimePeriodKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void TimePeriodKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string TimePeriodKey::toString() const {
    std::ostringstream oStr;
    oStr << _timeRangeStart << "-" << _timeRangeEnd << std::endl; 
    return oStr.str();
  }

}