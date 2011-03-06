#ifndef __STDAIR_BOM_BOMDISPLAY_HPP
#define __STDAIR_BOM_BOMDISPLAY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>

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
  struct BookingRequestStruct;

  /**
   * @brief Utility class to display TraDemGen objects with a pretty
   * format.
   */
  class BomDisplay {
  public:
    // //////////////// Display support methods /////////////////
    /**
     * Helper fuction to display an interger.
     */
    static void intDisplay (std::ostream&, const int&);

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
     * Recursively display (dump in the underlying output log stream)
     * the segment-class level objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be displayed.
     */
    static void csvBookingClassDisplay (std::ostream&, const FlightDate&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the given BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const BookingRequestStruct& Root of the BOM tree to be displayed.
     */
    static void csvDisplay (std::ostream&, const BookingRequestStruct&);
  };
  
}
#endif // __STDAIR_BOM_BOMDISPLAY_HPP
