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

