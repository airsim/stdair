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
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/ParsedKey.hpp>
#include <stdair/bom/BomKeyManager.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // ////////////// Tokenising support ///////////////
  /**
   * Boost Tokeniser.
   */
  typedef boost::tokenizer<boost::char_separator<char> > Tokeniser_T;

  // ////////////////////////////////////////////////////////////////////
  ParsedKey BomKeyManager::extractKeys (const std::string& iFullKeyStr) {
    ParsedKey oParsedKey;
    oParsedKey._fullKey = iFullKeyStr;

    // Token-ise the full key string
    Tokeniser_T lTokens (iFullKeyStr, DEFAULT_KEY_TOKEN_DELIMITER);
    Tokeniser_T::iterator itToken = lTokens.begin();

    // Airline code
    if (itToken != lTokens.end()) {
      oParsedKey._airlineCode = *itToken;
      
    // Flight number
      ++itToken;
      if (itToken != lTokens.end()) {
        oParsedKey._flightNumber = *itToken;

        // Departure date
        ++itToken;
        if (itToken != lTokens.end()) {
          oParsedKey._departureDate = *itToken;

          // Origin
          ++itToken;
          if (itToken != lTokens.end()) {
            oParsedKey._boardingPoint = *itToken;

            // Destination
            ++itToken;
            if (itToken != lTokens.end()) {
              oParsedKey._offPoint = *itToken;

              // Boarding time
              ++itToken;
              if (itToken != lTokens.end()) {
                oParsedKey._boardingTime = *itToken;
              }
            }
          }
        }
      }
    }

    return oParsedKey;
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryKey BomKeyManager::
  extractInventoryKey (const std::string& iFullKeyStr) {
    ParsedKey lParsedKey = extractKeys (iFullKeyStr);

    return lParsedKey.getInventoryKey();
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateKey BomKeyManager::
  extractFlightDateKey (const std::string& iFullKeyStr) {
    ParsedKey lParsedKey = extractKeys (iFullKeyStr);

    return lParsedKey.getFlightDateKey();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey BomKeyManager::
  extractSegmentDateKey (const std::string& iFullKeyStr) {
    ParsedKey lParsedKey = extractKeys (iFullKeyStr);

    return lParsedKey.getSegmentKey();
  }
}
