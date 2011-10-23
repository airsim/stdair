#ifndef __STDAIR_BOM_BOMDISPLAY_HPP
#define __STDAIR_BOM_BOMDISPLAY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/bom/TravelSolutionTypes.hpp>

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
   * @brief Utility class to display TraDemGen objects with a pretty
   * format.
   */
  class BomDisplay {
  public:
    // //////////////// Display support methods /////////////////
    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const BomRoot& Root of the BOM tree to be displayed.
     */
    static void csvDisplay (std::ostream&, const BomRoot&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree from the level of the given Inventory.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const Inventory& Root of the BOM tree to be displayed.
     */
    static void csvDisplay (std::ostream&, const Inventory&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree from the level of the given FlightDate.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be displayed.
     */
    static void csvDisplay (std::ostream&, const FlightDate&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the leg-date level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be displayed.
     */
    static void csvLegDateDisplay (std::ostream&, const FlightDate&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the segment-date level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be displayed.
     */
    static void csvSegmentDateDisplay (std::ostream&, const FlightDate&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the leg-cabin level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be displayed.
     */
    static void csvLegCabinDisplay (std::ostream&, const FlightDate&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the segment-cabin level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be displayed.
     */
    static void csvSegmentCabinDisplay (std::ostream&, const FlightDate&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the fare families level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be displayed.
     */
    static void csvFareFamilyDisplay (std::ostream&, const FlightDate&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the bucket holder level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be displayed.
     */
    static void csvBucketDisplay (std::ostream&, const FlightDate&);

    /**
     * Display (dump in the underlying output log stream) the segment-class,
     * without going recursively deeper in the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const BookingClass& Root of the BOM tree to be displayed.
     * @param const std::string& Leading string to be displayed.
     */
    static void csvBookingClassDisplay (std::ostream&, const BookingClass&,
                                        const std::string& iLeadingString);
    /**
     * Recursively display (dump in the underlying output log stream)
     * the segment-class level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be displayed.
     */
    static void csvBookingClassDisplay (std::ostream&, const FlightDate&);

    /**
     * Display (dump in the returned string) the full list of travel
     * solution structures.
     *
     * @return std::string Output string in which the list of travel
     *        solutions is logged/dumped.
     */
    static void csvDisplay (std::ostream&, const TravelSolutionList_T&);
  };
  
}
#endif // __STDAIR_BOM_BOMDISPLAY_HPP
