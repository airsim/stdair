#ifndef __STDAIR_BOM_BOMRETRIEVER_HPP
#define __STDAIR_BOM_BOMRETRIEVER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/bom/DatePeriod.hpp>

namespace stdair {

  /// Forward declarations
  class BomRoot;
  struct InventoryKey;
  class Inventory;
  struct FlightDateKey;
  class FlightDate;
  class LegDate;
  struct SegmentDateKey;
  class SegmentDate;
  class LegCabin;
  class SegmentCabin;
  class FareFamily;
  class BookingClass;
  class DatePeriod;
  class AirportPair;

  /**
   * @brief Utility class to retrieve StdAir objects.
   */
  class BomRetriever {
  public:
    // //////////////// Key management support methods /////////////////
    /**
     * Retrieve an Inventory object from a (full) key string.
     *
     * The full key string gathers airline code, flight number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const BomRoot& The root of the BOM tree.
     * @param const std::string& The full key string.
     * @return Inventory* The just retrieved Inventory object.
     */
    static Inventory*
    retrieveInventoryFromLongKey (const BomRoot&,
                                  const std::string& iFullKeyStr);

    /**
     * Retrieve an Inventory object from an InventoryKey structure.
     *
     * @param const BomRoot& The root of the BOM tree.
     * @param const InventoryKey& The key.
     * @return Inventory* The just retrieved Inventory object.
     */
    static Inventory* retrieveInventoryFromKey (const BomRoot&,
                                                const InventoryKey&);

    /**
     * Retrieve an Inventory object from an InventoryKey structure.
     *
     * @param const BomRoot& The root of the BOM tree.
     * @param const AirlineCode_T& The key.
     * @return Inventory* The just retrieved Inventory object.
     */
    static Inventory* retrieveInventoryFromKey (const BomRoot&,
                                                const AirlineCode_T&);

    /**
     * Retrieve a FlightDate object from a (full) key string.
     *
     * The full key string gathers airline code, flight number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const BomRoot& The root of the BOM tree.
     * @param const std::string& The full key string.
     * @return FlightDate* The just retrieved FlightDate object.
     */
    static FlightDate*
    retrieveFlightDateFromLongKey (const BomRoot&,
                                   const std::string& iFullKeyStr);

    /**
     * Retrieve a FlightDate object from a set of keys.
     *
     * @param const BomRoot& The root of the BOM tree.
     * @param const AirlineCode_T& The key.
     * @param const FlightNumber_T& Part of the key.
     * @param const Date_T& Part of the key.
     * @return FlightDate* The just retrieved FlightDate object.
     */
    static FlightDate*
    retrieveFlightDateFromKeySet (const BomRoot&,
                                  const AirlineCode_T&, const FlightNumber_T&,
                                  const Date_T& iFlightDateDate);

    /**
     * Retrieve a FlightDate object from a (full) key string.
     *
     * The full key string gathers airline code, flight number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const Inventory& The root of the BOM tree.
     * @param const std::string& The full key string.
     * @return FlightDate* The just retrieved FlightDate object.
     */
    static FlightDate*
    retrieveFlightDateFromLongKey (const Inventory&,
                                   const std::string& iFullKeyStr);

    /**
     * Retrieve a FlightDate object from an FlightDateKey structure.
     *
     * @param const Inventory& The root of the BOM tree.
     * @param const FlightDateKey& The key.
     * @return FlightDate* The just retrieved FlightDate object.
     */
    static FlightDate* retrieveFlightDateFromKey (const Inventory&,
                                                  const FlightDateKey&);

    /**
     * Retrieve a FlightDate object from an FlightDateKey structure.
     *
     * @param const Inventory& The root of the BOM tree.
     * @param const FlightNumber_T& Part of the key.
     * @param const Date_T& Part of the key.
     * @return FlightDate* The just retrieved FlightDate object.
     */
    static FlightDate* retrieveFlightDateFromKey (const Inventory&,
                                                  const FlightNumber_T&,
                                                  const Date_T& iFlightDateDate);

    /**
     * Retrieve a SegmentDate object from a (full) key string.
     *
     * The full key string gathers airline code, segment number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const BomRoot& The root of the BOM tree.
     * @param const std::string& The full key string.
     * @return SegmentDate* The just retrieved SegmentDate object.
     */
    static SegmentDate*
    retrieveSegmentDateFromLongKey (const BomRoot&,
                                    const std::string& iFullKeyStr);

    /**
     * Retrieve a SegmentDate object from a (full) key string.
     *
     * The full key string gathers airline code, segment number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const Inventory& The root of the BOM tree.
     * @param const std::string& The full key string.
     * @return SegmentDate* The just retrieved SegmentDate object.
     */
    static SegmentDate*
    retrieveSegmentDateFromLongKey (const Inventory&,
                                    const std::string& iFullKeyStr);

    /**
     * Retrieve a SegmentDate object from a (full) key string.
     *
     * The full key string gathers airline code, segment number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const FlightDate& The root of the BOM tree.
     * @param const std::string& The full key string.
     * @return SegmentDate* The just retrieved SegmentDate object.
     */
    static SegmentDate*
    retrieveSegmentDateFromLongKey (const FlightDate&,
                                    const std::string& iFullKeyStr);

    /**
     * Retrieve a SegmentDate object from an SegmentDateKey structure.
     *
     * @param const FlightDate& The root of the BOM tree.
     * @param const SegmentDateKey& The key.
     * @return SegmentDate* The just retrieved SegmentDate object.
     */
    static SegmentDate* retrieveSegmentDateFromKey (const FlightDate&,
                                                    const SegmentDateKey&);

    /**
     * Retrieve a SegmentDate object from an SegmentDateKey structure.
     *
     * @param const FlightDate& The root of the BOM tree.
     * @param const AirportCode_T& Origin, part of the key.
     * @param const AirportCode_T& Destination, part of the key.
     * @return SegmentDate* The just retrieved SegmentDate object.
     */
    static SegmentDate*
    retrieveSegmentDateFromKey (const FlightDate&,
                                const AirportCode_T& iOrigin,
                                const AirportCode_T& iDestination);

    /**
     * Retrieve a BookingClass object from a (full) key string.
     *
     * The full key string gathers airline code, segment number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * Besides being attached to segment-cabin objects (and fare
     * family objects, when they exist), the booking-class objects
     * must also be attached directly to the segment-date.
     *
     * Hence, if an assertion fails within that method call,
     * chances are that the booking-class objects have not been
     * attached to the segment-date objects. Check, for instance,
     * the CmdBomManager::buildSampleBom() to see how that should
     * be properly done.
     *
     * @param const Inventory& The root of the BOM tree.
     * @param const std::string& Part of the full key string.
     * @param const ClassCode_T& Part of the full key string.
     * @return BookingClass* The just retrieved BookingClass object.
     */
    static BookingClass*
    retrieveBookingClassFromLongKey (const Inventory&,
                                     const std::string& iFullKeyStr,
                                     const ClassCode_T&);

    
    /**
     * Retrieve an AirportPair object from an AirportPair structure.
     *
     * @param const BomRoot& The root of the BOM tree.
     * @param const AirportCode_T& Origin, part of the key.
     * @param const AirportCode_T& Destination, part of the key.
     * @return AirportPair* The just retrieved AirportPair object.
     */
    static AirportPair*
    retrieveAirportPairFromKeySet (const BomRoot& ,
                                   const stdair::AirportCode_T&,
                                   const stdair::AirportCode_T&);

    /**
     * Retrieve a list of date-period corresponding to a flight
     * date.
     *
     * @param const AirportPair& The root of the BOM tree.
     * @param const Date_T& Departure Date of the flight
     * @param stdair::DatePeriodList_T& List of DatePeriod to
     *                                  display.
     */ 
    static void
    retrieveDatePeriodListFromKey (const AirportPair&,
                                    const stdair::Date_T&,
                                    stdair::DatePeriodList_T&);

     /**
     * Retrieve a list of date-period from a set of keys.
     *
     * @param const BomRoot& The root of the BOM tree.
     * @param const AirportCode_T& Part of the AirportPair key:
     *                             the origin airport
     * @param const AirportCode_T& Part of the AirportPair key:
     *                             the destination airport.
     * @param const Date_T& Departure date of the flight
     * @param stdair::DatePeriodList_T& List of DatePeriod to
     *                                  display.
     */
    static void
    retrieveDatePeriodListFromKeySet (const BomRoot&,
                                      const stdair::AirportCode_T&,
                                      const stdair::AirportCode_T&,
                                      const stdair::Date_T&,
                                      stdair::DatePeriodList_T&);

    /**
     * Retrieve one sample leg-cabin of the dummy inventory of "XX".
     *
     * @param stdair::BomRoot& The BOM tree.
     * @param const bool Boolean to choose the sample leg-cabin.
     *                   True:  the dummy leg-cabin with fare families.
     *                   False: the dummy leg-cabin without fare families.
     *                   By default the value is false.
     */
    static stdair::LegCabin& 
    retrieveDummyLegCabin (stdair::BomRoot&,
                           const bool isForFareFamilies = false);

    /**
     * Retrieve one sample segment-cabin of the dummy inventory of "XX".
     *
     * @param stdair::BomRoot& The BOM tree.
     * @param const bool Boolean to choose the sample segment-cabin.
     *                   True:  the dummy segment-cabin with fare families.
     *                   False: the dummy segment-cabin without fare families.
     *                   By default the value is false.
     */
    static stdair::SegmentCabin& 
    retrieveDummySegmentCabin (stdair::BomRoot&,
                               const bool isForFareFamilies = false);

  };
  
}
#endif // __STDAIR_BOM_BOMRETRIEVER_HPP
