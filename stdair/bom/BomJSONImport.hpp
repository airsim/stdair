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
#include <stdair/basic/JSonCommand.hpp>


namespace stdair {

  /**
   * @brief Utility class to import StdAir objects in a JSON format.
   */
  class BomJSONImport {
  public:
    // //////////////// Import support methods /////////////////
    /**
     * Extract the JSON command from a given JSON-formatted string.
     *
     * @param std::string& JSON-formatted string.
     * @param JSonCommand::EN_JSonCommand& JSOM command extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportCommand (const std::string&,
                                   JSonCommand::EN_JSonCommand&);
    /**
     * Extract the airline code from a given JSON-formatted string.
     *
     * @param std::string& JSON-formatted string.
     * @param AirlineCode_T& Airline code extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportInventoryKey (const std::string&,
                                        AirlineCode_T&);

    /**
     * Extract the FlightDate from a given JSON-formatted string.
     *
     * @param std::string& JSON-formatted string.
     * @param Date_T& Departure date  extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportFlightDate (const std::string&,
                                      Date_T&);

    /**
     * Extract the FlightNumber from a given JSON-formatted string.
     *
     * @param std::string& JSON-formatted string.
     * @param FlightNumber_T& Flight number extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportFlightNumber (const std::string&,
                                        FlightNumber_T&);
  };

}
#endif // __STDAIR_BOM_BOMJSONIMPORT_HPP
