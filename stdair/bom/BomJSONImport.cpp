// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#if BOOST_VERSION >= 104100
// Boost Property Tree
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#endif // BOOST_VERSION >= 104100
// StdAir
#include <stdair/bom/BomJSONImport.hpp>

#if BOOST_VERSION >= 104100
namespace bpt = boost::property_tree;
#else // BOOST_VERSION >= 104100
namespace bpt {
  typedef char ptree;
}
#endif // BOOST_VERSION >= 104100

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportInventoryKey (const std::string& iBomTree,
                                              AirlineCode_T& ioAirlineCode) {
    bool hasKeyBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomTree);
      read_json (iStr, pt);

      // Get the airline_code and build an InventoryKey structure.
      // If the flight_date.airline_code key is not found, an
      // exception is thrown.
      ioAirlineCode = pt.get<AirlineCode_T> ("flight_date.airline_code");

    } catch (bpt::ptree_error& bptException) {
      hasKeyBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION >= 104100

    return hasKeyBeenSuccessfullyRetrieved;
  }

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportFlightDateKey (const std::string& iBomTree,
                                               FlightNumber_T& ioFlightNumber,
                                               Date_T& ioDepartureDate) {
    bool hasKeyBeenSuccessfullyRetrieved = false;

#if BOOST_VERSION >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomTree);
      read_json (iStr, pt);

      // Get the flight_number and departure_date and build an
      // FlightDateKey structure.
      ioFlightNumber = pt.get<FlightNumber_T> ("flight_date.flight_number");

      const std::string& lDepartureDateStr =
        pt.get<std::string> ("flight_date.departure_date");
      ioDepartureDate = boost::gregorian::from_simple_string (lDepartureDateStr);

    } catch (bpt::ptree_error& bptException) {
      hasKeyBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION >= 104100

    return hasKeyBeenSuccessfullyRetrieved;
  }

}
