// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost Property Tree
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
// StdAir
#include <stdair/bom/BomJSONImport.hpp>

namespace bpt = boost::property_tree;

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportInventoryKey (const std::string& iBomTree,
                                              AirlineCode_T& ioAirlineCode) {
    bool hasKeyBeenSuccessfullyRetrieved = true;

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

    return hasKeyBeenSuccessfullyRetrieved;
  }

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportFlightDateKey (const std::string& iBomTree,
                                               FlightNumber_T& ioFlightNumber,
                                               Date_T& ioDepartureDate) {
    bool hasKeyBeenSuccessfullyRetrieved = false;

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

    return hasKeyBeenSuccessfullyRetrieved;
  }

}
