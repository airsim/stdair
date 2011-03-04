// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/DatePeriod.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  DatePeriod::DatePeriod (const Key_T& iKey)
    : _key (iKey), _parent (NULL)  {
  }

  // ////////////////////////////////////////////////////////////////////
  DatePeriod::~DatePeriod () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string DatePeriod::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }
  
  // ////////////////////////////////////////////////////////////////////
  bool DatePeriod::
  isDepartureDateValid (const Date_T& iFlightDate) const {

    // Check if the departure date is within the date range.
    const DatePeriod_T& lPeriod = getDatePeriod ();
    if (lPeriod.contains (iFlightDate) == false) {
      return false;
    }

    return true;
  }
  
}

