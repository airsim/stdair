#ifndef __STDAIR_BOM_BOMJSONEXPORT_HPP
#define __STDAIR_BOM_BOMJSONEXPORT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// Boost Property Tree
#if BOOST_VERSION >= 104100
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#endif // BOOST_VERSION >= 104100
// StdAir
#include <stdair/bom/TravelSolutionTypes.hpp>

#if BOOST_VERSION >= 104100
  namespace bpt = boost::property_tree;
#else // BOOST_VERSION >= 104100
  namespace bpt {
    typedef char ptree;
  }
#endif // BOOST_VERSION >= 104100

namespace stdair {

  /// Forward declarations  
  class BomRoot; 
  class Inventory;
  class FlightDate; 
  class LegDate;
  class LegCabin; 
  class SegmentDate;
  class SegmentCabin;
  class BookingClass; 
  class EventQueue;

  /**
   * @brief Utility class to export StdAir objects in a JSON format.
   */
  
  class BomJSONExport {
  public:
    // //////////////// Export support methods /////////////////   

    /**
     * Export (dump in the underlying output log stream 
     * and in JSON format) a list of flight date objects.
     *
     * @param std::ostream& Output stream in which the flight date 
     *        objects should be logged/dumped.
     * @param const BomRoot& Root of the BOM tree containing flight-dates
     *        to be exported.      
     * @param const AirlineCode& Airline for which the flight-dates should be
     *        displayed. If set to "all" (default), all the inventories will
     *        be displayed.
     * @param const FlightNumber_T& Flight number for which all the departure
     *        dates should be displayed. If set to 0 (the default),
     *        all the flight numbers will be displayed.
     */
    static void jsonExportFlightDateList (std::ostream&, const BomRoot&,
					  const AirlineCode_T& iAirlineCode = "all",
					  const FlightNumber_T& iFlightNumber = 0);

    /**
     * Recursively export (dump in the underlying output log stream
     * and in JSON format) the objects of the BOM tree using the given 
     * FlightDate as root.
     *
     * @param std::ostream& Output stream in which the BOM tree should be
     *        logged/dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.   
     */
    static void jsonExportFlightDateObjects (std::ostream&, const FlightDate&); 

    /**
     * Export (dump in the underlying output log stream and in JSON format) 
     * the booking request objects stored into the event queue.
     *
     * @param std::ostream& Output stream in which the events should be
     *        logged/dumped.
     * @param const EventQueue& Queue in which the events are stored.
     */
    static void jsonExportBookingRequestObjects (std::ostream&, 
						 const EventQueue&);

  private:

    /**
     * Export (dump in the property tree) all the flight date objects 
     * corresponding to the given inventory and to the given flight number.
     *
     * @param bpt::ptree& Output tree in which the flight date 
     *        objects should be dumped.
     * @param const Inventory& Root of the BOM tree to be exported.      
     * @param const FlightNumber_T& Flight number for which all the departure
     *        dates should be displayed. If set to 0 all the flight numbers 
     *        will be displayed.
     */
    static void jsonExportFlightDate (bpt::ptree&,
				      const Inventory&,
				      const FlightNumber_T&); 

    /**
     * Export (dump in the property tree) all the objects of the BOM 
     * tree derivating from a leg date (including the leg date ones).
     *
     * @param bpt::ptree& Output tree in which the objects should be 
     *        dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonExportLegDate (bpt::ptree&, const FlightDate&);
     
    /**
     * Export (dump in the property tree) the objects of the BOM tree 
     * using the given leg date as root.
     *
     * @param bpt::ptree& Output tree in which the objects should be 
     *        dumped.
     * @param const LegDate& Root of the BOM tree to be exported.
     */
    static void jsonExportLegCabin (bpt::ptree&, const LegDate&);
 
    /**
     * Export (dump in the property tree) the objects of the BOM tree 
     * using the given leg cabin as root.
     *
     * @param bpt::ptree& Output tree in which the objects should be 
     *        dumped.
     * @param const LegCabin& Root of the BOM tree to be exported.
     */
    static void jsonExportBucket (bpt::ptree&, const LegCabin&);
  
    /**
     * Export (dump in the property tree) all the objects of the BOM 
     * tree derivating from a segment date (including the segment
     * date ones).
     *
     * @param bpt::ptree& Output tree in which the objects should be 
     *        dumped.
     * @param const FlightDate& Root of the BOM tree to be exported.
     */
    static void jsonExportSegmentDate (bpt::ptree&, const FlightDate&);

    /**
     * Export (dump in the property tree) all the objects of the BOM 
     * tree derivating from a segment date.
     *
     * @param bpt::ptree& Output tree in which the objects should be 
     *        dumped.
     * @param const SegmentDate& Root of the BOM tree to be exported.
     */
    static void jsonExportSegmentCabin (bpt::ptree&, const SegmentDate&);
 
    /**
     * Export (dump in the property tree) all the objects of the BOM 
     * tree derivating from a segment cabin.
     * Remark: those objects can be fare familie objects plus booking 
     * class objects or directly booking class objects if there are 
     * not a fare-family level in the BOM tree.
     *
     * @param bpt::ptree& Output tree in which the objects should be 
     *        dumped.
     * @param bpt::ptree& Input tree containing the segment cabin name.
     * @param const SegmentCabin& Root of the BOM tree to be exported.
     */
    static void jsonExportFareFamily (bpt::ptree&, bpt::ptree&, 
				      const SegmentCabin&);

    /**
     * Export (dump in the property tree) the given booking class.
     *
     * @param bpt::ptree& Output tree in which the objects should be 
     *        dumped.
     * @param bpt::ptree& Input tree containing the segment cabin name 
     *        and the fare family code (if there is a fare family) 
     * @param const BookingClass& Booking class to be exported
     */
    static void jsonExportBookingClass (bpt::ptree&, bpt::ptree&, 
					const BookingClass&);
    
  };

}
#endif // __STDAIR_BOM_BOMJSONEXPORT_HPP
