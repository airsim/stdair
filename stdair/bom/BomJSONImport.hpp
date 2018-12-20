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
#include <stdair/basic/EventType.hpp>
#include <stdair/bom/BreakPointStruct.hpp>


namespace stdair {

  /// Forward declarations
  class JSONString;
  struct ConfigHolderStruct;

  /**
   * @brief Utility class to import StdAir objects in a JSON format.
   */
  class BomJSONImport {
  public:
    // //////////////// Import support methods /////////////////
    /**
     * Extract the JSON command from a given JSON-formatted string.
     *
     * @param const JSONString& JSON-formatted string.
     * @param JSonCommand::EN_JSonCommand& JSOM command extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportCommand (const JSONString&,
                                   JSonCommand::EN_JSonCommand&);
    /**
     * Extract the airline code from a given JSON-formatted string.
     *
     * @param const JSONString& JSON-formatted string.
     * @param AirlineCode_T& Airline code extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportInventoryKey (const JSONString&,
                                        AirlineCode_T&);

    /**
     * Extract the FlightDate from a given JSON-formatted string.
     *
     * @param const JSONString& JSON-formatted string.
     * @param Date_T& Departure date  extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportFlightDate (const JSONString&,
                                      Date_T&);

    /**
     * Extract the FlightNumber from a given JSON-formatted string.
     *
     * @param const JSONString& JSON-formatted string.
     * @param FlightNumber_T& Flight number extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportFlightNumber (const JSONString&,
                                        FlightNumber_T&);

    /**
     * Extract the break points from a given JSON-formatted string.
     *
     * @param const JSONString& JSON-formatted string.
     * @param BreakPointList_T& List of breaking points extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportBreakPoints (const JSONString&,
				       BreakPointList_T&);
 
    /**
     * Extract the event type from a given JSON-formatted string.
     *
     * @param const JSONString& JSON-formatted string.
     * @param EventType::EN_EventType& Event type extracted from the given string.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportEventType (const JSONString&,
				     EventType::EN_EventType&);

    /**
     * Extract the configuration ptree from the given JSON-formatted string
     * and add it to the configuration holder
     *
     * @param const JSONString& JSON-formatted string.
     * @param ConfigHolderStruct& Configuration holder.
     * @return bool State whether the extracting has been successful.
     */
    static bool jsonImportConfig (const JSONString&,
                                  ConfigHolderStruct&);
  };

}
#endif // __STDAIR_BOM_BOMJSONIMPORT_HPP
