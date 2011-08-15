#ifndef __STDAIR_BOM_BOMDISPLAY_HPP
#define __STDAIR_BOM_BOMDISPLAY_HPP

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
  class EventQueue;
  class Inventory;
  class FlightDate;
  class LegDate;
  class SegmentDate;
  class LegCabin;
  class SegmentCabin;
  class FareFamily;
  class BookingClass;
  class AirportPair;
  class PosChannel;
  class DatePeriod;
  class TimePeriod;
  class FareFeatures;
  class YieldFeatures;
  class AirlineClassList;

  /**
   * @brief Utility class to display StdAir objects with a pretty
   * format.
   */
  class BomDisplay {
  public:
    // //////////////// Display support methods /////////////////
    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree.
     *
     * @param const stdair::EventQueue& Root of the BOM tree to be displayed.
     * @return std::string Output string in which the BOM tree should be
     *        logged/dumped.
     */
    static std::string csvDisplay (const EventQueue&);

    /**
     * Display (dump in the underlying output log stream) the list of
     * flight-dates contained within the given BOM tree.
     *
     * @param std::ostream& Output stream in which the flight-date keys
     *        should be logged/dumped.
     * @param const BomRoot& Root of the BOM tree to be displayed.
     * @param const AirlineCode& Airline for which the flight-dates should be
     *        displayed. If set to "all" (default), all the inventories will
     *        be displayed.
     * @param const FlightNumber_T& Flight number for which all the departure
     *        dates should be displayed. If set to 0 (the default),
     *        all the flight numbers will be displayed.
     */
    static void list (std::ostream&, const BomRoot&,
                      const AirlineCode_T& iAirlineCode = "all",
                      const FlightNumber_T& iFlightNumber = 0);

    /**
     * Display (dump in the underlying output log stream) the list of
     * flight-dates contained within the given BOM tree.
     *
     * @param std::ostream& Output stream in which the flight-date keys
     *        should be logged/dumped.
     * @param const Inventory& Root of the BOM tree to be displayed.
     * @param const unsigned short Index, within the list, of the inventory.
     *        It is 0 when that inventory is displayed alone.
     * @param const FlightNumber_T& Flight number for which all the departure
     *        dates should be displayed. If set to 0 (the default),
     *        all the flight numbers will be displayed.
     */
    static void list (std::ostream&, const Inventory&,
                      const unsigned short iInventoryIndex = 0,
                      const FlightNumber_T& iFlightNumber = 0);

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
     * Display (dump in the underlying output log stream) the full list of
     * travel solution structures.
     *
     * @param std::ostream& Output stream in which the list of travel
     *        solutions is logged/dumped.
     * @param TravelSolutionList_T& List of travel solutions to display.
     */
    static void csvDisplay (std::ostream&, const TravelSolutionList_T&);

    /**
     * Display (dump in the underlying output log stream) the full list of
     * date period fare rule sub bom tree.
     *
     * @param std::ostream& Output stream in which the list of travel
     *        solutions is logged/dumped.
     * @param DatePeriodList_T& List of date period to display.
     */
    static void csvDisplay (std::ostream&, const DatePeriodList_T&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const BomRoot& Root of the BOM tree to be displayed.
     */
    static void csvSimFQTAirRACDisplay (std::ostream&, const BomRoot&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree from the level of the given airport
     * pair.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const AirportPair& Root of the BOM tree to be displayed.
     */
    static void csvAirportPairDisplay (std::ostream&, const AirportPair&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree from the level of the given date
     * range.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const DatePeriod& Root of the BOM tree to be displayed.
     */
    static void csvDateDisplay (std::ostream&, const DatePeriod&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree from the level of the given point of
     * sale channel.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const PosChannel& Root of the BOM tree to be displayed.
     */
    static void csvPosChannelDisplay (std::ostream&, const PosChannel&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the objects of the BOM tree from the level of the given time
     * range.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const TimePeriod& Root of the BOM tree to be displayed.
     */
    static void csvTimeDisplay (std::ostream&, const TimePeriod&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the list of fare/yield features objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const TimePeriod& Root of the BOM tree to be displayed.
     */
    template <typename FEATURE_TYPE>
    static void csvFeatureListDisplay (std::ostream& oStream, const TimePeriod&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the fare/yield features objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FEATURE_TYPE& Root of the BOM tree to be displayed.
     */
    template <typename FEATURE_TYPE>
    static void csvFeaturesDisplay (std::ostream& oStream, const FEATURE_TYPE&);

    /**
     * Recursively display (dump in the underlying output log stream)
     * the airline class objects of the BOM tree.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const AirlineClassList& Root of the BOM tree to be displayed.
     */
    static void csvAirlineClassDisplay (std::ostream&, const AirlineClassList&);
  };
  
}
#endif // __STDAIR_BOM_BOMDISPLAY_HPP
