// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost Date-Time
#include <boost/date_time/gregorian/formatters.hpp>
// Boost.Serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/FlightDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::FlightDateKey()
    : _flightNumber (DEFAULT_FLIGHT_NUMBER),
      _departureDate (DEFAULT_DEPARTURE_DATE) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::FlightDateKey (const FlightNumber_T& iFlightNumber,
                                const Date_T& iFlightDate)
    : _flightNumber (iFlightNumber), _departureDate (iFlightDate) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::FlightDateKey (const FlightDateKey& iKey)
    : _flightNumber (iKey._flightNumber), _departureDate (iKey._departureDate) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::~FlightDateKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDateKey::toStream (std::ostream& ioOut) const {
    ioOut << "FlightDateKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDateKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string FlightDateKey::toString() const {
    std::ostringstream oStr;
    const std::string& lDepartureDateStr =
      boost::gregorian::to_simple_string (_departureDate);
    oStr << _flightNumber
         << DEFAULT_KEY_SUB_FLD_DELIMITER << " " << lDepartureDateStr;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDateKey::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void FlightDateKey::serialize (Archive& ioArchive,
                                 const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    std::string lDepartureDateStr =
      boost::gregorian::to_simple_string (_departureDate);
    ioArchive & _flightNumber & lDepartureDateStr;
  }

}
