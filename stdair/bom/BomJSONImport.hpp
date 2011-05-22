#ifndef __STDAIR_BOM_BOMJSONIMPORT_HPP
#define __STDAIR_BOM_BOMJSONIMPORT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>

namespace stdair {

  /**
   * @brief Utility class to import StdAir objects in a JSON format.
   */
  class BomJSONImport {
  public:
    // //////////////// Import support methods /////////////////
    /**
     * Extract the airline code from a given JSON-formatted string.
     *
     * @param std::string& JSON-formatted string.
     * @param AirlineCode_T& Airline code extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportInventoryKey (const std::string& iBomKey,
                                        AirlineCode_T&);

    /**
     * Build a FlightDateKey from a given JSON-formatted string.
     *
     * @param std::string& JSON-formatted string.
     * @param FlightNumber_T& Flight number extracted from the given string.
     * @param Date_T& Departure date  extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportFlightDateKey (const std::string& iBomKey,
                                         FlightNumber_T&,
                                         Date_T& ioDepartureDate);
  };

}
#endif // __STDAIR_BOM_BOMJSONIMPORT_HPP
