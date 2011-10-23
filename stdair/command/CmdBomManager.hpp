#ifndef __STDAIR_CMD_CMDBOMMANAGER_HPP
#define __STDAIR_CMD_CMDBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/command/CmdAbstract.hpp>

namespace stdair {

  // Forward declarations
  class BomRoot;


  /**
   * Class wrapping utility functions for handling the BOM tree
   * objects.
   */
  class CmdBomManager : public CmdAbstract {
  public:

    // //////////////// BOM initialisation support methods /////////////////
    /**
     * Build a sample BOM tree, and attach it to the given reference.
     *
     * As for now, two inventories (one for BA, another for AF) are
     * built, each containing one flight. One of those flights has two
     * legs (and therefore three segments).
     *     
     * @param BomRoot& Top of the BOM tree, to which the sample should
     *        be attached.
     */
    static void buildSampleBom (BomRoot&);

    /** Build a sample bom tree for RMOL. */
    static void buildSampleBomForRMOL (BomRoot&, const CabinCapacity_T&);

  };
}
#endif // ___STDAIR_CMD_CMDBOMMANAGER_HPP
