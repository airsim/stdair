#ifndef __STDAIR_BOM_BOMKEYMANAGER_HPP
#define __STDAIR_BOM_BOMKEYMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_basic_types.hpp>

namespace stdair {

  /// Forward declarations
  struct BomRootKey;
  struct InventoryKey;
  struct FlightDateKey;
  struct LegDateKey;
  struct SegmentDateKey;
  struct LegCabinKey;
  struct SegmentCabinKey;
  struct FareFamilyKey;
  struct BookingClassKey;
  struct ParsedKey;

  /**
   * @brief Utility class to extract key structures from strings.
   */
  class BomKeyManager {
  public:
    // //////////////// Key management support methods /////////////////
    /**
     * Build a ParsedKey structure from a full key string which includes
     * an inventory key, flight-date key elements, segment-date key elements.
     */
    static ParsedKey extractKeys (const std::string& iFullKeyStr);
    
    /**
     * Build a InventoryKey structure from a (full) key string.
     *
     * The full key string gathers airline code, flight number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const std::string& The full key string.
     * @return InventoryKey The just built InventoryKey structure.
     */
    static InventoryKey extractInventoryKey (const std::string& iFullKeyStr);

    /**
     * Build a FlightDateKey structure from a (full) key string.
     *
     * The full key string gathers airline code, flight number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const std::string& The full key string.
     * @return FlightDateKey The just built FlightDateKey structure.
     */
    static FlightDateKey extractFlightDateKey (const std::string& iFullKeyStr);

    /**
     * Build a SegmentDateKey structure from a (full) key string.
     *
     * The full key string gathers airline code, flight number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const std::string& The full key string.
     * @return SegmentDateKey The just built SegmentDateKey structure.
     */
    static SegmentDateKey extractSegmentDateKey (const std::string& iFullKeyStr);  

    /**
     * Build a LegDateKey structure from a (full) key string.
     *
     * The full key string gathers airline code, flight number, origin
     * and destination, cabin and booking class. It corresponds to the
     * output generated by the toString() methods of the XxxKey
     * structures.
     *
     * @param const std::string& The full key string.
     * @return LegDateKey The just built LegDateKey structure.
     */
    static LegDateKey extractLegDateKey (const std::string& iFullKeyStr);

  };
  
}
#endif // __STDAIR_BOM_BOMKEYMANAGER_HPP
