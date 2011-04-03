#ifndef __STDAIR_CMD_CMDBOMSERIALISER_HPP
#define __STDAIR_CMD_CMDBOMSERIALISER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>
#include <stdair/command/CmdAbstract.hpp>

namespace stdair {

  /// Forward declarations
  class BomRoot;
  struct BookingRequestStruct;


  /**
   * Class wrapping utility functions for handling the BOM tree
   * objects.
   */
  class CmdBomSerialiser : public CmdAbstract {
  public:

    // //////////////// BOM serialisation support methods /////////////////
    //
  };
}
#endif // ___STDAIR_CMD_CMDBOMSERIALISER_HPP
