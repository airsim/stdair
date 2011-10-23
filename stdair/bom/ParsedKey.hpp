#ifndef __STDAIR_BOM_PARSEDKEY_HPP
#define __STDAIR_BOM_PARSEDKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

namespace stdair {
  /// Forward declarations
  struct InventoryKey;
  struct FlightDateKey;
  struct SegmentDateKey;

  /** Structure which holds the results/keys after the parsing. */
  struct ParsedKey : public KeyAbstract{

    // //////////// Getter //////////////
    /** Inventory key. */
    InventoryKey getInventoryKey () const;

    /** Flight-date key. */
    FlightDateKey getFlightDateKey () const;

    /** Segment-date key. */
    SegmentDateKey getSegmentKey () const;

    /** Boarding time. */
    const Duration_T getBoardingTime () const;

  public:
    // /////////// Display support methods /////////
    /**
     * Dump a Business Object Key into an output stream.
     *
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;
    
    /**
     * Read a Business Object Key from an input stream.
     *
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn);
      
    /**
     * Get the serialised version of the Business Object Key.
     *
     * That string is unique, at the level of a given Business Object,
     * when among children of a given parent Business Object.
     *
     * For instance, "H" and "K" allow to differentiate among two
     * marketing classes for the same segment-date.
     */
    const std::string toString() const;

  public:
    // ////////////// Constructor and destructor. //////////////
    // Default constructor
    ParsedKey ();
    // Defaut destructor
    ~ParsedKey ();

  public:
    // ///////////// Attributes ///////////////
    std::string _fullKey;
    std::string _airlineCode;
    std::string _flightNumber;
    std::string _departureDate;
    std::string _boardingPoint;
    std::string _offPoint;
    std::string _boardingTime;
  };
  
}
#endif // __STDAIR_BOM_PARSEDKEY_HPP
