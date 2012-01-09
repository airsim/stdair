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
  jsonImportCommand (const std::string& iBomJSONStr,
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

      std::string::const_iterator itStart = iBomJSONStr.begin();
      std::string::const_iterator itEnd = iBomJSONStr.end();

      boost::match_results<std::string::const_iterator> lWhat;
      boost::match_flag_type lFlags = boost::match_default;
 
      regex_search (itStart, itEnd, lWhat, lExpression, lFlags);
 
      // Put the matched strings in the list of tokens to be returned back
      // to the caller
      std::vector<std::string> oTokenList;  
      for (boost::match_results<std::string::const_iterator>::const_iterator itMatch
             = lWhat.begin(); itMatch != lWhat.end(); ++itMatch) {
        
        const std::string lMatchedString (std::string (itMatch->first,
                                                       itMatch->second));
        oTokenList.push_back (lMatchedString);
      }

      // If the retrieved token list is empty, the command has not been
      // retrieved
      if (oTokenList.size() <= 1) {
        hasCommandBeenSuccessfullyRetrieved = false;
        return hasCommandBeenSuccessfullyRetrieved;
      }

      assert (oTokenList.size() >= 2);
      // Retrieved the command string into the token list
      const std::string lCommandStr = oTokenList.at(1);
    
      // Remember the first letter of the command string
      const std::string lCommandCharStr (lCommandStr.substr(0, 1));
      const JSonCommand lJSonCommand (lCommandCharStr);
      ioEnumJSonCommand = lJSonCommand.getCommand();

    } catch (stdair::CodeConversionException& ccException) {
      hasCommandBeenSuccessfullyRetrieved = false;
    }
    
    return hasCommandBeenSuccessfullyRetrieved;
    
  }

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportInventoryKey (const std::string& iBomJSONStr,
                                              AirlineCode_T& ioAirlineCode) {
    bool hasKeyBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomJSONStr);
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
  bool BomJSONImport::jsonImportFlightDate (const std::string& iBomJSONStr,
                                            Date_T& ioDepartureDate) {
    bool hasKeyBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomJSONStr);
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
  bool BomJSONImport::jsonImportFlightNumber (const std::string& iBomJSONStr,
                                              FlightNumber_T& ioFlightNumber) {
    
    bool hasKeyBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomJSONStr);
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
