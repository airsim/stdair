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
#include <stdair/bom/FlightDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::FlightDateKey()
    : _flightNumber (DEFAULT_FLIGHT_NUMBER), _flightDate (DEFAULT_FLIGHT_DATE) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::FlightDateKey (const FlightNumber_T& iFlightNumber,
                                const Date_T& iFlightDate)
    : _flightNumber (iFlightNumber), _flightDate (iFlightDate) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::FlightDateKey (const FlightDateKey& iKey)
    : _flightNumber (iKey._flightNumber), _flightDate (iKey._flightDate) {
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
    const std::string& lFlightDateStr =
      boost::gregorian::to_simple_string (_flightDate);
    oStr << _flightNumber << ", " << lFlightDateStr;
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
    std::string lFlightDateStr =
      boost::gregorian::to_simple_string (_flightDate);
    ioArchive & _flightNumber & lFlightDateStr;
  }

}
