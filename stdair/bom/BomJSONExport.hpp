#ifndef __STDAIR_BOM_BOMJSONEXPORT_HPP
#define __STDAIR_BOM_BOMJSONEXPORT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>

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
  };

}
#endif // __STDAIR_BOM_BOMJSONEXPORT_HPP
