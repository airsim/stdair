// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// STDAIR
#include <stdair/bom/DatePeriodKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  DatePeriodKey::DatePeriodKey (const stdair::DatePeriod_T& iDatePeriod)
    : _datePeriod (iDatePeriod) {
  }

  // ////////////////////////////////////////////////////////////////////
  DatePeriodKey::DatePeriodKey (const DatePeriodKey& iKey)
    : _datePeriod (iKey._datePeriod) {
  }

  // ////////////////////////////////////////////////////////////////////
  DatePeriodKey::~DatePeriodKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void DatePeriodKey::toStream (std::ostream& ioOut) const {
    ioOut << "DatePeriodKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void DatePeriodKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string DatePeriodKey::toString() const {
    std::ostringstream oStr;
    oStr << _datePeriod;
    return oStr.str();
  }

}
