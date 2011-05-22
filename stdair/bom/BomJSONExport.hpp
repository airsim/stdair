#ifndef __STDAIR_BOM_BOMJSONEXPORT_HPP
#define __STDAIR_BOM_BOMJSONEXPORT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/bom/TravelSolutionTypes.hpp>
#include <stdair/bom/DatePeriodTypes.hpp>

namespace stdair {

  /// Forward declarations
  class BomRoot;
  class Inventory;
  class FlightDate;
  class LegDate;
  class SegmentDate;
  class LegCabin;
  class SegmentCabin;
  class FareFamily;
  class BookingClass;

  /**
   * @brief Utility class to export StdAir objects in a JSON format.
   */
  class BomJSONExport {
  public:
    // //////////////// Export support methods /////////////////
    /**
     * Recursively export (dump in the underlying output log stream)
     * the objects of the BOM tree from the level of the given FlightDate.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonExport (std::ostream&, const FlightDate&);

    /**
     * Recursively export (dump in the underlying output log stream)
     * the leg-date level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonLegDateExport (std::ostream&, const FlightDate&);

    /**
     * Recursively export (dump in the underlying output log stream)
     * the segment-date level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonSegmentDateExport (std::ostream&, const FlightDate&);

    /**
     * Recursively export (dump in the underlying output log stream)
     * the leg-cabin level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonLegCabinExport (std::ostream&, const FlightDate&);

    /**
     * Recursively export (dump in the underlying output log stream)
     * the segment-cabin level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonSegmentCabinExport (std::ostream&, const FlightDate&);

    /**
     * Recursively export (dump in the underlying output log stream)
     * the fare families level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonFareFamilyExport (std::ostream&, const FlightDate&);

    /**
     * Recursively export (dump in the underlying output log stream)
     * the bucket holder level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonBucketExport (std::ostream&, const FlightDate&);

    /**
     * Export (dump in the underlying output log stream) the segment-class,
     * without going recursively deeper in the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const BookingClass& Root of the BOM tree to be exported.
     * @param const std::string& Leading string to be exported.
     */
    static void jsonBookingClassExport (std::ostream&, const BookingClass&,
                                        const std::string& iLeadingString);

    /**
     * Recursively export (dump in the underlying output log stream)
     * the segment-class level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonBookingClassExport (std::ostream&, const FlightDate&);

  };

}
#endif // __STDAIR_BOM_BOMJSONEXPORT_HPP
