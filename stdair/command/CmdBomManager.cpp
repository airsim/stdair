// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
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
#include <stdair/bom/BomManager.hpp>
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
    Inventory& lBAInv =
      FacBom<Inventory>::instance().create (lBAKey);
    FacBomManager::instance().addToList (ioBomRoot, lBAInv);

    // Create an Inventory for AF
    const InventoryKey lAFKey ("AF");
    Inventory& lAFInv =
      FacBom<Inventory>::instance().create (lAFKey);
    FacBomManager::instance().addToList (ioBomRoot, lAFInv);

    // ////// BA ///////    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA9/10-JUN-2011) for BA's Inventory
    FlightNumber_T lFlightNumber = 9;
    Date_T lDate (2011, 6, 10);
    FlightDateKey lFlightDateKey (lFlightNumber, lDate);

    FlightDate& lBA9_20110610_FD =
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::instance().addToList (lBAInv, lBA9_20110610_FD);
    
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
    FacBomManager::instance().addToList (lBA9_20110610_FD, lLHRSYDSegment);

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
    FacBomManager::instance().addToList (lBA9_20110610_FD, lLHRBKKSegment);

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
    FacBomManager::instance().addToList (lBA9_20110610_FD, lBKKSYDSegment);

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

    LegDate& lLHRLeg =
      FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::instance().addToList (lBA9_20110610_FD, lLHRLeg);

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

    LegDate& lBKKLeg =
      FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::instance().addToList (lBA9_20110610_FD, lBKKLeg);

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
    const CabinCode_T lY ("Y");
    SegmentCabinKey lYSegmentCabinKey (lY);

    SegmentCabin& lLHRBKKSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::instance().addToList (lLHRBKKSegment, lLHRBKKSegmentYCabin);

    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRBKKSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment BKK-SYD;
    SegmentCabin& lBKKSYDSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::instance().addToList (lBKKSYDSegment, lBKKSYDSegmentYCabin);
     
    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lBKKSYDSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment LHR-SYD;
    SegmentCabin& lLHRSYDSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::instance().addToList (lLHRSYDSegment, lLHRSYDSegmentYCabin);
      
    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRSYDSegmentYCabin.toString());

    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) for the Leg LHR-BKK on BA's Inventory
    LegCabinKey lYLegCabinKey (lY);

    LegCabin& lLHRLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::instance().addToList (lLHRLeg, lLHRLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Create a LegCabin (Y) for the Leg BKK-SYD
    LegCabin& lBKKLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::instance().addToList (lBKKLeg, lBKKLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lBKKLegYCabin.toString());

    // Step 0.7: fare family level
    // Create a FareFamily (1) for the Segment LHR-BKK, cabin Y on BA's Inv
    const FamilyCode_T l1 ("EcoSaver");
    FareFamilyKey l1FareFamilyKey (l1);

    FareFamily& lLHRBKKSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::instance().addToList (lLHRBKKSegmentYCabin,
                                         lLHRBKKSegmentYCabin1Family);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("FareFamily: "
    //                   << lLHRBKKSegmentYCabin1Family.toString());

    // Create a FareFamily (1)  for the Segment BKK-SYD, cabin Y on BA's Inv
    FareFamily& lBKKSYDSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::instance().addToList (lBKKSYDSegmentYCabin,
                                         lBKKSYDSegmentYCabin1Family);
    
    // Display the booking class
    // STDAIR_LOG_DEBUG ("FareFamily: "
    //                   << lLHRBKKSegmentYCabin1Family.toString());

    // Create a FareFamily (1)  for the Segment LHR-SYD, cabin Y on BA's Inv
    FareFamily& lLHRSYDSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::instance().addToList (lLHRSYDSegmentYCabin,
                                         lLHRSYDSegmentYCabin1Family);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("FareFamily: "
    //                   << lLHRBKKSegmentYCabin1Family.toString());


    // Step 0.8: booking class level Create a BookingClass (Q) for the
    // Segment LHR-BKK, cabin Y, fare family 1 on BA's Inv
    const ClassCode_T lQ ("Q");
    BookingClassKey lQBookingClassKey (lQ);

    BookingClass& lLHRBKKSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::instance().addToList (lLHRBKKSegmentYCabin1Family,
                                         lLHRBKKSegmentYCabin1FamilyQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lLHRBKKSegmentYCabin1FamilyQClass.toString());

    // Create a BookingClass (Q) for the Segment BKK-SYD, cabin Y,
    // fare family 1 on BA's Inv
    BookingClass& lBKKSYDSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::instance().addToList (lBKKSYDSegmentYCabin1Family,
                                         lBKKSYDSegmentYCabin1FamilyQClass);
    
    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lLHRBKKSegmentYCabin1FamilyQClass.toString());

    // Create a BookingClass (Q) for the Segment LHR-SYD, cabin Y,
    // fare family 1 on BA's Inv
    BookingClass& lLHRSYDSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::instance().addToList (lLHRSYDSegmentYCabin1Family,
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
    FacBomManager::instance().addToList (lAFInv, lAF084_20110320_FD);
    
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
    FacBomManager::instance().addToList (lAF084_20110320_FD, lCDGSFOSegment);

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
    FacBomManager::instance().addToList (lAF084_20110320_FD, lCDGLeg);

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
    SegmentCabin& lCDGSFOSegmentYCabin =
      FacBom<SegmentCabin>::instance().create (lYSegmentCabinKey);
    FacBomManager::instance().addToList (lCDGSFOSegment, lCDGSFOSegmentYCabin);

    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lCDGSFOSegmentYCabin.toString());

    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) for the Leg CDG-SFO on AF's Inventory
    LegCabin& lCDGLegYCabin =
      FacBom<LegCabin>::instance().create (lYLegCabinKey);
    FacBomManager::instance().addToList (lCDGLeg, lCDGLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());


    // Step 0.7: fare family level
    // Create a fareFamily (1) for the Segment CDG-SFO, cabin Y on AF's Inv
    FareFamily& lCDGSFOSegmentYCabin1Family =
      FacBom<FareFamily>::instance().create (l1FareFamilyKey);
    FacBomManager::instance().addToList (lCDGSFOSegmentYCabin,
                                         lCDGSFOSegmentYCabin1Family);

    // Display the fare family
    // STDAIR_LOG_DEBUG ("fareFamily: "
    //
    //                   << lCDGSFOSegmentYCabin1Family.toString());

    // Step 0.8: booking class level Create a BookingClass (Q) for the
    // Segment CDG-SFO, cabin Y, fare family 1 on AF's Inv
    BookingClass& lCDGSFOSegmentYCabin1FamilyQClass =
      FacBom<BookingClass>::instance().create (lQBookingClassKey);
    FacBomManager::instance().addToList (lCDGSFOSegmentYCabin1Family,
                                         lCDGSFOSegmentYCabin1FamilyQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lCDGSFOSegmentYCabin1FamilyQClass.toString());
  }
  
  // //////////////////////////////////////////////////////////////////////
  void CmdBomManager::buildSampleBomForRMOL (BomRoot& ioBomRoot,
                                             const CabinCapacity_T& iCapacity) {
    // Inventory
    const InventoryKey lInventoryKey ("DEFAULT_AIRLINE_CODE");
    Inventory& lInv =
      FacBom<Inventory>::instance().create (lInventoryKey);
    FacBomManager::instance().addToList (ioBomRoot, lInv);

    // Flight-date
    FlightDateKey lFlightDateKey (DEFAULT_FLIGHT_NUMBER, DEFAULT_FLIGHT_DATE);

    FlightDate& lFlightDate =
      FacBom<FlightDate>::instance().create (lFlightDateKey);
    FacBomManager::instance().addToList (lInv, lFlightDate);

    // Leg-date
    LegDateKey lLegDateKey (DEFAULT_ORIGIN);

    LegDate& lLeg = FacBom<LegDate>::instance().create (lLegDateKey);
    FacBomManager::instance().addToList (lFlightDate, lLeg);

    // Leg-cabin
    LegCabinKey lLegCabinKey (DEFAULT_CABIN_CODE);

    LegCabin& lLegCabin =
      FacBom<LegCabin>::instance().create (lLegCabinKey);
    FacBomManager::instance().addToList (lLeg, lLegCabin);

    lLegCabin.setCapacities (iCapacity);

    // Segment-date
    SegmentDateKey lSegmentDateKey (DEFAULT_ORIGIN, DEFAULT_DESTINATION);

    SegmentDate& lSegment =
      FacBom<SegmentDate>::instance().create (lSegmentDateKey);
    FacBomManager::instance().addToList (lFlightDate, lSegment);
    FacBomManager::instance().addToList (lLeg, lSegment);
    FacBomManager::instance().addToList (lSegment, lLeg);

    // Segment-cabin
    SegmentCabinKey lSegmentCabinKey (DEFAULT_CABIN_CODE);

    SegmentCabin& lSegmentCabin =
      FacBom<SegmentCabin>::instance().create (lSegmentCabinKey);
    FacBomManager::instance().addToList (lSegment, lSegmentCabin);
    FacBomManager::instance().addToList (lLegCabin, lSegmentCabin);
    FacBomManager::instance().addToList (lSegmentCabin, lLegCabin);
  }
  
}
