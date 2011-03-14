#ifndef __STDAIR_BAS_BASCONST_BOMMANAGER_HPP
#define __STDAIR_BAS_BASCONST_BOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost
#include <boost/tokenizer.hpp>

namespace stdair {

  /** Array with the indentation spaces needed for all the BOM
      hierachical levels. */
  extern const std::string DISPLAY_LEVEL_STRING_ARRAY[51];

  /** Default delimiter for string display (e.g delimiter for inventory key
      and flight-date key). */
  extern const std::string DEFAULT_KEY_FLD_DELIMITER;

  /** Default sub delimiter for string display (e.g delimiter for flight number
      and departure date of a flight-date key). */
  extern const std::string DEFAULT_KEY_SUB_FLD_DELIMITER;

  /** Default token for decoding a full string display. */
  extern const boost::char_separator<char> DEFAULT_KEY_TOKEN_DELIMITER;
      
}
#endif // __STDAIR_BAS_BASCONST_BOMMANAGER_HPP
