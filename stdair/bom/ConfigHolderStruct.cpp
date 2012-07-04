// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#if BOOST_VERSION >= 104100
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#endif // BOOST_VERSION >= 104100
// StdAir
#include <stdair/bom/ConfigHolderStruct.hpp>

namespace stdair {
  
  // ////////////////////////////////////////////////////////////////////
  ConfigHolderStruct::ConfigHolderStruct() {
  }
    
  // ////////////////////////////////////////////////////////////////////
  ConfigHolderStruct::
  ConfigHolderStruct (const ConfigHolderStruct& iConfigHolderStruct)
    : _pt (iConfigHolderStruct._pt) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  ConfigHolderStruct::~ConfigHolderStruct() {
  }

  // ////////////////////////////////////////////////////////////////////
  void ConfigHolderStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void ConfigHolderStruct::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string ConfigHolderStruct::describe() const {
    std::ostringstream oStr;
    return oStr.str();
  }  

  // ////////////////////////////////////////////////////////////////////
  void ConfigHolderStruct::add (const bpt::ptree& iConfigPropertyTree) {
    // Call the dedicated recursive method with an empty path in order to merge
    // the config property tree with the given new one.
    std::string lEmptyPath ("");	
    add (iConfigPropertyTree, lEmptyPath);
  }

  // ////////////////////////////////////////////////////////////////////
  void ConfigHolderStruct::add (const bpt::ptree& iConfigPropertyTree,
				const std::string& iPath) {

    // Are there any more children to browse?
    bool isThereAnyChild = false;

#if BOOST_VERSION >= 104100

    // Browse the children nodes
    BOOST_FOREACH(bpt::ptree::value_type itChild, iConfigPropertyTree) {

      isThereAnyChild = true;

      // Build the current path
      std::ostringstream lCurrentPathStr;
      const bool isPathEmptyForNow = iPath.empty();
      if (isPathEmptyForNow == false) { 
	lCurrentPathStr << iPath << ".";
      }
      // Add the current node name
      lCurrentPathStr << itChild.first.data(); 
      const std::string lCurrentPath (lCurrentPathStr.str()); 
      
      // Get the child tree
      const bpt::ptree& lChildTree = itChild.second;   
      add(lChildTree, lCurrentPath);
    }

    // If there is no child for this node, create the specified path and add 
    // the correponding value
    if (isThereAnyChild == false) {
      std::string lValue (iConfigPropertyTree.data());
      addValue(iPath, lValue);
    } 
#endif // BOOST_VERSION >= 104100
  }

  // ////////////////////////////////////////////////////////////////////
  void ConfigHolderStruct::addValue (const std::string& iValue,
				     const std::string& iPath) {
    // Create the given specified path and add the corresponding given value,
    // or replace the value if the path already exists. 
#if BOOST_VERSION >= 104100
    _pt.put(iPath, iValue);
#endif // BOOST_VERSION >= 104100
  }

}
