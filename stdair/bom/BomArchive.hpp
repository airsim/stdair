#ifndef __STDAIR_BOM_BOMARCHIVE_HPP
#define __STDAIR_BOM_BOMARCHIVE_HPP

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
   * @brief Utility class to archive/restore BOM objects with Boost
   * serialisation.
   */
  class BomArchive {
  public:
    /**
     * Recursively archive (dump in the underlying STL string)
     * the objects of the BOM tree.
     *
     * @param const BomRoot& Root of the BOM tree to be archived.
     */
    static void archive (const BomRoot&);

    /**
     * Recursively archive (dump in the underlying STL string)
     * the objects of the BOM tree.
     *
     * @param const Inventory& Root of the BOM tree to be archived.
     */
    static std::string archive (const Inventory&);

    /**
     * Recursively restore (from the underlying STL string)
     * the objects of the BOM tree.
     *
     * @param const std::string& String holding the serialised objects.
     * @param Inventory& Root of the BOM tree to be restored.
     */
    static void restore (const std::string& iArchive, Inventory&);

    /**
     * Recursively archive (dump in the underlying STL string)
     * the objects of the BOM tree.
     *
     * @param const FlightDate& Root of the BOM tree to be archived.
     */
    static void archive (const FlightDate&);
  };
  
}
#endif // __STDAIR_BOM_BOMARCHIVE_HPP
