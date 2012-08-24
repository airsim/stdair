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
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/ForecastingMethod.hpp>
#include <stdair/basic/UnconstrainingMethod.hpp>
#include <stdair/basic/PartnershipTechnique.hpp>
#include <stdair/basic/PreOptimisationMethod.hpp>
#include <stdair/basic/OptimisationMethod.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/ConfigHolderStruct.hpp>
#include <stdair/bom/BomRetriever.hpp>
#include <stdair/service/Logger.hpp>

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
  const std::string ConfigHolderStruct::jsonExport() const {    
    std::ostringstream oStr; 
#if BOOST_VERSION >= 104100
    // Write the property tree into the JSON stream.
    write_json (oStr, _pt);
#endif // BOOST_VERSION >= 104100
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
      const bool hasInsertionBeenSuccessful = addValue (lValue, iPath);
      assert (hasInsertionBeenSuccessful == true);   
    } 
#endif // BOOST_VERSION >= 104100
  }

  // ////////////////////////////////////////////////////////////////////
  bool ConfigHolderStruct::addValue (const std::string& iValue,
				     const std::string& iPath) {  
    bool hasInsertionBeenSuccessful = true;
    // Create the given specified path and add the corresponding given value,
    // or replace the value if the path already exists. 
#if BOOST_VERSION >= 104100

    try {
      std::size_t found;
      const std::string lPrefix ("config");
      std::string lFinalPath;
      found = iPath.find(lPrefix);
      if (found == std::string::npos) {
        lFinalPath += lPrefix;
        lFinalPath += ".";
      }
      lFinalPath += iPath;
      if (lFinalPath != lPrefix) {
        _pt.put (lFinalPath, iValue);
      }
    } catch (bpt::ptree_bad_data& bptException) {
      hasInsertionBeenSuccessful = false;
    }
#endif // BOOST_VERSION >= 104100

    return hasInsertionBeenSuccessful;
  } 

  // ////////////////////////////////////////////////////////////////////
  void ConfigHolderStruct::updateAirlineFeatures (BomRoot& iBomRoot) {  

    AirlineCode_T lAirlineCode ("");

    // Browse the children nodes
    BOOST_FOREACH(bpt::ptree::value_type itChild, _pt) { 
      std::ostringstream lPathStr;
      lPathStr << itChild.first.data() << ".airline_code";
      const bool hasAirlineCodeBeenRetrieved = 
	exportValue<AirlineCode_T> (lAirlineCode , lPathStr.str());
      if (hasAirlineCodeBeenRetrieved == true) {
	AirlineFeature* lAirlineFeature_ptr = 
	  BomRetriever::retrieveAirlineFeatureFromKey (iBomRoot, lAirlineCode);
	if (lAirlineFeature_ptr != NULL) { 

	  try {

	    std::ostringstream lPathStr;
	    char lChar;

	    // Try to extract the forecasting method from the config tree
	    lPathStr << itChild.first.data() << ".forecasting_method";
	    const bool hasForecastingMethodBeenRetrieved =    
	      exportValue<char> (lChar, lPathStr.str());	 
	    if (hasForecastingMethodBeenRetrieved == true) {
	      const ForecastingMethod lForecastingMethod (lChar);
	      lAirlineFeature_ptr->setForecastingMethod(lForecastingMethod);  
	    } 

	    // Try to extract the unconstraining method from the config tree
	    lPathStr.str("");  
	    lPathStr << itChild.first.data() << ".unconstraining_method"; 
	    const bool hasUnconstrainingMethodBeenRetrieved =    
	      exportValue<char> (lChar, lPathStr.str());
	    if (hasUnconstrainingMethodBeenRetrieved == true) {
	      const UnconstrainingMethod lUnconstrainingMethod (lChar);
	      lAirlineFeature_ptr->setUnconstrainingMethod(lUnconstrainingMethod);  
	    } 

	    // Try to extract the partnership technique from the config tree 
	    lPathStr.str("");    
	    lPathStr << itChild.first.data() << ".partnership_technique"; 
	    const bool hasPartnershipTechniqueBeenRetrieved =    
	      exportValue<char> (lChar, lPathStr.str());
	    if (hasPartnershipTechniqueBeenRetrieved == true) {
	      const PartnershipTechnique lPartnershipTechnique (lChar);
	      lAirlineFeature_ptr->setPartnershipTechnique(lPartnershipTechnique);  
	    } 

	    // Try to extract the pre optimisation method from the config tree  
	    lPathStr.str("");
	    lPathStr << itChild.first.data() << ".pre_optimisation_method"; 
	    const bool hasPreOptMethodBeenRetrieved =    
	      exportValue<char> (lChar, lPathStr.str());
	    if (hasPreOptMethodBeenRetrieved == true) {
	      const PreOptimisationMethod lPreOptimisationMethod (lChar);
	      lAirlineFeature_ptr->setPreOptimisationMethod(lPreOptimisationMethod);  
	    } 

	    // Try to extract the optimisation method from the config tree   
	    lPathStr.str("");
	    lPathStr << itChild.first.data() << ".optimisation_method"; 
	    const bool hasOptMethodBeenRetrieved =    
	      exportValue<char> (lChar, lPathStr.str());
	    if (hasOptMethodBeenRetrieved == true) {
	      const OptimisationMethod lOptimisationMethod (lChar);
	      lAirlineFeature_ptr->setOptimisationMethod(lOptimisationMethod);  
	    }

	  } catch (CodeConversionException& lCodeConversionException) {
	    std::ostringstream oMessage;
	    oMessage << "Wrong input features for the airline '" 
		     << lAirlineCode << "' in the input configuration file: "
		     << lCodeConversionException.what();
	    STDAIR_LOG_ERROR (oMessage.str());
	    throw CodeConversionException (oMessage.str());
	  }
	}
      }
    }
  }
}
