/*!
 * \page cmd_bom_manager_cpp C++ Class Building Sample StdAir BOM Trees
 * \code
 */
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/AirportPair.hpp>
#include <stdair/bom/PosChannel.hpp>
#include <stdair/bom/DatePeriod.hpp>
#include <stdair/bom/TimePeriod.hpp>
#include <stdair/bom/FareFeatures.hpp>
#include <stdair/bom/YieldFeatures.hpp>
#include <stdair/bom/AirlineClassList.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildSampleBom (BomRoot& ioBomRoot) {

    // DEBUG
    STDAIR_LOG_DEBUG ("StdAir will build the BOM tree from built-in "
                      << "specifications.");

    // Step 0.1: Inventory level
    // Create an Inventory for BA
    const InventoryKey lBAKey ("BA");
    Inventory& lBAInv = FacBom<Inventory>::instance().create (lBAKey);
    FacBomManager::addToListAndMap (ioBomRoot, lBAInv);
    FacBomManager::linkWithParent (ioBomRoot, lBAInv);

    // Create an Inventory for AF
    const InventoryKey lAFKey ("AF");
    Inventory& lAFInv = FacBom<Inventory>::instance().create (lAFKey);
    FacBomManager::addToListAndMap (ioBomRoot, lAFInv);
    FacBomManager::linkWithParent (ioBomRoot, lAFInv);

    // ////// BA ///////    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA9/10-JUN-2011) for BA's Inventory
    FlightNumber_T lFlightNumber = 9;
    Date_T lDate (2011, 6, 10);
    FlightDateKey lFlightDateKey (lFlightNumber, lDate);

    FlightDate& lBA9_20110610_FD =
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::addToListAndMap (lBAInv, lBA9_20110610_FD);
    FacBomManager::linkWithParent (lBAInv, lBA9_20110610_FD);
    
    // Display the flight-date
    // STDAIR_LOG_DEBUG ("FlightDate: " << lBA9_20110610_FD.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (LHR-SYD) for BA's Inventory
    // See http://www.britishairways.com/travel/flightinformation/public/fr_fr?&Carrier=BA&FlightNumber=0009&from=LHR&to=SYD&depDate=100611&SellingClass=O
    const AirportCode_T lLHR ("LHR");
    const AirportCode_T lSYD ("SYD");
    const DateOffset_T l1Day (1);
    const DateOffset_T l2Days (2);
    const Duration_T l2135 (21, 45, 0);
    const Duration_T l0610 (6, 10, 0);
    const Duration_T l2205 (22, 05, 0);
    SegmentDateKey lSegmentDateKey (lLHR, lSYD);

    SegmentDate& lLHRSYDSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lBA9_20110610_FD, lLHRSYDSegment);
    FacBomManager::linkWithParent (lBA9_20110610_FD, lLHRSYDSegment);

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
    const AirportCode_T lBKK ("BKK");
    const Duration_T l1540 (15, 40, 0);
    const Duration_T l1105 (11, 5, 0);
    lSegmentDateKey = SegmentDateKey (lLHR, lBKK);

    SegmentDate& lLHRBKKSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lBA9_20110610_FD, lLHRBKKSegment);
    FacBomManager::linkWithParent (lBA9_20110610_FD, lLHRBKKSegment);

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
    const Duration_T l1705 (17, 5, 0);
    const Duration_T l0905 (9, 5, 0);
    lSegmentDateKey = SegmentDateKey (lBKK, lSYD);

    SegmentDate& lBKKSYDSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lBA9_20110610_FD, lBKKSYDSegment);
    FacBomManager::linkWithParent (lBA9_20110610_FD, lBKKSYDSegment);

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
    LegDateKey lLegDateKey (lLHR);

    LegDate& lLHRLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::addToListAndMap (lBA9_20110610_FD, lLHRLeg);
    FacBomManager::linkWithParent (lBA9_20110610_FD, lLHRLeg);

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
    lLegDateKey = LegDateKey (lBKK);

    LegDate& lBKKLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::addToListAndMap (lBA9_20110610_FD, lBKKLeg);
    FacBomManager::linkWithParent (lBA9_20110610_FD, lBKKLeg);

    // Display the leg-date
    // STDAIR_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());

    // Fill the LegDate content
    lBKKLeg.setOffPoint (lSYD);
    lBKKLeg.setBoardingDate (lDate + l1Day);
    lBKKLeg.setOffDate (lDate + l2Days);
    lBKKLeg.setBoardingTime (l1705);
    lBKKLeg.setOffTime (l1540);
    lBKKLeg.setElapsedTime (l0905);

    // Link the segment-dates with the leg-dates
    FacBomManager::addToListAndMap (lLHRLeg, lLHRSYDSegment);
    FacBomManager::addToListAndMap (lLHRLeg, lLHRBKKSegment);
    FacBomManager::addToListAndMap (lBKKLeg, lLHRSYDSegment);
    FacBomManager::addToListAndMap (lBKKLeg, lBKKSYDSegment);
    FacBomManager::addToListAndMap (lLHRSYDSegment, lLHRLeg);
    FacBomManager::addToListAndMap (lLHRBKKSegment, lLHRLeg);
    FacBomManager::addToListAndMap (lLHRSYDSegment, lBKKLeg);
    FacBomManager::addToListAndMap (lBKKSYDSegment, lBKKLeg);


    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) for the Segment LHR-BKK of BA's Inventory
    const CabinCode_T lY ("Y");
    SegmentCabinKey lYSegmentCabinKey (lY);

    SegmentCabin& lLHRBKKSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lLHRBKKSegment, lLHRBKKSegmentYCabin);
    FacBomManager::linkWithParent (lLHRBKKSegment, lLHRBKKSegmentYCabin);

    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRBKKSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment BKK-SYD;
    SegmentCabin& lBKKSYDSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lBKKSYDSegment, lBKKSYDSegmentYCabin);
    FacBomManager::linkWithParent (lBKKSYDSegment, lBKKSYDSegmentYCabin);

     
    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lBKKSYDSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment LHR-SYD;
    SegmentCabin& lLHRSYDSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lLHRSYDSegment, lLHRSYDSegmentYCabin);
    FacBomManager::linkWithParent (lLHRSYDSegment, lLHRSYDSegmentYCabin);
      
    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRSYDSegmentYCabin.toString());

    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) for the Leg LHR-BKK on BA's Inventory
    LegCabinKey lYLegCabinKey (lY);

    LegCabin& lLHRLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::addToListAndMap (lLHRLeg, lLHRLegYCabin);
    FacBomManager::linkWithParent (lLHRLeg, lLHRLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Create a LegCabin (Y) for the Leg BKK-SYD
    LegCabin& lBKKLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::addToListAndMap (lBKKLeg, lBKKLegYCabin);
    FacBomManager::linkWithParent (lBKKLeg, lBKKLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lBKKLegYCabin.toString());

    /**
     * Add the segment-cabin to the list which the leg-cabin crosses.
     *
     * As several segment-cabins may cross the leg-cabin,
     * and as the segment-cabin key is only made by a cabin code (which
     * is the same as for the leg-cabin), all the segment-cabins
     * crossing the leg-cabin would have the same key.
     * Hence, the segment-cabins must be differentiated according to their
     * boarding and off points as well.
     */
    FacBomManager::addToListAndMap (lLHRLegYCabin, lLHRSYDSegmentYCabin,
                                    lLHRSYDSegmentYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lLHRLegYCabin, lLHRBKKSegmentYCabin,
                                    lLHRBKKSegmentYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lBKKLegYCabin, lLHRSYDSegmentYCabin,
                                    lLHRSYDSegmentYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lBKKLegYCabin, lBKKSYDSegmentYCabin,
                                    lBKKSYDSegmentYCabin.getFullerKey());

    /**
     * Add the leg-cabin to the segment-cabin routing.
     *
     * As several leg-cabins may compose the segment-cabin routing,
     * and as the leg-cabin key is only made by a cabin code (which
     * is the same as for the segment-cabin), all the leg-cabins
     * composing the routing would have the same key.
     * Hence, the leg-cabins must be differentiated according to their
     * boarding point as well.
     */
    FacBomManager::addToListAndMap (lLHRSYDSegmentYCabin, lLHRLegYCabin,
                                    lLHRLegYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lLHRBKKSegmentYCabin, lLHRLegYCabin,
                                    lLHRLegYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lLHRSYDSegmentYCabin, lBKKLegYCabin,
                                    lBKKLegYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lBKKSYDSegmentYCabin, lBKKLegYCabin,
                                    lBKKLegYCabin.getFullerKey());


    // Step 0.7: fare family level
    // Create a FareFamily (1) for the Segment LHR-BKK, cabin Y on BA's Inv
    const FamilyCode_T l1 ("EcoSaver");
    FareFamilyKey l1FareFamilyKey (l1);

    FareFamily& lLHRBKKSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lLHRBKKSegmentYCabin,
                                    lLHRBKKSegmentYCabin1Family);
    FacBomManager::linkWithParent (lLHRBKKSegmentYCabin,
                                   lLHRBKKSegmentYCabin1Family);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("FareFamily: "
    //                   << lLHRBKKSegmentYCabin1Family.toString());

    // Create a FareFamily (1)  for the Segment BKK-SYD, cabin Y on BA's Inv
    FareFamily& lBKKSYDSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lBKKSYDSegmentYCabin,
                                    lBKKSYDSegmentYCabin1Family);
    FacBomManager::linkWithParent (lBKKSYDSegmentYCabin,
                                   lBKKSYDSegmentYCabin1Family);
    
    // Display the booking class
    // STDAIR_LOG_DEBUG ("FareFamily: "
    //                   << lLHRBKKSegmentYCabin1Family.toString());

    // Create a FareFamily (1)  for the Segment LHR-SYD, cabin Y on BA's Inv
    FareFamily& lLHRSYDSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lLHRSYDSegmentYCabin,
                                    lLHRSYDSegmentYCabin1Family);
    FacBomManager::linkWithParent (lLHRSYDSegmentYCabin,
                                   lLHRSYDSegmentYCabin1Family);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("FareFamily: "
    //                   << lLHRBKKSegmentYCabin1Family.toString());


    // Step 0.8: booking class level
    // Create a BookingClass (Q) for the Segment LHR-BKK, cabin Y,
    // fare family 1 on BA's Inv
    const ClassCode_T lQ ("Q");
    BookingClassKey lQBookingClassKey (lQ);

    BookingClass& lLHRBKKSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::addToListAndMap (lLHRBKKSegmentYCabin1Family,
                                    lLHRBKKSegmentYCabin1FamilyQClass);
    FacBomManager::linkWithParent (lLHRBKKSegmentYCabin1Family,
                                   lLHRBKKSegmentYCabin1FamilyQClass);

    FacBomManager::addToListAndMap (lLHRBKKSegmentYCabin,
                                    lLHRBKKSegmentYCabin1FamilyQClass);
    FacBomManager::addToListAndMap (lLHRBKKSegment,
                                    lLHRBKKSegmentYCabin1FamilyQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lLHRBKKSegmentYCabin1FamilyQClass.toString());

    // Create a BookingClass (Q) for the Segment BKK-SYD, cabin Y,
    // fare family 1 on BA's Inv
    BookingClass& lBKKSYDSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::addToListAndMap (lBKKSYDSegmentYCabin1Family,
                                    lBKKSYDSegmentYCabin1FamilyQClass);
    FacBomManager::linkWithParent (lBKKSYDSegmentYCabin1Family,
                                   lBKKSYDSegmentYCabin1FamilyQClass);
    
    FacBomManager::addToListAndMap (lBKKSYDSegmentYCabin,
                                    lBKKSYDSegmentYCabin1FamilyQClass);
    FacBomManager::addToListAndMap (lBKKSYDSegment,
                                    lBKKSYDSegmentYCabin1FamilyQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lLHRBKKSegmentYCabin1FamilyQClass.toString());

    // Create a BookingClass (Q) for the Segment LHR-SYD, cabin Y,
    // fare family 1 on BA's Inv
    BookingClass& lLHRSYDSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::addToListAndMap (lLHRSYDSegmentYCabin1Family,
                                    lLHRSYDSegmentYCabin1FamilyQClass);
    FacBomManager::linkWithParent (lLHRSYDSegmentYCabin1Family,
                                   lLHRSYDSegmentYCabin1FamilyQClass);

    FacBomManager::addToListAndMap (lLHRSYDSegmentYCabin,
                                    lLHRSYDSegmentYCabin1FamilyQClass);
    FacBomManager::addToListAndMap (lLHRSYDSegment,
                                    lLHRSYDSegmentYCabin1FamilyQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lLHRBKKSegmentYCabin1FamilyQClass.toString());

    
    // ////// AF ///////    
    // Step 0.2: Flight-date level
    // Create a FlightDate (AF084/20-MAR-2011) for AF's Inventory
    lFlightNumber = 84;
    lDate = Date_T (2011, 3, 20);
    lFlightDateKey = FlightDateKey (lFlightNumber, lDate);

    FlightDate& lAF084_20110320_FD =
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::addToListAndMap (lAFInv, lAF084_20110320_FD);
    FacBomManager::linkWithParent (lAFInv, lAF084_20110320_FD);
    
    // Display the flight-date
    // STDAIR_LOG_DEBUG ("FlightDate: " << lAF084_20110320_FD.toString());

    // Step 0.3: Segment-date level
    // Create a SegmentDate (CDG-SFO) for AF's Inventory
    const AirportCode_T lCDG ("CDG");
    const AirportCode_T lSFO ("SFO");
    const Duration_T l1040 (10, 40, 0);
    const Duration_T l1250 (12, 50, 0);
    const Duration_T l1110 (11, 10, 0);
    lSegmentDateKey = SegmentDateKey (lCDG, lSFO);

    SegmentDate& lCDGSFOSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lAF084_20110320_FD, lCDGSFOSegment);
    FacBomManager::linkWithParent (lAF084_20110320_FD, lCDGSFOSegment);

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
    lLegDateKey = LegDateKey (lCDG);

    LegDate& lCDGLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::addToListAndMap (lAF084_20110320_FD, lCDGLeg);
    FacBomManager::linkWithParent (lAF084_20110320_FD, lCDGLeg);

    // Fill the LegDate content
    lCDGLeg.setOffPoint (lSFO);
    lCDGLeg.setBoardingDate (lDate);
    lCDGLeg.setOffDate (lDate);
    lCDGLeg.setBoardingTime (l1040);
    lCDGLeg.setOffTime (l1250);
    lCDGLeg.setElapsedTime (l1110);

    // Display the leg-date
    // STDAIR_LOG_DEBUG ("LegDate: " << lCDGLeg.toString());

    // Link the segment-dates with the leg-dates
    FacBomManager::addToListAndMap (lCDGLeg, lCDGSFOSegment);
    FacBomManager::addToListAndMap (lCDGSFOSegment, lCDGLeg);


    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) for the Segment CDG-SFO of AF's Inventory
    SegmentCabin& lCDGSFOSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lCDGSFOSegment, lCDGSFOSegmentYCabin);
    FacBomManager::linkWithParent (lCDGSFOSegment, lCDGSFOSegmentYCabin);

    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lCDGSFOSegmentYCabin.toString());

    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) for the Leg CDG-SFO on AF's Inventory
    LegCabin& lCDGLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::addToListAndMap (lCDGLeg, lCDGLegYCabin);
    FacBomManager::linkWithParent (lCDGLeg, lCDGLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Link the segment-dates with the leg-dates
    FacBomManager::addToListAndMap (lCDGLegYCabin, lCDGSFOSegmentYCabin,
                                    lCDGSFOSegmentYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lCDGSFOSegmentYCabin, lCDGLegYCabin,
                                    lCDGLegYCabin.getFullerKey());


    // Step 0.7: fare family level
    // Create a fareFamily (1) for the Segment CDG-SFO, cabin Y on AF's Inv
    FareFamily& lCDGSFOSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lCDGSFOSegmentYCabin,
                                    lCDGSFOSegmentYCabin1Family);
    FacBomManager::linkWithParent (lCDGSFOSegmentYCabin,
                                   lCDGSFOSegmentYCabin1Family);

    // Display the fare family
    // STDAIR_LOG_DEBUG ("fareFamily: "
    //
    //                   << lCDGSFOSegmentYCabin1Family.toString());

    // Step 0.8: booking class level Create a BookingClass (Q) for the
    // Segment CDG-SFO, cabin Y, fare family 1 on AF's Inv
    BookingClass& lCDGSFOSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::addToListAndMap (lCDGSFOSegmentYCabin1Family,
                                    lCDGSFOSegmentYCabin1FamilyQClass);
    FacBomManager::linkWithParent (lCDGSFOSegmentYCabin1Family,
                                   lCDGSFOSegmentYCabin1FamilyQClass);

    FacBomManager::addToListAndMap (lCDGSFOSegmentYCabin,
                                    lCDGSFOSegmentYCabin1FamilyQClass);
    FacBomManager::addToListAndMap (lCDGSFOSegment,
                                    lCDGSFOSegmentYCabin1FamilyQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lCDGSFOSegmentYCabin1FamilyQClass.toString());
  }
  
  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildSampleBomForRMOL (BomRoot& ioBomRoot,
                                             const CabinCapacity_T& iCapacity) {
    // Inventory
    const InventoryKey lInventoryKey (DEFAULT_AIRLINE_CODE);
    Inventory& lInv = FacBom<Inventory>::instance().create (lInventoryKey);
    FacBomManager::addToListAndMap (ioBomRoot, lInv);
    FacBomManager::linkWithParent (ioBomRoot, lInv);

    // Flight-date
    FlightDateKey lFlightDateKey(DEFAULT_FLIGHT_NUMBER, DEFAULT_DEPARTURE_DATE);
    FlightDate& lFlightDate =
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::addToListAndMap (lInv, lFlightDate);
    FacBomManager::linkWithParent (lInv, lFlightDate);

    // Leg-date
    LegDateKey lLegDateKey (DEFAULT_ORIGIN);
    LegDate& lLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::addToListAndMap (lFlightDate, lLeg);
    FacBomManager::linkWithParent (lFlightDate, lLeg);

    // Fill the LegDate content
    lLeg.setOffPoint (DEFAULT_DESTINATION);
    lLeg.setBoardingDate (DEFAULT_DEPARTURE_DATE);
    lLeg.setOffDate (DEFAULT_DEPARTURE_DATE);
    lLeg.setBoardingTime (Duration_T (14, 0, 0));
    lLeg.setOffTime (Duration_T (16, 0, 0));
    lLeg.setElapsedTime (Duration_T (8, 0, 0));

    // Leg-cabin
    LegCabinKey lLegCabinKey (DEFAULT_CABIN_CODE);
    LegCabin& lLegCabin = FacBom<LegCabin>::instance().create (lLegCabinKey);
    FacBomManager::addToListAndMap (lLeg, lLegCabin);
    FacBomManager::linkWithParent (lLeg, lLegCabin);

    lLegCabin.setCapacities (iCapacity);
    lLegCabin.setAvailabilityPool (iCapacity);

    // Segment-date
    SegmentDateKey lSegmentDateKey (DEFAULT_ORIGIN, DEFAULT_DESTINATION);
    SegmentDate& lSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lFlightDate, lSegment);
    FacBomManager::linkWithParent (lFlightDate, lSegment);

    // Links between the segment-date and the leg-date
    FacBomManager::addToListAndMap (lLeg, lSegment);
    FacBomManager::addToListAndMap (lSegment, lLeg);

    // Fill the SegmentDate content
    lSegment.setBoardingDate (DEFAULT_DEPARTURE_DATE);
    lSegment.setOffDate (DEFAULT_DEPARTURE_DATE);
    lSegment.setBoardingTime (Duration_T (14, 0, 0));
    lSegment.setOffTime (Duration_T (16, 0, 0));
    lSegment.setElapsedTime (Duration_T (8, 0, 0));

    // Segment-cabin
    SegmentCabinKey lSegmentCabinKey (DEFAULT_CABIN_CODE);
    SegmentCabin& lSegmentCabin =
      FacBom<SegmentCabin>::instance().create (lSegmentCabinKey);
    FacBomManager::addToListAndMap (lSegment, lSegmentCabin);
    FacBomManager::linkWithParent (lSegment, lSegmentCabin);

    // Links between the segment-cabin and the leg-cabin
    FacBomManager::addToListAndMap (lLegCabin, lSegmentCabin,
                                    lSegmentCabin.getFullerKey());
    FacBomManager::addToListAndMap (lSegmentCabin, lLegCabin,
                                    lLegCabin.getFullerKey());

    // Create a FareFamily (1) for the Segment LHR-BKK, cabin Y on BA's Inv
    const FamilyCode_T l1 ("EcoSaver");
    FareFamilyKey l1FareFamilyKey (l1);

    FareFamily& lSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lSegmentCabin, lSegmentYCabin1Family);
    FacBomManager::linkWithParent (lSegmentCabin, lSegmentYCabin1Family);

    // Create a booking-class
    const ClassCode_T lQ ("Q");
    BookingClassKey lQBookingClassKey (lQ);

    BookingClass& lSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::addToListAndMap (lSegmentYCabin1Family,
                                    lSegmentYCabin1FamilyQClass);
    FacBomManager::linkWithParent (lSegmentYCabin1Family,
                                   lSegmentYCabin1FamilyQClass);

    FacBomManager::addToListAndMap (lSegmentCabin, lSegmentYCabin1FamilyQClass);
    FacBomManager::addToListAndMap (lSegment, lSegmentYCabin1FamilyQClass);
  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildSampleBomForFareQuoter (BomRoot& ioBomRoot) {

    // Set the airport-pair primary key.
    const AirportCode_T lLHR ("LHR");
    const AirportCode_T lSYD ("SYD");
    const AirportPairKey lAirportPairLHRSYDKey (lLHR, lSYD);
    
    // Create the AirportPairKey object and link it to the ioBomRoot object.
    AirportPair& lLHRSYDAirportPair =
      FacBom<AirportPair>::instance().create (lAirportPairLHRSYDKey);
    FacBomManager::addToListAndMap (ioBomRoot, lLHRSYDAirportPair);
    FacBomManager::linkWithParent (ioBomRoot, lLHRSYDAirportPair);

    // Set the fare date-period primary key.
    const Date_T lDateRangeStart (2011, 1, 15);
    const Date_T lDateRangeEnd (2011, 12, 31);
    const DatePeriod_T lDatePeriod (lDateRangeStart, lDateRangeEnd); 
    const DatePeriodKey lFareDatePeriodKey (lDatePeriod);

    // Create the DatePeriodKey object and link it to the PosChannel object.
    DatePeriod& lFareDatePeriod =
      FacBom<DatePeriod>::instance().create (lFareDatePeriodKey);
    FacBomManager::addToListAndMap (lLHRSYDAirportPair, lFareDatePeriod);
    FacBomManager::linkWithParent (lLHRSYDAirportPair, lFareDatePeriod);    

    // Set the point-of-sale-channel primary key.
    const CityCode_T& lPosLHR("LHR");
    const ChannelLabel_T& lChannelDN("DN");
    const PosChannelKey lPosLHRChannelDNKey (lPosLHR, lChannelDN);  

    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lPosLHRChannelDN =
      FacBom<PosChannel>::instance().create (lPosLHRChannelDNKey);
    FacBomManager::addToListAndMap (lFareDatePeriod, lPosLHRChannelDN);
    FacBomManager::linkWithParent (lFareDatePeriod, lPosLHRChannelDN);
   
    // Set the fare time-period primary key.
    const Duration_T l0000 (00, 00, 0);
    const Duration_T l2300 (23, 00, 0);
    const Time_T lTimeRangeStart (l0000);
    const Time_T lTimeRangeEnd (l2300);
    const TimePeriodKey lFareTimePeriodKey (lTimeRangeStart, lTimeRangeEnd);

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lFareTimePeriod =
      FacBom<TimePeriod>::instance().create (lFareTimePeriodKey);
    FacBomManager::addToListAndMap (lPosLHRChannelDN, lFareTimePeriod);
    FacBomManager::linkWithParent (lPosLHRChannelDN, lFareTimePeriod);        

    // Generate the FareRule
    const TripType_T lTripType ("RT");
    const DayDuration_T lAdvancePurchase (0);
    const SaturdayStay_T lSaturdayStay (true); 
    const ChangeFees_T lChangeFees (20.0);
    const NonRefundable_T lNonRefundable (true);
    const DayDuration_T lMinimumStay (0); 
    const FareFeaturesKey lFareFeaturesKey (lTripType, lAdvancePurchase,
                                            lSaturdayStay, lChangeFees,
                                            lNonRefundable, lMinimumStay);

    // Create the FareFeaturesKey and link it to the TimePeriod object.
    FareFeatures& lFareFeatures =
      FacBom<FareFeatures>::instance().create (lFareFeaturesKey);
    FacBomManager::addToListAndMap (lFareTimePeriod, lFareFeatures);
    FacBomManager::linkWithParent (lFareTimePeriod, lFareFeatures);        

    // Generate Segment Features and link them to their FareRule.
    AirlineCodeList_T lAirlineCodeList;
    lAirlineCodeList.push_back ("BA");
    ClassList_StringList_T lClassCodeList;
    lClassCodeList.push_back ("Y");
    const AirlineClassListKey lAirlineClassListKey (lAirlineCodeList,
                                                    lClassCodeList);

    // Create the AirlineClassListKey and link it to the FareFeatures object.
    // const Fare_T& lFare (900.0);
    AirlineClassList& lAirlineClassList =
      stdair::FacBom<AirlineClassList>::instance().create (lAirlineClassListKey);
    lAirlineClassList.setFare(900.0);
    FacBomManager::addToListAndMap (lFareFeatures, lAirlineClassList);
    FacBomManager::linkWithParent (lFareFeatures, lAirlineClassList);
  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildSampleBomForAirRAC (BomRoot& ioBomRoot) {

    // Set the airport-pair primary key.
    const AirportCode_T lLHR ("LHR");
    const AirportCode_T lSYD ("SYD");
    const AirportPairKey lAirportPairLHRSYDKey (lLHR, lSYD);
    
    // Create the AirportPairKey object and link it to the ioBomRoot object.
    AirportPair& lLHRSYDAirportPair =
      FacBom<AirportPair>::instance().create (lAirportPairLHRSYDKey);
    FacBomManager::addToListAndMap (ioBomRoot, lLHRSYDAirportPair);
    FacBomManager::linkWithParent (ioBomRoot, lLHRSYDAirportPair);

    // Set the point-of-sale-channel primary key.
    const CityCode_T& lPosLHR("LHR");
    const ChannelLabel_T& lChannelDN("DN");
    const PosChannelKey lPosLHRChannelDNKey (lPosLHR, lChannelDN);  

    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lPosLHRChannelDN =
      FacBom<PosChannel>::instance().create (lPosLHRChannelDNKey);
    FacBomManager::addToListAndMap (lLHRSYDAirportPair, lPosLHRChannelDN);
    FacBomManager::linkWithParent (lLHRSYDAirportPair, lPosLHRChannelDN);

    // Set the yield date-period primary key.
    const Date_T lDateRangeStart (2011, 1, 15);
    const Date_T lDateRangeEnd (2011, 12, 31);
    const DatePeriod_T lDatePeriod (lDateRangeStart, lDateRangeEnd); 
    const DatePeriodKey lYieldDatePeriodKey (lDatePeriod);

    // Create the DatePeriodKey object and link it to the PosChannel object.
    DatePeriod& lYieldDatePeriod =
      FacBom<DatePeriod>::instance().create (lYieldDatePeriodKey);
    FacBomManager::addToListAndMap (lPosLHRChannelDN, lYieldDatePeriod);
    FacBomManager::linkWithParent (lPosLHRChannelDN, lYieldDatePeriod);    
   
    // Set the yield time-period primary key.
    const Duration_T l0000 (00, 00, 0);
    const Duration_T l2300 (23, 00, 0);
    const Time_T lTimeRangeStart (l0000);
    const Time_T lTimeRangeEnd (l2300);
    const TimePeriodKey lYieldTimePeriodKey (lTimeRangeStart, lTimeRangeEnd);

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lYieldTimePeriod =
      FacBom<TimePeriod>::instance().create (lYieldTimePeriodKey);
    FacBomManager::addToListAndMap (lYieldDatePeriod, lYieldTimePeriod);
    FacBomManager::linkWithParent (lYieldDatePeriod, lYieldTimePeriod);        

    // Generate the YieldRule
    const CabinCode_T lCabinCode ("Y");
    const Yield_T lYield (900.0);
    const YieldFeaturesKey lYieldFeaturesKey (lCabinCode);

    // Create the YieldFeaturesKey and link it to the TimePeriod object.
    YieldFeatures& lYieldFeatures =
      FacBom<YieldFeatures>::instance().create (lYieldFeaturesKey);
    FacBomManager::addToListAndMap (lYieldTimePeriod, lYieldFeatures);
    FacBomManager::linkWithParent (lYieldTimePeriod, lYieldFeatures);     
                                              
    // Generate Segment Features and link them to their YieldRule.
    AirlineCodeList_T lAirlineCodeList;
    lAirlineCodeList.push_back ("BA");
    ClassList_StringList_T lClassCodeList;
    lClassCodeList.push_back ("Y");
    const AirlineClassListKey lAirlineClassListKey (lAirlineCodeList,
                                                    lClassCodeList);

    // Create the AirlineClassListKey and link it to the YieldFeatures object.
    AirlineClassList& lAirlineClassList =
      stdair::FacBom<AirlineClassList>::instance().create(lAirlineClassListKey);
    FacBomManager::addToListAndMap (lYieldFeatures, lAirlineClassList);
    FacBomManager::linkWithParent (lYieldFeatures, lAirlineClassList);
    lAirlineClassList.setYield (lYield);
  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::
  buildSampleTravelSolutionForPricing (TravelSolutionList_T& ioTravelSolutionList) {

    // Clean the list
    ioTravelSolutionList.clear();

    //
    const std::string lBA9_SegmentDateKey ("BA, 9, 2011-06-10, LHR, SYD, 21:45");

    // Add the segment date key to the travel solution
    TravelSolutionStruct lTS;
    lTS.addSegment (lBA9_SegmentDateKey);

    // Add the travel solution to the list
    ioTravelSolutionList.push_back (lTS);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::
  buildSampleTravelSolutions (TravelSolutionList_T& ioTravelSolutionList) {

    // Clean the list
    ioTravelSolutionList.clear();

    //
    const std::string lBA9_SegmentDateKey ("BA, 9, 2011-06-10, LHR, SYD, 21:45");

    // Add the segment date key to the travel solution
    TravelSolutionStruct lTS;
    lTS.addSegment (lBA9_SegmentDateKey);

    // Fare option
    const std::string lClassPath ("Q");
    const Fare_T lFare (900.0);
    const ChangeFees_T lChangeFee (20.0);
    const NonRefundable_T isRefundable (true);
    const SaturdayStay_T lSaturdayStay (true);
    const FareOptionStruct lFareOption (lClassPath, lFare, lChangeFee,
                                        isRefundable, lSaturdayStay);

    // Add (a copy of) the fare option
    lTS.addFareOption (lFareOption);

    // Map of class availabilities: set the availability for the Q
    // booking class (the one corresponding to the fare option) to 8.
    ClassAvailabilityMap_T lClassAvailabilityMap;
    const Availability_T lAvl (8);
    const bool hasInsertBeenSuccessful = lClassAvailabilityMap.
      insert (ClassAvailabilityMap_T::value_type (lClassPath, lAvl)).second;
    assert (hasInsertBeenSuccessful == true);
    // Add the map to the dedicated list held by the travel solution
    lTS.addClassAvailabilityMap (lClassAvailabilityMap);

    // Add the travel solution to the list
    ioTravelSolutionList.push_back (lTS);
  }

  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct CmdBomManager::buildSampleBookingRequest() {
    // Origin
    const AirportCode_T lOrigin ("LHR");

    // Destination
    const AirportCode_T lDestination ("SYD");

    // Point of Sale (POS)
    const AirportCode_T lPOS ("LHR");

    // Preferred departure date (10-JUN-2011)
    const Date_T lPreferredDepartureDate (2011, boost::gregorian::Jun, 10);

    // Preferred departure time (08:00)
    const Duration_T lPreferredDepartureTime (8, 0, 0);

    // Date of the request (15-MAY-2011)
    const Date_T lRequestDate (2011, boost::gregorian::May, 15);

    // Time of the request (10:00)
    const Duration_T lRequestTime (10, 0, 0);

    // Date-time of the request (made of the date and time above)
    const DateTime_T lRequestDateTime (lRequestDate, lRequestTime);

    // Preferred cabin (also named class of service sometimes)
    const CabinCode_T lPreferredCabin ("Eco");

    // Number of persons in the party
    const PartySize_T lPartySize (3);

    // Channel (direct/indirect, on-line/off-line)
    const ChannelLabel_T lChannel ("DN");

    // Type of the trip (one-way, inbound/outbound of a return trip)
    const TripType_T lTripType ("RI");

    // Duration of the stay (expressed as a number of days)
    const DayDuration_T lStayDuration (7);

    // Frequent flyer tier (member, silver, gold, platinum, senator, etc)
    const FrequentFlyer_T lFrequentFlyerType ("M");

    // Maximum willing-to-pay (WTP, expressed in monetary unit, e.g., EUR)
    const WTP_T lWTP (1000.0);

    // Value of time, for the customer (expressed in monetary unit per
    // unit of time, e.g., EUR/hour)
    const PriceValue_T lValueOfTime (100.0);

    // Creation of the booking request structure
    BookingRequestStruct oBookingRequest (lOrigin, lDestination, lPOS,
                                          lPreferredDepartureDate,
                                          lRequestDateTime,
                                          lPreferredCabin,
                                          lPartySize, lChannel,
                                          lTripType, lStayDuration,
                                          lFrequentFlyerType,
                                          lPreferredDepartureTime,
                                          lWTP, lValueOfTime);

    return oBookingRequest;
  }

  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct CmdBomManager::buildSampleBookingRequestForCRS() {
    // Origin
    const AirportCode_T lOrigin ("SIN");

    // Destination
    const AirportCode_T lDestination ("BKK");

    // Point of Sale (POS)
    const AirportCode_T lPOS ("SIN");

    // Preferred departure date (30-JAN-2010)
    const Date_T lPreferredDepartureDate (2010, boost::gregorian::Jan, 30);

    // Preferred departure time (10:00)
    const Duration_T lPreferredDepartureTime (10, 0, 0);

    // Date of the request (22-JAN-2010)
    const Date_T lRequestDate (2010, boost::gregorian::Jan, 22);

    // Time of the request (10:00)
    const Duration_T lRequestTime (10, 0, 0);

    // Date-time of the request (made of the date and time above)
    const DateTime_T lRequestDateTime (lRequestDate, lRequestTime);

    // Preferred cabin (also named class of service sometimes)
    const CabinCode_T lPreferredCabin ("Eco");

    // Number of persons in the party
    const PartySize_T lPartySize (3);

    // Channel (direct/indirect, on-line/off-line)
    const ChannelLabel_T lChannel ("IN");

    // Type of the trip (one-way, inbound/outbound of a return trip)
    const TripType_T lTripType ("RI");

    // Duration of the stay (expressed as a number of days)
    const DayDuration_T lStayDuration (7);

    // Frequent flyer tier (member, silver, gold, platinum, senator, etc)
    const FrequentFlyer_T lFrequentFlyerType ("M");

    // Maximum willing-to-pay (WTP, expressed in monetary unit, e.g., EUR)
    const WTP_T lWTP (1000.0);

    // Value of time, for the customer (expressed in monetary unit per
    // unit of time, e.g., EUR/hour)
    const PriceValue_T lValueOfTime (100.0);

    // Creation of the booking request structure
    BookingRequestStruct oBookingRequest (lOrigin, lDestination, lPOS,
                                          lPreferredDepartureDate,
                                          lRequestDateTime,
                                          lPreferredCabin,
                                          lPartySize, lChannel,
                                          lTripType, lStayDuration,
                                          lFrequentFlyerType,
                                          lPreferredDepartureTime,
                                          lWTP, lValueOfTime);

    return oBookingRequest;
  }

}

/*!
 * \endcode
 */
