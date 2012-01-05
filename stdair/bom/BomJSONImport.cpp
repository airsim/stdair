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
#include <boost/regex.hpp>
#endif // BOOST_VERSION >= 104100
// StdAir
#include <stdair/bom/BomJSONImport.hpp>
#include <stdair/stdair_exceptions.hpp>

#if BOOST_VERSION >= 104100
namespace bpt = boost::property_tree;
#else // BOOST_VERSION >= 104100
namespace bpt {
  typedef char ptree;
}
#endif // BOOST_VERSION >= 104100

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::
  jsonImportCommand (const std::string& iBomTree,
                     JSonCommand::EN_JSonCommand& ioEnumJSonCommand) {

    bool hasCommandBeenSuccessfullyRetrieved = true;

    try {
      /**
       * Expected format:
       *   line:            {"command":{details}}
       *   command:         word with underscore character allowed
       *                    ([[:alpha:]|_]*)
       *   details:         expression componed of alpha, numeric and
       *                    punctuation characters plus spaces
       */
      const std::string lRegEx("^[{][[:space:]]*\""
                               "([[:alpha:]|_]*)\"[[:space:]]*:"
                               "[[:space:]]*[{]"
                               "([[:alnum:]|[:punct:]|[:space:]]*)"
                               "[}][}]");
    
      // See the caller for the regular expression
      boost::regex lExpression (lRegEx);

      std::string::const_iterator itStart = iBomTree.begin();
      std::string::const_iterator itEnd = iBomTree.end();

      boost::match_results<std::string::const_iterator> lWhat;
      boost::match_flag_type lFlags = boost::match_default;
 
      regex_search (itStart, itEnd, lWhat, lExpression, lFlags);
 
      // Put the matched strings in the list of tokens to be returned back
      // to the caller
      std::vector<std::string> oTokenList;
      const unsigned short lMatchSetSize = lWhat.size();
      for (unsigned short matchIdx = 1; matchIdx != lMatchSetSize; ++matchIdx) {
        const std::string lMatchedString (std::string (lWhat[matchIdx].first,
                                                       lWhat[matchIdx].second));
        oTokenList.push_back (lMatchedString);
      }

      // If the retrieved token list is empty, the command has not been
      // retrieved
      if (oTokenList.empty() == true) {
        hasCommandBeenSuccessfullyRetrieved = false;
        return hasCommandBeenSuccessfullyRetrieved;
      }

      assert (oTokenList.empty() == false);
      // Retrieved the command string into the token list
      const std::string lCommandStr = oTokenList[0];
    
      // Remember the first letter of the command string
      const char lCommandChar (lCommandStr[0]);
      const JSonCommand lJSonCommand (lCommandChar);
      ioEnumJSonCommand = lJSonCommand.getCommand();

    } catch (stdair::CodeConversionException& ccException) {
      hasCommandBeenSuccessfullyRetrieved = false;
    }
    
    return hasCommandBeenSuccessfullyRetrieved;
    
  }

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
      bpt::ptree::const_iterator itBegin = pt.begin();
      const std::string lCommandName = itBegin->first;
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
      bpt::ptree::const_iterator itBegin = pt.begin();
      const std::string lCommandName = itBegin->first;
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
