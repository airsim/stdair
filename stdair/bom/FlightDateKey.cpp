// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/FlightDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey::FlightDateKey ()
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
  FlightDateKey::~FlightDateKey () {
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
    oStr << _flightNumber << ", " << _flightDate;
    return oStr.str();
  }

}
