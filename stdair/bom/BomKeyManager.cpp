// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/bom/BomRootKey.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/LegDateKey.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/LegCabinKey.hpp>
#include <stdair/bom/SegmentCabinKey.hpp>
#include <stdair/bom/FareFamilyKey.hpp>
#include <stdair/bom/BookingClassKey.hpp>
#include <stdair/bom/BomKeyManager.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // ////////////// Tokenising support ///////////////
  /**
   * Boost Tokeniser.
   */
  typedef boost::tokenizer<boost::char_separator<char> > Tokeniser_T;

  /**
   * Delimitors for the tokenisation process.
   */
  const boost::char_separator<char> TokeniserSeparator (",. ");

  /**
   * Dash delimitor for the tokenisation process.
   */
  const boost::char_separator<char> TokeniserDashSeparator ("-");


  // ////////////////////////////////////////////////////////////////////
  InventoryKey BomKeyManager::
  extractInventoryKey (const std::string& iFullKeyStr) {

    // Token-ise the full key string
    Tokeniser_T lTokens (iFullKeyStr, TokeniserSeparator);

    //
    Tokeniser_T::iterator itToken = lTokens.begin();

    // Airline code
    //
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No airline code can be found in '" << iFullKeyStr
                        << "'");
      throw KeyNotFoundException ("No airline code can be found in '"
                                  + iFullKeyStr + "'");
    }

    const AirlineCode_T lAirlineCode (*itToken);

    //
    const InventoryKey oInventoryKey (lAirlineCode);

    return oInventoryKey;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey BomKeyManager::
  extractFlightDateKey (const std::string& iFullKeyStr) {

    // Token-ise the full key string
    Tokeniser_T lTokens (iFullKeyStr, TokeniserSeparator);

    //
    Tokeniser_T::iterator itToken = lTokens.begin();

    // Airline code
    //
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No airline code can be found in '" << iFullKeyStr
                        << "'");
      throw KeyNotFoundException ("No airline code can be found in '"
                                  + iFullKeyStr + "'");
    }

    const AirlineCode_T lAirlineCode (*itToken);

    // Flight number
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No flight number can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No flight number can be found in '"
                                  + iFullKeyStr + "'");
    }
    
    const FlightNumber_T lFlightNumber =
      boost::lexical_cast<FlightNumber_T> (*itToken);

    // Flight departure date
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No date can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No date can be found in '"
                                  + iFullKeyStr + "'");
    }

    const Date_T lFlightDateDate =
      boost::gregorian::from_simple_string (*itToken);

    //
    const FlightDateKey oFlightDateKey (lFlightNumber, lFlightDateDate);

    return oFlightDateKey;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey BomKeyManager::
  extractSegmentDateKey (const std::string& iFullKeyStr) {

    // Token-ise the full key string
    Tokeniser_T lTokens (iFullKeyStr, TokeniserSeparator);

    //
    Tokeniser_T::iterator itToken = lTokens.begin();

    // Airline code
    //
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No airline code can be found in '" << iFullKeyStr
                        << "'");
      throw KeyNotFoundException ("No airline code can be found in '"
                                  + iFullKeyStr + "'");
    }

    // Flight number
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No flight number can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No flight number can be found in '"
                                  + iFullKeyStr + "'");
    }

    // Flight departure date
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No date can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No date can be found in '"
                                  + iFullKeyStr + "'");
    }

    // Origin
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No origin can be found in '" << iFullKeyStr << "'");
      throw KeyNotFoundException ("No origin can be found in '"
                                  + iFullKeyStr + "'");
    }
    
    const AirportCode_T lOrigin (*itToken);

    // Destination
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No destination can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No destination can be found in '"
                                  + iFullKeyStr + "'");
    }

    const AirportCode_T lDestination (*itToken);

    //
    const SegmentDateKey oSegmentDateKey (lOrigin, lDestination);

    return oSegmentDateKey;
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassKey BomKeyManager::
  extractBookingClassKey (const std::string& iFullKeyStr) {

    // Token-ise the full key string
    Tokeniser_T lTokens (iFullKeyStr, TokeniserSeparator);

    //
    Tokeniser_T::iterator itToken = lTokens.begin();

    // Airline code
    //
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No booking class can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No booking class can be found in '"
                                  + iFullKeyStr + "'");
    }
    
    // Flight number
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No flight number can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No flight number can be found in '"
                                  + iFullKeyStr + "'");
    }

    // Flight departure date
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No date can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No date can be found in '"
                                  + iFullKeyStr + "'");
    }

    // Origin
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No origin can be found in '" << iFullKeyStr << "'");
      throw KeyNotFoundException ("No origin can be found in '"
                                  + iFullKeyStr + "'");
    }
    
    // Destination
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No destination can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No destination can be found in '"
                                  + iFullKeyStr + "'");
    }

    // Class code
    ++itToken;
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No booking class can be found in '"
                        << iFullKeyStr << "'");
      throw KeyNotFoundException ("No booking class can be found in '"
                                  + iFullKeyStr + "'");
    }

    const ClassCode_T lClassCode (*itToken);

    //
    const BookingClassKey oBookingClassKey (lClassCode);

    return oBookingClassKey;
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassKey BomKeyManager::
  extractBookingClassKeyFromClassList (const ClassList_String_T& iClassList) {

    // Token-ise the full key string
    Tokeniser_T lTokens (iClassList, TokeniserDashSeparator);

    //
    Tokeniser_T::iterator itToken = lTokens.begin();

    // Booking class code
    //
    //
    if (itToken == lTokens.end()) {
      STDAIR_LOG_ERROR ("No booking class code can be found in '"
                        << iClassList << "'");
      throw KeyNotFoundException ("No booking class code can be found in '"
                                  + iClassList + "'");
    }

    const ClassCode_T lClassCode (*itToken);

    //
    const BookingClassKey oBookingClassKey (lClassCode);

    return oBookingClassKey;
  }

}
