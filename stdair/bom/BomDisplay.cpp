// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <ostream>
// StdAir
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomDisplay.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvDisplay (std::ostream& oStream,
                               const BomRoot& iBomRoot) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
     * Bom root level (only)
     */
    oStream << std::endl;
    oStream << "==============================================================="
            << std::endl;
    oStream << "BomRoot: " << iBomRoot.describeKey() << std::endl;
    oStream << "==============================================================="
            << std::endl;

    // Browse the inventories
    const InventoryList_T& lInventoryList =
      BomManager::getList<Inventory> (iBomRoot);
    for (InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const Inventory* lInv_ptr = *itInv;
      assert (lInv_ptr != NULL);

      // Display the inventory
      csvDisplay (oStream, *lInv_ptr);
    }
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvDisplay (std::ostream& oStream,
                               const Inventory& iInventory) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
     * Inventory level (only)
     */
    oStream << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    oStream << "Inventory: " << iInventory.describeKey() << std::endl;
    oStream << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    
    // Browse the flight-dates
    const FlightDateList_T& lFlightDateList =
      BomManager::getList<FlightDate> (iInventory);
    for (FlightDateList_T::const_iterator itFD = lFlightDateList.begin();
         itFD != lFlightDateList.end(); ++itFD) {
      const FlightDate* lFD_ptr = *itFD;
      assert (lFD_ptr != NULL);
      
      // Display the flight-date
      csvDisplay (oStream, *lFD_ptr);
    }   
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvDisplay (std::ostream& oStream,
                               const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
     * Flight-date level (only)
     */
    oStream << "******************************************" << std::endl;
    oStream << "FlightDate: " << iFlightDate.describeKey()  << std::endl;
    oStream << "******************************************" << std::endl;

    //
    csvLegDateDisplay (oStream, iFlightDate);

    //
    csvLegCabinDisplay (oStream, iFlightDate);

    //
    csvFareFamilyDisplay (oStream, iFlightDate);

    //
    csvBookingClassDisplay (oStream, iFlightDate);

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvLegDateDisplay (std::ostream& oStream,
                                      const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
     * Leg-date level (only).
     *
     * Display the header.
     */
      oStream << "******************************************" << std::endl;
      oStream << "Leg-Dates:" << std::endl
              << "----------" << std::endl;
      oStream << "FlightNb (FlightDate), Leg, BoardDate, BoardTime, "
              << "OffDate, OffTime, Date Offset, Time Offset, Elapsed, "
              << "Distance, Capacity, "
              << std::endl << std::endl;

      // Retrieve the key of the flight-date
      const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
      const Date_T& lFlightDateDate = iFlightDate.getFlightDate();

      // Browse the leg-dates
      const LegDateList_T& lLegDateList =
        BomManager::getList<LegDate> (iFlightDate);
      for (LegDateList_T::const_iterator itLD = lLegDateList.begin();
           itLD != lLegDateList.end(); ++itLD) {
        const LegDate* lLD_ptr = *itLD;
        assert (lLD_ptr != NULL);
      
        oStream << lFlightNumber << " (" << lFlightDateDate << "), ";
        oStream << lLD_ptr->getBoardingPoint() << "-"
                << lLD_ptr->getOffPoint() << ", "
                << lLD_ptr->getBoardingDate() << ", "
                << lLD_ptr->getBoardingTime() << ", "
                << lLD_ptr->getOffDate() << ", "
                << lLD_ptr->getOffTime() << ", "
                << lLD_ptr->getElapsedTime() << ", "
                << lLD_ptr->getDateOffset() << ", "
                << lLD_ptr->getTimeOffset() << ", "
                << lLD_ptr->getDistance() << ", "
                << lLD_ptr->getCapacity() << ", "
                << std::endl;
      }
      oStream << "******************************************" << std::endl;
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvSegmentDateDisplay (std::ostream& oStream,
                                          const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
     * Segment-date level (only)
     */
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvLegCabinDisplay (std::ostream& oStream,
                                       const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
     * Leg-cabin level (only)
     */
      oStream << "******************************************" << std::endl;
      oStream << "LegCabins:" << std::endl
                  << "----------" << std::endl;
      oStream << "FlightNb (FlightDate), Leg, Cabin, "
              << "OffedCAP, PhyCAP, RgdADJ, AU, UPR, SS, Staff, WL, Group, "
              << "CommSpace, AvPool, Avl, NAV, GAV, ACP, ETB, BidPrice, "
              << std::endl;

      // Retrieve the key of the flight-date
      const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
      const Date_T& lFlightDateDate = iFlightDate.getFlightDate();

      // Browse the leg-dates
      const LegDateList_T& lLegDateList =
        BomManager::getList<LegDate> (iFlightDate);
      for (LegDateList_T::const_iterator itLD = lLegDateList.begin();
           itLD != lLegDateList.end(); ++itLD) {
        const LegDate* lLD_ptr = *itLD;
        assert (lLD_ptr != NULL);
      
        // Retrieve the key of the leg-date, as well as its off point
        const AirportCode_T& lBoardPoint = lLD_ptr->getBoardingPoint();
        const AirportCode_T& lOffPoint = lLD_ptr->getOffPoint();

        // Browse the leg-cabins
        const LegCabinList_T& lLegCabinList =
          BomManager::getList<LegCabin> (*lLD_ptr);
        for (LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
             itLC != lLegCabinList.end(); ++itLC) {
          const LegCabin* lLC_ptr = *itLC;
          assert (lLC_ptr != NULL);
      
          oStream << lFlightNumber << " (" << lFlightDateDate << "), ";
          oStream << lBoardPoint << "-" << lOffPoint << ", ";
          
          oStream << lLC_ptr->getCabinCode() << ", ";

          oStream << lLC_ptr->getOfferedCapacity() << ", "
                  << lLC_ptr->getPhysicalCapacity() << ", "
                  << lLC_ptr->getRegradeAdjustment() << ", "
                  << lLC_ptr->getAuthorizationLevel() << ", "
                  << lLC_ptr->getUPR() << ", "
                  << lLC_ptr->getSoldSeat() << ", "
                  << lLC_ptr->getStaffNbOfSeats() << ", "
                  << lLC_ptr->getWLNbOfSeats() << ", "
                  << lLC_ptr->getGroupNbOfSeats() << ", "
                  << lLC_ptr->getCommittedSpace() << ", "
                  << lLC_ptr->getAvailabilityPool() << ", "
                  << lLC_ptr->getAvailability() << ", "
                  << lLC_ptr->getNetAvailability() << ", "
                  << lLC_ptr->getGrossAvailability() << ", "
                  << lLC_ptr->getAvgCancellationPercentage() << ", "
                  << lLC_ptr->getETB() << ", "
                  << lLC_ptr->getCurrentBidPrice() << ", "
                  << std::endl;
        }
      }
      oStream << "******************************************" << std::endl;
      
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvSegmentCabinDisplay (std::ostream& oStream,
                                           const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
     * Segment-cabin level (only)
     */

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvFareFamilyDisplay (std::ostream& oStream,
                                         const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
     * Fare family level (only)
     */

    oStream << "******************************************" << std::endl;
    oStream << "SegmentCabins:" << std::endl
            << "--------------" << std::endl;
    oStream << "Segment, Cabin, FF, Bkgs, MIN, UPR, "
            << "CommSpace, AvPool, BP, " << std::endl;
    
    // Retrieve the key of the flight-date
    // const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    // const Date_T& lFlightDateDate = iFlightDate.getFlightDate();

    // Browse the segment-dates
    const SegmentDateList_T& lSegmentDateList =
      BomManager::getList<SegmentDate> (iFlightDate);
    for (SegmentDateList_T::const_iterator itSD = lSegmentDateList.begin();
         itSD != lSegmentDateList.end(); ++itSD) {
      const SegmentDate* lSD_ptr = *itSD;
      assert (lSD_ptr != NULL);
      
      // Retrieve the key of the segment-date, as well as its dates
      const AirportCode_T& lBoardPoint = lSD_ptr->getBoardingPoint();
      const AirportCode_T& lOffPoint = lSD_ptr->getOffPoint();

      // Browse the segment-cabins
      const SegmentCabinList_T& lSegmentCabinList =
        BomManager::getList<SegmentCabin> (*lSD_ptr);
      for (SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
           itSC != lSegmentCabinList.end(); ++itSC) {
        const SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);
        
        // Retrieve the key of the segment-cabin
        const CabinCode_T& lCabinCode = lSC_ptr->getCabinCode();

        // Browse the fare families
        const FareFamilyList_T& lFareFamilyList =
          BomManager::getList<FareFamily> (*lSC_ptr);
        for (FareFamilyList_T::const_iterator itFF = lFareFamilyList.begin();
             itFF != lFareFamilyList.end(); ++itFF) {
          const FareFamily* lFF_ptr = *itFF;
          assert (lFF_ptr != NULL);
          
          // Display the fare family
          oStream << lBoardPoint << "-" << lOffPoint << ", ";
          oStream << lCabinCode << ", " << lFF_ptr->getFamilyCode() << ", ";
          oStream << lSC_ptr->getBookingCounter() << ", "
                  << lSC_ptr->getMIN() << ", "
                  << lSC_ptr->getUPR() << ", "
                  << lSC_ptr->getCommittedSpace() << ", "
                  << lSC_ptr->getAvailabilityPool() << ", "
                  << lSC_ptr->getCurrentBidPrice() << ", "
                  << std::endl;
        }
      }
    }
    oStream << "******************************************" << std::endl;

    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvBookingClassDisplay (std::ostream& oStream,
                                           const FlightDate& iFlightDate) {
    // Store current formatting flags of the given output stream
    std::ios::fmtflags oldFlags = oStream.flags();

    /**
     * Booking-class level (only)
     */
    oStream << "******************************************" << std::endl;
    oStream << "Subclasses:" << std::endl
            << "-----------" << std::endl;
    oStream << "Segment, Cabin, Subclass, MIN, N, MAX, N, "
            << "Bkgs, WL-Bkgs, "
            << "OB%, SEs, NewSEs, "
            << "UPR, CUPR, CnUPR, tmpUPR, FctdBkgs, "
            << "MNO, NewMNO, CMNO, SEChange, "
            << "GrUpMAX, RmgMAX, "
            << "ClassAvl, RevAvl, SegAvl, FLDYield, SDRYield, FavAvl, "
            << "Low-NL, High-NL, ProfName, ProfType, NoShow, NegoSeats, "
            << std::endl;
    
    // Retrieve the key of the flight-date
    // const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    // const Date_T& lFlightDateDate = iFlightDate.getFlightDate();
    
    // Browse the segment-dates
    const SegmentDateList_T& lSegmentDateList =
      BomManager::getList<SegmentDate> (iFlightDate);
    for (SegmentDateList_T::const_iterator itSD = lSegmentDateList.begin();
         itSD != lSegmentDateList.end(); ++itSD) {
      const SegmentDate* lSD_ptr = *itSD;
      assert (lSD_ptr != NULL);
      
      // Retrieve the key of the segment-date, as well as its dates
      const AirportCode_T& lBoardPoint = lSD_ptr->getBoardingPoint();
      const AirportCode_T& lOffPoint = lSD_ptr->getOffPoint();
      
      // Browse the segment-cabins
      const SegmentCabinList_T& lSegmentCabinList =
        BomManager::getList<SegmentCabin> (*lSD_ptr);
      for (SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
           itSC != lSegmentCabinList.end(); ++itSC) {
        const SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);
        
        // Retrieve the key of the segment-cabin
        const CabinCode_T& lCabinCode = lSC_ptr->getCabinCode();
        
        // Browse the fare families
        const FareFamilyList_T& lFareFamilyList =
          BomManager::getList<FareFamily> (*lSC_ptr);
        for (FareFamilyList_T::const_iterator itFF = lFareFamilyList.begin();
             itFF != lFareFamilyList.end(); ++itFF) {
          const FareFamily* lFF_ptr = *itFF;
          assert (lFF_ptr != NULL);
          
          // Retrieve the key of the segment-cabin
          const FamilyCode_T& lFamilyCode = lFF_ptr->getFamilyCode();
        
          // Browse the booking-classes
          const BookingClassList_T& lBookingClassList =
            BomManager::getList<BookingClass> (*lFF_ptr);
          for (BookingClassList_T::const_iterator itBC =
                 lBookingClassList.begin();
               itBC != lBookingClassList.end(); ++itBC) {
            const BookingClass* lBC_ptr = *itBC;
            assert (lBC_ptr != NULL);
            
            oStream << lBoardPoint << "-" << lOffPoint << ", ";
            oStream << lCabinCode << ", " << lFamilyCode << ", "
                    << lBC_ptr->getClassCode();
            if (lBC_ptr->getSubclassCode() != 0) {
              oStream << ", ";
            } else {
              oStream << lBC_ptr->getSubclassCode() << ", ";
            }
            oStream << lBC_ptr->getAuthorizationLevel() << " ("
                    << lBC_ptr->getProtection() << "), "
                    << lBC_ptr->getNegotiatedSpace() << ", "
                    << lBC_ptr->getNoShowPercentage() << ", "
                    << lBC_ptr->getOverbookingPercentage() << ", "
                    << lBC_ptr->getNbOfBookings() << ", "
                    << lBC_ptr->getNbOfGroupBookings() << ", "
                    << lBC_ptr->getNbOfPendingGroupBookings() << ", "
                    << lBC_ptr->getNbOfStaffBookings() << ", "
                    << lBC_ptr->getNbOfWLBookings() << ", "
                    << lBC_ptr->getETB() << ", "
                    << lBC_ptr->getNetClassAvailability() << ", "
                    << lBC_ptr->getSegmentAvailability() << ", "
                    << lBC_ptr->getNetRevenueAvailability() << ", "
                    << std::endl;
          }
        }
      }
    }
    oStream << "******************************************" << std::endl;
    
    // Reset formatting flags of the given output stream
    oStream.flags (oldFlags);
  }
    
}
