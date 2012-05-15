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
#include <stdair/basic/BasConst_DefaultObject.hpp>
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomRetriever.hpp>
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
#include <stdair/bom/OnDDate.hpp>
#include <stdair/bom/SegmentPeriod.hpp>
#include <stdair/bom/FlightPeriod.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildSampleBom (BomRoot& ioBomRoot) {

    // DEBUG
    STDAIR_LOG_DEBUG ("StdAir is building the BOM tree from built-in "
                      << "specifications.");

    // ////// Basic Bom Tree ///////
    // Build the inventory (flight-dates) and the schedule (flight period) 
    // parts.
    buildSampleInventorySchedule (ioBomRoot);

    // Build the pricing (fare rules) and revenue accounting (yields) parts.
    buildSamplePricing (ioBomRoot);

    // ////// Partnership Bom Tree ///////    
    // Build the inventory (flight-dates) and the schedule (flight period) 
    // parts.
    buildPartnershipsSampleInventoryAndRM (ioBomRoot);

    // Build the pricing (fare rules) and revenue accounting (yields) parts.
    buildPartnershipsSamplePricing (ioBomRoot);

    // Build a dummy inventory, needed by RMOL.
    buildCompleteDummyInventory (ioBomRoot);

    // ////// Fare Families Bom Tree ///////
    // Build the inventory (flight-dates) and the schedule (flight period) 
    // parts with fare families.
    buildSampleInventoryScheduleForFareFamilies (ioBomRoot);
    
    // Build the pricing (fare rules) and revenue accounting (yields) parts.
    buildSamplePricingForFareFamilies (ioBomRoot);

    // Build a dummy inventory, needed by RMOL.
    buildCompleteDummyInventoryForFareFamilies (ioBomRoot);
  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildSampleInventorySchedule (BomRoot& ioBomRoot) {

    // Inventory
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

    // BA
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

    /*================================================================================
      ================================================================================
      ================================================================================*/
    // Schedule:
    // BA:
    // Step 1: flight period level
    // Create a flight period for BA9:
    const DoWStruct lDoWSrtuct ("1111111");
    const Date_T lBA9DateRangeStart (2010, boost::gregorian::Jun, 6);
    const Date_T lBA9DateRangeEnd (2010, boost::gregorian::Jun, 7);
    const DatePeriod_T lBA9DatePeriod (lBA9DateRangeStart, lBA9DateRangeEnd);
    const PeriodStruct lBA9PeriodStruct (lBA9DatePeriod, lDoWSrtuct);

    lFlightNumber = FlightNumber_T (9);

    FlightPeriodKey lBA9FlightPeriodKey (lFlightNumber, lBA9PeriodStruct);

    FlightPeriod& lBA9FlightPeriod =
      FacBom<FlightPeriod>::instance().create (lBA9FlightPeriodKey);
    FacBomManager::addToListAndMap (lBAInv, lBA9FlightPeriod);
    FacBomManager::linkWithParent (lBAInv, lBA9FlightPeriod);

    // Step 2: segment period level
    // Create a segment period for SIN-BKK:

    SegmentPeriodKey lLHRSYDSegmentPeriodKey (lLHR, lSYD);

    SegmentPeriod& lLHRSYDSegmentPeriod =
      FacBom<SegmentPeriod>::instance().create (lLHRSYDSegmentPeriodKey);
    FacBomManager::addToListAndMap (lBA9FlightPeriod, lLHRSYDSegmentPeriod);
    FacBomManager::linkWithParent (lBA9FlightPeriod, lLHRSYDSegmentPeriod);

    lLHRSYDSegmentPeriod.setBoardingTime (l2135);
    lLHRSYDSegmentPeriod.setOffTime (l1540);
    lLHRSYDSegmentPeriod.setElapsedTime (l1105);
    ClassList_String_T lYM ("YM");
    lLHRSYDSegmentPeriod.addCabinBookingClassList (lY,lYM);

    // AF:
    // Step 1: flight period level
    // Create a flight period for AF84:
    const Date_T lAF84DateRangeStart (2011, boost::gregorian::Mar, 20);
    const Date_T lAF84DateRangeEnd (2011, boost::gregorian::Mar, 21);
    const DatePeriod_T lAF84DatePeriod (lAF84DateRangeStart, lAF84DateRangeEnd);
    const PeriodStruct lAF84PeriodStruct (lAF84DatePeriod, lDoWSrtuct);

    lFlightNumber = FlightNumber_T (84);

    FlightPeriodKey lAF84FlightPeriodKey (lFlightNumber, lAF84PeriodStruct);

    FlightPeriod& lAF84FlightPeriod =
      FacBom<FlightPeriod>::instance().create (lAF84FlightPeriodKey);
    FacBomManager::addToListAndMap (lAFInv, lAF84FlightPeriod);
    FacBomManager::linkWithParent (lAFInv, lAF84FlightPeriod);

    // Step 2: segment period level
    // Create a segment period for SIN-BKK:

    SegmentPeriodKey lCDGSFOSegmentPeriodKey (lCDG, lSFO);

    SegmentPeriod& lCDGSFOSegmentPeriod =
      FacBom<SegmentPeriod>::instance().create (lCDGSFOSegmentPeriodKey);
    FacBomManager::addToListAndMap (lAF84FlightPeriod, lCDGSFOSegmentPeriod);
    FacBomManager::linkWithParent (lAF84FlightPeriod, lCDGSFOSegmentPeriod);

    lCDGSFOSegmentPeriod.setBoardingTime (l1040);
    lCDGSFOSegmentPeriod.setOffTime (l1250);
    lCDGSFOSegmentPeriod.setElapsedTime (l1110);
    lCDGSFOSegmentPeriod.addCabinBookingClassList (lY,lYM);

    /*================================================================================
      ================================================================================
      ================================================================================*/
    // O&D 
    // Create an O&D Date (BA;9,2010-Jun-06;LHR,SYD) for BA's Inventory
    OnDString_T  lBALHRSYDOnDStr = "BA;9,2010-Jun-06;LHR,SYD";
    OnDStringList_T lBAOnDStrList;
    lBAOnDStrList.push_back (lBALHRSYDOnDStr);

    OnDDateKey lBAOnDDateKey (lBAOnDStrList);
    OnDDate& lBA_LHRSYD_OnDDate =
      FacBom<OnDDate>::instance().create (lBAOnDDateKey);
    // Link to the inventory
    FacBomManager::addToListAndMap (lBAInv, lBA_LHRSYD_OnDDate);
    FacBomManager::linkWithParent (lBAInv, lBA_LHRSYD_OnDDate);

    // Add the segment
    FacBomManager::addToListAndMap (lBA_LHRSYD_OnDDate, lLHRSYDSegment);

    // Add total forecast info for cabin Y.
    const MeanStdDevPair_T lMean60StdDev6 (60.0, 6.0);
    const WTP_T lWTP750 = 750.0;
    const WTPDemandPair_T lWTP750Mean60StdDev6 (lWTP750, lMean60StdDev6);
    lBA_LHRSYD_OnDDate.setTotalForecast (lY, lWTP750Mean60StdDev6);

    // Create an O&D Date (AF;84,2011-Mar-21;CDG,SFO) for AF's Inventory
    OnDString_T lAFLHRSYDOnDStr = "AF;9,2011-Mar-20;CDG,SFO";
    OnDStringList_T lAFOnDStrList;
    lAFOnDStrList.push_back (lAFLHRSYDOnDStr);

    OnDDateKey lAFOnDDateKey (lAFOnDStrList);
    OnDDate& lAF_LHRSYD_OnDDate =
      FacBom<OnDDate>::instance().create (lAFOnDDateKey);
    // Link to the inventory
    FacBomManager::addToListAndMap (lAFInv, lAF_LHRSYD_OnDDate);
    FacBomManager::linkWithParent (lAFInv, lAF_LHRSYD_OnDDate);

    // Add the segment
    FacBomManager::addToListAndMap (lAF_LHRSYD_OnDDate, lLHRSYDSegment);

    // Add total forecast info for cabin Y. 
    lAF_LHRSYD_OnDDate.setTotalForecast (lY, lWTP750Mean60StdDev6);
    
  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::
  buildSampleInventoryScheduleForFareFamilies (BomRoot& ioBomRoot) {

    // Inventory
    // Step 0.1: Inventory level
    // Get the Inventory SQ (already built by construction)  
    const InventoryKey lSQKey ("SQ");
    Inventory& lSQInv = BomManager::getObject<Inventory>(ioBomRoot,
							 lSQKey.toString());

    // SQ
    // Step 0.2: Flight-date level
    // Create a FlightDate (SQ747/8-FEB-2010) for SQ's Inventory
    const FlightNumber_T lFlightNumber747 = 747;
    const Date_T lDate (2010, 2, 8);
    const FlightDateKey lFlightDateKey (lFlightNumber747, lDate);

    FlightDate& lSQ747_20100208_FD =
        FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::addToListAndMap (lSQInv, lSQ747_20100208_FD);
    FacBomManager::linkWithParent (lSQInv, lSQ747_20100208_FD);

    // Display the flight-date
    // STDAIR_LOG_DEBUG ("FlightDate: " << lSQ747_20100208_FD.toString());
    
    // Step 0.3: Segment-date level
    // Create a SegmentDate (SIN-BKK) for SQ's Inventory
    const AirportCode_T lSIN ("SIN");
    const AirportCode_T lBKK ("BKK");
    const Duration_T l0635 (6, 35, 0);
    const Duration_T l0800 (8, 0, 0);
    const Duration_T l0225 (2, 25, 0);
    const SegmentDateKey lSegmentDateKey (lSIN, lBKK);

    SegmentDate& lSINBKKSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lSQ747_20100208_FD, lSINBKKSegment);
    FacBomManager::linkWithParent (lSQ747_20100208_FD, lSINBKKSegment);

    // Fill the SegmentDate content
    lSINBKKSegment.setBoardingDate (lDate);
    lSINBKKSegment.setOffDate (lDate);
    lSINBKKSegment.setBoardingTime (l0635);
    lSINBKKSegment.setOffTime (l0800);
    lSINBKKSegment.setElapsedTime (l0225);
  
    // Display the segment-date
    // STDAIR_LOG_DEBUG ("SegmentDate: " << lSINBKKSegment);

    // Step 0.4: Leg-date level
    // Create a LegDate (SIN) for SQ's Inventory
    const LegDateKey lLegDateKey (lSIN);

    LegDate& lSINLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::addToListAndMap (lSQ747_20100208_FD, lSINLeg);
    FacBomManager::linkWithParent (lSQ747_20100208_FD, lSINLeg);

    // Fill the LegDate content
    lSINLeg.setOffPoint (lBKK);
    lSINLeg.setBoardingDate (lDate);
    lSINLeg.setOffDate (lDate);
    lSINLeg.setBoardingTime (l0635);
    lSINLeg.setOffTime (l0800);
    lSINLeg.setElapsedTime (l0225);

    // Display the leg-date
    // STDAIR_LOG_DEBUG ("LegDate: " << lSINLeg.toString());

    // Link the segment-dates with the leg-dates
    FacBomManager::addToListAndMap (lSINLeg, lSINBKKSegment);
    FacBomManager::addToListAndMap (lSINBKKSegment, lSINLeg);

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) for the Segment SIN-BKK of SQ's Inventory
    const CabinCode_T lY ("Y");
    const SegmentCabinKey lYSegmentCabinKey (lY);
    SegmentCabin& lSINBKKSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lSINBKKSegment, lSINBKKSegmentYCabin);
    FacBomManager::linkWithParent (lSINBKKSegment, lSINBKKSegmentYCabin);
    lSINBKKSegmentYCabin.activateFareFamily ();
    
    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lSINBKKSegmentYCabin.toString());

    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) for the Leg SIN-BKK on SQ's Inventory
    const LegCabinKey lYLegCabinKey (lY);
    LegCabin& lSINLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::addToListAndMap (lSINLeg, lSINLegYCabin);
    FacBomManager::linkWithParent (lSINLeg, lSINLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lSINLegYCabin.toString());

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
    FacBomManager::addToListAndMap (lSINLegYCabin, lSINBKKSegmentYCabin,
				    lSINBKKSegmentYCabin.getFullerKey());
    
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
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin, lSINLegYCabin,
				    lSINLegYCabin.getFullerKey());
   
    // Step 0.7: fare family level
    // Create a FareFamily (1) for the Segment SIN-BKK, cabin Y on SQ's Inv
    const FamilyCode_T l1 ("1");
    const FareFamilyKey l1FareFamilyKey (l1);
    FareFamily& lSINBKKSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin,
                                      lSINBKKSegmentYCabin1Family);
    FacBomManager::linkWithParent (lSINBKKSegmentYCabin,
				   lSINBKKSegmentYCabin1Family);
    
    // Display the booking class
    // STDAIR_LOG_DEBUG ("FareFamily: "
    //                   << lSINBKKSegmentYCabin1Family.toString());

    // Create a FareFamily (2) for the Segment SIN-BKK, cabin Y on SQ's Inv
    const FamilyCode_T l2 ("2");
    const FareFamilyKey l2FareFamilyKey (l2);
    FareFamily& lSINBKKSegmentYCabin2Family =
        FacBom<FareFamily>::instance().create (l2FareFamilyKey);
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin,
                                      lSINBKKSegmentYCabin2Family);
    FacBomManager::linkWithParent (lSINBKKSegmentYCabin,
				   lSINBKKSegmentYCabin2Family);
    
    // Display the booking class
    // STDAIR_LOG_DEBUG ("FareFamily: "
    //                   << lSINBKKSegmentYCabin2Family.toString());
   
    // Step 0.8: booking class level
    // Create a BookingClass (Y) for the Segment SIN-BKK, cabin Y,
    // fare family 2 on SQ's Inv
    const ClassCode_T lClassY ("Y");
    const BookingClassKey lYBookingClassKey (lClassY);
    BookingClass& lSINBKKSegmentYCabin2FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin2Family,
				    lSINBKKSegmentYCabin2FamilyYClass);
    FacBomManager::linkWithParent (lSINBKKSegmentYCabin2Family,
				   lSINBKKSegmentYCabin2FamilyYClass);

    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin,
				    lSINBKKSegmentYCabin2FamilyYClass);
    FacBomManager::addToListAndMap (lSINBKKSegment,
				    lSINBKKSegmentYCabin2FamilyYClass);
    lSINBKKSegmentYCabin2FamilyYClass.setYield(1200);
    
    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lSINBKKSegmentYCabin2FamilyYClass.toString());
    
    // Create a BookingClass (B) for the Segment SIN-BKK, cabin Y,
    // fare family 2 on SQ's Inv
    const ClassCode_T lB ("B");
    const BookingClassKey lBBookingClassKey (lB);
    BookingClass& lSINBKKSegmentYCabin2FamilyBClass =
      FacBom<BookingClass>::instance().create (lBBookingClassKey);
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin2Family,
				    lSINBKKSegmentYCabin2FamilyBClass);
    FacBomManager::linkWithParent (lSINBKKSegmentYCabin2Family,
				   lSINBKKSegmentYCabin2FamilyBClass);

    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin,
				    lSINBKKSegmentYCabin2FamilyBClass);
    FacBomManager::addToListAndMap (lSINBKKSegment,
				    lSINBKKSegmentYCabin2FamilyBClass);
    lSINBKKSegmentYCabin2FamilyBClass.setYield(800);
    
    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lSINBKKSegmentYCabin2FamilyBClass.toString());

    // Create a BookingClass (M) for the Segment SIN-BKK, cabin Y,
    // fare family 1 on SQ's Inv
    const ClassCode_T lM ("M");
    const BookingClassKey lMBookingClassKey (lM);
    BookingClass& lSINBKKSegmentYCabin1FamilyMClass =
      FacBom<BookingClass>::instance().create (lMBookingClassKey);
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin1Family,
				    lSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::linkWithParent (lSINBKKSegmentYCabin1Family,
				   lSINBKKSegmentYCabin1FamilyMClass);

    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin,
				    lSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::addToListAndMap (lSINBKKSegment,
				    lSINBKKSegmentYCabin1FamilyMClass);
    lSINBKKSegmentYCabin1FamilyMClass.setYield(900);
    
    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lSINBKKSegmentYCabin1FamilyMClass.toString());
   
    // Create a BookingClass (Q) for the Segment SIN-BKK, cabin Y,
    // fare family 1 on SQ's Inv
    const ClassCode_T lQ ("Q");
    const BookingClassKey lQBookingClassKey (lQ);
    BookingClass& lSINBKKSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin1Family,
				    lSINBKKSegmentYCabin1FamilyQClass);
    FacBomManager::linkWithParent (lSINBKKSegmentYCabin1Family,
				   lSINBKKSegmentYCabin1FamilyQClass);

    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin,
				    lSINBKKSegmentYCabin1FamilyQClass);
    FacBomManager::addToListAndMap (lSINBKKSegment,
				    lSINBKKSegmentYCabin1FamilyQClass);
    lSINBKKSegmentYCabin1FamilyQClass.setYield(600);

  
    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lSINBKKSegmentYCabin1FamilyQClass.toString());

    /*================================================================================
      ================================================================================
      ================================================================================*/
    // Schedule:
    // SQ:
    // Step 1: flight period level
    // Create a flight period for SQ747:
    const DoWStruct lDoWSrtuct ("1111111");
    const Date_T lSQ747DateRangeStart (2010, boost::gregorian::Feb, 8);
    const Date_T lSQ747DateRangeEnd (2010, boost::gregorian::Feb, 9);
    const DatePeriod_T lSQ747DatePeriod (lSQ747DateRangeStart, 
					 lSQ747DateRangeEnd);
    const PeriodStruct lSQ747PeriodStruct (lSQ747DatePeriod, lDoWSrtuct);

    const FlightPeriodKey lSQ747FlightPeriodKey (lFlightNumber747, 
					   lSQ747PeriodStruct);
    FlightPeriod& lSQ747FlightPeriod =
      FacBom<FlightPeriod>::instance().create (lSQ747FlightPeriodKey);
    FacBomManager::addToListAndMap (lSQInv, lSQ747FlightPeriod);
    FacBomManager::linkWithParent (lSQInv, lSQ747FlightPeriod);

    // Step 2: segment period level
    // Create a segment period for SIN-BKK:

    const SegmentPeriodKey lSINBKKSegmentPeriodKey (lSIN, lBKK);
    SegmentPeriod& lSINBKKSegmentPeriod =
      FacBom<SegmentPeriod>::instance().create (lSINBKKSegmentPeriodKey);
    FacBomManager::addToListAndMap (lSQ747FlightPeriod, lSINBKKSegmentPeriod);
    FacBomManager::linkWithParent (lSQ747FlightPeriod, lSINBKKSegmentPeriod);
     
    ClassList_String_T lYBMQ  ("YBMQ");
    lSINBKKSegmentPeriod.addCabinBookingClassList (lY,lYBMQ);
    lSINBKKSegmentPeriod.setBoardingTime (l0635);
    lSINBKKSegmentPeriod.setOffTime (l0800);
    lSINBKKSegmentPeriod.setElapsedTime (l0225);

    /*================================================================================
      ================================================================================
      ================================================================================*/
    // O&D 
    // Create an O&D Date (SQ;747,2011-Feb-14;SIN,BKK) for SQ's Inventory
    const OnDString_T lSQSINBKKOnDStr = "SQ;747,2011-Feb-14;SIN,BKK";
    OnDStringList_T lSQOnDStrList;
    lSQOnDStrList.push_back (lSQSINBKKOnDStr);

    const OnDDateKey lSQOnDDateKey (lSQOnDStrList);
    OnDDate& lSQ_SINBKK_OnDDate =
      FacBom<OnDDate>::instance().create (lSQOnDDateKey);
    // Link to the inventory
    FacBomManager::addToListAndMap (lSQInv, lSQ_SINBKK_OnDDate);
    FacBomManager::linkWithParent (lSQInv, lSQ_SINBKK_OnDDate);
    // Add total forecast info for cabin Y.
    const MeanStdDevPair_T lMean120StdDev12 (120.0, 12.0);
    const WTP_T lWTP1000 = 1000.0;
    const WTPDemandPair_T lWTP1000Mean120StdDev12 (lWTP1000, lMean120StdDev12);
    lSQ_SINBKK_OnDDate.setTotalForecast (lY, lWTP1000Mean120StdDev12);
 
    // Add the segment
    FacBomManager::addToListAndMap (lSQ_SINBKK_OnDDate, lSINBKKSegment);
  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildCompleteDummyInventory  (BomRoot& ioBomRoot) {

    // Build a dummy inventory, containing a dummy flight-date with a
    // single segment-cabin and a single leg-cabin.
    const CabinCapacity_T lCapacity = DEFAULT_CABIN_CAPACITY;
    buildDummyInventory (ioBomRoot, lCapacity);

    // Retrieve the (sample) segment-cabin.
    SegmentCabin& lDummySegmentCabin =
      BomRetriever::retrieveDummySegmentCabin (ioBomRoot);
    
    // Retrieve the (sample) leg-cabin.
    LegCabin& lDummyLegCabin =
      BomRetriever::retrieveDummyLegCabin (ioBomRoot);

    // Add some booking classes to the dummy segment-cabin and some
    // virtual ones to the dummy leg-cabin.
    // First booking class yield and demand information.
    Yield_T lYield = 100;
    MeanValue_T lMean = 20;
    StdDevValue_T lStdDev= 9;
    BookingClassKey lBCKey (DEFAULT_CLASS_CODE);

    BookingClass& lDummyBookingClass =
      FacBom<BookingClass>::instance().create (lBCKey);
    lDummyBookingClass.setYield (lYield);
    lDummyBookingClass.setMean (lMean);
    lDummyBookingClass.setStdDev (lStdDev);
    // Add a booking class to the segment-cabin.
    FacBomManager::addToList (lDummySegmentCabin, lDummyBookingClass);
    BookingClassList_T lDummyBookingClassList;
    lDummyBookingClassList.push_back(&lDummyBookingClass);

    VirtualClassStruct lDummyVirtualClass (lDummyBookingClassList);
    lDummyVirtualClass.setYield (lYield);
    lDummyVirtualClass.setMean (lMean);
    lDummyVirtualClass.setStdDev (lStdDev);
    // Add the corresponding virtual class to the leg-cabin.
    lDummyLegCabin.addVirtualClass (lDummyVirtualClass);

    // Second booking class yield and demand information.
    lYield = 70;
    lMean = 45;
    lStdDev= 12;
    lDummyBookingClass.setYield (lYield);
    lDummyBookingClass.setMean (lMean);
    lDummyBookingClass.setStdDev (lStdDev);
    // Add a booking class to the segment-cabin.
    FacBomManager::addToList (lDummySegmentCabin, lDummyBookingClass);

    lDummyVirtualClass.setYield (lYield);
    lDummyVirtualClass.setMean (lMean);
    lDummyVirtualClass.setStdDev (lStdDev);
    // Add the corresponding virtual class to the leg-cabin.
    lDummyLegCabin.addVirtualClass (lDummyVirtualClass);
    
    // Third booking class yield and demand information.
    lYield = 42;
    lMean = 80;
    lStdDev= 16;
    lDummyBookingClass.setYield (lYield);
    lDummyBookingClass.setMean (lMean);
    lDummyBookingClass.setStdDev (lStdDev);
    // Add a booking class to the segment-cabin.
    FacBomManager::addToList (lDummySegmentCabin, lDummyBookingClass);

    lDummyVirtualClass.setYield (lYield);
    lDummyVirtualClass.setMean (lMean);
    lDummyVirtualClass.setStdDev (lStdDev);
    // Add the corresponding virtual class to the leg-cabin.
    lDummyLegCabin.addVirtualClass (lDummyVirtualClass);
    
  }
  
  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildDummyInventory (BomRoot& ioBomRoot,
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

    /*================================================================================
      ================================================================================
      ================================================================================*/
    // Schedule:
    // XX:
    // Step 1: flight period level
    // Create a flight period for XX:
    const DoWStruct lDoWSrtuct ("1111111");
    const Date_T lXXDateRangeStart (DEFAULT_DEPARTURE_DATE);
    const Date_T lXXDateRangeEnd (DEFAULT_DEPARTURE_DATE);
    const DatePeriod_T lXXDatePeriod (lXXDateRangeStart, lXXDateRangeEnd);
    const PeriodStruct lXXPeriodStruct (lXXDatePeriod, lDoWSrtuct);

    FlightPeriodKey lXXFlightPeriodKey (DEFAULT_FLIGHT_NUMBER, lXXPeriodStruct);

    FlightPeriod& lXXFlightPeriod =
      FacBom<FlightPeriod>::instance().create (lXXFlightPeriodKey);
    FacBomManager::addToListAndMap (lInv, lXXFlightPeriod);
    FacBomManager::linkWithParent (lInv, lXXFlightPeriod);

    // Step 2: segment period level
    // Create a segment period 

    SegmentPeriodKey lXXSegmentPeriodKey (DEFAULT_ORIGIN, DEFAULT_DESTINATION);

    SegmentPeriod& lXXSegmentPeriod =
      FacBom<SegmentPeriod>::instance().create (lXXSegmentPeriodKey);
    FacBomManager::addToListAndMap (lXXFlightPeriod, lXXSegmentPeriod);
    FacBomManager::linkWithParent (lXXFlightPeriod, lXXSegmentPeriod);

    lXXSegmentPeriod.setBoardingTime (Duration_T (14, 0, 0));
    lXXSegmentPeriod.setOffTime (Duration_T (16, 0, 0));
    lXXSegmentPeriod.setElapsedTime (Duration_T (8, 0, 0));
    const CabinCode_T lY ("Y");
    const ClassList_String_T lYQ ("YQ");
    lXXSegmentPeriod.addCabinBookingClassList (lY,lYQ);


  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::
  buildCompleteDummyInventoryForFareFamilies (BomRoot& ioBomRoot) {

    // Build a dummy inventory, containing a dummy flight-date with a
    // single segment-cabin and a single leg-cabin (for fare families 
    // algorithms)

    // Get the default Inventory object (already built in by construction)
    const InventoryKey lInventoryKey (DEFAULT_AIRLINE_CODE);
    Inventory& lInv = BomManager::getObject<Inventory>(ioBomRoot,
                                                  lInventoryKey.toString());

    // Create a dummy Flight-date
    const FlightDateKey lFlightDateKey(DEFAULT_FLIGHT_NUMBER_FF, 
				       DEFAULT_DEPARTURE_DATE);
    FlightDate& lFlightDate = 
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::addToListAndMap (lInv, lFlightDate);
    FacBomManager::linkWithParent (lInv, lFlightDate);

    // Create a dummy Leg-date
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

    // Create a dummy Leg-cabin
    const LegCabinKey lLegCabinKey (DEFAULT_CABIN_CODE);
    LegCabin& lLegCabin = FacBom<LegCabin>::instance().create (lLegCabinKey);
    FacBomManager::addToListAndMap (lLeg, lLegCabin);
    FacBomManager::linkWithParent (lLeg, lLegCabin);
    const CabinCapacity_T lCapacity = DEFAULT_CABIN_CAPACITY;
    lLegCabin.setCapacities (lCapacity);
    lLegCabin.setAvailabilityPool (lCapacity);

    // Create a dummy Segment-date
    const SegmentDateKey lSegmentDateKey (DEFAULT_ORIGIN, DEFAULT_DESTINATION);
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

    // Create a dummy Segment-cabin
    const SegmentCabinKey lSegmentCabinKey (DEFAULT_CABIN_CODE);
    SegmentCabin& lSegmentCabin =
      FacBom<SegmentCabin>::instance().create (lSegmentCabinKey);
    FacBomManager::addToListAndMap (lSegment, lSegmentCabin);
    FacBomManager::linkWithParent (lSegment, lSegmentCabin);

    // Links between the segment-cabin and the leg-cabin
    FacBomManager::addToListAndMap (lLegCabin, lSegmentCabin,
                                    lSegmentCabin.getFullerKey());
    FacBomManager::addToListAndMap (lSegmentCabin, lLegCabin,
                                    lLegCabin.getFullerKey());

    // Create a dummy FareFamily (FF1) 
    const FamilyCode_T l1 ("FF1");
    const FareFamilyKey l1FareFamilyKey (l1);

    FareFamily& lSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    // Set the forecasted demand
    // TODO change the size (hard code)
    MeanStdDevPairVector_T lDemandVector1FareFamily;
    const unsigned int size = 16;
    for (unsigned int idx = 0; idx < size; ++idx) {
      double i = static_cast<double> (idx);
      MeanStdDevPair_T lMeanStdDevPair (i/4.0, i/20.0);
      lDemandVector1FareFamily.push_back(lMeanStdDevPair);
    }
    lSegmentYCabin1Family.setMeanStdDev(lDemandVector1FareFamily);
    FacBomManager::addToListAndMap (lSegmentCabin, lSegmentYCabin1Family);
    FacBomManager::linkWithParent (lSegmentCabin, lSegmentYCabin1Family);

    // Create a dummy booking-class
    const ClassCode_T lY ("Y");
    const BookingClassKey lYBookingClassKey (lY);

    BookingClass& lSegmentYCabin1FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    Yield_T lYield = 1000;
    lSegmentYCabin1FamilyYClass.setYield(lYield);
    FacBomManager::addToListAndMap (lSegmentYCabin1Family,
                                    lSegmentYCabin1FamilyYClass);
    FacBomManager::linkWithParent (lSegmentYCabin1Family,
                                   lSegmentYCabin1FamilyYClass);
    
    FacBomManager::addToListAndMap (lSegmentCabin, lSegmentYCabin1FamilyYClass);
    FacBomManager::addToListAndMap (lSegment, lSegmentYCabin1FamilyYClass);

    // Create a second dummy booking-class
    const ClassCode_T lU ("U");
    const BookingClassKey lUBookingClassKey (lU);

    BookingClass& lSegmentYCabin1FamilyUClass =
      FacBom<BookingClass>::instance().create (lUBookingClassKey);
    lYield = 600;
    lSegmentYCabin1FamilyUClass.setYield(lYield);
    FacBomManager::addToListAndMap (lSegmentYCabin1Family,
                                    lSegmentYCabin1FamilyUClass);
    FacBomManager::linkWithParent (lSegmentYCabin1Family,
                                   lSegmentYCabin1FamilyUClass);
    
    FacBomManager::addToListAndMap (lSegmentCabin, lSegmentYCabin1FamilyUClass);
    FacBomManager::addToListAndMap (lSegment, lSegmentYCabin1FamilyUClass);

    // Create a second dummy FareFamily (2) 
    const FamilyCode_T l2 ("FF2");
    const FareFamilyKey l2FareFamilyKey (l2);

    FareFamily& lSegmentYCabin2Family =
      FacBom<FareFamily>::instance().create (l2FareFamilyKey);
    // Set the forecasted demand
    // TODO change the size (hard code)
    MeanStdDevPairVector_T lDemandVector2FareFamily;
    for (unsigned int idx = 0; idx < size; ++idx) {
      double i = static_cast<double> (idx);
      MeanStdDevPair_T lMeanStdDevPair (i/2.0, i/10.0);
      lDemandVector2FareFamily.push_back(lMeanStdDevPair);
    }
    lSegmentYCabin2Family.setMeanStdDev(lDemandVector2FareFamily);

    FacBomManager::addToListAndMap (lSegmentCabin, lSegmentYCabin2Family);
    FacBomManager::linkWithParent (lSegmentCabin, lSegmentYCabin2Family);

    // Create a third dummy booking-class
    const ClassCode_T lO ("O");
    const BookingClassKey lOBookingClassKey (lO);

    BookingClass& lSegmentYCabin2FamilyOClass =
      FacBom<BookingClass>::instance().create (lOBookingClassKey);
    lYield = 750;
    lSegmentYCabin2FamilyOClass.setYield(lYield);
    FacBomManager::addToListAndMap (lSegmentYCabin2Family,
                                    lSegmentYCabin2FamilyOClass);
    FacBomManager::linkWithParent (lSegmentYCabin2Family,
                                   lSegmentYCabin2FamilyOClass);
    
    FacBomManager::addToListAndMap (lSegmentCabin, lSegmentYCabin2FamilyOClass);
    FacBomManager::addToListAndMap (lSegment, lSegmentYCabin2FamilyOClass);

     // Create a fourth dummy booking-class
    const ClassCode_T lQ ("Q");
    const BookingClassKey lQBookingClassKey (lQ);

    BookingClass& lSegmentYCabin2FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    lYield = 400;
    lSegmentYCabin2FamilyQClass.setYield(lYield);
    FacBomManager::addToListAndMap (lSegmentYCabin2Family,
                                    lSegmentYCabin2FamilyQClass);
    FacBomManager::linkWithParent (lSegmentYCabin2Family,
                                   lSegmentYCabin2FamilyQClass);
    
    FacBomManager::addToListAndMap (lSegmentCabin, lSegmentYCabin2FamilyQClass);
    FacBomManager::addToListAndMap (lSegment, lSegmentYCabin2FamilyQClass);


    /*================================================================================
      ================================================================================
      ================================================================================*/
    // Schedule:
    // XX:
    // Step 1: flight period level
    // Create a flight period for XX:
    const DoWStruct lDoWSrtuct ("1111111");
    const Date_T lXXDateRangeStart (DEFAULT_DEPARTURE_DATE);
    const Date_T lXXDateRangeEnd (DEFAULT_DEPARTURE_DATE);
    const DatePeriod_T lXXDatePeriod (lXXDateRangeStart, lXXDateRangeEnd);
    const PeriodStruct lXXPeriodStruct (lXXDatePeriod, lDoWSrtuct);

    const FlightPeriodKey lXXFlightPeriodKey (DEFAULT_FLIGHT_NUMBER_FF, 
					      lXXPeriodStruct);

    FlightPeriod& lXXFlightPeriod =
      FacBom<FlightPeriod>::instance().create (lXXFlightPeriodKey);
    FacBomManager::addToListAndMap (lInv, lXXFlightPeriod);
    FacBomManager::linkWithParent (lInv, lXXFlightPeriod);

    // Step 2: segment period level
    // Create a segment period 
    const SegmentPeriodKey lXXSegmentPeriodKey (DEFAULT_ORIGIN, 
						DEFAULT_DESTINATION);

    SegmentPeriod& lXXSegmentPeriod =
      FacBom<SegmentPeriod>::instance().create (lXXSegmentPeriodKey);
    FacBomManager::addToListAndMap (lXXFlightPeriod, lXXSegmentPeriod);
    FacBomManager::linkWithParent (lXXFlightPeriod, lXXSegmentPeriod);

    lXXSegmentPeriod.setBoardingTime (Duration_T (14, 0, 0));
    lXXSegmentPeriod.setOffTime (Duration_T (16, 0, 0));
    lXXSegmentPeriod.setElapsedTime (Duration_T (8, 0, 0));
    const CabinCode_T lYCabin ("Y");
    const ClassList_String_T lYUOQ ("YUOQ");
    lXXSegmentPeriod.addCabinBookingClassList (lYCabin,lYUOQ);

  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildSamplePricing (BomRoot& ioBomRoot) {

    // Set the airport-pair primary key.
    const AirportPairKey lAirportPairKey (AIRPORT_LHR, AIRPORT_SYD);
    
    // Create the AirportPairKey object and link it to the BOM tree root.
    AirportPair& lAirportPair =
      FacBom<AirportPair>::instance().create (lAirportPairKey);
    FacBomManager::addToListAndMap (ioBomRoot, lAirportPair);
    FacBomManager::linkWithParent (ioBomRoot, lAirportPair);

    // Set the fare date-period primary key.
    const Date_T lDateRangeStart (2011, boost::gregorian::Jan, 15);
    const Date_T lDateRangeEnd (2011, boost::gregorian::Dec, 31);
    const DatePeriod_T lDateRange (lDateRangeStart, lDateRangeEnd);
    const DatePeriodKey lDatePeriodKey (lDateRange);

    // Create the DatePeriodKey object and link it to the PosChannel object.
    DatePeriod& lDatePeriod =
      FacBom<DatePeriod>::instance().create (lDatePeriodKey);
    FacBomManager::addToListAndMap (lAirportPair, lDatePeriod);
    FacBomManager::linkWithParent (lAirportPair, lDatePeriod);    

    // Set the point-of-sale-channel primary key.
    const PosChannelKey lPosChannelKey (POS_LHR, CHANNEL_DN);  
    
    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lPosChannel =
      FacBom<PosChannel>::instance().create (lPosChannelKey);
    FacBomManager::addToListAndMap (lDatePeriod, lPosChannel);
    FacBomManager::linkWithParent (lDatePeriod, lPosChannel);
   
    // Set the fare time-period primary key.
    const Time_T lTimeRangeStart (0, 0, 0);
    const Time_T lTimeRangeEnd (23, 0, 0);
    const TimePeriodKey lTimePeriodKey (lTimeRangeStart, lTimeRangeEnd);

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lTimePeriod =
      FacBom<TimePeriod>::instance().create (lTimePeriodKey);
    FacBomManager::addToListAndMap (lPosChannel, lTimePeriod);
    FacBomManager::linkWithParent (lPosChannel, lTimePeriod);        

    // Pricing -- Generate the FareRule
    const FareFeaturesKey lFareFeaturesKey (TRIP_TYPE_ROUND_TRIP,
                                            NO_ADVANCE_PURCHASE,
                                            SATURDAY_STAY,
                                            CHANGE_FEES,
                                            NON_REFUNDABLE,
                                            NO_STAY_DURATION);

    // Create the FareFeaturesKey and link it to the TimePeriod object.
    FareFeatures& lFareFeatures =
      FacBom<FareFeatures>::instance().create (lFareFeaturesKey);
    FacBomManager::addToListAndMap (lTimePeriod, lFareFeatures);
    FacBomManager::linkWithParent (lTimePeriod, lFareFeatures);        

    // Revenue Accounting -- Generate the YieldRule
    const YieldFeaturesKey lYieldFeaturesKey (TRIP_TYPE_ROUND_TRIP,
                                              CABIN_Y);
    
    // Create the YieldFeaturesKey and link it to the TimePeriod object.
    YieldFeatures& lYieldFeatures =
      FacBom<YieldFeatures>::instance().create (lYieldFeaturesKey);
    FacBomManager::addToListAndMap (lTimePeriod, lYieldFeatures);
    FacBomManager::linkWithParent (lTimePeriod, lYieldFeatures);     
                                              
    // Generate Segment Features and link them to their respective
    // fare and yield rules.
    AirlineCodeList_T lAirlineCodeList;
    lAirlineCodeList.push_back (AIRLINE_CODE_BA);
    ClassList_StringList_T lClassCodeList;
    lClassCodeList.push_back (CLASS_CODE_Y);
    const AirlineClassListKey lAirlineClassListKey (lAirlineCodeList,
                                                    lClassCodeList);

    // Create the AirlineClassList
    AirlineClassList& lAirlineClassList =
      FacBom<AirlineClassList>::instance().create (lAirlineClassListKey);
    // Link the AirlineClassList to the FareFeatures object
    lAirlineClassList.setFare (900);
    FacBomManager::addToListAndMap (lFareFeatures, lAirlineClassList);
    FacBomManager::linkWithParent (lFareFeatures, lAirlineClassList);

    // Link the AirlineClassList to the YieldFeatures object
    lAirlineClassList.setYield (900);
    FacBomManager::addToListAndMap (lYieldFeatures, lAirlineClassList);
    // \todo (gsabatier): the following calls overrides the parent for
    //       lAirlineClassList. Check that it is what is actually wanted.
    FacBomManager::linkWithParent (lYieldFeatures, lAirlineClassList);
  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildSamplePricingForFareFamilies (BomRoot& ioBomRoot) {

    // Get the airport-pair primary key SIN-BKK
    // (already built by construction)
    const AirportPairKey lAirportPairKey ("SIN", "BKK");
    AirportPair& lAirportPair =
      BomManager::getObject<AirportPair>(ioBomRoot, lAirportPairKey.toString());

    // Set the fare date-period primary key.
    const Date_T lDateRangeStart (2010, boost::gregorian::Feb, 1);
    const Date_T lDateRangeEnd (2011, boost::gregorian::Feb, 15);
    const DatePeriod_T lDateRange (lDateRangeStart, lDateRangeEnd);
    const DatePeriodKey lDatePeriodKey (lDateRange);

    // Create the DatePeriodKey object and link it to the PosChannel object.
    DatePeriod& lDatePeriod =
      FacBom<DatePeriod>::instance().create (lDatePeriodKey);
    FacBomManager::addToListAndMap (lAirportPair, lDatePeriod);
    FacBomManager::linkWithParent (lAirportPair, lDatePeriod);  

    // Set the point-of-sale-channel primary key.
    const PosChannelKey lPosChannelKey ("SIN", CHANNEL_IN);  
    
    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lPosChannel =
      FacBom<PosChannel>::instance().create (lPosChannelKey);
    FacBomManager::addToListAndMap (lDatePeriod, lPosChannel);
    FacBomManager::linkWithParent (lDatePeriod, lPosChannel);

    // Set the fare time-period primary key.
    const Time_T lTimeRangeStart (0, 0, 0);
    const Time_T lTimeRangeEnd (23, 0, 0);
    const TimePeriodKey lTimePeriodKey (lTimeRangeStart, lTimeRangeEnd);

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lTimePeriod =
      FacBom<TimePeriod>::instance().create (lTimePeriodKey);
    FacBomManager::addToListAndMap (lPosChannel, lTimePeriod);
    FacBomManager::linkWithParent (lPosChannel, lTimePeriod);        

    // Pricing -- Generate the FareRule
    const DayDuration_T ONE_MONTH_ADVANCE_PURCHASE = 30;
    // Generate the first FareFeatures for the class Q 
    const FareFeaturesKey lFareFeaturesQKey (TRIP_TYPE_ONE_WAY,
                                            ONE_MONTH_ADVANCE_PURCHASE,
                                            SATURDAY_STAY,
                                            CHANGE_FEES,
                                            NON_REFUNDABLE,
                                            NO_STAY_DURATION);

    // Create the FareFeaturesKey and link it to the TimePeriod object.
    FareFeatures& lFareFeaturesQ =
      FacBom<FareFeatures>::instance().create (lFareFeaturesQKey);
    FacBomManager::addToListAndMap (lTimePeriod, lFareFeaturesQ);
    FacBomManager::linkWithParent (lTimePeriod, lFareFeaturesQ);

    // Generate the second FareFeatures for the class M 
    const FareFeaturesKey lFareFeaturesMKey (TRIP_TYPE_ONE_WAY,
                                            NO_ADVANCE_PURCHASE,
                                            SATURDAY_STAY,
                                            CHANGE_FEES,
                                            NON_REFUNDABLE,
                                            NO_STAY_DURATION);

    // Create the FareFeaturesKey and link it to the TimePeriod object.
    FareFeatures& lFareFeaturesM =
      FacBom<FareFeatures>::instance().create (lFareFeaturesMKey);
    FacBomManager::addToListAndMap (lTimePeriod, lFareFeaturesM);
    FacBomManager::linkWithParent (lTimePeriod, lFareFeaturesM); 

    // Generate the third FareFeatures for the class B
    const FareFeaturesKey lFareFeaturesBKey (TRIP_TYPE_ONE_WAY,
					     ONE_MONTH_ADVANCE_PURCHASE,
					     SATURDAY_STAY,
					     NO_CHANGE_FEES,
					     NO_NON_REFUNDABLE,//Refundable
					     NO_STAY_DURATION);

    // Create the FareFeaturesKey and link it to the TimePeriod object.
    FareFeatures& lFareFeaturesB =
      FacBom<FareFeatures>::instance().create (lFareFeaturesBKey);
    FacBomManager::addToListAndMap (lTimePeriod, lFareFeaturesB);
    FacBomManager::linkWithParent (lTimePeriod, lFareFeaturesB);       

    // Generate the fourth FareFeatures for the class Y
    const FareFeaturesKey lFareFeaturesYKey (TRIP_TYPE_ONE_WAY,
                                            NO_ADVANCE_PURCHASE,
                                            SATURDAY_STAY,
                                            NO_CHANGE_FEES,
                                            NO_NON_REFUNDABLE,//Refundable
                                            NO_STAY_DURATION);

    // Create the FareFeaturesKey and link it to the TimePeriod object.
    FareFeatures& lFareFeaturesY =
      FacBom<FareFeatures>::instance().create (lFareFeaturesYKey);
    FacBomManager::addToListAndMap (lTimePeriod, lFareFeaturesY);
    FacBomManager::linkWithParent (lTimePeriod, lFareFeaturesY);
  
    // Revenue Accounting -- Generate the YieldRule
    const YieldFeaturesKey lYieldFeaturesKey (TRIP_TYPE_ONE_WAY,
                                              CABIN_Y);

    // Create the YieldFeaturesKey and link it to the TimePeriod object.
    YieldFeatures& lYieldFeatures =
      FacBom<YieldFeatures>::instance().create (lYieldFeaturesKey);
    FacBomManager::addToListAndMap (lTimePeriod, lYieldFeatures);
    FacBomManager::linkWithParent (lTimePeriod, lYieldFeatures);
                                  
    // Generate Segment Features and link them to their respective
    // fare and yield rules.
    AirlineCodeList_T lAirlineCodeList;
    lAirlineCodeList.push_back ("SQ");

    ClassList_StringList_T lClassYList;
    lClassYList.push_back (CLASS_CODE_Y);
    const AirlineClassListKey lAirlineClassYListKey (lAirlineCodeList,
                                                    lClassYList);
    
    // Create the AirlineClassList
    AirlineClassList& lAirlineClassYList =
        FacBom<AirlineClassList>::instance().create (lAirlineClassYListKey);
    // Link the AirlineClassList to the FareFeatures object
    FacBomManager::addToListAndMap (lFareFeaturesY, lAirlineClassYList);
    FacBomManager::linkWithParent (lFareFeaturesY, lAirlineClassYList);
    lAirlineClassYList.setFare (1200);    
    lAirlineClassYList.setYield (1200);

    // Link the AirlineClassList to the YieldFeatures object
    FacBomManager::addToListAndMap (lYieldFeatures, lAirlineClassYList);
    // \todo (gsabatier): the following calls overrides the parent for
    //       lAirlineClassList. Check that it is what is actually wanted.
    FacBomManager::linkWithParent (lYieldFeatures, lAirlineClassYList);

    ClassList_StringList_T lClassBList;
    lClassBList.push_back ("B");
    const AirlineClassListKey lAirlineClassBListKey (lAirlineCodeList,
                                                     lClassBList);
    // Create the AirlineClassList
    AirlineClassList& lAirlineClassBList =
      FacBom<AirlineClassList>::instance().create (lAirlineClassBListKey);
    // Link the AirlineClassList to the FareFeatures object
    FacBomManager::addToListAndMap (lFareFeaturesB, lAirlineClassBList);
    FacBomManager::linkWithParent (lFareFeaturesB, lAirlineClassBList);
    lAirlineClassBList.setFare (800); 
    lAirlineClassBList.setYield (800);
  
    // Link the AirlineClassList to the YieldFeatures object
    FacBomManager::addToListAndMap (lYieldFeatures, lAirlineClassBList);
    // \todo (gsabatier): the following calls overrides the parent for
    //       lAirlineClassList. Check that it is what is actually wanted.
    FacBomManager::linkWithParent (lYieldFeatures, lAirlineClassBList);

    ClassList_StringList_T lClassMList;
    lClassMList.push_back ("M");
    const AirlineClassListKey lAirlineClassMListKey (lAirlineCodeList,
                                                    lClassMList);

    // Create the AirlineClassList
    AirlineClassList& lAirlineClassMList =
      FacBom<AirlineClassList>::instance().create (lAirlineClassMListKey);
    // Link the AirlineClassList to the FareFeatures object
    FacBomManager::addToListAndMap (lFareFeaturesM, lAirlineClassMList);
    FacBomManager::linkWithParent (lFareFeaturesM, lAirlineClassMList);
    lAirlineClassMList.setFare (900);   
    lAirlineClassMList.setYield (900);

    // Link the AirlineClassList to the YieldFeatures object
    FacBomManager::addToListAndMap (lYieldFeatures, lAirlineClassMList);
    // \todo (gsabatier): the following calls overrides the parent for
    //       lAirlineClassList. Check that it is what is actually wanted.
    FacBomManager::linkWithParent (lYieldFeatures, lAirlineClassMList);

    ClassList_StringList_T lClassQList;
    lClassQList.push_back ("Q");
    const AirlineClassListKey lAirlineClassQListKey (lAirlineCodeList,
						     lClassQList);

    // Create the AirlineClassList
    AirlineClassList& lAirlineClassQList =
      FacBom<AirlineClassList>::instance().create (lAirlineClassQListKey);
    // Link the AirlineClassList to the FareFeatures object
    FacBomManager::addToListAndMap (lFareFeaturesQ, lAirlineClassQList);
    FacBomManager::linkWithParent (lFareFeaturesQ, lAirlineClassQList);
    lAirlineClassQList.setFare (600);  
    lAirlineClassQList.setYield (600);
    
    // Link the AirlineClassList to the YieldFeatures object
    FacBomManager::addToListAndMap (lYieldFeatures, lAirlineClassQList);
    // \todo (gsabatier): the following calls overrides the parent for
    //       lAirlineClassList. Check that it is what is actually wanted.
    FacBomManager::linkWithParent (lYieldFeatures, lAirlineClassQList);
	
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
    const ClassCode_T lClassPath (CLASS_CODE_Q);
    const Fare_T lFare (900);
    const ChangeFees_T lChangeFee (CHANGE_FEES);
    const NonRefundable_T isNonRefundable (NON_REFUNDABLE);
    const SaturdayStay_T lSaturdayStay (SATURDAY_STAY);
    const FareOptionStruct lFareOption (lClassPath, lFare, lChangeFee,
                                        isNonRefundable, lSaturdayStay);

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
    const AirportCode_T lOrigin (AIRPORT_LHR);

    // Destination
    const AirportCode_T lDestination (AIRPORT_SYD);

    // Point of Sale (POS)
    const CityCode_T lPOS (POS_LHR);

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
    const CabinCode_T lPreferredCabin (CABIN_ECO);

    // Number of persons in the party
    const PartySize_T lPartySize (3);

    // Channel (direct/indirect, on-line/off-line)
    const ChannelLabel_T lChannel (CHANNEL_DN);

    // Type of the trip (one-way, inbound/outbound of a return trip)
    const TripType_T lTripType (TRIP_TYPE_INBOUND);

    // Duration of the stay (expressed as a number of days)
    const DayDuration_T lStayDuration (DEFAULT_STAY_DURATION);

    // Frequent flyer tier (member, silver, gold, platinum, senator, etc)
    const FrequentFlyer_T lFrequentFlyerType (FREQUENT_FLYER_MEMBER);

    // Maximum willing-to-pay (WTP, expressed in monetary unit, e.g., EUR)
    const WTP_T lWTP (DEFAULT_WTP);

    // Value of time, for the customer (expressed in monetary unit per
    // unit of time, e.g., EUR/hour)
    const PriceValue_T lValueOfTime (DEFAULT_VALUE_OF_TIME);

    // Restrictions
    const ChangeFees_T lChangeFees = true;
    const NonRefundable_T lNonRefundable = true;

    // Creation of the booking request structure
    BookingRequestStruct oBookingRequest (lOrigin, lDestination, lPOS,
                                          lPreferredDepartureDate,
                                          lRequestDateTime,
                                          lPreferredCabin,
                                          lPartySize, lChannel,
                                          lTripType, lStayDuration,
                                          lFrequentFlyerType,
                                          lPreferredDepartureTime,
                                          lWTP, lValueOfTime,
                                          lChangeFees, lNonRefundable);

    return oBookingRequest;
  }

  // //////////////////////////////////////////////////////////////////////
  BookingRequestStruct CmdBomManager::buildSampleBookingRequestForCRS() {
    // Origin
    const AirportCode_T lOrigin (AIRPORT_SIN);

    // Destination
    const AirportCode_T lDestination (AIRPORT_BKK);

    // Point of Sale (POS)
    const CityCode_T lPOS (POS_SIN);

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
    const CabinCode_T lPreferredCabin (CABIN_ECO);

    // Number of persons in the party
    const PartySize_T lPartySize (3);

    // Channel (direct/indirect, on-line/off-line)
    const ChannelLabel_T lChannel (CHANNEL_IN);

    // Type of the trip (one-way, inbound/outbound of a return trip)
    const TripType_T lTripType (TRIP_TYPE_INBOUND);

    // Duration of the stay (expressed as a number of days)
    const DayDuration_T lStayDuration (DEFAULT_STAY_DURATION);

    // Frequent flyer tier (member, silver, gold, platinum, senator, etc)
    const FrequentFlyer_T lFrequentFlyerType (FREQUENT_FLYER_MEMBER);

    // Maximum willing-to-pay (WTP, expressed in monetary unit, e.g., EUR)
    const WTP_T lWTP (DEFAULT_WTP);

    // Value of time, for the customer (expressed in monetary unit per
    // unit of time, e.g., EUR/hour)
    const PriceValue_T lValueOfTime (DEFAULT_VALUE_OF_TIME);

    // Restrictions
    const ChangeFees_T lChangeFees = true;
    const NonRefundable_T lNonRefundable = true;
    
    // Creation of the booking request structure
    BookingRequestStruct oBookingRequest (lOrigin,
                                          lDestination,
                                          lPOS,
                                          lPreferredDepartureDate,
                                          lRequestDateTime,
                                          lPreferredCabin,
                                          lPartySize, lChannel,
                                          lTripType, lStayDuration,
                                          lFrequentFlyerType,
                                          lPreferredDepartureTime,
                                          lWTP, lValueOfTime,
                                          lChangeFees, lNonRefundable);

    return oBookingRequest;
  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::
  buildPartnershipsSampleInventoryAndRM (BomRoot& ioBomRoot) {

    // Step 0.1: Inventory level
    // Create an Inventory for SQ
    const InventoryKey lSQKey ("SQ");
    Inventory& lSQInv = FacBom<Inventory>::instance().create (lSQKey);
    FacBomManager::addToListAndMap (ioBomRoot, lSQInv);
    FacBomManager::linkWithParent (ioBomRoot, lSQInv);
    
    // Create an Inventory for CX
    const InventoryKey lCXKey ("CX");
    Inventory& lCXInv = FacBom<Inventory>::instance().create (lCXKey);
    FacBomManager::addToListAndMap (ioBomRoot, lCXInv);
    FacBomManager::linkWithParent (ioBomRoot, lCXInv);
    
    // ////// SQ ///////    
    // Step 0.2: Flight-date level
    // Create a FlightDate (SQ11/08-FEB-2010) for SQ's Inventory
    FlightNumber_T lFlightNumber = 11;
    Date_T lDate (2010, 2, 8);
    FlightDateKey lFlightDateKey (lFlightNumber, lDate);

    FlightDate& lSQ11_20100208_FD =
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::addToListAndMap (lSQInv, lSQ11_20100208_FD);
    FacBomManager::linkWithParent (lSQInv, lSQ11_20100208_FD);

    // Create a (mkt) FlightDate (SQ1200/08-FEB-2010) for SQ's Inventory
    FlightNumber_T lMktFlightNumber = 1200;
    //lDate = Date_T (2010, 2, 8);
    FlightDateKey lMktFlightDateKey (lMktFlightNumber, lDate);

    FlightDate& lSQ1200_20100208_FD =
      FacBom<FlightDate>::instance().create (lMktFlightDateKey);
    FacBomManager::addToListAndMap (lSQInv, lSQ1200_20100208_FD);
    FacBomManager::linkWithParent (lSQInv, lSQ1200_20100208_FD);
    
    // Display the flight-date
    // STDAIR_LOG_DEBUG ("FlightDate: " << lBA9_20110610_FD.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (SIN-BKK) for SQ's Inventory
    const AirportCode_T lSIN ("SIN");
    const AirportCode_T lBKK ("BKK");
    const DateOffset_T l1Day (1);
    const DateOffset_T l2Days (2);
    const Duration_T l0820 (8, 20, 0);
    const Duration_T l1100 (11, 0, 0);
    const Duration_T l0340 (3, 40, 0);
    SegmentDateKey lSegmentDateKey (lSIN, lBKK);

    SegmentDate& lSINBKKSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lSQ11_20100208_FD, lSINBKKSegment);
    FacBomManager::linkWithParent (lSQ11_20100208_FD, lSINBKKSegment);

    // Fill the SegmentDate content
    lSINBKKSegment.setBoardingDate (lDate);
    lSINBKKSegment.setOffDate (lDate);
    lSINBKKSegment.setBoardingTime (l0820);
    lSINBKKSegment.setOffTime (l1100);
    lSINBKKSegment.setElapsedTime (l0340);

    // Create a second (mkt) SegmentDate (BKK-HKG) for SQ's Inventory
    const AirportCode_T lHKG ("HKG");
    const Duration_T l1200 (12, 0, 0);
    const Duration_T l1540 (15, 40, 0);
    const Duration_T l0240 (2, 40, 0);
    SegmentDateKey lMktSegmentDateKey (lBKK, lHKG);

    SegmentDate& lMktBKKHKGSegment =
      FacBom<SegmentDate>::instance().create (lMktSegmentDateKey);
    FacBomManager::addToListAndMap (lSQ1200_20100208_FD, lMktBKKHKGSegment);
    FacBomManager::linkWithParent (lSQ1200_20100208_FD, lMktBKKHKGSegment);

    // Fill the (mkt) SegmentDate content
    lMktBKKHKGSegment.setBoardingDate (lDate);
    lMktBKKHKGSegment.setOffDate (lDate);
    lMktBKKHKGSegment.setBoardingTime (l1200);
    lMktBKKHKGSegment.setOffTime (l1540);
    lMktBKKHKGSegment.setElapsedTime (l0240);

    // Step 0.4: Leg-date level
    // Create a first LegDate (SIN) for SQ's Inventory
    LegDateKey lLegDateKey (lSIN);

    LegDate& lSINLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::addToListAndMap (lSQ11_20100208_FD, lSINLeg);
    FacBomManager::linkWithParent (lSQ11_20100208_FD, lSINLeg);

    // Fill the LegDate content
    lSINLeg.setOffPoint (lBKK);
    lSINLeg.setBoardingDate (lDate);
    lSINLeg.setOffDate (lDate);
    lSINLeg.setBoardingTime (l0820);
    lSINLeg.setOffTime (l1100);
    lSINLeg.setElapsedTime (l0340);

    
    // Link the segment-dates with the leg-dates
    FacBomManager::addToListAndMap (lSINLeg, lSINBKKSegment);  
    FacBomManager::addToListAndMap (lSINBKKSegment, lSINLeg);

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) for the Segment SIN-BKK of SQ's Inventory
    const CabinCode_T lY ("Y");
    SegmentCabinKey lYSegmentCabinKey (lY);

    SegmentCabin& lSINBKKSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lSINBKKSegment, lSINBKKSegmentYCabin);
    FacBomManager::linkWithParent (lSINBKKSegment, lSINBKKSegmentYCabin);

    // Create a SegmentCabin (Y) for the (mkt) Segment BKK-HKG of SQ's Inventory
    SegmentCabin& lMktBKKHKGSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lMktBKKHKGSegment, lMktBKKHKGSegmentYCabin);
    FacBomManager::linkWithParent (lMktBKKHKGSegment, lMktBKKHKGSegmentYCabin);


    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) for the Leg SIN-BKK on SQ's Inventory
    LegCabinKey lYLegCabinKey (lY);

    LegCabin& lSINLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::addToListAndMap (lSINLeg, lSINLegYCabin);
    FacBomManager::linkWithParent (lSINLeg, lSINLegYCabin);

    CabinCapacity_T lCapacity (100);
    lSINLegYCabin.setCapacities (lCapacity);
    lSINLegYCabin.setAvailabilityPool (lCapacity);
    
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
    
    FacBomManager::addToListAndMap (lSINLegYCabin, lSINBKKSegmentYCabin,
                                    lSINBKKSegmentYCabin.getFullerKey());
    
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
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin, lSINLegYCabin,
                                    lSINLegYCabin.getFullerKey());

    // Step 0.7: fare family level
    // Create a FareFamily (1) for the Segment SIN-BKK, cabin Y on SQ's Inv
    const FamilyCode_T l1 ("EcoSaver");
    FareFamilyKey l1FareFamilyKey (l1);

    FareFamily& lSINBKKSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin,
                                    lSINBKKSegmentYCabin1Family);
    FacBomManager::linkWithParent (lSINBKKSegmentYCabin,
                                   lSINBKKSegmentYCabin1Family);

    // Create a FareFamily (1) for the (mkt) Segment BKK-HKG, cabin Y on SQ's Inv
    FareFamily& lMktBKKHKGSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lMktBKKHKGSegmentYCabin,
                                    lMktBKKHKGSegmentYCabin1Family);
    FacBomManager::linkWithParent (lMktBKKHKGSegmentYCabin,
                                    lMktBKKHKGSegmentYCabin1Family);
    
    // Step 0.8: booking class level
    // Create a BookingClass (Y) for the Segment SIN-BKK, cabin Y,
    // fare family 1 on SQ's Inv
    BookingClassKey lYBookingClassKey (lY);

    BookingClass& lSINBKKSegmentYCabin1FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin1Family,
                                    lSINBKKSegmentYCabin1FamilyYClass);
    FacBomManager::linkWithParent (lSINBKKSegmentYCabin1Family,
                                   lSINBKKSegmentYCabin1FamilyYClass);

    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin,
                                    lSINBKKSegmentYCabin1FamilyYClass);
    FacBomManager::addToListAndMap (lSINBKKSegment,
                                    lSINBKKSegmentYCabin1FamilyYClass);

    lSINBKKSegmentYCabin1FamilyYClass.setYield(700);

    // Create a BookingClass (Y) for the (mkt) Segment BKK-HKG, cabin Y,
    // fare family 1 on SQ's Inv
    BookingClass& lMktBKKHKGSegmentYCabin1FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    FacBomManager::addToListAndMap (lMktBKKHKGSegmentYCabin1Family,
                                    lMktBKKHKGSegmentYCabin1FamilyYClass);
    FacBomManager::linkWithParent (lMktBKKHKGSegmentYCabin1Family,
                                   lMktBKKHKGSegmentYCabin1FamilyYClass);

    FacBomManager::addToListAndMap (lMktBKKHKGSegmentYCabin,
                                    lMktBKKHKGSegmentYCabin1FamilyYClass);
    FacBomManager::addToListAndMap (lMktBKKHKGSegment,
                                    lMktBKKHKGSegmentYCabin1FamilyYClass);

    lMktBKKHKGSegmentYCabin1FamilyYClass.setYield(700);

   
    // Create a BookingClass (M) for the Segment SIN-BKK, cabin Y,
    // fare family 1 on SQ's Inv
    const ClassCode_T lM ("M");
    BookingClassKey lMBookingClassKey (lM);

    BookingClass& lSINBKKSegmentYCabin1FamilyMClass =
      FacBom<BookingClass>::instance().create (lMBookingClassKey);
    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin1Family,
                                    lSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::linkWithParent (lSINBKKSegmentYCabin1Family,
                                   lSINBKKSegmentYCabin1FamilyMClass);

    FacBomManager::addToListAndMap (lSINBKKSegmentYCabin,
                                    lSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::addToListAndMap (lSINBKKSegment,
                                    lSINBKKSegmentYCabin1FamilyMClass);

    lSINBKKSegmentYCabin1FamilyMClass.setYield(500);

    // Create a BookingClass (M) for the (mkt) Segment BKK-HKG, cabin Y,
    // fare family 1 on SQ's Inv
    BookingClass& lMktBKKHKGSegmentYCabin1FamilyMClass =
      FacBom<BookingClass>::instance().create (lMBookingClassKey);
    FacBomManager::addToListAndMap (lMktBKKHKGSegmentYCabin1Family,
                                    lMktBKKHKGSegmentYCabin1FamilyMClass);
    FacBomManager::linkWithParent (lMktBKKHKGSegmentYCabin1Family,
                                   lMktBKKHKGSegmentYCabin1FamilyMClass);

    FacBomManager::addToListAndMap (lMktBKKHKGSegmentYCabin,
                                    lMktBKKHKGSegmentYCabin1FamilyMClass);
    FacBomManager::addToListAndMap (lMktBKKHKGSegment,
                                    lMktBKKHKGSegmentYCabin1FamilyMClass);

    lMktBKKHKGSegmentYCabin1FamilyMClass.setYield(500);

    /* =================================================================================== */
    // Step 0.9: Partner Inventory
    // Create a partner Inventory CX for SQ    
    const InventoryKey lPartnerCXKey ("CX");
    Inventory& lPartnerCXInv = FacBom<Inventory>::instance().create (lPartnerCXKey);
    FacBomManager::addToListAndMap (lSQInv, lPartnerCXInv);
    FacBomManager::linkWithParent (lSQInv, lPartnerCXInv);

    // Step 0.9.2 : Flight-date level
    lFlightNumber = 12;
    lFlightDateKey = FlightDateKey (lFlightNumber, lDate);

    FlightDate& lPartnerCX12_20100208_FD =
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::addToListAndMap (lPartnerCXInv, lPartnerCX12_20100208_FD);
    FacBomManager::linkWithParent (lPartnerCXInv, lPartnerCX12_20100208_FD);

    lFlightNumber = 1100;
    lMktFlightDateKey = FlightDateKey (lFlightNumber, lDate);

    FlightDate& lPartnerCX1100_20100208_FD =
      FacBom<FlightDate>::instance().create (lMktFlightDateKey);
    FacBomManager::addToListAndMap (lPartnerCXInv, lPartnerCX1100_20100208_FD);
    FacBomManager::linkWithParent (lPartnerCXInv, lPartnerCX1100_20100208_FD);

    // Step 0.9.3: Segment-date level
    lSegmentDateKey = SegmentDateKey (lBKK, lHKG);

    SegmentDate& lPartnerBKKHKGSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lPartnerCX12_20100208_FD, 
				    lPartnerBKKHKGSegment);
    FacBomManager::linkWithParent (lPartnerCX12_20100208_FD, 
				   lPartnerBKKHKGSegment);

    lPartnerBKKHKGSegment.setBoardingDate (lDate);
    lPartnerBKKHKGSegment.setOffDate (lDate);
    lPartnerBKKHKGSegment.setBoardingTime (l1200);
    lPartnerBKKHKGSegment.setOffTime (l1540);
    lPartnerBKKHKGSegment.setElapsedTime (l0240);

    lMktSegmentDateKey = SegmentDateKey (lSIN, lBKK);

    SegmentDate& lPartnerMktSINBKKSegment =
      FacBom<SegmentDate>::instance().create (lMktSegmentDateKey);
    FacBomManager::addToListAndMap (lPartnerCX1100_20100208_FD, 
				    lPartnerMktSINBKKSegment);
    FacBomManager::linkWithParent (lPartnerCX1100_20100208_FD, 
				   lPartnerMktSINBKKSegment);

    lPartnerMktSINBKKSegment.setBoardingDate (lDate);
    lPartnerMktSINBKKSegment.setOffDate (lDate);
    lPartnerMktSINBKKSegment.setBoardingTime (l0820);
    lPartnerMktSINBKKSegment.setOffTime (l1100);
    lPartnerMktSINBKKSegment.setElapsedTime (l0340);

    // Step 0.9.4: Leg-date level
    lLegDateKey = LegDateKey (lBKK);

    LegDate& lPartnerBKKLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::addToListAndMap (lPartnerCX12_20100208_FD, lPartnerBKKLeg);
    FacBomManager::linkWithParent (lPartnerCX12_20100208_FD, lPartnerBKKLeg);

    lPartnerBKKLeg.setOffPoint (lHKG);
    lPartnerBKKLeg.setBoardingDate (lDate);
    lPartnerBKKLeg.setOffDate (lDate);
    lPartnerBKKLeg.setBoardingTime (l1200);
    lPartnerBKKLeg.setOffTime (l1540);
    lPartnerBKKLeg.setElapsedTime (l0240);

    FacBomManager::addToListAndMap (lPartnerBKKLeg, lPartnerBKKHKGSegment);
    FacBomManager::addToListAndMap (lPartnerBKKHKGSegment, lPartnerBKKLeg);

    // Step 9.0.5: segment-cabin level
    
    SegmentCabin& lPartnerBKKHKGSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lPartnerBKKHKGSegment, 
				    lPartnerBKKHKGSegmentYCabin);
    FacBomManager::linkWithParent (lPartnerBKKHKGSegment, 
				   lPartnerBKKHKGSegmentYCabin);

    SegmentCabin& lPartnerMktSINBKKSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lPartnerMktSINBKKSegment, 
				    lPartnerMktSINBKKSegmentYCabin);
    FacBomManager::linkWithParent (lPartnerMktSINBKKSegment, 
				   lPartnerMktSINBKKSegmentYCabin);

    // Step 9.0.6: leg-cabin level
    
    LegCabin& lPartnerBKKLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::addToListAndMap (lPartnerBKKLeg, lPartnerBKKLegYCabin);
    FacBomManager::linkWithParent (lPartnerBKKLeg, lPartnerBKKLegYCabin);

    lCapacity = CabinCapacity_T(999);
    lPartnerBKKLegYCabin.setCapacities (lCapacity);
    lPartnerBKKLegYCabin.setAvailabilityPool (lCapacity);

    FacBomManager::addToListAndMap (lPartnerBKKLegYCabin, 
				    lPartnerBKKHKGSegmentYCabin,
                                    lPartnerBKKHKGSegmentYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lPartnerBKKHKGSegmentYCabin, 
				    lPartnerBKKLegYCabin,
                                    lPartnerBKKLegYCabin.getFullerKey());

    // Step 9.0.7: fare family level
    
    FareFamily& lPartnerBKKHKGSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lPartnerBKKHKGSegmentYCabin,
                                    lPartnerBKKHKGSegmentYCabin1Family);
    FacBomManager::linkWithParent (lPartnerBKKHKGSegmentYCabin,
                                   lPartnerBKKHKGSegmentYCabin1Family);

    FareFamily& lPartnerMktSINBKKSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lPartnerMktSINBKKSegmentYCabin,
                                    lPartnerMktSINBKKSegmentYCabin1Family);
    FacBomManager::linkWithParent (lPartnerMktSINBKKSegmentYCabin,
                                   lPartnerMktSINBKKSegmentYCabin1Family);

    // Step 9.0.8: booking class level

    BookingClass& lPartnerBKKHKGSegmentYCabin1FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    FacBomManager::addToListAndMap (lPartnerBKKHKGSegmentYCabin1Family,
                                    lPartnerBKKHKGSegmentYCabin1FamilyYClass);
    FacBomManager::linkWithParent (lPartnerBKKHKGSegmentYCabin1Family,
                                   lPartnerBKKHKGSegmentYCabin1FamilyYClass);

    FacBomManager::addToListAndMap (lPartnerBKKHKGSegmentYCabin,
                                    lPartnerBKKHKGSegmentYCabin1FamilyYClass);
    FacBomManager::addToListAndMap (lPartnerBKKHKGSegment,
                                    lPartnerBKKHKGSegmentYCabin1FamilyYClass);

    BookingClass& lPartnerMktSINBKKSegmentYCabin1FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    FacBomManager::addToListAndMap (lPartnerMktSINBKKSegmentYCabin1Family,
                                    lPartnerMktSINBKKSegmentYCabin1FamilyYClass);
    FacBomManager::linkWithParent (lPartnerMktSINBKKSegmentYCabin1Family,
                                   lPartnerMktSINBKKSegmentYCabin1FamilyYClass);

    FacBomManager::addToListAndMap (lPartnerMktSINBKKSegmentYCabin,
                                    lPartnerMktSINBKKSegmentYCabin1FamilyYClass);
    FacBomManager::addToListAndMap (lPartnerMktSINBKKSegment,
                                    lPartnerMktSINBKKSegmentYCabin1FamilyYClass);
    
    BookingClass& lPartnerBKKHKGSegmentYCabin1FamilyMClass =
      FacBom<BookingClass>::instance().create (lMBookingClassKey);
    FacBomManager::addToListAndMap (lPartnerBKKHKGSegmentYCabin1Family,
                                    lPartnerBKKHKGSegmentYCabin1FamilyMClass);
    FacBomManager::linkWithParent (lPartnerBKKHKGSegmentYCabin1Family,
                                   lPartnerBKKHKGSegmentYCabin1FamilyMClass);

    FacBomManager::addToListAndMap (lPartnerBKKHKGSegmentYCabin,
                                    lPartnerBKKHKGSegmentYCabin1FamilyMClass);
    FacBomManager::addToListAndMap (lPartnerBKKHKGSegment,
                                    lPartnerBKKHKGSegmentYCabin1FamilyMClass);

    BookingClass& lPartnerMktSINBKKSegmentYCabin1FamilyMClass =
      FacBom<BookingClass>::instance().create (lMBookingClassKey);
    FacBomManager::addToListAndMap (lPartnerMktSINBKKSegmentYCabin1Family,
                                    lPartnerMktSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::linkWithParent (lPartnerMktSINBKKSegmentYCabin1Family,
                                   lPartnerMktSINBKKSegmentYCabin1FamilyMClass);

    FacBomManager::addToListAndMap (lPartnerMktSINBKKSegmentYCabin,
                                    lPartnerMktSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::addToListAndMap (lPartnerMktSINBKKSegment,
                                    lPartnerMktSINBKKSegmentYCabin1FamilyMClass);    

    // Step 9.0.9: link SQ inventory objects to Partner CX inventory objects

    FacBomManager::addToList (lSINBKKSegment, lPartnerMktSINBKKSegment);

    lMktBKKHKGSegment.linkWithOperating (lPartnerBKKHKGSegment);
    
    /* =================================================================================== */

    // Step 1.0: O&D level
    // Create an O&D Date (SQ11/08-FEB-2010/SIN-BKK-SQ1200/08-FEB-2010/BKK-HKG)
    // for SQ's Inventory
    OnDString_T lSQSINBKKOnDStr = "SQ;11,2010-Feb-08;SIN,BKK";
    OnDString_T lMktSQBKKHKGOnDStr = "SQ;1200,2010-Feb-08;BKK,HKG";
    OnDStringList_T lOnDStringList;
    lOnDStringList.push_back (lSQSINBKKOnDStr);
    lOnDStringList.push_back (lMktSQBKKHKGOnDStr);

    OnDDateKey lOnDDateKey (lOnDStringList);
    OnDDate& lSQ_SINHKG_OnDDate =
      FacBom<OnDDate>::instance().create (lOnDDateKey);
    // Link to the inventory
    FacBomManager::addToListAndMap (lSQInv, lSQ_SINHKG_OnDDate);
    FacBomManager::linkWithParent (lSQInv, lSQ_SINHKG_OnDDate);

    // Add the segments
    FacBomManager::addToListAndMap (lSQ_SINHKG_OnDDate, lSINBKKSegment);
    FacBomManager::addToListAndMap (lSQ_SINHKG_OnDDate, lMktBKKHKGSegment);

    // Add total forecast info for cabin Y.
    const MeanStdDevPair_T lMean60StdDev6 (60.0, 6.0);
    const WTP_T lWTP750 = 750.0;
    const WTPDemandPair_T lWTP750Mean60StdDev6 (lWTP750, lMean60StdDev6);
    lSQ_SINHKG_OnDDate.setTotalForecast (lY, lWTP750Mean60StdDev6);

    // Add demand info (optional).
    // 2 legs here, so 2 CabinClassPair to add in the list.
    // Fist leg: cabin Y, class M.
    CabinClassPair_T lCC_YM1 (lY,lM);
    // Second leg: cabin Y, class M too.
    CabinClassPair_T lCC_YM2 (lY,lM);
    CabinClassPairList_T lCabinClassPairList;
    lCabinClassPairList.push_back(lCC_YM1);
    lCabinClassPairList.push_back(lCC_YM2);
    const MeanStdDevPair_T lMean20StdDev2 (20.0, 2.0);
    const Yield_T lYield850 = 850.0;
    const YieldDemandPair_T lYield850Mean20StdDev2 (lYield850, lMean20StdDev2);
    lSQ_SINHKG_OnDDate.setDemandInformation (lCabinClassPairList, lYield850Mean20StdDev2);
    
    CabinClassPair_T lCC_YY1 (lY,lY);
    CabinClassPair_T lCC_YY2 (lY,lY);
    lCabinClassPairList.clear();
    lCabinClassPairList.push_back(lCC_YY1);
    lCabinClassPairList.push_back(lCC_YY2);
    const MeanStdDevPair_T lMean10StdDev1 (10.0, 1.0);
    const Yield_T lYield1200 = 1200.0;
    const YieldDemandPair_T lYield1200Mean10StdDev1 (lYield1200, 
						     lMean10StdDev1);
    lSQ_SINHKG_OnDDate.setDemandInformation (lCabinClassPairList, 
					     lYield1200Mean10StdDev1);

    // Create an O&D Date (SQ11/08-FEB-2010/SIN-BKK) for SQ's Inventory
    lOnDStringList.clear();
    lOnDStringList.push_back (lSQSINBKKOnDStr);

    lOnDDateKey = OnDDateKey(lOnDStringList);
    OnDDate& lSQ_SINBKK_OnDDate =
      FacBom<OnDDate>::instance().create (lOnDDateKey);
    // Link to the inventory
    FacBomManager::addToListAndMap (lSQInv, lSQ_SINBKK_OnDDate);
    FacBomManager::linkWithParent (lSQInv, lSQ_SINBKK_OnDDate);

    // Add the segments
    FacBomManager::addToListAndMap (lSQ_SINBKK_OnDDate, lSINBKKSegment);

    // Add total forecast info for cabin Y.
    const WTP_T lWTP400 = 400.0;
    const WTPDemandPair_T lWTP400Mean60StdDev6 (lWTP400, lMean60StdDev6);
    lSQ_SINBKK_OnDDate.setTotalForecast (lY, lWTP400Mean60StdDev6);

    // Add demand info (optional).
    lCabinClassPairList.clear();
    lCabinClassPairList.push_back(lCC_YM1);
    const MeanStdDevPair_T lMean20StdDev1 (20.0, 1.0);
    const Yield_T lYield500 = 500.0;
    const YieldDemandPair_T lYield500Mean20StdDev1 (lYield500, lMean20StdDev1);
    lSQ_SINBKK_OnDDate.setDemandInformation (lCabinClassPairList, 
					     lYield500Mean20StdDev1);

    lCabinClassPairList.clear();
    lCabinClassPairList.push_back(lCC_YY1);
    const Yield_T lYield700 = 700.0;
    const YieldDemandPair_T lYield700Mean20StdDev1 (lYield700, lMean10StdDev1 );
    lSQ_SINBKK_OnDDate.setDemandInformation (lCabinClassPairList, 
					     lYield700Mean20StdDev1);

    /*******************************************************************************
    // Create an O&D Date (SQ1200/08-FEB-2010/BKK-HKG) for SQ's Inventory
    lFullKeyList.clear();
    lFullKeyList.push_back (lMktSQBKKHKGFullKeyStr);

    lOnDDateKey = OnDDateKey(lFullKeyList);
    OnDDate& lMktSQ_BKKHKG_OnDDate =
      FacBom<OnDDate>::instance().create (lOnDDateKey);
    // Link to the inventory
    FacBomManager::addToListAndMap (lSQInv, lMktSQ_BKKHKG_OnDDate);
    FacBomManager::linkWithParent (lSQInv, lMktSQ_BKKHKG_OnDDate);

    // Add the segments
    FacBomManager::addToListAndMap (lMktSQ_BKKHKG_OnDDate, lMktBKKHKGSegment);

    // Demand info is not added for purely marketed O&Ds
    // Add demand info
    // lCabinClassPairList.clear();
    // lCabinClassPairList.push_back(lCC_YM2);
    // lMktSQ_BKKHKG_OnDDate.setDemandInformation (lCabinClassPairList, 500.0, 20.0, 1.0);
    ***********************************************************************************/
    
            
    // ////// CX ///////    
    // Step 0.2: Flight-date level
    // Create a FlightDate (CX12/08-FEB-2010) for CX's Inventory
    lFlightNumber = 12;
    //lDate = Date_T (2010, 2, 8);
    lFlightDateKey = FlightDateKey (lFlightNumber, lDate);

    FlightDate& lCX12_20100208_FD =
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::addToListAndMap (lCXInv, lCX12_20100208_FD);
    FacBomManager::linkWithParent (lCXInv, lCX12_20100208_FD);

    // Create a (mkt) FlightDate (CX1100/08-FEB-2010) for CX's Inventory
    lFlightNumber = 1100;
    //lDate = Date_T (2010, 2, 8);
    lMktFlightDateKey = FlightDateKey (lFlightNumber, lDate);

    FlightDate& lCX1100_20100208_FD =
      FacBom<FlightDate>::instance().create (lMktFlightDateKey);
    FacBomManager::addToListAndMap (lCXInv, lCX1100_20100208_FD);
    FacBomManager::linkWithParent (lCXInv, lCX1100_20100208_FD);
    
    // Display the flight-date
    // STDAIR_LOG_DEBUG ("FlightDate: " << lAF084_20110320_FD.toString());

    // Step 0.3: Segment-date level
    // Create a SegmentDate BKK-HKG for CX's Inventory
    
    lSegmentDateKey = SegmentDateKey (lBKK, lHKG);

    SegmentDate& lBKKHKGSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lCX12_20100208_FD, lBKKHKGSegment);
    FacBomManager::linkWithParent (lCX12_20100208_FD, lBKKHKGSegment);  

    // Fill the SegmentDate content
    lBKKHKGSegment.setBoardingDate (lDate);
    lBKKHKGSegment.setOffDate (lDate);
    lBKKHKGSegment.setBoardingTime (l1200);
    lBKKHKGSegment.setOffTime (l1540);
    lBKKHKGSegment.setElapsedTime (l0240);

    // Create a second (mkt) SegmentDate (SIN-BKK) for CX's Inventory
    lMktSegmentDateKey = SegmentDateKey (lSIN, lBKK);

    SegmentDate& lMktSINBKKSegment =
      FacBom<SegmentDate>::instance().create (lMktSegmentDateKey);
    FacBomManager::addToListAndMap (lCX1100_20100208_FD, lMktSINBKKSegment);
    FacBomManager::linkWithParent (lCX1100_20100208_FD, lMktSINBKKSegment);

    // Fill the (mkt) SegmentDate content
    lMktSINBKKSegment.setBoardingDate (lDate);
    lMktSINBKKSegment.setOffDate (lDate);
    lMktSINBKKSegment.setBoardingTime (l0820);
    lMktSINBKKSegment.setOffTime (l1100);
    lMktSINBKKSegment.setElapsedTime (l0340);

    // Step 0.4: Leg-date level
    // Create a LegDate (BKK) for CX's Inventory
    lLegDateKey = LegDateKey (lBKK);

    LegDate& lBKKLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::addToListAndMap (lCX12_20100208_FD, lBKKLeg);
    FacBomManager::linkWithParent (lCX12_20100208_FD, lBKKLeg);

    // Fill the LegDate content
    lBKKLeg.setOffPoint (lHKG);
    lBKKLeg.setBoardingDate (lDate);
    lBKKLeg.setOffDate (lDate);
    lBKKLeg.setBoardingTime (l1200);
    lBKKLeg.setOffTime (l1540);
    lBKKLeg.setElapsedTime (l0240);

    // Display the leg-date
    // STDAIR_LOG_DEBUG ("LegDate: " << lCDGLeg.toString());

    // Link the segment-dates with the leg-dates
    FacBomManager::addToListAndMap (lBKKLeg, lBKKHKGSegment);
    FacBomManager::addToListAndMap (lBKKHKGSegment, lBKKLeg);

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) for the Segment BKK-HKG of CX's Inventory
    SegmentCabin& lBKKHKGSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lBKKHKGSegment, lBKKHKGSegmentYCabin);
    FacBomManager::linkWithParent (lBKKHKGSegment, lBKKHKGSegmentYCabin);

    // Create a SegmentCabin (Y) for the (mkt) Segment SIN-BKK of CX's Inventory
    SegmentCabin& lMktSINBKKSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lMktSINBKKSegment, lMktSINBKKSegmentYCabin);
    FacBomManager::linkWithParent (lMktSINBKKSegment, lMktSINBKKSegmentYCabin);

    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) for the Leg BKK-HKG on CX's Inventory
    LegCabin& lBKKLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::addToListAndMap (lBKKLeg, lBKKLegYCabin);
    FacBomManager::linkWithParent (lBKKLeg, lBKKLegYCabin);

    lCapacity = CabinCapacity_T(100);
    lBKKLegYCabin.setCapacities (lCapacity);
    lBKKLegYCabin.setAvailabilityPool (lCapacity);

    // Link the segment-dates with the leg-dates
    FacBomManager::addToListAndMap (lBKKLegYCabin, lBKKHKGSegmentYCabin,
                                    lBKKHKGSegmentYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lBKKHKGSegmentYCabin, lBKKLegYCabin,
                                    lBKKLegYCabin.getFullerKey());
   
    // Step 0.7: fare family level
    // Create a fareFamily (1) for the Segment BKK-HKG, cabin Y on CX's Inv
    FareFamily& lBKKHKGSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lBKKHKGSegmentYCabin,
                                    lBKKHKGSegmentYCabin1Family);
    FacBomManager::linkWithParent (lBKKHKGSegmentYCabin,
                                   lBKKHKGSegmentYCabin1Family);

    // Create a FareFamily (1) for the (mkt) Segment SIN-BKK, cabin Y on CX's Inv
    FareFamily& lMktSINBKKSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lMktSINBKKSegmentYCabin,
                                    lMktSINBKKSegmentYCabin1Family);
    FacBomManager::linkWithParent (lMktSINBKKSegmentYCabin,
                                   lMktSINBKKSegmentYCabin1Family);

    
    // Step 0.8: booking class level
    // Create a BookingClass (Y) for the
    // Segment BKK-HKG, cabin Y, fare family 1 on CX's Inv
    BookingClass& lBKKHKGSegmentYCabin1FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    FacBomManager::addToListAndMap (lBKKHKGSegmentYCabin1Family,
                                    lBKKHKGSegmentYCabin1FamilyYClass);
    FacBomManager::linkWithParent (lBKKHKGSegmentYCabin1Family,
                                   lBKKHKGSegmentYCabin1FamilyYClass);

    FacBomManager::addToListAndMap (lBKKHKGSegmentYCabin,
                                    lBKKHKGSegmentYCabin1FamilyYClass);
    FacBomManager::addToListAndMap (lBKKHKGSegment,
                                    lBKKHKGSegmentYCabin1FamilyYClass);

    lBKKHKGSegmentYCabin1FamilyYClass.setYield(700);

    // Create a BookingClass (Y) for the (mkt) Segment SIN-BKK, cabin Y,
    // fare family 1 on CX's Inv
    BookingClass& lMktSINBKKSegmentYCabin1FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    FacBomManager::addToListAndMap (lMktSINBKKSegmentYCabin1Family,
                                    lMktSINBKKSegmentYCabin1FamilyYClass);
    FacBomManager::linkWithParent (lMktSINBKKSegmentYCabin1Family,
                                   lMktSINBKKSegmentYCabin1FamilyYClass);

    FacBomManager::addToListAndMap (lMktSINBKKSegmentYCabin,
                                    lMktSINBKKSegmentYCabin1FamilyYClass);
    FacBomManager::addToListAndMap (lMktSINBKKSegment,
                                    lMktSINBKKSegmentYCabin1FamilyYClass);

    lMktSINBKKSegmentYCabin1FamilyYClass.setYield(700);
    
    //Create a BookingClass (M) for the
    // Segment BKK-HKG, cabin Y, fare family 1 on CX's Inv
    BookingClass& lBKKHKGSegmentYCabin1FamilyMClass =
      FacBom<BookingClass>::instance().create (lMBookingClassKey);
    FacBomManager::addToListAndMap (lBKKHKGSegmentYCabin1Family,
                                    lBKKHKGSegmentYCabin1FamilyMClass);
    FacBomManager::linkWithParent (lBKKHKGSegmentYCabin1Family,
                                   lBKKHKGSegmentYCabin1FamilyMClass);

    FacBomManager::addToListAndMap (lBKKHKGSegmentYCabin,
                                    lBKKHKGSegmentYCabin1FamilyMClass);
    FacBomManager::addToListAndMap (lBKKHKGSegment,
                                    lBKKHKGSegmentYCabin1FamilyMClass);

    lBKKHKGSegmentYCabin1FamilyMClass.setYield(500);

    // Create a BookingClass (M) for the (mkt) Segment SIN-BKK, cabin Y,
    // fare family 1 on CX's Inv
    BookingClass& lMktSINBKKSegmentYCabin1FamilyMClass =
      FacBom<BookingClass>::instance().create (lMBookingClassKey);
    FacBomManager::addToListAndMap (lMktSINBKKSegmentYCabin1Family,
                                    lMktSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::linkWithParent (lMktSINBKKSegmentYCabin1Family,
                                   lMktSINBKKSegmentYCabin1FamilyMClass);

    FacBomManager::addToListAndMap (lMktSINBKKSegmentYCabin,
                                    lMktSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::addToListAndMap (lMktSINBKKSegment,
                                    lMktSINBKKSegmentYCabin1FamilyMClass);

    lMktSINBKKSegmentYCabin1FamilyMClass.setYield(500);

    /* =================================================================================== */
    // Step 0.9: Partner Inventory
    // Create a partner Inventory SQ for CX   
    const InventoryKey lPartnerSQKey ("SQ");
    Inventory& lPartnerSQInv = 
      FacBom<Inventory>::instance().create (lPartnerSQKey);
    FacBomManager::addToListAndMap (lCXInv, lPartnerSQInv);
    FacBomManager::linkWithParent (lCXInv, lPartnerSQInv);

    // Step 0.9.2 : Flight-date level
    lFlightNumber = 11;
    lFlightDateKey = FlightDateKey (lFlightNumber, lDate);

    FlightDate& lPartnerSQ11_20100208_FD =
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::addToListAndMap (lPartnerSQInv, lPartnerSQ11_20100208_FD);
    FacBomManager::linkWithParent (lPartnerSQInv, lPartnerSQ11_20100208_FD);

    lFlightNumber = 1200;
    lMktFlightDateKey = FlightDateKey (lFlightNumber, lDate);

    FlightDate& lPartnerSQ1200_20100208_FD =
      FacBom<FlightDate>::instance().create (lMktFlightDateKey);
    FacBomManager::addToListAndMap (lPartnerSQInv, lPartnerSQ1200_20100208_FD);
    FacBomManager::linkWithParent (lPartnerSQInv, lPartnerSQ1200_20100208_FD);

    // Step 0.9.3: Segment-date level
    lSegmentDateKey = SegmentDateKey (lSIN, lBKK);

    SegmentDate& lPartnerSINBKKSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::addToListAndMap (lPartnerSQ11_20100208_FD, 
				    lPartnerSINBKKSegment);
    FacBomManager::linkWithParent (lPartnerSQ11_20100208_FD, 
				   lPartnerSINBKKSegment);
    
    lPartnerSINBKKSegment.setBoardingDate (lDate);
    lPartnerSINBKKSegment.setOffDate (lDate);
    lPartnerSINBKKSegment.setBoardingTime (l0820);
    lPartnerSINBKKSegment.setOffTime (l1100);
    lPartnerSINBKKSegment.setElapsedTime (l0340);
    
    lMktSegmentDateKey = SegmentDateKey (lBKK, lHKG);

    SegmentDate& lPartnerMktBKKHKGSegment =
      FacBom<SegmentDate>::instance().create (lMktSegmentDateKey);
    FacBomManager::addToListAndMap (lPartnerSQ1200_20100208_FD, 
				    lPartnerMktBKKHKGSegment);
    FacBomManager::linkWithParent (lPartnerSQ1200_20100208_FD,
				   lPartnerMktBKKHKGSegment);

    lPartnerMktBKKHKGSegment.setBoardingDate (lDate);
    lPartnerMktBKKHKGSegment.setOffDate (lDate);
    lPartnerMktBKKHKGSegment.setBoardingTime (l1200);
    lPartnerMktBKKHKGSegment.setOffTime (l1540);
    lPartnerMktBKKHKGSegment.setElapsedTime (l0240);
  
    // Step 0.9.4: Leg-date level
    lLegDateKey = LegDateKey (lSIN);

    LegDate& lPartnerSINLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::addToListAndMap (lPartnerSQ11_20100208_FD, lPartnerSINLeg);
    FacBomManager::linkWithParent (lPartnerSQ11_20100208_FD, lPartnerSINLeg);

    lPartnerSINLeg.setOffPoint (lBKK);
    lPartnerSINLeg.setBoardingDate (lDate);
    lPartnerSINLeg.setOffDate (lDate);
    lPartnerSINLeg.setBoardingTime (l0820);
    lPartnerSINLeg.setOffTime (l1100);
    lPartnerSINLeg.setElapsedTime (l0340);

    FacBomManager::addToListAndMap (lPartnerSINLeg, lPartnerSINBKKSegment);
    FacBomManager::addToListAndMap (lPartnerSINBKKSegment, lPartnerSINLeg);

    // Step 9.0.5: segment-cabin level

    SegmentCabin& lPartnerSINBKKSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lPartnerSINBKKSegment, 
				    lPartnerSINBKKSegmentYCabin);
    FacBomManager::linkWithParent (lPartnerSINBKKSegment, 
				   lPartnerSINBKKSegmentYCabin);
    
    SegmentCabin& lPartnerMktBKKHKGSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::addToListAndMap (lPartnerMktBKKHKGSegment, 
				    lPartnerMktBKKHKGSegmentYCabin);
    FacBomManager::linkWithParent (lPartnerMktBKKHKGSegment, 
				   lPartnerMktBKKHKGSegmentYCabin);
    
    // Step 9.0.6: leg-cabin level
    
    LegCabin& lPartnerSINLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::addToListAndMap (lPartnerSINLeg, lPartnerSINLegYCabin);
    FacBomManager::linkWithParent (lPartnerSINLeg, lPartnerSINLegYCabin);

    lCapacity = CabinCapacity_T(999);
    lPartnerSINLegYCabin.setCapacities (lCapacity);
    lPartnerSINLegYCabin.setAvailabilityPool (lCapacity);

    FacBomManager::addToListAndMap (lPartnerSINLegYCabin, 
				    lPartnerSINBKKSegmentYCabin,
                                    lPartnerSINBKKSegmentYCabin.getFullerKey());
    FacBomManager::addToListAndMap (lPartnerSINBKKSegmentYCabin, 
				    lPartnerSINLegYCabin,
                                    lPartnerSINLegYCabin.getFullerKey());

    // Step 9.0.7: fare family level

    FareFamily& lPartnerSINBKKSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lPartnerSINBKKSegmentYCabin,
                                    lPartnerSINBKKSegmentYCabin1Family);
    FacBomManager::linkWithParent (lPartnerSINBKKSegmentYCabin,
                                   lPartnerSINBKKSegmentYCabin1Family);
    
    FareFamily& lPartnerMktBKKHKGSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::addToListAndMap (lPartnerMktBKKHKGSegmentYCabin,
                                    lPartnerMktBKKHKGSegmentYCabin1Family);
    FacBomManager::linkWithParent (lPartnerMktBKKHKGSegmentYCabin,
                                   lPartnerMktBKKHKGSegmentYCabin1Family);

    
    // Step 9.0.8: booking class level

    BookingClass& lPartnerSINBKKSegmentYCabin1FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    FacBomManager::addToListAndMap (lPartnerSINBKKSegmentYCabin1Family,
                                    lPartnerSINBKKSegmentYCabin1FamilyYClass);
    FacBomManager::linkWithParent (lPartnerSINBKKSegmentYCabin1Family,
                                   lPartnerSINBKKSegmentYCabin1FamilyYClass);

    FacBomManager::addToListAndMap (lPartnerSINBKKSegmentYCabin,
                                    lPartnerSINBKKSegmentYCabin1FamilyYClass);
    FacBomManager::addToListAndMap (lPartnerSINBKKSegment,
                                    lPartnerSINBKKSegmentYCabin1FamilyYClass);

    BookingClass& lPartnerMktBKKHKGSegmentYCabin1FamilyYClass =
      FacBom<BookingClass>::instance().create (lYBookingClassKey);
    FacBomManager::addToListAndMap (lPartnerMktBKKHKGSegmentYCabin1Family,
                                    lPartnerMktBKKHKGSegmentYCabin1FamilyYClass);
    FacBomManager::linkWithParent (lPartnerMktBKKHKGSegmentYCabin1Family,
                                   lPartnerMktBKKHKGSegmentYCabin1FamilyYClass);

    FacBomManager::addToListAndMap (lPartnerMktBKKHKGSegmentYCabin,
                                    lPartnerMktBKKHKGSegmentYCabin1FamilyYClass);
    FacBomManager::addToListAndMap (lPartnerMktBKKHKGSegment,
                                    lPartnerMktBKKHKGSegmentYCabin1FamilyYClass);    
    
    BookingClass& lPartnerSINBKKSegmentYCabin1FamilyMClass =
      FacBom<BookingClass>::instance().create (lMBookingClassKey);
    FacBomManager::addToListAndMap (lPartnerSINBKKSegmentYCabin1Family,
                                    lPartnerSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::linkWithParent (lPartnerSINBKKSegmentYCabin1Family,
                                   lPartnerSINBKKSegmentYCabin1FamilyMClass);

    FacBomManager::addToListAndMap (lPartnerSINBKKSegmentYCabin,
                                    lPartnerSINBKKSegmentYCabin1FamilyMClass);
    FacBomManager::addToListAndMap (lPartnerSINBKKSegment,
                                    lPartnerSINBKKSegmentYCabin1FamilyMClass);

    BookingClass& lPartnerMktBKKHKGSegmentYCabin1FamilyMClass =
      FacBom<BookingClass>::instance().create (lMBookingClassKey);
    FacBomManager::addToListAndMap (lPartnerMktBKKHKGSegmentYCabin1Family,
                                    lPartnerMktBKKHKGSegmentYCabin1FamilyMClass);
    FacBomManager::linkWithParent (lPartnerMktBKKHKGSegmentYCabin1Family,
                                   lPartnerMktBKKHKGSegmentYCabin1FamilyMClass);

    FacBomManager::addToListAndMap (lPartnerMktBKKHKGSegmentYCabin,
                                    lPartnerMktBKKHKGSegmentYCabin1FamilyMClass);
    FacBomManager::addToListAndMap (lPartnerMktBKKHKGSegment,
                                    lPartnerMktBKKHKGSegmentYCabin1FamilyMClass);

    // Step 9.0.9: link CX inventory objects to Partner SQ inventory objects
    FacBomManager::addToList (lBKKHKGSegment, lPartnerMktBKKHKGSegment);

    lMktSINBKKSegment.linkWithOperating (lPartnerSINBKKSegment);

    /* =================================================================================== */

    // Step 1.0: O&D level
    // Create an O&D Date (CX1100/08-FEB-2010/SIN-BKK-CX12/08-FEB-2010/BKK-HKG) for CX's Inventory
    OnDString_T lMktCXSINBKKOnDStr = "CX;1100,2010-Feb-08;SIN,BKK";
    OnDString_T lCXBKKHKGOnDStr = "CX;12,2010-Feb-08;BKK,HKG";
    lOnDStringList.clear();
    lOnDStringList.push_back (lMktCXSINBKKOnDStr);
    lOnDStringList.push_back (lCXBKKHKGOnDStr);

    lOnDDateKey = OnDDateKey(lOnDStringList);
    OnDDate& lCX_SINHKG_OnDDate =
      FacBom<OnDDate>::instance().create (lOnDDateKey);
    // Link to the inventory
    FacBomManager::addToListAndMap (lCXInv, lCX_SINHKG_OnDDate);
    FacBomManager::linkWithParent (lCXInv, lCX_SINHKG_OnDDate);

    // Add the segments
    FacBomManager::addToListAndMap (lCX_SINHKG_OnDDate, lMktSINBKKSegment);
    FacBomManager::addToListAndMap (lCX_SINHKG_OnDDate, lBKKHKGSegment);

    // Add total forecast info for cabin Y.
    lCX_SINHKG_OnDDate.setTotalForecast (lY, lWTP750Mean60StdDev6);
    
    // Add demand info
    lCabinClassPairList.clear();
    lCabinClassPairList.push_back(lCC_YM1);
    lCabinClassPairList.push_back(lCC_YM2);
    lCX_SINHKG_OnDDate.setDemandInformation (lCabinClassPairList, 
					     lYield850Mean20StdDev2);

    lCabinClassPairList.clear();
    lCabinClassPairList.push_back(lCC_YY1);
    lCabinClassPairList.push_back(lCC_YY2);
    lCX_SINHKG_OnDDate.setDemandInformation (lCabinClassPairList, 
					     lYield1200Mean10StdDev1);

    /***********************************************************************************
    // Create an O&D Date (CX1100/08-FEB-2010/SIN-BKK) for CX's Inventory
    lFullKeyList.clear();
    lFullKeyList.push_back (lMktCXSINBKKFullKeyStr);

    lOnDDateKey = OnDDateKey(lFullKeyList);
    OnDDate& lMktCX_SINBKK_OnDDate =
      FacBom<OnDDate>::instance().create (lOnDDateKey);
    // Link to the inventory
    FacBomManager::addToListAndMap (lCXInv, lMktCX_SINBKK_OnDDate);
    FacBomManager::linkWithParent (lCXInv, lMktCX_SINBKK_OnDDate);

    // Add the segments
    FacBomManager::addToListAndMap (lMktCX_SINBKK_OnDDate, lMktSINBKKSegment);

    // Demand info is not added for purely marketed O&Ds
    // Add demand info
    // lCabinClassPairList.clear();
    // lCabinClassPairList.push_back(lCC_YM1);
    // lMktCX_SINBKK_OnDDate.setDemandInformation (lCabinClassPairList, 500.0, 20.0, 1.0);
    *************************************************************************************/
    
    // Create an O&D Date (CX12/08-FEB-2010/BKK-HKG) for CX's Inventory
    lOnDStringList.clear();
    lOnDStringList.push_back (lCXBKKHKGOnDStr);

    lOnDDateKey = OnDDateKey(lOnDStringList);
    OnDDate& lCX_BKKHKG_OnDDate =
      FacBom<OnDDate>::instance().create (lOnDDateKey);
    // Link to the inventory
    FacBomManager::addToListAndMap (lCXInv, lCX_BKKHKG_OnDDate);
    FacBomManager::linkWithParent (lCXInv, lCX_BKKHKG_OnDDate);

    // Add the segments
    FacBomManager::addToListAndMap (lCX_BKKHKG_OnDDate, lBKKHKGSegment);

    // Add total forecast info for cabin Y.
    lCX_BKKHKG_OnDDate.setTotalForecast (lY, lWTP400Mean60StdDev6);

    // Add demand info
    lCabinClassPairList.clear();
    lCabinClassPairList.push_back(lCC_YM2);
    lCX_BKKHKG_OnDDate.setDemandInformation (lCabinClassPairList, 
					     lYield500Mean20StdDev1);

    lCabinClassPairList.clear();
    lCabinClassPairList.push_back(lCC_YY2);
    const YieldDemandPair_T lYield700Mean10StdDev1 (lYield700, lMean10StdDev1 );
    lCX_BKKHKG_OnDDate.setDemandInformation (lCabinClassPairList, 
					     lYield700Mean10StdDev1);

    /*================================================================================
      ================================================================================
      ================================================================================*/
    // Schedule:
    // SQ:
    // Step 1: flight period level
    // Create a flight period for SQ11:
    const DoWStruct lDoWSrtuct ("1111111");
    const Date_T lDateRangeStart (2010, boost::gregorian::Feb, 8);
    const Date_T lDateRangeEnd (2010, boost::gregorian::Feb, 9);
    const DatePeriod_T lDatePeriod (lDateRangeStart, lDateRangeEnd);
    const PeriodStruct lPeriodStruct (lDatePeriod,lDoWSrtuct);

    lFlightNumber = FlightNumber_T (11);

    FlightPeriodKey lFlightPeriodKey (lFlightNumber, lPeriodStruct);

    FlightPeriod& lSQ11FlightPeriod =
      FacBom<FlightPeriod>::instance().create (lFlightPeriodKey);
    FacBomManager::addToListAndMap (lSQInv, lSQ11FlightPeriod);
    FacBomManager::linkWithParent (lSQInv, lSQ11FlightPeriod);

    // Step 2: segment period level
    // Create a segment period for SIN-BKK:

    SegmentPeriodKey lSegmentPeriodKey (lSIN, lBKK);

    SegmentPeriod& lSINBKKSegmentPeriod =
      FacBom<SegmentPeriod>::instance().create (lSegmentPeriodKey);
    FacBomManager::addToListAndMap (lSQ11FlightPeriod, lSINBKKSegmentPeriod);
    FacBomManager::linkWithParent (lSQ11FlightPeriod, lSINBKKSegmentPeriod);

    lSINBKKSegmentPeriod.setBoardingTime (l0820);
    lSINBKKSegmentPeriod.setOffTime (l1100);
    lSINBKKSegmentPeriod.setElapsedTime (l0340);
    ClassList_String_T lYM ("YM");
    lSINBKKSegmentPeriod.addCabinBookingClassList (lY,lYM);

    // CX:
    // Step 1: flight period level
    // Create a flight period for CX12:  
    lFlightNumber = FlightNumber_T (12);

    lFlightPeriodKey = FlightPeriodKey(lFlightNumber, lPeriodStruct);

    FlightPeriod& lCX12FlightPeriod =
      FacBom<FlightPeriod>::instance().create (lFlightPeriodKey);
    FacBomManager::addToListAndMap (lCXInv, lCX12FlightPeriod);
    FacBomManager::linkWithParent (lCXInv, lCX12FlightPeriod);

    // Step 2: segment period level
    // Create a segment period for BKK-HKG:

    lSegmentPeriodKey = SegmentPeriodKey (lBKK, lHKG);

    SegmentPeriod& lBKKHKGSegmentPeriod =
      FacBom<SegmentPeriod>::instance().create (lSegmentPeriodKey);
    FacBomManager::addToListAndMap (lCX12FlightPeriod, lBKKHKGSegmentPeriod);
    FacBomManager::linkWithParent (lCX12FlightPeriod, lBKKHKGSegmentPeriod);

    lBKKHKGSegmentPeriod.setBoardingTime (l1200);
    lBKKHKGSegmentPeriod.setOffTime (l1540);
    lBKKHKGSegmentPeriod.setElapsedTime (l0240);
    lBKKHKGSegmentPeriod.addCabinBookingClassList (lY,lYM);
    
  }

  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildPartnershipsSamplePricing (BomRoot& ioBomRoot) {

    ////////////////////// SimFQT //////////////////////

    /*===================================================================================*/
    // First airport pair SIN-BKK.
    // Set the airport-pair primary key.
    AirportPairKey lAirportPairKey ("SIN", "BKK");
    
    // Create the AirportPairKey object and link it to the ioBomRoot object.
    AirportPair& lSINBKKAirportPair =
      FacBom<AirportPair>::instance().create (lAirportPairKey);
    FacBomManager::addToListAndMap (ioBomRoot, lSINBKKAirportPair);
    FacBomManager::linkWithParent (ioBomRoot, lSINBKKAirportPair);

    // Set the fare date-period primary key.
    const Date_T lDateRangeStart (2010, boost::gregorian::Jan, 15);
    const Date_T lDateRangeEnd (2010, boost::gregorian::Dec, 31);
    const DatePeriod_T lDateRange (lDateRangeStart, lDateRangeEnd);
    const DatePeriodKey lDatePeriodKey (lDateRange);

    // Create the DatePeriodKey object and link it to the PosChannel object.
    DatePeriod& lSINBKKDatePeriod =
      FacBom<DatePeriod>::instance().create (lDatePeriodKey);
    FacBomManager::addToListAndMap (lSINBKKAirportPair, lSINBKKDatePeriod);
    FacBomManager::linkWithParent (lSINBKKAirportPair, lSINBKKDatePeriod);    

    // Set the point-of-sale-channel primary key.
    PosChannelKey lPosChannelKey ("SIN","IN");  
    
    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lSINPosChannel =
      FacBom<PosChannel>::instance().create (lPosChannelKey);
    FacBomManager::addToListAndMap (lSINBKKDatePeriod, lSINPosChannel);
    FacBomManager::linkWithParent (lSINBKKDatePeriod, lSINPosChannel);
   
    // Set the fare time-period primary key.
    const Time_T lTimeRangeStart (0, 0, 0);
    const Time_T lTimeRangeEnd (23, 0, 0);
    const TimePeriodKey lFareTimePeriodKey (lTimeRangeStart,
                                            lTimeRangeEnd);

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lSINBKKFareTimePeriod =
      FacBom<TimePeriod>::instance().create (lFareTimePeriodKey);
    FacBomManager::addToListAndMap (lSINPosChannel, lSINBKKFareTimePeriod);
    FacBomManager::linkWithParent (lSINPosChannel, lSINBKKFareTimePeriod); 

    // Generate the FareRule
    const FareFeaturesKey lFareFeaturesKey (TRIP_TYPE_ONE_WAY,
                                            NO_ADVANCE_PURCHASE,
                                            SATURDAY_STAY,
                                            CHANGE_FEES,
                                            NON_REFUNDABLE,
                                            NO_STAY_DURATION);

    // Create the FareFeaturesKey and link it to the TimePeriod object.
    FareFeatures& lSINBKKFareFeatures =
      FacBom<FareFeatures>::instance().create (lFareFeaturesKey);
    FacBomManager::addToListAndMap (lSINBKKFareTimePeriod, lSINBKKFareFeatures);
    FacBomManager::linkWithParent (lSINBKKFareTimePeriod, lSINBKKFareFeatures);

    // Generate Segment Features and link them to their FareRule.
    AirlineCodeList_T lSQAirlineCodeList;
    lSQAirlineCodeList.push_back ("SQ");
    
    ClassList_StringList_T lYClassCodeList;
    lYClassCodeList.push_back ("Y");    
    const AirlineClassListKey lSQAirlineYClassListKey (lSQAirlineCodeList,
                                                       lYClassCodeList);

    ClassList_StringList_T lMClassCodeList;
    lMClassCodeList.push_back ("M");
    const AirlineClassListKey lSQAirlineMClassListKey (lSQAirlineCodeList,
                                                       lMClassCodeList);

    // Create the AirlineClassListKey and link it to the FareFeatures object.
    AirlineClassList& lSQAirlineYClassList =
      FacBom<AirlineClassList>::instance().create (lSQAirlineYClassListKey);
    lSQAirlineYClassList.setFare(700);
    FacBomManager::addToListAndMap (lSINBKKFareFeatures, lSQAirlineYClassList);
    FacBomManager::linkWithParent (lSINBKKFareFeatures, lSQAirlineYClassList);

    AirlineClassList& lSQAirlineMClassList =
      FacBom<AirlineClassList>::instance().create (lSQAirlineMClassListKey);
    lSQAirlineMClassList.setFare(500);
    FacBomManager::addToListAndMap (lSINBKKFareFeatures, lSQAirlineMClassList);
    FacBomManager::linkWithParent (lSINBKKFareFeatures, lSQAirlineMClassList);

    /*===================================================================================*/
    // Second airport pair BKK-HKG.
    // Set the airport-pair primary key.
    lAirportPairKey = AirportPairKey ("BKK", "HKG");
    
    // Create the AirportPairKey object and link it to the ioBomRoot object.
    AirportPair& lBKKHKGAirportPair =
      FacBom<AirportPair>::instance().create (lAirportPairKey);
    FacBomManager::addToListAndMap (ioBomRoot, lBKKHKGAirportPair);
    FacBomManager::linkWithParent (ioBomRoot, lBKKHKGAirportPair);

    // Set the fare date-period primary key.
    // Use the same as previously.

    // Create the DatePeriodKey object and link it to the PosChannel object.
    DatePeriod& lBKKHKGDatePeriod =
      FacBom<DatePeriod>::instance().create (lDatePeriodKey);
    FacBomManager::addToListAndMap (lBKKHKGAirportPair, lBKKHKGDatePeriod);
    FacBomManager::linkWithParent (lBKKHKGAirportPair, lBKKHKGDatePeriod);    

    // Set the point-of-sale-channel primary key.
    lPosChannelKey  = PosChannelKey("BKK","IN");  
    
    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lBKKPosChannel =
      FacBom<PosChannel>::instance().create (lPosChannelKey);
    FacBomManager::addToListAndMap (lBKKHKGDatePeriod, lBKKPosChannel);
    FacBomManager::linkWithParent (lBKKHKGDatePeriod, lBKKPosChannel);
   
    // Set the fare time-period primary key.
    // Use the same as previously.

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lBKKHKGFareTimePeriod =
      FacBom<TimePeriod>::instance().create (lFareTimePeriodKey);
    FacBomManager::addToListAndMap (lBKKPosChannel, lBKKHKGFareTimePeriod);
    FacBomManager::linkWithParent (lBKKPosChannel, lBKKHKGFareTimePeriod);

    // Generate the FareRule
    // Use the same key as previously.

    // Create the FareFeaturesKey and link it to the TimePeriod object.
    FareFeatures& lBKKHKGFareFeatures =
      FacBom<FareFeatures>::instance().create (lFareFeaturesKey);
    FacBomManager::addToListAndMap (lBKKHKGFareTimePeriod, lBKKHKGFareFeatures);
    FacBomManager::linkWithParent (lBKKHKGFareTimePeriod, lBKKHKGFareFeatures);

    // Generate Segment Features and link them to their FareRule.
    AirlineCodeList_T lCXAirlineCodeList;
    lCXAirlineCodeList.push_back ("CX");
    
    const AirlineClassListKey lCXAirlineYClassListKey (lCXAirlineCodeList,
                                                       lYClassCodeList);

    const AirlineClassListKey lCXAirlineMClassListKey (lCXAirlineCodeList,
                                                       lMClassCodeList);

    // Create the AirlineClassListKey and link it to the FareFeatures object.
    AirlineClassList& lCXAirlineYClassList =
      FacBom<AirlineClassList>::instance().create (lCXAirlineYClassListKey);
    lCXAirlineYClassList.setFare(700);
    FacBomManager::addToListAndMap (lBKKHKGFareFeatures, lCXAirlineYClassList);
    FacBomManager::linkWithParent (lBKKHKGFareFeatures, lCXAirlineYClassList);
    
    AirlineClassList& lCXAirlineMClassList =
      FacBom<AirlineClassList>::instance().create (lCXAirlineMClassListKey);
    lCXAirlineMClassList.setFare(500);
    FacBomManager::addToListAndMap (lBKKHKGFareFeatures, lCXAirlineMClassList);
    FacBomManager::linkWithParent (lBKKHKGFareFeatures, lCXAirlineMClassList);

    /*===================================================================================*/
    // Third airport pair SIN-HKG.
    // Set the airport-pair primary key.
    lAirportPairKey = AirportPairKey ("SIN", "HKG");
    
    // Create the AirportPairKey object and link it to the ioBomRoot object.
    AirportPair& lSINHKGAirportPair =
      FacBom<AirportPair>::instance().create (lAirportPairKey);
    FacBomManager::addToListAndMap (ioBomRoot, lSINHKGAirportPair);
    FacBomManager::linkWithParent (ioBomRoot, lSINHKGAirportPair);

    // Set the fare date-period primary key.
    // Use the same as previously.

    // Create the DatePeriodKey object and link it to the PosChannel object.
    DatePeriod& lSINHKGDatePeriod =
      FacBom<DatePeriod>::instance().create (lDatePeriodKey);
    FacBomManager::addToListAndMap (lSINHKGAirportPair, lSINHKGDatePeriod);
    FacBomManager::linkWithParent (lSINHKGAirportPair, lSINHKGDatePeriod);    

    // Set the point-of-sale-channel primary key.
    lPosChannelKey = PosChannelKey("SIN","IN");  
    
    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lOnDSINPosChannel =
      FacBom<PosChannel>::instance().create (lPosChannelKey);
    FacBomManager::addToListAndMap (lSINHKGDatePeriod, lOnDSINPosChannel);
    FacBomManager::linkWithParent (lSINHKGDatePeriod, lOnDSINPosChannel);
   
    // Set the fare time-period primary key.
    // Use the same as previously.

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lSINHKGFareTimePeriod =
      FacBom<TimePeriod>::instance().create (lFareTimePeriodKey);
    FacBomManager::addToListAndMap (lOnDSINPosChannel, lSINHKGFareTimePeriod);
    FacBomManager::linkWithParent (lOnDSINPosChannel, lSINHKGFareTimePeriod);

    // Generate the FareRule
    // Use the same key as previously.

    // Create the FareFeaturesKey and link it to the TimePeriod object.
    FareFeatures& lSINHKGFareFeatures =
      FacBom<FareFeatures>::instance().create (lFareFeaturesKey);
    FacBomManager::addToListAndMap (lSINHKGFareTimePeriod, lSINHKGFareFeatures);
    FacBomManager::linkWithParent (lSINHKGFareTimePeriod, lSINHKGFareFeatures);

    // Generate Segment Features and link them to their FareRule.
    AirlineCodeList_T lSQ_CXAirlineCodeList;
    lSQ_CXAirlineCodeList.push_back ("SQ");
    lSQ_CXAirlineCodeList.push_back ("CX");

    ClassList_StringList_T lY_YClassCodeList;
    lY_YClassCodeList.push_back ("Y");
    lY_YClassCodeList.push_back ("Y");
    const AirlineClassListKey lSQ_CXAirlineYClassListKey (lSQ_CXAirlineCodeList,
                                                          lY_YClassCodeList);

    ClassList_StringList_T lM_MClassCodeList;
    lM_MClassCodeList.push_back ("M");
    lM_MClassCodeList.push_back ("M");
    const AirlineClassListKey lSQ_CXAirlineMClassListKey (lSQ_CXAirlineCodeList,
                                                          lM_MClassCodeList);

    // Create the AirlineClassListKey and link it to the FareFeatures object.
    AirlineClassList& lSQ_CXAirlineYClassList =
      FacBom<AirlineClassList>::instance().create (lSQ_CXAirlineYClassListKey);
    lSQ_CXAirlineYClassList.setFare(1200);
    FacBomManager::addToListAndMap (lSINHKGFareFeatures, 
				    lSQ_CXAirlineYClassList);
    FacBomManager::linkWithParent (lSINHKGFareFeatures, 
				   lSQ_CXAirlineYClassList);
    
    AirlineClassList& lSQ_CXAirlineMClassList =
      FacBom<AirlineClassList>::instance().create (lSQ_CXAirlineMClassListKey);
    lSQ_CXAirlineMClassList.setFare(850);
    FacBomManager::addToListAndMap (lSINHKGFareFeatures, 
				    lSQ_CXAirlineMClassList);
    FacBomManager::linkWithParent (lSINHKGFareFeatures, 
				   lSQ_CXAirlineMClassList);


    ////////////////////// AirRAC //////////////////////

    /*===================================================================================*/

    // Use the same airport pair, and date period for adding SQ SIN-BKK yields.
    
    // Set the point-of-sale-channel primary key.
    lPosChannelKey = PosChannelKey(DEFAULT_POS, DEFAULT_CHANNEL);  
    
    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lRAC_SINBKKPosChannel =
      FacBom<PosChannel>::instance().create (lPosChannelKey);
    FacBomManager::addToListAndMap (lSINBKKDatePeriod, lRAC_SINBKKPosChannel);
    FacBomManager::linkWithParent (lSINBKKDatePeriod, lRAC_SINBKKPosChannel);
   
    // Set the yield time-period primary key.
    const TimePeriodKey lYieldTimePeriodKey (lTimeRangeStart,
                                            lTimeRangeEnd);

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lSINBKKYieldTimePeriod =
      FacBom<TimePeriod>::instance().create (lYieldTimePeriodKey);
    FacBomManager::addToListAndMap (lRAC_SINBKKPosChannel, 
				    lSINBKKYieldTimePeriod);
    FacBomManager::linkWithParent (lRAC_SINBKKPosChannel, 
				   lSINBKKYieldTimePeriod);        

    // Generate the YieldRule
    const YieldFeaturesKey lYieldFeaturesKey (TRIP_TYPE_ONE_WAY,
                                              CABIN_Y);

    // Create the YieldFeaturesKey and link it to the TimePeriod object.
    YieldFeatures& lSINBKKYieldFeatures =
      FacBom<YieldFeatures>::instance().create (lYieldFeaturesKey);
    FacBomManager::addToListAndMap (lSINBKKYieldTimePeriod,
				    lSINBKKYieldFeatures);
    FacBomManager::linkWithParent (lSINBKKYieldTimePeriod, 
				   lSINBKKYieldFeatures);        

    // Generate Segment Features and link them to their YieldRule.
    // Use the same key as previously.

    // Create the AirlineClassListKey and link it to the YieldFeatures object.
    AirlineClassList& lRAC_SQAirlineYClassList =
      FacBom<AirlineClassList>::instance().create (lSQAirlineYClassListKey);
    lRAC_SQAirlineYClassList.setYield(700);
    FacBomManager::addToListAndMap (lSINBKKYieldFeatures, 
				    lRAC_SQAirlineYClassList);
    FacBomManager::linkWithParent (lSINBKKYieldFeatures, 
				   lRAC_SQAirlineYClassList);

    AirlineClassList& lRAC_SQAirlineMClassList =
      FacBom<AirlineClassList>::instance().create (lSQAirlineMClassListKey);
    lRAC_SQAirlineMClassList.setYield(500);
    FacBomManager::addToListAndMap (lSINBKKYieldFeatures, 
				    lRAC_SQAirlineMClassList);
    FacBomManager::linkWithParent (lSINBKKYieldFeatures, 
				   lRAC_SQAirlineMClassList);

    /*===================================================================================*/

    // Use the same airport pair, and date period for adding CX BKK-HKG yields. 
    
    // Set the point-of-sale-channel primary key.
    // Use the same as previously.
    
    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lRAC_BKKHKGPosChannel =
      FacBom<PosChannel>::instance().create (lPosChannelKey);
    FacBomManager::addToListAndMap (lBKKHKGDatePeriod, lRAC_BKKHKGPosChannel);
    FacBomManager::linkWithParent (lBKKHKGDatePeriod, lRAC_BKKHKGPosChannel);
   
    // Set the yield time-period primary key.
    // Use the same as previously.

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lBKKHKGYieldTimePeriod =
      FacBom<TimePeriod>::instance().create (lYieldTimePeriodKey);
    FacBomManager::addToListAndMap (lRAC_BKKHKGPosChannel, 
				    lBKKHKGYieldTimePeriod);
    FacBomManager::linkWithParent (lRAC_BKKHKGPosChannel, 
				   lBKKHKGYieldTimePeriod);        

    // Generate the YieldRule
    // Use the same key as previously.

    // Create the YieldFeaturesKey and link it to the TimePeriod object.
    YieldFeatures& lBKKHKGYieldFeatures =
      FacBom<YieldFeatures>::instance().create (lYieldFeaturesKey);
    FacBomManager::addToListAndMap (lBKKHKGYieldTimePeriod, 
				    lBKKHKGYieldFeatures);
    FacBomManager::linkWithParent (lBKKHKGYieldTimePeriod, 
				   lBKKHKGYieldFeatures);        

    // Generate Segment Features and link them to their YieldRule.
    // Use the same key as previously.

    // Create the AirlineClassListKey and link it to the YieldFeatures object.
    AirlineClassList& lRAC_CXAirlineYClassList =
      FacBom<AirlineClassList>::instance().create (lCXAirlineYClassListKey);
    lRAC_CXAirlineYClassList.setYield(700);
    FacBomManager::addToListAndMap (lBKKHKGYieldFeatures, 
				    lRAC_CXAirlineYClassList);
    FacBomManager::linkWithParent (lBKKHKGYieldFeatures, 
				   lRAC_CXAirlineYClassList);
    
    AirlineClassList& lRAC_CXAirlineMClassList =
      FacBom<AirlineClassList>::instance().create (lCXAirlineMClassListKey);
    lRAC_CXAirlineMClassList.setYield(500);
    FacBomManager::addToListAndMap (lBKKHKGYieldFeatures, 
				    lRAC_CXAirlineMClassList);
    FacBomManager::linkWithParent (lBKKHKGYieldFeatures, 
				   lRAC_CXAirlineMClassList);

    /*===================================================================================*/

    // Use the same airport pair, and date period for SQ-CX SIN-HKG

    // Set the point-of-sale-channel primary key.
    // Use the same as previously.
    
    // Create the PositionKey object and link it to the AirportPair object.
    PosChannel& lRAC_SINHKGChannel =
      FacBom<PosChannel>::instance().create (lPosChannelKey);
    FacBomManager::addToListAndMap (lSINHKGDatePeriod, lRAC_SINHKGChannel);
    FacBomManager::linkWithParent (lSINHKGDatePeriod, lRAC_SINHKGChannel);
   
    // Set the yield time-period primary key.
    // Use the same as previously.

    // Create the TimePeriodKey and link it to the DatePeriod object.
    TimePeriod& lSINHKGYieldTimePeriod =
      FacBom<TimePeriod>::instance().create (lYieldTimePeriodKey);
    FacBomManager::addToListAndMap (lRAC_SINHKGChannel, lSINHKGYieldTimePeriod);
    FacBomManager::linkWithParent (lRAC_SINHKGChannel, lSINHKGYieldTimePeriod);  

    // Generate the YieldRule
    // Use the same key as previously.

    // Create the YieldFeaturesKey and link it to the TimePeriod object.
    YieldFeatures& lSINHKGYieldFeatures =
      FacBom<YieldFeatures>::instance().create (lYieldFeaturesKey);
    FacBomManager::addToListAndMap (lSINHKGYieldTimePeriod, 
				    lSINHKGYieldFeatures);
    FacBomManager::linkWithParent (lSINHKGYieldTimePeriod, 
				   lSINHKGYieldFeatures);        

    // Generate Segment Features and link them to their YieldRule.
    // Use the same key as previously
    
    // Create the AirlineClassListKey and link it to the YieldFeatures object.
    AirlineClassList& lRAC_SQ_CXAirlineYClassList =
      FacBom<AirlineClassList>::instance().create (lSQ_CXAirlineYClassListKey);
    lRAC_SQ_CXAirlineYClassList.setYield(1200);
    FacBomManager::addToListAndMap (lSINHKGYieldFeatures, 
				    lRAC_SQ_CXAirlineYClassList);
    FacBomManager::linkWithParent (lSINHKGYieldFeatures, 
				   lRAC_SQ_CXAirlineYClassList);
    
    AirlineClassList& lRAC_SQ_CXAirlineMClassList =
      FacBom<AirlineClassList>::instance().create (lSQ_CXAirlineMClassListKey);
    lRAC_SQ_CXAirlineMClassList.setYield(850);
    FacBomManager::addToListAndMap (lSINHKGYieldFeatures, 
				    lRAC_SQ_CXAirlineMClassList);
    FacBomManager::linkWithParent (lSINHKGYieldFeatures, 
				   lRAC_SQ_CXAirlineMClassList);
    
  }

}

/*!
 * \endcode
 */
