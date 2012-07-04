// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#if BOOST_VERSION >= 104100
// Boost Property Tree
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#endif // BOOST_VERSION >= 104100
// StdAir
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/BomINIImport.hpp>
#include <stdair/bom/ConfigHolderStruct.hpp>

#if BOOST_VERSION >= 104100
namespace bpt = boost::property_tree;
#else // BOOST_VERSION >= 104100
namespace bpt {
  typedef char ptree;
}
#endif // BOOST_VERSION >= 104100

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  void BomINIImport::importINIConfig (ConfigHolderStruct& iConfigHolder,
				      const ConfigINIFile& iConfigINIFile) {

    // Get the config file name.
    const stdair::Filename_T lFilename = iConfigINIFile.name();

    // Check that the file path given as input corresponds to an actual file
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (lFilename);
    if (doesExistAndIsReadable == false) {
      return;
    }
    
#if BOOST_VERSION >= 104100

    // Transform the INI file into a BOOST property tree.
    bpt::ptree pt;
    bpt::ini_parser::read_ini(lFilename, pt); 
    // Add the property tree to the configuration structure.
    iConfigHolder.add(pt);

#endif // BOOST_VERSION >= 104100  
  }
  
}
