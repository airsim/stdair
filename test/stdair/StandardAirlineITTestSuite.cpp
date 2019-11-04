/*!
 * \page StandardAirlineITTestSuite_cpp Command-Line Test to Demonstrate How To Extend StdAir BOM
 * \code
 */
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <fstream>
#include <string>
// Boost MPL
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
// Boost Unit Test Framework (UTF)
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE StdAirTest
#if BOOST_VERSION_MACRO >= 103900
#include <boost/test/unit_test.hpp>
#else  // BOOST_VERSION_MACRO >= 103900
#include <boost/test/test_tools.hpp>
#include <boost/test/results_reporter.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#endif // BOOST_VERSION_MACRO >= 103900
// Boost Serialisation
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <stdair/basic/float_utils.hpp>
#include <stdair/bom/BomDisplay.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/factory/FacBomManager.hpp>
// StdAir Test Suite
#include <test/stdair/StdairTestLib.hpp>
#include <test/stdair/MPInventory.hpp>

namespace boost_utf = boost::unit_test;

#if BOOST_VERSION_MACRO >= 103900

// (Boost) Unit Test XML Report
std::ofstream utfReportStream ("StandardAirlineITTestSuite_utfresults.xml");

/**
 * Configuration for the Boost Unit Test Framework (UTF)
 */
struct UnitTestConfig {
  /** Constructor. */
  UnitTestConfig() {
    boost_utf::unit_test_log.set_stream (utfReportStream);
#if BOOST_VERSION_MACRO >= 105900
    boost_utf::unit_test_log.set_format (boost_utf::OF_XML);
#else
    boost_utf::unit_test_log.set_format (boost_utf::XML);
#endif
    boost_utf::unit_test_log.set_threshold_level (boost_utf::log_test_units);
    // boost_utf::unit_test_log.set_threshold_level (boost_utf::log_successful_tests);
  }

  /** Destructor. */
  ~UnitTestConfig() {
  }
};


// /////////////// Main: Unit Test Suite //////////////

// Set the UTF configuration (re-direct the output to a specific file)
BOOST_GLOBAL_FIXTURE (UnitTestConfig);

// Start the test suite
BOOST_AUTO_TEST_SUITE (master_test_suite)

/**
 * Test the comparison of two floating point numbers, first the Boost way,
 * then the Google way.
 */
BOOST_AUTO_TEST_CASE (float_comparison_test) {
  float a = 0.2f;
  a = 5*a;
  const float b = 1.0f;

  // Test the Boost way
  BOOST_CHECK_MESSAGE (a == b, "The two floats (" << a << " and " << b
                       << ") should be equal, but are not");
  BOOST_CHECK_CLOSE (a, b, 0.0001);

  // Test the Google way
  const FloatingPoint<float> lhs (a), rhs (b);
  BOOST_CHECK_MESSAGE (lhs.AlmostEquals (rhs),
                       "The two floats (" << a << " and " << b
                       << ") should be equal, but are not");
}

/**
 * Test MPL-based type handling, just as a proof-of-concept. It does
 * not use StdAir BOM.
 */
BOOST_AUTO_TEST_CASE (mpl_structure_test) {
  const stdair::ClassCode_T lBookingClassCodeA ("A");
  const stdair_test::BookingClass lA (lBookingClassCodeA);
  const stdair_test::Cabin lCabin (lA);

  BOOST_CHECK_EQUAL (lCabin.toString(), lBookingClassCodeA);
  BOOST_CHECK_MESSAGE (lCabin.toString() == lBookingClassCodeA,
                       "The cabin key, '" << lCabin.toString()
                       << "' is not equal to '" << lBookingClassCodeA << "'");

  // MPL
  typedef boost::mpl::vector<stdair_test::BookingClass> MPL_BookingClass;
  typedef boost::mpl::push_back<MPL_BookingClass,
                                stdair_test::Cabin>::type types;
  
  if (boost::is_same<stdair_test::BookingClass,
                     stdair_test::Cabin::child>::value == false) {
    BOOST_ERROR ("The two types mut be equal, but are not");
  }
  
  if (boost::is_same<boost::mpl::at_c<types, 1>::type,
                     stdair_test::Cabin>::value == false) {
    BOOST_ERROR ("The type must be stdair_test::Cabin, but is not");
  }
}

/**
 * Test the initialisation of the Standard Airline IT base library.
 */
BOOST_AUTO_TEST_CASE (stdair_service_initialisation_test) {
  // Output log File
  const std::string lLogFilename ("StandardAirlineITTestSuite_init.log");
    
  // Set the log parameters
  std::ofstream logOutputFile;
  
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  
  // Initialise the stdair BOM
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  stdair::STDAIR_Service stdairService (lLogParams);

  // Retrieve (a reference on) the top of the persistent BOM tree
  stdair::BomRoot& lPersistentBomRoot = stdairService.getPersistentBomRoot();

  // Retrieve the BomRoot key, and compare it to the expected one
  const std::string& lBomRootKeyStr = lPersistentBomRoot.describeKey();
  const std::string lBomRootString (" -- ROOT -- ");

  // DEBUG
  STDAIR_LOG_DEBUG ("The BOM root key is '" << lBomRootKeyStr
                    << "'. It should be equal to '" << lBomRootString << "'");
  
  BOOST_CHECK_EQUAL (lBomRootKeyStr, lBomRootString);
  BOOST_CHECK_MESSAGE (lBomRootKeyStr == lBomRootString,
                       "The BOM root key, '" << lBomRootKeyStr
                       << "', should be equal to '" << lBomRootString
                       << "', but is not.");

  // Build a sample BOM tree
  stdairService.buildSampleBom();

  // DEBUG: Display the whole BOM tree
  const std::string& lCSVDump = stdairService.csvDisplay ();
  STDAIR_LOG_DEBUG (lCSVDump);

  // Close the Log outputFile
  logOutputFile.close();
}

/**
 * Test the initialisation of Standard Airline IT BOM objects.
 */
BOOST_AUTO_TEST_CASE (bom_structure_instantiation_test) {
  // Step 0.0: initialisation
  // Create the root of a Bom tree (i.e., a BomRoot object)
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();
        
  // Step 0.1: Inventory level
  // Create an Inventory (BA)
  const stdair::AirlineCode_T lBAAirlineCode ("BA");
  const stdair::InventoryKey lBAKey (lBAAirlineCode);
  myprovider::Inventory& lBAInv =
    stdair::FacBom<myprovider::Inventory>::instance().create (lBAKey);
  stdair::FacBomManager::addToList (lBomRoot, lBAInv);

  BOOST_CHECK_EQUAL (lBAInv.describeKey(), lBAAirlineCode);
  BOOST_CHECK_MESSAGE (lBAInv.describeKey() == lBAAirlineCode,
                       "The inventory key, '" << lBAInv.describeKey()
                       << "', should be equal to '" << lBAAirlineCode
                       << "', but is not");

  // Create an Inventory for AF
  const stdair::AirlineCode_T lAFAirlineCode ("AF");
  const stdair::InventoryKey lAFKey (lAFAirlineCode);
  myprovider::Inventory& lAFInv =
    stdair::FacBom<myprovider::Inventory>::instance().create (lAFKey);
  stdair::FacBomManager::addToList (lBomRoot, lAFInv);

  BOOST_CHECK_EQUAL (lAFInv.describeKey(), lAFAirlineCode);
  BOOST_CHECK_MESSAGE (lAFInv.describeKey() == lAFAirlineCode,
                       "The inventory key, '" << lAFInv.describeKey()
                       << "', should be equal to '" << lAFAirlineCode
                       << "', but is not");
  
  // Browse the inventories
  const myprovider::InventoryList_T& lInventoryList =
      stdair::BomManager::getList<myprovider::Inventory> (lBomRoot);
  const std::string lInventoryKeyArray[2] = {lBAAirlineCode, lAFAirlineCode};
  short idx = 0;
  for (myprovider::InventoryList_T::const_iterator itInv =
         lInventoryList.begin(); itInv != lInventoryList.end();
       ++itInv, ++idx) {
    const myprovider::Inventory* lInv_ptr = *itInv;
    BOOST_REQUIRE (lInv_ptr != NULL);
    
    BOOST_CHECK_EQUAL (lInventoryKeyArray[idx], lInv_ptr->describeKey());
    BOOST_CHECK_MESSAGE (lInventoryKeyArray[idx] == lInv_ptr->describeKey(),
                         "They inventory key, '" << lInventoryKeyArray[idx]
                         << "', does not match that of the Inventory object: '"
                         << lInv_ptr->describeKey() << "'");
  }
}

/**
 * Test the serialisation of Standard Airline IT BOM objects.
 */
BOOST_AUTO_TEST_CASE (bom_structure_serialisation_test) {

  // Backup (thanks to Boost.Serialisation) file
  const std::string lBackupFilename = "StandardAirlineITTestSuite_serial.txt";

  // Output log File
  const std::string lLogFilename ("StandardAirlineITTestSuite_serial.log");
    
  // Set the log parameters
  std::ofstream logOutputFile;
  
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  
  // Initialise the stdair BOM
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  stdair::STDAIR_Service stdairService (lLogParams);

  // Build a sample BOM tree
  stdairService.buildSampleBom();

  // Retrieve (a reference on) the top of the persistent BOM tree
  stdair::BomRoot& lPersistentBomRoot = stdairService.getPersistentBomRoot();

  // DEBUG: Display the whole BOM tree
  const std::string& lCSVDump = stdairService.csvDisplay ();
  STDAIR_LOG_DEBUG (lCSVDump);

  // Clone the persistent BOM
  stdairService.clonePersistentBom ();

  // Retrieve the BomRoot key, and compare it to the expected one
  const std::string lBAInvKeyStr ("BA");
  stdair::Inventory* lBAInv_ptr = 
    lPersistentBomRoot.getInventory (lBAInvKeyStr);

  // DEBUG
  STDAIR_LOG_DEBUG ("There should be an Inventory object corresponding to the '"
                    << lBAInvKeyStr << "' key.");

  BOOST_REQUIRE_MESSAGE (lBAInv_ptr != NULL,
                         "An Inventory object should exist with the key, '"
                         << lBAInvKeyStr << "'.");

  // create and open a character archive for output
  std::ofstream ofs (lBackupFilename.c_str());

  // save data to archive
  {
    boost::archive::text_oarchive oa (ofs);
    // write class instance to archive
    oa << lPersistentBomRoot;
    // archive and stream closed when destructors are called
  }

  // ... some time later restore the class instance to its orginal state
  stdair::BomRoot& lRestoredBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();
  {
    // create and open an archive for input
    std::ifstream ifs (lBackupFilename.c_str());
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> lRestoredBomRoot;
    // archive and stream closed when destructors are called
  }
  
  // DEBUG: Display the whole restored BOM tree
  const std::string& lRestoredCSVDump = 
    stdairService.csvDisplay(lRestoredBomRoot);
  STDAIR_LOG_DEBUG (lRestoredCSVDump);

  // Retrieve the BomRoot key, and compare it to the expected one
  const std::string& lBomRootKeyStr = lRestoredBomRoot.describeKey();
  const std::string lBomRootString (" -- ROOT -- ");

  // DEBUG
  STDAIR_LOG_DEBUG ("The BOM root key is '" << lBomRootKeyStr
                    << "'. It should be equal to '" << lBomRootString << "'");
  
  BOOST_CHECK_EQUAL (lBomRootKeyStr, lBomRootString);
  BOOST_CHECK_MESSAGE (lBomRootKeyStr == lBomRootString,
                       "The BOM root key, '" << lBomRootKeyStr
                       << "', should be equal to '" << lBomRootString
                       << "', but is not.");

  // Retrieve the Inventory
  stdair::Inventory* lRestoredBAInv_ptr =
    lRestoredBomRoot.getInventory (lBAInvKeyStr);

  // DEBUG
  STDAIR_LOG_DEBUG ("There should be an Inventory object corresponding to the '"
                    << lBAInvKeyStr << "' key in the restored BOM root.");

  BOOST_CHECK_MESSAGE (lRestoredBAInv_ptr != NULL,
                       "An Inventory object should exist with the key, '"
                       << lBAInvKeyStr << "' in the restored BOM root.");

  // Close the Log outputFile
  logOutputFile.close();
}

/**
 * Test the clone of Standard Airline IT BOM objects.
 */
BOOST_AUTO_TEST_CASE (bom_structure_clone_test) {  

  // Output log File
  const std::string lLogFilename ("StandardAirlineITTestSuite_clone.log");

  // Set the log parameters
  std::ofstream logOutputFile;
  
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  
  // Initialise the stdair BOM
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  stdair::STDAIR_Service stdairService (lLogParams);

  // Build a sample BOM tree
  stdairService.buildSampleBom();

  // Retrieve (a constant reference on) the top of the persistent BOM tree
  const stdair::BomRoot& lPersistentBomRoot =
    stdairService.getPersistentBomRoot();  

  // DEBUG: Display the whole persistent BOM tree
  const std::string& lCSVDump = stdairService.csvDisplay (); 
  STDAIR_LOG_DEBUG ("Display the persistent BOM tree.");
  STDAIR_LOG_DEBUG (lCSVDump); 

  // Clone the persistent BOM
  stdairService.clonePersistentBom (); 

  // Retrieve (a reference on) the top of the clone BOM tree
  stdair::BomRoot& lCloneBomRoot = stdairService.getBomRoot();   

  // DEBUG: Display the clone BOM tree after the clone process.
  const std::string& lAfterCloneCSVDump = 
    stdairService.csvDisplay(lCloneBomRoot); 
  STDAIR_LOG_DEBUG ("Display the clone BOM tree after the clone process.");
  STDAIR_LOG_DEBUG (lAfterCloneCSVDump);

  // Retrieve the clone BomRoot key, and compare it to the persistent BomRoot 
  // key.
  const std::string& lCloneBomRootKeyStr = lCloneBomRoot.describeKey();
  const std::string& lPersistentBomRootKeyStr = 
    lPersistentBomRoot.describeKey();

  // DEBUG
  STDAIR_LOG_DEBUG ("The clone BOM root key is '" << lCloneBomRootKeyStr
                    << "'. It should be equal to '" 
		    << lPersistentBomRootKeyStr << "'");
  
  BOOST_CHECK_EQUAL (lCloneBomRootKeyStr, lPersistentBomRootKeyStr);
  BOOST_CHECK_MESSAGE (lCloneBomRootKeyStr == lPersistentBomRootKeyStr,
                       "The clone BOM root key, '" << lCloneBomRootKeyStr
                       << "', should be equal to '" << lPersistentBomRootKeyStr
                       << "', but is not.");

  // Retrieve the BA inventory in the clone BOM root
  const std::string lBAInvKeyStr ("BA");
  stdair::Inventory* lCloneBAInv_ptr =
    lCloneBomRoot.getInventory (lBAInvKeyStr); 

  // DEBUG
  STDAIR_LOG_DEBUG ("There should be an Inventory object corresponding to the '"
                    << lBAInvKeyStr << "' key in the clone BOM root.");

  BOOST_CHECK_MESSAGE (lCloneBAInv_ptr != NULL,
                       "An Inventory object should exist with the key, '"
                       << lBAInvKeyStr << "' in the clone BOM root.");

  // Close the Log outputFile
  logOutputFile.close();
}

// End the test suite
BOOST_AUTO_TEST_SUITE_END()

#else // BOOST_VERSION_MACRO >= 103900
boost_utf::test_suite* init_unit_test_suite (int, char* []) {
  boost_utf::test_suite* test = BOOST_TEST_SUITE ("Unit test example 1");
  return test;
}
#endif // BOOST_VERSION_MACRO >= 103900

/*!
 * \endcode
 */
