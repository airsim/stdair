/*!
 * \page StandardAirlineITTestSuite_cpp Command-Line Test to Demonstrate How To Extend StdAir BOM
 * \code
 */
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <fstream>
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
#include <boost/test/unit_test.hpp>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/factory/FacBomManager.hpp>
// StdAir Test Suite
#include <test/stdair/StdairTestLib.hpp>
#include <test/stdair/MPInventory.hpp>

namespace boost_utf = boost::unit_test;

/**
 * Configuration for the Boost Unit Test Framework (UTF)
 */
struct UnitTestConfig {
  /** Constructor. */
  UnitTestConfig() {
    static std::ofstream _test_log("StandardAirlineITTestSuite_utfresults.xml");
    boost_utf::unit_test_log.set_stream (_test_log);
    boost_utf::unit_test_log.set_format (boost_utf::XML);
    boost_utf::unit_test_log.set_threshold_level (boost_utf::log_test_units);
    //boost_utf::unit_test_log.set_threshold_level (boost_utf::log_successful_tests);
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
    BOOST_REQUIRE ("The two types mut be equal, but are not");
  }
  
  if (boost::is_same<boost::mpl::at_c<types, 1>::type,
                     stdair_test::Cabin>::value == false) {
    BOOST_REQUIRE ("The type must be stdair_test::Cabin, but is not");
  }
}

/**
 * Test the initialisation of the Standard Airline IT base library.
 */
BOOST_AUTO_TEST_CASE (stdair_service_initialisation_test) {
  // Output log File
  const std::string lLogFilename ("testServiceInitialisation.log");
    
  // Set the log parameters
  std::ofstream logOutputFile;
  
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  
  // Initialise the stdair BOM
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  stdair::STDAIR_Service stdairService (lLogParams);

  // Get the BOM Root
  const stdair::BomRoot& lBomRoot = stdairService.getBomRoot();
  const std::string& lBomRootKeyStr = lBomRoot.describeKey();

  const std::string lBomRootString (" -- ROOT -- ");
  BOOST_CHECK_EQUAL (lBomRootKeyStr, lBomRootString);
  BOOST_CHECK_MESSAGE (lBomRootKeyStr == lBomRootString,
                       "The BOM root key, '" << lBomRootKeyStr
                       << "', should be equal to '" << lBomRootString
                       << "', but is not.");

  // Close the Log outputFile
  logOutputFile.close();
}

/**
 * Test the initialisation of Standard Airline IT BOM objects.
 */
BOOST_AUTO_TEST_CASE (bom_structure_instantiation_test) {
  // Step 0.0: initialisation
  // Create the root of the Bom tree (i.e., a BomRoot object)
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();
        
  // Step 0.1: Inventory level
  // Create an Inventory (BA)
  const stdair::AirlineCode_T lBAAirlineCode ("BA");
  const stdair::InventoryKey lBAKey (lBAAirlineCode);
  myprovider::Inventory& lBAInv =
    stdair::FacBom<myprovider::Inventory>::instance().create (lBAKey);
  stdair::FacBomManager::instance().addToList (lBomRoot, lBAInv);

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
  stdair::FacBomManager::instance().addToList (lBomRoot, lAFInv);

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

// End the test suite
BOOST_AUTO_TEST_SUITE_END()

/*!
 * \endcode
 */
