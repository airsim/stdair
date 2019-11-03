// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#if BOOST_VERSION_MACRO >= 104100
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace bpt = boost::property_tree;
#endif // BOOST_VERSION_MACRO >= 104100
#include <boost/foreach.hpp>
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
    oStr << "Configuration Display:" << std::endl;

    // Look for the start and end date values.
    stdair::Date_T lStartDate;
    const bool hasStartDateBeenRetrieved = 
      exportValue<Date_T> (lStartDate, "date.start"); 
    if (hasStartDateBeenRetrieved == true) {
      oStr << "  Start date: " << lStartDate << std::endl;
    }
    stdair::Date_T lEndDate;
    const bool hasEndDateBeenRetrieved = 
      exportValue<Date_T> (lEndDate, "date.end");
    if (hasEndDateBeenRetrieved == true) {
      oStr << "  End date: " << lEndDate << std::endl;
    }
    
    // Look for the random seed value.
    RandomSeed_T lRandomSeed;
    const bool hasSeedBeenRetrieved = 
      exportValue<RandomSeed_T> (lRandomSeed, "random.seed");
    if (hasSeedBeenRetrieved == true) {
      oStr << "  Random Seed: " << lRandomSeed << std::endl;
    }

    // Look for the demand generation method.
    char lChar;
    const bool hasDemandGenMethodBeenRetrieved = 
      exportValue<char> (lChar, "demand generation.method"); 
    if (hasDemandGenMethodBeenRetrieved == true) {
      oStr << "  Demand Generation method: " << lChar << std::endl;
    }
   
    // Look for the number of runs value.
    Count_T lTotalNumberOfRuns;
    const bool hasNumberOfRunsBeenRetrieved = 
      exportValue<Count_T> (lTotalNumberOfRuns, "runs.number");
    if (hasNumberOfRunsBeenRetrieved == true) {
      oStr << "  Number Of Runs: " << lTotalNumberOfRuns << std::endl;
    }
    
    // Look for the input files.
    stdair::Filename_T lFilename (""); 
    const bool hasScheduleFileBeenRetrieved = 
      exportValue<stdair::Filename_T> (lFilename, "input.schedule"); 
    if (hasScheduleFileBeenRetrieved == true) {
      oStr << "  Schedule input file: " << lFilename << std::endl;
    }
    const bool hasODFileBeenRetrieved = 
      exportValue<stdair::Filename_T> (lFilename, "input.ond");  
    if (hasODFileBeenRetrieved == true) {
      oStr << "  OnD input file: " << lFilename << std::endl;
    }     
    const bool hasFrat5FileBeenRetrieved = 
      exportValue<stdair::Filename_T> (lFilename, "input.frat5");  
    if (hasFrat5FileBeenRetrieved == true) {
      oStr << "  Frat5 input file: " << lFilename << std::endl;
    }
    const bool hasFFdisutilityFileBeenRetrieved = 
      exportValue<stdair::Filename_T> (lFilename, "input.ffdisutility");  
    if (hasFFdisutilityFileBeenRetrieved == true) {
      oStr << "  FFdisutility input file: " << lFilename << std::endl;
    }
    const bool hasYieldFileBeenRetrieved = 
      exportValue<stdair::Filename_T> (lFilename, "input.yield");  
    if (hasYieldFileBeenRetrieved == true) {
      oStr << "  Yield input file: " << lFilename << std::endl;
    }
    const bool hasFareFileBeenRetrieved = 
      exportValue<stdair::Filename_T> (lFilename, "input.fare");  
    if (hasFareFileBeenRetrieved == true) {
      oStr << "  Fare input file: " << lFilename << std::endl;
    }
    const bool hasDemandFileBeenRetrieved = 
      exportValue<stdair::Filename_T> (lFilename, "input.demand");  
    if  (hasDemandFileBeenRetrieved == true) {
      oStr << "  Demand input file: " << lFilename << std::endl;
    }
    
    return oStr.str();
  } 
 
  // ////////////////////////////////////////////////////////////////////
  const std::string ConfigHolderStruct::jsonExport() const {    
    std::ostringstream oStr; 
#if BOOST_VERSION_MACRO >= 104100
    // Write the property tree into the JSON stream.
    write_json (oStr, _pt);
#endif // BOOST_VERSION_MACRO >= 104100
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

#if BOOST_VERSION_MACRO >= 104100

    // Browse the children nodes
    BOOST_FOREACH(boost::property_tree::ptree::value_type itChild, iConfigPropertyTree) {

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
#endif // BOOST_VERSION_MACRO >= 104100
  }

  // ////////////////////////////////////////////////////////////////////
  bool ConfigHolderStruct::addValue (const std::string& iValue,
				     const std::string& iPath) {  
    bool hasInsertionBeenSuccessful = true;
    // Create the given specified path and add the corresponding given value,
    // or replace the value if the path already exists. 
#if BOOST_VERSION_MACRO >= 104100

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
#endif // BOOST_VERSION_MACRO >= 104100

    return hasInsertionBeenSuccessful;
  } 

  // ////////////////////////////////////////////////////////////////////
  void ConfigHolderStruct::updateAirlineFeatures (BomRoot& iBomRoot) {  

#if BOOST_VERSION_MACRO >= 104100
    AirlineCode_T lAirlineCode ("");

    // Browse the children nodes
    BOOST_FOREACH(boost::property_tree::ptree::value_type itChild, _pt) { 
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
#endif // BOOST_VERSION_MACRO >= 104100
  }
}

