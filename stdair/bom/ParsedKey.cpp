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
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/ParsedKey.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // ////////////// Tokenising support ///////////////
  /**
   * Boost Tokeniser.
   */
  typedef boost::tokenizer<boost::char_separator<char> > Tokeniser_T;

  /**
   * Dash delimitor for the tokenisation process.
   */
  const boost::char_separator<char> TokeniserDashSeparator ("-");
  
  /**
   * Time delimitor for the tokenisation process.
   */
  const boost::char_separator<char> TokeniserTimeSeparator (":");

  // ////////////////////////////////////////////////////////////////////
  ParsedKey::ParsedKey () : _fullKey (""), _airlineCode (""), _flightNumber (""),
                            _departureDate (""), _boardingPoint (""),
                            _offPoint (""), _boardingTime ("") {
  }

  // ////////////////////////////////////////////////////////////////////
  ParsedKey::~ParsedKey () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  InventoryKey ParsedKey:: getInventoryKey () const {
    if (_airlineCode.size() < 2 || _airlineCode.size() > 3) {
      STDAIR_LOG_ERROR ("No airline code can be found in '" << _fullKey
                        << "'");
      STDAIR_LOG_DEBUG ("Parsed key: " << toString());
      throw KeyNotFoundException ("No airline code can be found in '"
                                  + _fullKey + "'");
    }
    return _airlineCode;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey ParsedKey:: getFlightDateKey () const {
    // Verify if the departure date has been parsed correctly.
    Tokeniser_T lDateTokens (_departureDate, TokeniserDashSeparator);
    if (lDateTokens.begin() == lDateTokens.end()) {
      STDAIR_LOG_ERROR ("No date can be found in '"
                        << _fullKey << "'");
      STDAIR_LOG_DEBUG ("Parsed key: " << toString());
      throw KeyNotFoundException ("No date can be found in '"
                                  + _fullKey + "'");
    }

    const FlightNumber_T lFlightNumber =
      boost::lexical_cast<FlightNumber_T> (_flightNumber);

    const Date_T lDepartureDate =
      boost::gregorian::from_simple_string (_departureDate);

    const FlightDateKey oFlightDateKey (lFlightNumber, lDepartureDate);

    return oFlightDateKey;
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey ParsedKey:: getSegmentKey () const {
    if (_boardingPoint.size() != 3 || _offPoint.size() != 3) {
      STDAIR_LOG_ERROR ("No airport code can be found in '" << _fullKey
                        << "'");
      STDAIR_LOG_DEBUG ("Parsed key: " << toString());
      throw KeyNotFoundException ("No airport code can be found in '"
                                  + _fullKey + "'");
    }

    const SegmentDateKey oSegmentDateKey (_boardingPoint, _offPoint);

    return oSegmentDateKey;
  }

  // ////////////////////////////////////////////////////////////////////
  const Duration_T ParsedKey::getBoardingTime () const {
    // Verify if the boarding time has been parsed correctly.
    Tokeniser_T lTimeTokens (_boardingTime, TokeniserTimeSeparator);
    if (lTimeTokens.begin() == lTimeTokens.end()) {
      STDAIR_LOG_ERROR ("No boarding time can be found in '"
                        << _fullKey << "'");
      STDAIR_LOG_DEBUG ("Parsed key: " << toString());
      throw KeyNotFoundException ("No boarding time can be found in '"
                                  + _fullKey + "'");
    }

    const Duration_T oBoardingTime (boost::posix_time::duration_from_string (_boardingTime));

    return oBoardingTime;
  }

  // ////////////////////////////////////////////////////////////////////
  void ParsedKey::toStream (std::ostream& ioOut) const {
    ioOut << "ParsedKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void ParsedKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string ParsedKey::toString() const {
    std::ostringstream oStr;
    
    oStr << _airlineCode
         << DEFAULT_KEY_FLD_DELIMITER << " "
         << _flightNumber
         << DEFAULT_KEY_SUB_FLD_DELIMITER << " "
         << _departureDate
         << DEFAULT_KEY_FLD_DELIMITER << " "
         << _boardingPoint
         << DEFAULT_KEY_SUB_FLD_DELIMITER << " "
         << _offPoint
         << DEFAULT_KEY_FLD_DELIMITER << " "
         << _boardingTime;
    
    return oStr.str();
  }

}
