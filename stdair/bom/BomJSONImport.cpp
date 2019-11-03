// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <sstream>
#if BOOST_VERSION_MACRO >= 104100
// Boost Property Tree
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#endif // BOOST_VERSION_MACRO >= 104100
#include <boost/regex.hpp>
// StdAir
#include <stdair/bom/BomJSONImport.hpp>
#include <stdair/stdair_exceptions.hpp>
#include <stdair/stdair_json.hpp>
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/ConfigHolderStruct.hpp>

#if BOOST_VERSION_MACRO >= 104100
namespace bpt = boost::property_tree;
#else // BOOST_VERSION_MACRO >= 104100
namespace boost {
  namespace property_tree {
    typedef std::string ptree;
  }
}
#endif // BOOST_VERSION_MACRO >= 104100

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::
  jsonImportCommand (const JSONString& iBomJSONStr,
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
			       "[[]?"
                               "[[:space:]]*[{]?"
                               "([[:alnum:]|[:punct:]|[:space:]]*)"
                               "[}]?[]]?[}]");
    
      // See the caller for the regular expression
      boost::regex lExpression (lRegEx);

      const std::string& lBomJSONStr = iBomJSONStr.getString();
      std::string::const_iterator itStart = lBomJSONStr.begin();
      std::string::const_iterator itEnd = lBomJSONStr.end();

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
      const JSonCommand lJSonCommand (lCommandStr);
      ioEnumJSonCommand = lJSonCommand.getCommand();

    } catch (stdair::CodeConversionException& ccException) {
      hasCommandBeenSuccessfullyRetrieved = false;
    }
    
    return hasCommandBeenSuccessfullyRetrieved;
    
  }

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportInventoryKey (const JSONString& iBomJSONStr,
                                              AirlineCode_T& ioAirlineCode) {
    bool hasKeyBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION_MACRO >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomJSONStr.getString());
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
      
#endif // BOOST_VERSION_MACRO >= 104100
    return hasKeyBeenSuccessfullyRetrieved;
  }

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportFlightDate (const JSONString& iBomJSONStr,
                                            Date_T& ioDepartureDate) {
    bool hasKeyBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION_MACRO >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomJSONStr.getString());
      read_json (iStr, pt);

      // Build the right path to obtain the departure date value.
      const std::string& lDepartureDateStr =
        pt.get<std::string> ("flight_date.departure_date");
      
      // Get the departure_date.
      // If the path key is not found, an exception is thrown.
      ioDepartureDate = 
	boost::gregorian::from_simple_string (lDepartureDateStr);

    } catch (bpt::ptree_error& bptException) {
      hasKeyBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION_MACRO >= 104100

    return hasKeyBeenSuccessfullyRetrieved;
  }

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportFlightNumber (const JSONString& iBomJSONStr,
                                              FlightNumber_T& ioFlightNumber) {
    
    bool hasKeyBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION_MACRO >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomJSONStr.getString());
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
#endif // BOOST_VERSION_MACRO >= 104100

    return hasKeyBeenSuccessfullyRetrieved;
  } 

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportBreakPoints (const JSONString& iBomJSONStr,
					     BreakPointList_T& oBreakPointList) { 
    
    bool hasKeyBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION_MACRO >= 104100
    // Create an empty property tree object
    bpt::ptree pt;    

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomJSONStr.getString());
      read_json (iStr, pt);    

      // Access the break point list tree
      bpt::ptree::const_iterator itBegin = pt.begin();
      bpt::ptree ptListOfBP = itBegin->second; 
      // Browse the break point list
      for (bpt::ptree::const_iterator itBP = ptListOfBP.begin();   
	   itBP != ptListOfBP.end(); ++itBP) { 
	// Access the current break point tree
	bpt::ptree ptBP = itBP->second;
	// Access the date of the break point
	bpt::ptree::const_iterator itDate = ptBP.begin(); 
	bpt::ptree ptDate = itDate->second;
	// Recover the string containing the date
	std::string lDateString = ptDate.data();
	if (lDateString.empty() == false) {
	  // Construct the break point using the recovered string
	  const Date_T lDate = 
	    boost::gregorian::from_simple_string (lDateString);
	  BreakPointStruct lBreakPoint (lDate);
	  // Add the break point to the list
	  oBreakPointList.push_back (lBreakPoint);
	}
      }
    } catch (bpt::ptree_error& bptException) {
      hasKeyBeenSuccessfullyRetrieved = false;
    } catch (boost::bad_lexical_cast& eCast) { 
      hasKeyBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION_MACRO >= 104100

    return hasKeyBeenSuccessfullyRetrieved;
  }  

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportEventType (const JSONString& iBomJSONStr,
					   EventType::EN_EventType& ioEventType) {
    
    bool hasKeyBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION_MACRO >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomJSONStr.getString());
      read_json (iStr, pt);

      // Build the right path to obtain the event type value.
      bpt::ptree::const_iterator itBegin = pt.begin();
      const std::string lEventTypeName = itBegin->first;
      std::ostringstream lPath;
      lPath << lEventTypeName << ".event_type";
      
      // Get the event type string
      // If the path key is not found, an exception bpt::ptree_error is thrown.
      const std::string lEventTypeStr = pt.get<std::string> (lPath.str());  
      // Build the event type using the string.
      // If the input string is incorrect, an exception 
      // stdair::CodeConversionException is thrown.
      const EventType lEventType (lEventTypeStr);
      ioEventType = lEventType.getType();

    } catch (bpt::ptree_error& bptException) {
      hasKeyBeenSuccessfullyRetrieved = false;
    } catch (stdair::CodeConversionException& cceException) {
      hasKeyBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION_MACRO >= 104100

    return hasKeyBeenSuccessfullyRetrieved;
  }

  // ////////////////////////////////////////////////////////////////////
  bool BomJSONImport::jsonImportConfig (const JSONString& iBomJSONStr,
                                        ConfigHolderStruct& iConfigHolderStruct) {
    
    bool hasConfigBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION_MACRO >= 104100
    // Create an empty property tree object
    bpt::ptree pt;

    try {

      // Load the JSON formatted string into the property tree.
      // If reading fails (cannot open stream, parse error), an
      // exception is thrown.
      std::istringstream iStr (iBomJSONStr.getString());
      read_json (iStr, pt);

      // Load the pt in the configuration holder
      iConfigHolderStruct.add (pt);
    } catch (bpt::ptree_error& bptException) {
      hasConfigBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION_MACRO >= 104100

    return hasConfigBeenSuccessfullyRetrieved;
  } 

}
