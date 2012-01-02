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

      // Build the right path to obtain the airline code value.
      const std::string lCommandName = (pt.front()).first;
      std::ostringstream lPath;
      lPath << lCommandName << ".airline_code";

      // Get the airline_code.
      // If the path key is not found, an exception is thrown.
      ioAirlineCode = pt.get<AirlineCode_T> (lPath.str());  

    } catch (bpt::ptree_error& bptException) {
      hasKeyBeenSuccessfullyRetrieved = false;
    }
      
  #endif // BOOST_VERSION >= 104100  
    return hasKeyBeenSuccessfullyRetrieved;
  }

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportFlightDate (const std::string& iBomTree,
                                            Date_T& ioDepartureDate) {
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

      // Build the right path to obtain the departure date value.
      const std::string& lDepartureDateStr =
        pt.get<std::string> ("flight_date.departure_date");
      
      // Get the departure_date.
      // If the path key is not found, an exception is thrown.
      ioDepartureDate = boost::gregorian::from_simple_string (lDepartureDateStr);

    } catch (bpt::ptree_error& bptException) {
      hasKeyBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION >= 104100

    return hasKeyBeenSuccessfullyRetrieved;
  }

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportFlightNumber (const std::string& iBomTree,
                                              FlightNumber_T& ioFlightNumber) {
    
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

      // Build the right path to obtain the flight number value.
      const std::string lCommandName = (pt.front()).first;
      std::ostringstream lPath;
      lPath << lCommandName << ".flight_number";
      
      // Get the flight_number.
      // If the path key is not found, an exception is thrown.
      ioFlightNumber = pt.get<FlightNumber_T> (lPath.str());

    } catch (bpt::ptree_error& bptException) {
      hasKeyBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION >= 104100

    return hasKeyBeenSuccessfullyRetrieved;
  }

}
