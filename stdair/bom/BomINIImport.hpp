#ifndef __STDAIR_BOM_BOMINIIMPORT_HPP
#define __STDAIR_BOM_BOMINIIMPORT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_file.hpp>


namespace stdair {  

  /// Forward declarations  
  struct ConfigHolderStruct; 

  /**
   * @brief Utility class to import StdAir objects in a INI format.
   */
  class BomINIImport {
  public:
    // //////////////// Import support methods /////////////////
    /**
     * Extract a boost property tree from an INI config file.
     * @param ConfigHolderStruct& Holder of the configuration tree.
     * @param const ConfigINIFile& INI config file.
     */
    static void importINIConfig (ConfigHolderStruct&,
				 const ConfigINIFile&);
    
  };
}
#endif // __STDAIR_BOM_BOMINIIMPORT_HPP
