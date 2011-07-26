// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/TimePeriod.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  TimePeriod::TimePeriod()
    : _key (DEFAULT_EPSILON_DURATION, DEFAULT_EPSILON_DURATION),
      _parent (NULL)  {
    // That constructor is used by the serialisation process
  }

  // ////////////////////////////////////////////////////////////////////
  TimePeriod::TimePeriod (const TimePeriod& iTimePeriod)
    : _key (iTimePeriod.getKey()), _parent (NULL)  {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  TimePeriod::TimePeriod (const Key_T& iKey)
    : _key (iKey), _parent (NULL)  {
  }

  // ////////////////////////////////////////////////////////////////////
  TimePeriod::~TimePeriod () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string TimePeriod::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }
  
  // ////////////////////////////////////////////////////////////////////
  bool TimePeriod::
  isDepartureTimeValid (const Time_T& iFlightTime) const {

    const Time_T& lTimeRangeStart = getTimeRangeStart();
    const Time_T& lTimeRangeEnd = getTimeRangeEnd();
    
    // Check if the departure time is within the time range.
    if (lTimeRangeStart >= iFlightTime) {
      // DEBUG
      STDAIR_LOG_DEBUG ("Time range begin: " << lTimeRangeStart << ", "
                        << "time: " << iFlightTime);
      return false;
    }
    if (lTimeRangeEnd <= iFlightTime) {
      // DEBUG
      STDAIR_LOG_DEBUG ("Time range end: " << lTimeRangeEnd << ", "
                        << "time: " << iFlightTime);
      return false;
    }

    return true;
  }
  
}

