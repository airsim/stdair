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
#include <stdair/bom/BookingClass.hpp>

#if BOOST_VERSION >= 104100
  namespace bpt = boost::property_tree;
#else // BOOST_VERSION >= 104100
  namespace bpt {
    typedef char ptree;
  }
#endif // BOOST_VERSION >= 104100

namespace stdair {

  /// Forward declarations
  class FlightDate;

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

  private:
    
    static void jsonLegDateExport (bpt::ptree&, const FlightDate&);
    
    static void jsonLegCabinExport (bpt::ptree&, const FlightDate&);

    static void jsonBucketExport (bpt::ptree&, const FlightDate&);

    static void jsonSegmentDateExport (bpt::ptree&, const FlightDate&);

    static void jsonSegmentCabinExport (bpt::ptree&, const FlightDate&);

    static void jsonFareFamilyExport (bpt::ptree&, const FlightDate&);
    
    static void jsonBookingClassExport (bpt::ptree&,
                                        const BookingClass&,
                                        const std::string&);

    static void jsonBookingClassExport (bpt::ptree&, const FlightDate&);
    
  };

}
#endif // __STDAIR_BOM_BOMJSONEXPORT_HPP
