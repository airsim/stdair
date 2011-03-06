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
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/BomManager.hpp>
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
    oStream << "******************************************" << std::endl;
    oStream << "FlightDate: " << iFlightDate.describeKey()  << std::endl;
    oStream << "******************************************" << std::endl;

    //
    csvLegDateDisplay (oStream, iFlightDate);

    //
    csvLegCabinDisplay (oStream, iFlightDate);

    //
    // csvBucketDisplay (oStream, iFlightDate);

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
    oStream << "FlightNb (FlightDate), Leg, BoardDate, BoardTime, "
            << "OffDate, OffTime, Date Offset, Time Offset, Elapsed, "
            << "Distance, Capacity, " << std::endl;

    // Retrieve the key of the flight-date
    const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    const Date_T& lFlightDateDate = iFlightDate.getFlightDate();

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
    oStream << "FlightNb (FlightDate), Leg, Cabin, "
            << "OffedCAP, PhyCAP, RgdADJ, AU, UPR, SS, Staff, WL, Group, "
            << "CommSpace, AvPool, Avl, NAV, GAV, ACP, ETB, BidPrice, "
            << std::endl;
    
    // Retrieve the key of the flight-date
    const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    const Date_T& lFlightDateDate = iFlightDate.getFlightDate();
    
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
    oStream << "Segment, Cabin, FF, Bkgs, MIN, UPR, "
            << "CommSpace, AvPool, BP, " << std::endl;
    
    // Retrieve the key of the flight-date
    // const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    // const Date_T& lFlightDateDate = iFlightDate.getFlightDate();

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

        // Check whether there are SegmentDate objects
        if (BomManager::hasList<FareFamily> (*lSC_ptr) == false) {
          return;
        }
    
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
    oStream << "Leg, Cabin, Yield, AU, SS, AV, "
            << std::endl;

    // Retrieve the key of the flight-date
    // const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    // const Date_T& lFlightDateDate = iFlightDate.getFlightDate();

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
      const AirportCode_T& lBoardPoint = lLD_ptr->getBoardingPoint();
      const AirportCode_T& lOffPoint = lLD_ptr->getOffPoint();

      // Browse the leg-cabins
      const LegCabinList_T& lLegCabinList =
        BomManager::getList<LegCabin> (*lLD_ptr);
      for (LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
           itLC != lLegCabinList.end(); ++itLC) {
        const LegCabin* lLC_ptr = *itLC;
        assert (lLC_ptr != NULL);
      
        oStream << lBoardPoint << "-" << lOffPoint << ", ";
        oStream << lLC_ptr->getCabinCode() << ", ";
        /*
          oStream << lBucket_ptr->getYieldRangeUpperValue() << ", "
          << lBucket_ptr->getAU() << ", "
          << lBucket_ptr->getSoldSeats() << ", "
          << lBucket_ptr->getAvailability() << ", ";
        */
        oStream << std::endl;
      }
    }
    oStream << "******************************************" << std::endl;
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvBookingClassDisplay (std::ostream& oStream,
                                           const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

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
        
        // Check whether there are SegmentDate objects
        if (BomManager::hasList<FareFamily> (*lSC_ptr) == false) {
          return;
        }
    
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
  }
    

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::intDisplay (std::ostream& oStream, const int& iInt) {
    const int dInt = iInt - static_cast<int>(iInt/100)*100;
    if (dInt < 10) {
      oStream << "0" << dInt;
    } else {
      oStream << dInt;
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvDisplay (std::ostream& oStream,
                               const BookingRequestStruct& iBookingRequest) {

    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
      #id, request_date (YYMMDD), request_time (HHMMSS), POS (three-letter code),
       origin (three-letter code), destination (three-letter code),
       preferred departure date (YYMMDD), preferred departure time (HHMM),
       min departure time (HHMM), max departure time (HHMM),
       preferred cabin (F/C/M), trip type (OW/RO/RI), duration of stay (days),
       frequent flyer tier (G/S/K/N), willingness-to-pay (SGD),
       disutility per stop (SGD), preferred arrival date (YYMMDD),
       preferred arrival time (HHMM), value of time (SGD per hour)

      #Preferred cabin: F=First, C=Business M=Economy
      #Trip type: OW=One-way, RO=Round-trip outbound portion,
        RI=Round-trip inbound portion
      #Duration of stay: irrelevant in case of one-way, but set to 0
      #Frequent-flyer tier: G=Gold, S=Silver, K=Basic (Krisflyer), N=None
    */

    // Request date&time
    const stdair::DateTime_T& lRequestDateTime =
      iBookingRequest.getRequestDateTime();
    intDisplay (oStream, lRequestDateTime.date().year());
    intDisplay (oStream, lRequestDateTime.date().month());
    intDisplay (oStream, lRequestDateTime.date().day());
    oStream << ", ";
    intDisplay (oStream, lRequestDateTime.time_of_day().hours());
    intDisplay (oStream, lRequestDateTime.time_of_day().minutes());
    intDisplay (oStream, lRequestDateTime.time_of_day().seconds());
    oStream << ", ";

    // POS
    oStream << iBookingRequest.getPOS() << ", ";

    // Origin
    oStream << iBookingRequest.getOrigin() << ", ";

    // Destination
    oStream << iBookingRequest.getDestination() << ", ";

    // Preferred departure date
    const stdair::Date_T& lPreferredDepartureDate =
      iBookingRequest.getPreferedDepartureDate();
    intDisplay (oStream, lPreferredDepartureDate.year());
    intDisplay (oStream, lPreferredDepartureDate.month());
    intDisplay (oStream, lPreferredDepartureDate.day());
    oStream << ", ";

    // Preferred departure time
    const stdair::Duration_T& lPreferredDepartureTime =
      iBookingRequest.getPreferredDepartureTime();
    intDisplay (oStream, lPreferredDepartureTime.hours());
    intDisplay (oStream, lPreferredDepartureTime.minutes());
    oStream << ", ";

    // MIN & MAX preferred departure time (hardcode)
    oStream << "0000, 2359, ";

    // Preferred cabin
    oStream << iBookingRequest.getPreferredCabin() << ", ";

    // Trip type
    oStream << iBookingRequest.getTripType() << ", ";

    // Duration of stay
    if (iBookingRequest.getTripType() == "OW") {
      oStream << "0, ";
    } else {
      oStream << iBookingRequest.getStayDuration() << ", ";
    }

    // Frequent flyer tier
    oStream << iBookingRequest.getFrequentFlyerType() << ", ";

    // Willingness-to-pay
    oStream << iBookingRequest.getWTP() << ", ";

    // Disutility per stop (hardcode to 100)
    oStream << "100, ";

    // Preferred arrival date (hardcode to the preferred departure date)
    intDisplay (oStream, lPreferredDepartureDate.year());
    intDisplay (oStream, lPreferredDepartureDate.month());
    intDisplay (oStream, lPreferredDepartureDate.day());
    oStream << ", ";

    // Preferred arrival time (hardcode to 23:55
    oStream << "2355, ";

    // Value of time
    oStream <<iBookingRequest.getValueOfTime() << std::endl;
  }

}
