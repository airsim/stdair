// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <ostream>
// StdAir
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/Bucket.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/BomDisplay.hpp>

namespace stdair {

  /**
   * Helper singleton structure to store the current formatting flags
   * of any given output stream. The flags are re-set at the
   * structure destruction.
   */
  struct FlagSaver {
  public:
    /** Constructor. */
    FlagSaver (std::ostream& oStream)
      : _oStream (oStream), _streamFlags (oStream.flags()) {
    }

    /** Destructor. */
    ~FlagSaver() {
      // Reset formatting flags of the given output stream
      _oStream.flags (_streamFlags);
    }
    
  private:
    /** Reference on the STL stream, for which the flags must be saved. */
    std::ostream& _oStream;
    /** Saved STL stream flags. */
    std::ios::fmtflags _streamFlags;
  };

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvDisplay (std::ostream& oStream,
                               const BomRoot& iBomRoot) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Bom root level (only)
     */
    oStream << std::endl;
    oStream << "==============================================================="
            << std::endl;
    oStream << "BomRoot: " << iBomRoot.describeKey() << std::endl;
    oStream << "==============================================================="
            << std::endl;

    // Check whether there are Inventory objects
    if (BomManager::hasList<Inventory> (iBomRoot) == false) {
      return;
    }
    
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
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvDisplay (std::ostream& oStream,
                               const Inventory& iInventory) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Inventory level (only)
     */
    oStream << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    oStream << "Inventory: " << iInventory.describeKey() << std::endl;
    oStream << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    
    // Check whether there are FlightDate objects
    if (BomManager::hasList<FlightDate> (iInventory) == false) {
      return;
    }
    
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
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvDisplay (std::ostream& oStream,
                               const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Flight-date level (only)
     */
    const AirlineCode_T& lAirlineCode = iFlightDate.getAirlineCode();
    oStream << "******************************************" << std::endl;
    oStream << "FlightDate: " << lAirlineCode << iFlightDate.describeKey()
            << std::endl;
    oStream << "******************************************" << std::endl;

    //
    csvLegDateDisplay (oStream, iFlightDate);

    //
    csvLegCabinDisplay (oStream, iFlightDate);

    //
    csvBucketDisplay (oStream, iFlightDate);

    //
    csvFareFamilyDisplay (oStream, iFlightDate);

    //
    csvBookingClassDisplay (oStream, iFlightDate);
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvLegDateDisplay (std::ostream& oStream,
                                      const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Leg-date level (only).
     *
     * Display the header.
     */
    oStream << "******************************************" << std::endl;
    oStream << "Leg-Dates:" << std::endl
            << "----------" << std::endl;
    oStream << "Flight, Leg, BoardDate, BoardTime, "
            << "OffDate, OffTime, Date Offset, Time Offset, Elapsed, "
            << "Distance, Capacity, " << std::endl;

    // Retrieve the key of the flight-date
    const AirlineCode_T& lAirlineCode = iFlightDate.getAirlineCode();
    const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    const Date_T& lFlightDateDate = iFlightDate.getDepartureDate();

    // Check whether there are LegDate objects
    if (BomManager::hasList<LegDate> (iFlightDate) == false) {
      return;
    }
    
    // Browse the leg-dates
    const LegDateList_T& lLegDateList =
      BomManager::getList<LegDate> (iFlightDate);
    for (LegDateList_T::const_iterator itLD = lLegDateList.begin();
         itLD != lLegDateList.end(); ++itLD) {
      const LegDate* lLD_ptr = *itLD;
      assert (lLD_ptr != NULL);
      
      oStream << lAirlineCode << lFlightNumber << " "
              << lFlightDateDate << ", ";

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
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvSegmentDateDisplay (std::ostream& oStream,
                                          const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Segment-date level (only)
     */
    
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvLegCabinDisplay (std::ostream& oStream,
                                       const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Leg-cabin level (only)
     */
    oStream << "******************************************" << std::endl;
    oStream << "LegCabins:" << std::endl
            << "----------" << std::endl;
    oStream << "Flight, Leg, Cabin, "
            << "OffedCAP, PhyCAP, RgdADJ, AU, UPR, SS, Staff, WL, Group, "
            << "CommSpace, AvPool, Avl, NAV, GAV, ACP, ETB, BidPrice, "
            << std::endl;
    
    // Retrieve the key of the flight-date
    const AirlineCode_T& lAirlineCode = iFlightDate.getAirlineCode();
    const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    const Date_T& lFlightDateDate = iFlightDate.getDepartureDate();
    
    // Check whether there are LegDate objects
    if (BomManager::hasList<LegDate> (iFlightDate) == false) {
      return;
    }
    
    // Browse the leg-dates
    const LegDateList_T& lLegDateList =
      BomManager::getList<LegDate> (iFlightDate);
    for (LegDateList_T::const_iterator itLD = lLegDateList.begin();
         itLD != lLegDateList.end(); ++itLD) {
      const LegDate* lLD_ptr = *itLD;
      assert (lLD_ptr != NULL);

      // Retrieve the key of the leg-date, as well as its off point
      const Date_T& lLegDateDate = lLD_ptr->getBoardingDate();
      const AirportCode_T& lBoardPoint = lLD_ptr->getBoardingPoint();
      const AirportCode_T& lOffPoint = lLD_ptr->getOffPoint();

      // Browse the leg-cabins
      const LegCabinList_T& lLegCabinList =
        BomManager::getList<LegCabin> (*lLD_ptr);
      for (LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
           itLC != lLegCabinList.end(); ++itLC) {
        const LegCabin* lLC_ptr = *itLC;
        assert (lLC_ptr != NULL);
      
        oStream << lAirlineCode << lFlightNumber << " "
                << lFlightDateDate << ", ";

        oStream << lBoardPoint << "-" << lOffPoint
                << " " << lLegDateDate << ", ";

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
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvSegmentCabinDisplay (std::ostream& oStream,
                                           const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Segment-cabin level (only)
     */
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvFareFamilyDisplay (std::ostream& oStream,
                                         const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Fare family level (only)
     */

    oStream << "******************************************" << std::endl;
    oStream << "SegmentCabins:" << std::endl
            << "--------------" << std::endl;
    oStream << "Flight, Segment, Cabin, FF, Bkgs, MIN, UPR, "
            << "CommSpace, AvPool, BP, " << std::endl;
    
    // Retrieve the key of the flight-date
    const AirlineCode_T& lAirlineCode = iFlightDate.getAirlineCode();
    const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    const Date_T& lFlightDateDate = iFlightDate.getDepartureDate();

    // Check whether there are SegmentDate objects
    if (BomManager::hasList<SegmentDate> (iFlightDate) == false) {
      return;
    }
    
    // Browse the segment-dates
    const SegmentDateList_T& lSegmentDateList =
      BomManager::getList<SegmentDate> (iFlightDate);
    for (SegmentDateList_T::const_iterator itSD = lSegmentDateList.begin();
         itSD != lSegmentDateList.end(); ++itSD) {
      const SegmentDate* lSD_ptr = *itSD;
      assert (lSD_ptr != NULL);
      
      // Retrieve the key of the segment-date, as well as its dates
      const Date_T& lSegmentDateDate = lSD_ptr->getBoardingDate();
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

        // Check whether there are fare family objects
        if (BomManager::hasList<FareFamily> (*lSC_ptr) == false) {
          continue;
        }
    
        // Browse the fare families
        const FareFamilyList_T& lFareFamilyList =
          BomManager::getList<FareFamily> (*lSC_ptr);
        for (FareFamilyList_T::const_iterator itFF = lFareFamilyList.begin();
             itFF != lFareFamilyList.end(); ++itFF) {
          const FareFamily* lFF_ptr = *itFF;
          assert (lFF_ptr != NULL);

          oStream << lAirlineCode << lFlightNumber << " "
                  << lFlightDateDate << ", ";

          oStream << lBoardPoint << "-" << lOffPoint << " "
                  << lSegmentDateDate << ", ";

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
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvBucketDisplay (std::ostream& oStream,
                                     const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Bucket level (only)
     */
    oStream << "******************************************" << std::endl;
    oStream << "Buckets:" << std::endl
            << "--------" << std::endl;
    oStream << "Flight, Leg, Cabin, Yield, AU/SI, SS, AV, "
            << std::endl;

    // Retrieve the key of the flight-date
    const AirlineCode_T& lAirlineCode = iFlightDate.getAirlineCode();
    const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    const Date_T& lFlightDateDate = iFlightDate.getDepartureDate();

    // Check whether there are LegDate objects
    if (BomManager::hasList<LegDate> (iFlightDate) == false) {
      return;
    }
    
    // Browse the leg-dates
    const LegDateList_T& lLegDateList =
      BomManager::getList<LegDate> (iFlightDate);
    for (LegDateList_T::const_iterator itLD = lLegDateList.begin();
         itLD != lLegDateList.end(); ++itLD) {
      const LegDate* lLD_ptr = *itLD;
      assert (lLD_ptr != NULL);
      
      // Retrieve the key of the leg-date, as well as its off point
      const Date_T& lLegDateDate = lLD_ptr->getBoardingDate();
      const AirportCode_T& lBoardPoint = lLD_ptr->getBoardingPoint();
      const AirportCode_T& lOffPoint = lLD_ptr->getOffPoint();

      // Browse the leg-cabins
      const LegCabinList_T& lLegCabinList =
        BomManager::getList<LegCabin> (*lLD_ptr);
      for (LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
           itLC != lLegCabinList.end(); ++itLC) {
        const LegCabin* lLC_ptr = *itLC;
        assert (lLC_ptr != NULL);

        // Check whether there are bucket objects
        if (BomManager::hasList<Bucket> (*lLC_ptr) == false) {
          continue;
        }

        // Retrieve the key of the leg-cabin
        const CabinCode_T& lCabinCode = lLC_ptr->getCabinCode();      

        // Browse the buckets
        const BucketList_T& lBucketList = BomManager::getList<Bucket> (*lLC_ptr);
        for (BucketList_T::const_iterator itBuck = lBucketList.begin();
             itBuck != lBucketList.end(); ++itBuck) {
          const Bucket* lBucket_ptr = *itBuck;
          assert (lBucket_ptr != NULL);

          oStream << lAirlineCode << lFlightNumber << " "
                  << lFlightDateDate << ", ";

          oStream << lBoardPoint << "-" << lOffPoint << " "
                  << lLegDateDate << ", " << lCabinCode << ", ";

          oStream << lBucket_ptr->getYieldRangeUpperValue() << ", "
                  << lBucket_ptr->getSeatIndex() << ", "
                  << lBucket_ptr->getSoldSeats() << ", "
                  << lBucket_ptr->getAvailability() << ", ";
          oStream << std::endl;
        }
      }
    }
    oStream << "******************************************" << std::endl;
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvBookingClassDisplay (std::ostream& oStream,
                                           const BookingClass& iBookingClass,
                                           const std::string& iLeadingString) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Booking-class level (only)
     *
     * See the method below (csvBookingClassDisplay() at FlightDate level)
     * for the details of the header.
     */
    oStream << iLeadingString << iBookingClass.getClassCode();

    if (iBookingClass.getSubclassCode() == 0) {
      oStream << ", ";
    } else {
      oStream << iBookingClass.getSubclassCode() << ", ";
    }
    oStream << iBookingClass.getAuthorizationLevel() << " ("
            << iBookingClass.getProtection() << "), "
            << iBookingClass.getNegotiatedSpace() << ", "
            << iBookingClass.getNoShowPercentage() << ", "
            << iBookingClass.getOverbookingPercentage() << ", "
            << iBookingClass.getNbOfBookings() << ", "
            << iBookingClass.getNbOfGroupBookings() << " ("
            << iBookingClass.getNbOfPendingGroupBookings() << "), "
            << iBookingClass.getNbOfStaffBookings() << ", "
            << iBookingClass.getNbOfWLBookings() << ", "
            << iBookingClass.getETB() << ", "
            << iBookingClass.getNetClassAvailability() << ", "
            << iBookingClass.getNetRevenueAvailability() << ", "
            << iBookingClass.getSegmentAvailability() << ", "
            << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvBookingClassDisplay (std::ostream& oStream,
                                           const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Headers
    oStream << "******************************************" << std::endl;
    oStream << "Subclasses:" << std::endl
            << "-----------" << std::endl;
    oStream << "Flight, Segment, Cabin, FF, Subclass, MIN/AU (Prot), "
            << "Nego, NS%, OB%, "
            << "Bkgs, GrpBks (pdg), StfBkgs, WLBkgs, ETB, "
            << "ClassAvl, RevAvl, SegAvl, "
            << std::endl;

    // Retrieve the key of the flight-date
    const AirlineCode_T& lAirlineCode = iFlightDate.getAirlineCode();
    const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    const Date_T& lFlightDateDate = iFlightDate.getDepartureDate();
    
    // Check whether there are SegmentDate objects
    if (BomManager::hasList<SegmentDate> (iFlightDate) == false) {
      return;
    }
    
    // Browse the segment-dates
    const SegmentDateList_T& lSegmentDateList =
      BomManager::getList<SegmentDate> (iFlightDate);
    for (SegmentDateList_T::const_iterator itSD = lSegmentDateList.begin();
         itSD != lSegmentDateList.end(); ++itSD) {
      const SegmentDate* lSD_ptr = *itSD;
      assert (lSD_ptr != NULL);
      
      // Retrieve the key of the segment-date, as well as its dates
      const Date_T& lSegmentDateDate = lSD_ptr->getBoardingDate();
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
        
        // Build the leading string to be displayed
        std::ostringstream oLeadingStr;
        oLeadingStr << lAirlineCode << lFlightNumber << " "
                    << lFlightDateDate << ", "
                    << lBoardPoint << "-" << lOffPoint << " "
                    << lSegmentDateDate << ", "
                    << lCabinCode << ", ";

        // Default Fare Family code, when there are no FF
        FamilyCode_T lFamilyCode ("NoFF");

        // Check whether there are FareFamily objects
        if (BomManager::hasList<FareFamily> (*lSC_ptr) == true) {

          // Browse the fare families
          const FareFamilyList_T& lFareFamilyList =
            BomManager::getList<FareFamily> (*lSC_ptr);
          for (FareFamilyList_T::const_iterator itFF = lFareFamilyList.begin();
               itFF != lFareFamilyList.end(); ++itFF) {
            const FareFamily* lFF_ptr = *itFF;
            assert (lFF_ptr != NULL);

            // Retrieve the key of the segment-cabin
            lFamilyCode = lFF_ptr->getFamilyCode();

            // Complete the leading string to be displayed
            oLeadingStr << lFamilyCode << ", ";

            // Browse the booking-classes
            const BookingClassList_T& lBookingClassList =
              BomManager::getList<BookingClass> (*lFF_ptr);
            for (BookingClassList_T::const_iterator itBC =
                   lBookingClassList.begin();
                 itBC != lBookingClassList.end(); ++itBC) {
              const BookingClass* lBC_ptr = *itBC;
              assert (lBC_ptr != NULL);

              //
              csvBookingClassDisplay (oStream, *lBC_ptr, oLeadingStr.str());
            }
          }

          return;
        }
        assert (BomManager::hasList<FareFamily> (*lSC_ptr) == false);

        // The fare family code is a fake one ('NoFF'), and therefore
        // does not vary
        oLeadingStr << lFamilyCode << ", ";

        // Browse the booking-classes, directly from the segment-cabin object
        const BookingClassList_T& lBookingClassList =
          BomManager::getList<BookingClass> (*lSC_ptr);
        for (BookingClassList_T::const_iterator itBC =
               lBookingClassList.begin();
             itBC != lBookingClassList.end(); ++itBC) {
          const BookingClass* lBC_ptr = *itBC;
          assert (lBC_ptr != NULL);

          //
          csvBookingClassDisplay (oStream, *lBC_ptr, oLeadingStr.str());
        }
      }
    }
    oStream << "******************************************" << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::
  csvDisplay (std::ostream& oStream,
              const TravelSolutionList_T& iTravelSolutionList) {

    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    oStream << "Travel solutions:";
    unsigned short idx = 0;
    for (TravelSolutionList_T::const_iterator itTS =
           iTravelSolutionList.begin();
         itTS != iTravelSolutionList.end(); ++itTS, ++idx) {
      const TravelSolutionStruct& lTS = *itTS;

      oStream << std::endl;
      oStream << "    [" << idx << "] " << lTS.display();
    }
  }

}
