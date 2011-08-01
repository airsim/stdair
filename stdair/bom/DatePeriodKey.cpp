// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// Boost Date-Time
#include <boost/date_time/gregorian/formatters.hpp>
// STDAIR
#include <stdair/basic/BasConst_Period_BOM.hpp>
#include <stdair/bom/DatePeriodKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  DatePeriodKey::DatePeriodKey()
    : _datePeriod (BOOST_DEFAULT_DATE_PERIOD) {
    assert (false);
  }

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
    const stdair::Date_T lStart = _datePeriod.begin();
    const stdair::Date_T lEnd = _datePeriod.end();
    oStr << "[" << boost::gregorian::to_simple_string(lStart)
         << "/" << boost::gregorian::to_simple_string(lEnd)
         << "]";
    return oStr.str();
  }

}
