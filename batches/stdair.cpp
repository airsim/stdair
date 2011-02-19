/*!
 * \page batch_stdair_cpp Command-Line Utility to Demonstrate Typical StdAir Usage
 * \code
 */
// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
// StdAir
#include <stdair/config/stdair-paths.hpp>
#include <stdair/stdair_types.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomDisplay.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>

// //////// Constants //////
/** Default name and location for the log file. */
const std::string K_STDAIR_DEFAULT_LOG_FILENAME ("stdair.log");

/** Default name and location for the (CSV) input file. */
const std::string K_STDAIR_DEFAULT_INPUT_FILENAME ("../../test/samples/stdair01.csv");

/** Default for the input type. It can be either built-in or provided by an
    input file. That latter must then be given with the -i option. */
const bool K_STDAIR_DEFAULT_BUILT_IN_INPUT = false;

/** Early return status (so that it can be differentiated from an
    error). */
const int K_STDAIR_EARLY_RETURN_STATUS = 99;

// ///////// Parsing of Options & Configuration /////////
// A helper function to simplify the main part.
template<class T> std::ostream& operator<< (std::ostream& os,
                                            const std::vector<T>& v) {
  std::copy (v.begin(), v.end(), std::ostream_iterator<T> (std::cout, " ")); 
  return os;
}

/** Read and parse the command line options. */
int readConfiguration (int argc, char* argv[], bool& ioIsBuiltin,
                       stdair::Filename_T& ioInputFilename,
                       std::string& ioLogFilename) {
  // Default for the built-in input
  ioIsBuiltin = K_STDAIR_DEFAULT_BUILT_IN_INPUT;
  
  // Declare a group of options that will be allowed only on command line
  boost::program_options::options_description generic ("Generic options");
  generic.add_options()
    ("prefix", "print installation prefix")
    ("version,v", "print version string")
    ("help,h", "produce help message");
    
  // Declare a group of options that will be allowed both on command
  // line and in config file

  boost::program_options::options_description config ("Configuration");
  config.add_options()
    ("builtin,b",
     "The sample BOM tree can be either built-in or parsed from an input file. That latter must then be given with the -i/--input option")
    ("input,i",
     boost::program_options::value< std::string >(&ioInputFilename)->default_value(K_STDAIR_DEFAULT_INPUT_FILENAME),
     "(CVS) input file for the demand distributions")
    ("log,l",
     boost::program_options::value< std::string >(&ioLogFilename)->default_value(K_STDAIR_DEFAULT_LOG_FILENAME),
     "Filename for the logs")
    ;

  // Hidden options, will be allowed both on command line and
  // in config file, but will not be shown to the user.
  boost::program_options::options_description hidden ("Hidden options");
  hidden.add_options()
    ("copyright",
     boost::program_options::value< std::vector<std::string> >(),
     "Show the copyright (license)");
        
  boost::program_options::options_description cmdline_options;
  cmdline_options.add(generic).add(config).add(hidden);

  boost::program_options::options_description config_file_options;
  config_file_options.add(config).add(hidden);
  boost::program_options::options_description visible ("Allowed options");
  visible.add(generic).add(config);
        
  boost::program_options::positional_options_description p;
  p.add ("copyright", -1);
        
  boost::program_options::variables_map vm;
  boost::program_options::
    store (boost::program_options::command_line_parser (argc, argv).
           options (cmdline_options).positional(p).run(), vm);

  std::ifstream ifs ("stdair.cfg");
  boost::program_options::store (parse_config_file (ifs, config_file_options),
                                 vm);
  boost::program_options::notify (vm);
    
  if (vm.count ("help")) {
    std::cout << visible << std::endl;
    return K_STDAIR_EARLY_RETURN_STATUS;
  }

  if (vm.count ("version")) {
    std::cout << PACKAGE_NAME << ", version " << PACKAGE_VERSION << std::endl;
    return K_STDAIR_EARLY_RETURN_STATUS;
  }

  if (vm.count ("prefix")) {
    std::cout << "Installation prefix: " << PREFIXDIR << std::endl;
    return K_STDAIR_EARLY_RETURN_STATUS;
  }

  if (vm.count ("builtin")) {
    ioIsBuiltin = true;
  }
  const std::string isBuiltinStr = (ioIsBuiltin == true)?"yes":"no";
  std::cout << "The BOM should be built-in? " << isBuiltinStr << std::endl;

  if (ioIsBuiltin == false) {
    if (vm.count ("input")) {
      ioInputFilename = vm["input"].as< std::string >();
      std::cout << "Input filename is: " << ioInputFilename << std::endl;
    }
  }

  if (vm.count ("log")) {
    ioLogFilename = vm["log"].as< std::string >();
    std::cout << "Log filename is: " << ioLogFilename << std::endl;
  }

  return 0;
}

// //////////////////////////////////////////////////////////////////////
void buildSampleBom() {

  // DEBUG
  STDAIR_LOG_DEBUG ("StdAir will build the BOM tree from built-in "
                    << "specifications.");

  // ///////////// Step 0.0: Initialisation ////////////
  // Create the root of the Bom tree (i.e., a BomRoot object)
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();

  // Step 0.1: Inventory level
  // Create an Inventory for BA
  const stdair::InventoryKey lBAKey ("BA");
  stdair::Inventory& lBAInv =
    stdair::FacBom<stdair::Inventory>::instance().create (lBAKey);
  stdair::FacBomManager::instance().addToList (lBomRoot, lBAInv);

  // Create an Inventory for AF
  const stdair::InventoryKey lAFKey ("AF");
  stdair::Inventory& lAFInv =
    stdair::FacBom<stdair::Inventory>::instance().create (lAFKey);
  stdair::FacBomManager::instance().addToList (lBomRoot, lAFInv);

  // ////// BA ///////    
  // Step 0.2: Flight-date level
  // Create a FlightDate (BA9/10-JUN-2011) for BA's Inventory
  stdair::FlightNumber_T lFlightNumber = 9;
  stdair::Date_T lDate (2011, 6, 10);
  stdair::FlightDateKey lFlightDateKey (lFlightNumber, lDate);

  stdair::FlightDate& lBA9_20110610_FD =
    stdair::FacBom<stdair::FlightDate>::instance().create (lFlightDateKey);
  stdair::FacBomManager::instance().addToList (lBAInv, lBA9_20110610_FD);
    
  // Display the flight-date
  // STDAIR_LOG_DEBUG ("FlightDate: " << lBA9_20110610_FD.toString());
    
  // Step 0.3: Segment-date level
  // Create a first SegmentDate (LHR-SYD) for BA's Inventory
  // See http://www.britishairways.com/travel/flightinformation/public/fr_fr?&Carrier=BA&FlightNumber=0009&from=LHR&to=SYD&depDate=100611&SellingClass=O
  const stdair::AirportCode_T lLHR ("LHR");
  const stdair::AirportCode_T lSYD ("SYD");
  const stdair::DateOffset_T l1Day (1);
  const stdair::DateOffset_T l2Days (2);
  const stdair::Duration_T l2135 (21, 45, 0);
  const stdair::Duration_T l0610 (6, 10, 0);
  const stdair::Duration_T l2205 (22, 05, 0);
  stdair::SegmentDateKey lSegmentDateKey (lLHR, lSYD);

  stdair::SegmentDate& lLHRSYDSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lBA9_20110610_FD,
                                               lLHRSYDSegment);

  // Fill the SegmentDate content
  lLHRSYDSegment.setBoardingDate (lDate);
  lLHRSYDSegment.setOffDate (lDate + l2Days);
  lLHRSYDSegment.setBoardingTime (l2135);
  lLHRSYDSegment.setOffTime (l0610);
  lLHRSYDSegment.setElapsedTime (l2135);
  
  // Display the segment-date
  // STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment);

  // Create a second SegmentDate (LHR-BKK) for BA's Inventory
  // See http://www.britishairways.com/travel/flightinformation/public/fr_fr?&Carrier=BA&FlightNumber=0009&from=LHR&to=BKK&depDate=100611&SellingClass=O
  const stdair::AirportCode_T lBKK ("BKK");
  const stdair::Duration_T l1540 (15, 40, 0);
  const stdair::Duration_T l1105 (11, 5, 0);
  lSegmentDateKey = stdair::SegmentDateKey (lLHR, lBKK);

  stdair::SegmentDate& lLHRBKKSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lBA9_20110610_FD,
                                               lLHRBKKSegment);

  // Fill the SegmentDate content
  lLHRBKKSegment.setBoardingDate (lDate);
  lLHRBKKSegment.setOffDate (lDate + l1Day);
  lLHRBKKSegment.setBoardingTime (l2135);
  lLHRBKKSegment.setOffTime (l1540);
  lLHRBKKSegment.setElapsedTime (l1105);
  
  // Display the segment-date
  // STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment);


  // Create a third SegmentDate (BKK-SYD) for BA's Inventory
  // See http://www.britishairways.com/travel/flightinformation/public/fr_fr?&Carrier=BA&FlightNumber=0009&from=BKK&to=SYD&depDate=110611&SellingClass=O
  const stdair::Duration_T l1705 (17, 5, 0);
  const stdair::Duration_T l0905 (9, 5, 0);
  lSegmentDateKey = stdair::SegmentDateKey (lBKK, lSYD);

  stdair::SegmentDate& lBKKSYDSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lBA9_20110610_FD,
                                               lBKKSYDSegment);

  // Fill the SegmentDate content
  lBKKSYDSegment.setBoardingDate (lDate + l1Day);
  lBKKSYDSegment.setOffDate (lDate + l2Days);
  lBKKSYDSegment.setBoardingTime (l1705);
  lBKKSYDSegment.setOffTime (l1540);
  lBKKSYDSegment.setElapsedTime (l0905);
  
  // Display the segment-date
  // STDAIR_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment);

  // Step 0.4: Leg-date level
  // Create a first LegDate (LHR) for BA's Inventory
  stdair::LegDateKey lLegDateKey (lLHR);

  stdair::LegDate& lLHRLeg =
    stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
  stdair::FacBomManager::instance().addToList (lBA9_20110610_FD, lLHRLeg);

  // Fill the LegDate content
  lLHRLeg.setOffPoint (lBKK);
  lLHRLeg.setBoardingDate (lDate);
  lLHRLeg.setOffDate (lDate + l1Day);
  lLHRLeg.setBoardingTime (l2135);
  lLHRLeg.setOffTime (l1540);
  lLHRLeg.setElapsedTime (l1105);

  // Display the leg-date
  // STDAIR_LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
  // Create a second LegDate (BKK)
  lLegDateKey = stdair::LegDateKey (lBKK);

  stdair::LegDate& lBKKLeg =
    stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
  stdair::FacBomManager::instance().addToList (lBA9_20110610_FD, lBKKLeg);

  // Display the leg-date
  // STDAIR_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());

  // Fill the LegDate content
  lBKKLeg.setOffPoint (lSYD);
  lBKKLeg.setBoardingDate (lDate + l1Day);
  lBKKLeg.setOffDate (lDate + l2Days);
  lBKKLeg.setBoardingTime (l1705);
  lBKKLeg.setOffTime (l1540);
  lBKKLeg.setElapsedTime (l0905);

  // Step 0.5: segment-cabin level
  // Create a SegmentCabin (Y) for the Segment LHR-BKK of BA's Inventory
  const stdair::CabinCode_T lY ("Y");
  stdair::SegmentCabinKey lYSegmentCabinKey (lY);

  stdair::SegmentCabin& lLHRBKKSegmentYCabin =
    stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
  stdair::FacBomManager::instance().addToList (lLHRBKKSegment,
                                               lLHRBKKSegmentYCabin);

  // Display the segment-cabin
  // STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRBKKSegmentYCabin.toString());

  // Create a SegmentCabin (Y) of the Segment BKK-SYD;
  stdair::SegmentCabin& lBKKSYDSegmentYCabin =
    stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
  stdair::FacBomManager::instance().addToList (lBKKSYDSegment,
                                               lBKKSYDSegmentYCabin);
     
  // Display the segment-cabin
  // STDAIR_LOG_DEBUG ("SegmentCabin: " << lBKKSYDSegmentYCabin.toString());

  // Create a SegmentCabin (Y) of the Segment LHR-SYD;
  stdair::SegmentCabin& lLHRSYDSegmentYCabin =
    stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
  stdair::FacBomManager::instance().addToList (lLHRSYDSegment,
                                               lLHRSYDSegmentYCabin);
      
  // Display the segment-cabin
  // STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRSYDSegmentYCabin.toString());

  // Step 0.6: leg-cabin level
  // Create a LegCabin (Y) for the Leg LHR-BKK on BA's Inventory
  stdair::LegCabinKey lYLegCabinKey (lY);

  stdair::LegCabin& lLHRLegYCabin =
    stdair::FacBom<stdair::LegCabin>::instance().create (lYLegCabinKey);
  stdair::FacBomManager::instance().addToList (lLHRLeg, lLHRLegYCabin);

  // Display the leg-cabin
  // STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

  // Create a LegCabin (Y) for the Leg BKK-SYD
  stdair::LegCabin& lBKKLegYCabin =
    stdair::FacBom<stdair::LegCabin>::instance().create (lYLegCabinKey);
  stdair::FacBomManager::instance().addToList (lBKKLeg, lBKKLegYCabin);

  // Display the leg-cabin
  // STDAIR_LOG_DEBUG ("LegCabin: " << lBKKLegYCabin.toString());

  // Step 0.7: fare family level
  // Create a FareFamily (1) for the Segment LHR-BKK, cabin Y on BA's Inv
  const stdair::FamilyCode_T l1 ("EcoSaver");
  stdair::FareFamilyKey l1FareFamilyKey (l1);

  stdair::FareFamily& lLHRBKKSegmentYCabin1Family =
    stdair::FacBom<stdair::FareFamily>::instance().create(l1FareFamilyKey);
  stdair::FacBomManager::instance().addToList (lLHRBKKSegmentYCabin,
                                               lLHRBKKSegmentYCabin1Family);

  // Display the booking class
  // STDAIR_LOG_DEBUG ("FareFamily: "
  //                   << lLHRBKKSegmentYCabin1Family.toString());

  // Create a FareFamily (1)  for the Segment BKK-SYD, cabin Y on BA's Inv
  stdair::FareFamily& lBKKSYDSegmentYCabin1Family =
    stdair::FacBom<stdair::FareFamily>::instance().create (l1FareFamilyKey);
  stdair::FacBomManager::instance().addToList (lBKKSYDSegmentYCabin,
                                               lBKKSYDSegmentYCabin1Family);
    
  // Display the booking class
  // STDAIR_LOG_DEBUG ("FareFamily: "
  //                   << lLHRBKKSegmentYCabin1Family.toString());

  // Create a FareFamily (1)  for the Segment LHR-SYD, cabin Y on BA's Inv
  stdair::FareFamily& lLHRSYDSegmentYCabin1Family =
    stdair::FacBom<stdair::FareFamily>::instance().create(l1FareFamilyKey);
  stdair::FacBomManager::instance().addToList (lLHRSYDSegmentYCabin,
                                               lLHRSYDSegmentYCabin1Family);

  // Display the booking class
  // STDAIR_LOG_DEBUG ("FareFamily: "
  //                   << lLHRBKKSegmentYCabin1Family.toString());


  // Step 0.8: booking class level
  // Create a BookingClass (Q) for the Segment LHR-BKK, cabin Y, fare family 1 on BA's Inv
  const stdair::ClassCode_T lQ ("Q");
  stdair::BookingClassKey lQBookingClassKey (lQ);

  stdair::BookingClass& lLHRBKKSegmentYCabin1FamilyQClass =
    stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
  stdair::FacBomManager::instance().addToList (lLHRBKKSegmentYCabin1Family,
                                               lLHRBKKSegmentYCabin1FamilyQClass);

  // Display the booking class
  // STDAIR_LOG_DEBUG ("BookingClass: "
  //                   << lLHRBKKSegmentYCabin1FamilyQClass.toString());

  // Create a BookingClass (Q) for the Segment BKK-SYD, cabin Y, fare family 1 on BA's Inv
  stdair::BookingClass& lBKKSYDSegmentYCabin1FamilyQClass =
    stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
  stdair::FacBomManager::instance().addToList (lBKKSYDSegmentYCabin1Family,
                                               lBKKSYDSegmentYCabin1FamilyQClass);
    
  // Display the booking class
  // STDAIR_LOG_DEBUG ("BookingClass: "
  //                   << lLHRBKKSegmentYCabin1FamilyQClass.toString());

  // Create a BookingClass (Q) for the Segment LHR-SYD, cabin Y, fare family 1 on BA's Inv
  stdair::BookingClass& lLHRSYDSegmentYCabin1FamilyQClass =
    stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
  stdair::FacBomManager::instance().addToList (lLHRSYDSegmentYCabin1Family,
                                               lLHRSYDSegmentYCabin1FamilyQClass);

  // Display the booking class
  // STDAIR_LOG_DEBUG ("BookingClass: "
  //                   << lLHRBKKSegmentYCabin1FamilyQClass.toString());

    
  // ////// AF ///////    
  // Step 0.2: Flight-date level
  // Create a FlightDate (AF084/20-MAR-2011) for AF's Inventory
  lFlightNumber = 84;
  lDate = stdair::Date_T (2011, 3, 20);
  lFlightDateKey = stdair::FlightDateKey (lFlightNumber, lDate);

  stdair::FlightDate& lAF084_20110320_FD =
    stdair::FacBom<stdair::FlightDate>::instance().create (lFlightDateKey);
  stdair::FacBomManager::instance().addToList (lAFInv, lAF084_20110320_FD);
    
  // Display the flight-date
  // STDAIR_LOG_DEBUG ("FlightDate: " << lAF084_20110320_FD.toString());

  // Step 0.3: Segment-date level
  // Create a SegmentDate (CDG-SFO) for AF's Inventory
  const stdair::AirportCode_T lCDG ("CDG");
  const stdair::AirportCode_T lSFO ("SFO");
  const stdair::Duration_T l1040 (10, 40, 0);
  const stdair::Duration_T l1250 (12, 50, 0);
  const stdair::Duration_T l1110 (11, 10, 0);
  lSegmentDateKey = stdair::SegmentDateKey (lCDG, lSFO);

  stdair::SegmentDate& lCDGSFOSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lAF084_20110320_FD,
                                               lCDGSFOSegment);

  // Display the segment-date
  // STDAIR_LOG_DEBUG ("SegmentDate: " << lCDGSFOSegment.toString());

  // Fill the SegmentDate content
  lCDGSFOSegment.setBoardingDate (lDate);
  lCDGSFOSegment.setOffDate (lDate);
  lCDGSFOSegment.setBoardingTime (l1040);
  lCDGSFOSegment.setOffTime (l1250);
  lCDGSFOSegment.setElapsedTime (l1110);

  // Step 0.4: Leg-date level
  // Create a LegDate (CDG) for AF's Inventory
  lLegDateKey = stdair::LegDateKey (lCDG);

  stdair::LegDate& lCDGLeg =
    stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
  stdair::FacBomManager::instance().addToList (lAF084_20110320_FD, lCDGLeg);

  // Fill the LegDate content
  lCDGLeg.setOffPoint (lSFO);
  lCDGLeg.setBoardingDate (lDate);
  lCDGLeg.setOffDate (lDate);
  lCDGLeg.setBoardingTime (l1040);
  lCDGLeg.setOffTime (l1250);
  lCDGLeg.setElapsedTime (l1110);

  // Display the leg-date
  // STDAIR_LOG_DEBUG ("LegDate: " << lCDGLeg.toString());

  // Step 0.5: segment-cabin level
  // Create a SegmentCabin (Y) for the Segment CDG-SFO of AF's Inventory
  stdair::SegmentCabin& lCDGSFOSegmentYCabin =
    stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
  stdair::FacBomManager::instance().addToList (lCDGSFOSegment,
                                               lCDGSFOSegmentYCabin);

  // Display the segment-cabin
  // STDAIR_LOG_DEBUG ("SegmentCabin: " << lCDGSFOSegmentYCabin.toString());

  // Step 0.6: leg-cabin level
  // Create a LegCabin (Y) for the Leg CDG-SFO on AF's Inventory
  stdair::LegCabin& lCDGLegYCabin =
    stdair::FacBom<stdair::LegCabin>::instance().create (lYLegCabinKey);
  stdair::FacBomManager::instance().addToList (lCDGLeg, lCDGLegYCabin);

  // Display the leg-cabin
  // STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());


  // Step 0.7: fare family level
  // Create a fareFamily (1) for the Segment CDG-SFO, cabin Y on AF's Inv
  stdair::FareFamily& lCDGSFOSegmentYCabin1Family =
    stdair::FacBom<stdair::FareFamily>::instance().create(l1FareFamilyKey);
  stdair::FacBomManager::instance().addToList (lCDGSFOSegmentYCabin,
                                               lCDGSFOSegmentYCabin1Family);

  // Display the fare family
  // STDAIR_LOG_DEBUG ("fareFamily: "
  //
  //                   << lCDGSFOSegmentYCabin1Family.toString());

  // Step 0.8: booking class level
  // Create a BookingClass (Q) for the Segment CDG-SFO, cabin Y, fare family 1 on AF's Inv
  stdair::BookingClass& lCDGSFOSegmentYCabin1FamilyQClass =
    stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
  stdair::FacBomManager::instance().addToList (lCDGSFOSegmentYCabin1Family,
                                               lCDGSFOSegmentYCabin1FamilyQClass);

  // Display the booking class
  // STDAIR_LOG_DEBUG ("BookingClass: "
  //                   << lCDGSFOSegmentYCabin1FamilyQClass.toString());

  // DEBUG: Display the whole BOM (structure and data)
  std::ostringstream oStr;
  stdair::BomDisplay::csvDisplay (oStr, lBomRoot);
  STDAIR_LOG_DEBUG (oStr.str());
}


// ///////////////// M A I N ////////////////////
int main (int argc, char* argv[]) {

  // Built-in
  bool isBuiltin;
    
  // Input file name
  stdair::Filename_T lInputFilename;

  // Output log File
  std::string lLogFilename;
    
  // Call the command-line option parser
  const int lOptionParserStatus =
    readConfiguration (argc, argv, isBuiltin, lInputFilename, lLogFilename);

  if (lOptionParserStatus == K_STDAIR_EARLY_RETURN_STATUS) {
    return 0;
  }

  // Set the log parameters
  std::ofstream logOutputFile;
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();

  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  stdair::STDAIR_Service stdairService (lLogParams);

  // DEBUG
  STDAIR_LOG_DEBUG ("Welcome to stdair");

  // Check wether or not a (CSV) input file should be read
  if (isBuiltin == true) {
    // Build a sample BOM tree
    buildSampleBom();
      
  } else {
    // Read the input file
    //stdairService.readFromInputFile (lInputFilename);

    // DEBUG
    STDAIR_LOG_DEBUG ("StdAir will parse " << lInputFilename
                      << " and build the corresponding BOM tree.");
  }

  // Close the Log outputFile
  logOutputFile.close();

  /*
    Note: as that program is not intended to be run on a server in
    production, it is better not to catch the exceptions. When it
    happens (that an exception is throwned), that way we get the
    call stack.
  */
    
  return 0;	
}

/*!
 * \endcode
 */
