/*!
 * \page bom_display_cpp C++ Utility Class Browsing and Dumping the StdAir BOM Tree
 * \code
 */
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
#include <stdair/bom/AirportPair.hpp>
#include <stdair/bom/PosChannel.hpp>
#include <stdair/bom/DatePeriod.hpp>
#include <stdair/bom/TimePeriod.hpp>
#include <stdair/bom/FareFeatures.hpp>
#include <stdair/bom/YieldFeatures.hpp>
#include <stdair/bom/AirlineClassList.hpp>
#include <stdair/bom/Bucket.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/BomDisplay.hpp>
#include <stdair/bom/OnDDate.hpp>

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
  void BomDisplay::list (std::ostream& oStream, const BomRoot& iBomRoot,
                         const AirlineCode_T& iAirlineCode,
                         const FlightNumber_T& iFlightNumber) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Check whether there are Inventory objects
    if (BomManager::hasList<Inventory> (iBomRoot) == false) {
      return;
    }
    
    // Browse the inventories
    unsigned short invIdx = 1;
    const InventoryList_T& lInventoryList =
      BomManager::getList<Inventory> (iBomRoot);
    for (InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv, ++invIdx) {
      const Inventory* lInv_ptr = *itInv;
      assert (lInv_ptr != NULL);

      // Retrieve the inventory key (airline code)
      const AirlineCode_T& lAirlineCode = lInv_ptr->getAirlineCode();

      // Display only the requested inventories
      if (iAirlineCode == "all" || iAirlineCode == lAirlineCode) {
        // Get the list of flight-dates for that inventory
        list (oStream, *lInv_ptr, invIdx, iFlightNumber);
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::list (std::ostream& oStream, const Inventory& iInventory,
                         const unsigned short iInventoryIndex,
                         const FlightNumber_T& iFlightNumber) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Check whether there are FlightDate objects
    if (BomManager::hasMap<FlightDate> (iInventory) == false) {
      return;
    }
    
    /**
     * \note It is assumed in this method that the flight-date key is made of
     *       a mere string, concatenating the flight number and the departure
     *       date. Hence, all the departure dates of a given flight number
     *       are assumed to be grouped in the flight-date map held by the
     *       inventory.
     */
    
    //
    const AirlineCode_T& lAirlineCode = iInventory.getAirlineCode();
    oStream << iInventoryIndex << ". " << lAirlineCode << std::endl;

    // Browse the flight-dates
    unsigned short lCurrentFlightNumber = 0;
    unsigned short flightNumberIdx = 0;
    unsigned short departureDateIdx = 1;
    const FlightDateMap_T& lFlightDateList =
      BomManager::getMap<FlightDate> (iInventory);
    for (FlightDateMap_T::const_iterator itFD = lFlightDateList.begin();
         itFD != lFlightDateList.end(); ++itFD, ++departureDateIdx) {
      const FlightDate* lFD_ptr = itFD->second;
      assert (lFD_ptr != NULL);
      
      // Retrieve the key of the flight-date
      const FlightNumber_T& lFlightNumber = lFD_ptr->getFlightNumber();
      const Date_T& lFlightDateDate = lFD_ptr->getDepartureDate();

      // Display only the requested flight number
      if (iFlightNumber == 0 || iFlightNumber == lFlightNumber) {
        //
        if (lCurrentFlightNumber != lFlightNumber) {
          lCurrentFlightNumber = lFlightNumber;
          ++flightNumberIdx; departureDateIdx = 1;
          oStream << "  " << iInventoryIndex << "." << flightNumberIdx << ". "
                  << lAirlineCode << lFlightNumber << std::endl;
        }
      
        oStream << "    " << iInventoryIndex << "." << flightNumberIdx
                << "." << departureDateIdx << ". "
                << lAirlineCode << lFlightNumber << " / " << lFlightDateDate
                << std::endl;
      }
    }   
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::listAirportPairDateRange (std::ostream& oStream,
                                             const BomRoot& iBomRoot) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Check whether there are AirportPair objects
    if (BomManager::hasList<AirportPair> (iBomRoot) == false) {
      return;
    }

    const AirportPairList_T& lAirportPairList =
      BomManager::getList<AirportPair> (iBomRoot);
    for (AirportPairList_T::const_iterator itAir = lAirportPairList.begin();
         itAir != lAirportPairList.end(); ++itAir ) {
      const AirportPair* lAir_ptr = *itAir;      
      assert (lAir_ptr != NULL);

      // Check whether there are date-period objects
      assert (BomManager::hasList<DatePeriod> (*lAir_ptr) == true);

      // Browse the date-period objects
      const DatePeriodList_T& lDatePeriodList =
        BomManager::getList<DatePeriod> (*lAir_ptr);
      
      for (DatePeriodList_T::const_iterator itDP = lDatePeriodList.begin();
           itDP != lDatePeriodList.end(); ++itDP) {
        const DatePeriod* lDP_ptr = *itDP;
        assert (lDP_ptr != NULL);
      
        // Display the date-period object
        oStream << lAir_ptr->describeKey()
                <<" / " << lDP_ptr->describeKey() << std::endl;
      }  

    }   
  }
  
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

    // Check if the inventory contains a list of partners

    if (BomManager::hasList<Inventory> (iInventory)){
    
      // Browse the partner's inventories
      const InventoryList_T& lPartnerInventoryList =
        BomManager::getList<Inventory> (iInventory);
      
      for (InventoryList_T::const_iterator itInv = lPartnerInventoryList.begin();
           itInv != lPartnerInventoryList.end(); ++itInv) {           
      
        oStream << "-------------------------------------------------" << std::endl;
        oStream << "Partner inventory:" << std::endl;
        oStream << "-------------------------------------------------" << std::endl;
        const Inventory* lInv_ptr = *itInv;
        assert (lInv_ptr != NULL);
      
        // Display the inventory
        csvDisplay (oStream, *lInv_ptr);      
      }
      oStream << "******************************************" << std::endl;
      oStream << std::endl;
    }

    // Check if the inventory contains a list of O&D dates

    if (BomManager::hasList<OnDDate> (iInventory)){

      //Browse the O&Ds
      const OnDDateList_T& lOnDDateList =
        BomManager::getList<OnDDate> (iInventory);

      for (OnDDateList_T::const_iterator itOnD = lOnDDateList.begin();
           itOnD != lOnDDateList.end(); ++itOnD) {
        oStream << "******************************************" << std::endl;
        oStream << "O&D-Date:" << std::endl;
        oStream << "----------" << std::endl;
        oStream << "Airline, Date, Origin-Destination, Segments, " << std::endl;
       
        const OnDDate* lOnDDate_ptr = *itOnD;
        assert (lOnDDate_ptr != NULL);

        // Display the O&D date
        csvDisplay (oStream, *lOnDDate_ptr);
      }
      oStream << "******************************************" << std::endl;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvDisplay (std::ostream& oStream,
                               const OnDDate& iOnDDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * O&D-date level (only)
     */
    const AirlineCode_T& lAirlineCode = iOnDDate.getAirlineCode();
    const Date_T& lDate = iOnDDate.getDate();
    const AirportCode_T& lOrigin = iOnDDate.getOrigin();
    const AirportCode_T& lDestination = iOnDDate.getDestination();
    
    oStream << lAirlineCode <<", " << lDate << ", "<< lOrigin << "-"
            << lDestination << ", " << iOnDDate.describeKey() << ", "
            << std::endl;
        
    const StringDemandStructMap_T& lDemandInfoMap =
      iOnDDate.getDemandInfoMap();

    // Check if the map contains information.
    const bool isInfoMapEmpty = lDemandInfoMap.empty();
    if (isInfoMapEmpty) {
      return;
    }
    assert (lDemandInfoMap.empty() ==false);
    
    oStream << "----------" << std::endl;        
    oStream << "Cabin-Class path, Demand mean, Demand std dev, Yield, "
            << std::endl;
    
    for (StringDemandStructMap_T::const_iterator itDI = lDemandInfoMap.begin();
         itDI != lDemandInfoMap.end(); ++itDI) {
      
      const std::string& lCabinClassPath = itDI->first;
      const YieldDemandPair_T lYieldDemandPair =
        itDI->second;
      const Yield_T lYield = lYieldDemandPair.first;
      const MeanStdDevPair_T lMeanStdDevPair =
        lYieldDemandPair.second;
      const MeanValue_T lDemandMean = lMeanStdDevPair.first;
      const StdDevValue_T lDemandStdDev = lMeanStdDevPair.second;

      oStream << lCabinClassPath << ", "
              << lDemandMean << ", "
              << lDemandStdDev << ", "
              << lYield << ", "
              << std::endl;
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
    csvSegmentDateDisplay (oStream, iFlightDate);
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
              << lLD_ptr->getDateOffset().days() << ", "
              << lLD_ptr->getTimeOffset() << ", "
              << lLD_ptr->getDistance() << ", "
              << lLD_ptr->getCapacity() << ", " << std::endl;
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
    oStream << "******************************************" << std::endl;
    oStream << "SegmentDates:" << std::endl
            << "----------" << std::endl;
    oStream << "Flight, Segment, Date"
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
      oStream << lAirlineCode << lFlightNumber << " " << lFlightDateDate << ", "
              << lBoardPoint << "-" << lOffPoint << ", " << lSegmentDateDate << std::endl;

      // Check if the current segment has corresponding marketing segments. 
      const bool isMarketingSDListEmpty = BomManager::hasList<SegmentDate>(*lSD_ptr);
      if (isMarketingSDListEmpty == false) {
        //
        const SegmentDateList_T& lMarketingSDList = BomManager::getList<SegmentDate>(*lSD_ptr);
          
        oStream << " *** Marketed by ";
        for (SegmentDateList_T::const_iterator itMarketingSD = lMarketingSDList.begin();
             itMarketingSD != lMarketingSDList.end(); ++itMarketingSD) {
          SegmentDate* lMarketingSD_ptr = *itMarketingSD;
          FlightDate* lMarketingFD_ptr = BomManager::getParentPtr<FlightDate>(*lMarketingSD_ptr);
          Inventory* lMarketingInv_ptr = BomManager::getParentPtr<Inventory>(*lMarketingFD_ptr);
          oStream << lMarketingInv_ptr->toString() << lMarketingFD_ptr->toString() <<" * ";
        }
      }

      // Check if the current segment is operated by another segment date. 
      const SegmentDate* lOperatingSD_ptr = lSD_ptr->getOperatingSegmentDate ();
      if (lOperatingSD_ptr != NULL) {

        const FlightDate* lOperatingFD_ptr = BomManager::getParentPtr<FlightDate>(*lOperatingSD_ptr);
        const Inventory* lOperatingInv_ptr = BomManager::getParentPtr<Inventory>(*lOperatingFD_ptr);
        oStream << " *** Operated by " << lOperatingInv_ptr->toString()
                << lOperatingFD_ptr->toString() << std::endl;
      }
      
      oStream << std::endl;
    }
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
            << iBookingClass.getCancellationPercentage() << ", "
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
        std::ostringstream oSCLeadingStr;
        oSCLeadingStr << lAirlineCode << lFlightNumber << " "
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
            std::ostringstream oFFLeadingStr;
            oFFLeadingStr << oSCLeadingStr.str() << lFamilyCode << ", ";

            // Browse the booking-classes
            const BookingClassList_T& lBookingClassList =
              BomManager::getList<BookingClass> (*lFF_ptr);
            for (BookingClassList_T::const_iterator itBC =
                   lBookingClassList.begin();
                 itBC != lBookingClassList.end(); ++itBC) {
              const BookingClass* lBC_ptr = *itBC;
              assert (lBC_ptr != NULL);

              //
              csvBookingClassDisplay (oStream, *lBC_ptr, oFFLeadingStr.str());
            }
          }

          // Go on to the next segment-cabin
          continue;
        }
        assert (BomManager::hasList<FareFamily> (*lSC_ptr) == false);

        // The fare family code is a fake one ('NoFF'), and therefore
        // does not vary
        std::ostringstream oFFLeadingStr;
        oFFLeadingStr << oSCLeadingStr.str() << lFamilyCode << ", ";

        // Browse the booking-classes, directly from the segment-cabin object
        const BookingClassList_T& lBookingClassList =
          BomManager::getList<BookingClass> (*lSC_ptr);
        for (BookingClassList_T::const_iterator itBC =
               lBookingClassList.begin();
             itBC != lBookingClassList.end(); ++itBC) {
          const BookingClass* lBC_ptr = *itBC;
          assert (lBC_ptr != NULL);

          //
          csvBookingClassDisplay (oStream, *lBC_ptr, oFFLeadingStr.str());
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

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::
  csvDisplay (std::ostream& oStream,
              const DatePeriodList_T& iDatePeriodList) {

    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Browse the date-period objects
    for (DatePeriodList_T::const_iterator itDP = iDatePeriodList.begin();
         itDP != iDatePeriodList.end(); ++itDP) {
      const DatePeriod* lDP_ptr = *itDP;
      assert (lDP_ptr != NULL);
      
      // Display the date-period object
      csvDateDisplay (oStream, *lDP_ptr);
    }   
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvSimFQTAirRACDisplay (std::ostream& oStream,
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

    // Check whether there are airport-pair objects
    if (BomManager::hasList<AirportPair> (iBomRoot) == false) {
      return;
    }
    
    // Browse the airport-pair objects
    const AirportPairList_T& lAirportPairList =
      BomManager::getList<AirportPair> (iBomRoot);
    for (AirportPairList_T::const_iterator itAir = lAirportPairList.begin();
         itAir != lAirportPairList.end(); ++itAir ) {
      const AirportPair* lAir_ptr = *itAir;
      assert (lAir_ptr != NULL);

      // Display the airport pair object
      csvAirportPairDisplay (oStream, *lAir_ptr);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvAirportPairDisplay (std::ostream& oStream,
                                          const AirportPair& iAirportPair) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Airport pair level (only)
     */
    oStream << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    oStream << "AirportPair: " << iAirportPair.describeKey() << std::endl;
    oStream << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    
    // Check whether there are date-period objects
    if (BomManager::hasList<DatePeriod> (iAirportPair) == false) {
      return;
    }

    // Browse the date-period objects
    const DatePeriodList_T& lDatePeriodList =
      BomManager::getList<DatePeriod> (iAirportPair);
    for (DatePeriodList_T::const_iterator itDP = lDatePeriodList.begin();
         itDP != lDatePeriodList.end(); ++itDP) {
      const DatePeriod* lDP_ptr = *itDP;
      assert (lDP_ptr != NULL);
      
      // Display the date-period object
      csvDateDisplay (oStream, *lDP_ptr);
    }   
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvDateDisplay (std::ostream& oStream,
                                   const DatePeriod& iDatePeriod) {

    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Date-Period level (only).
     */
    oStream << "------------------------------------------" << std::endl;
    oStream << "DatePeriod: " << iDatePeriod.describeKey() << std::endl;
    oStream << "------------------------------------------" << std::endl;

    // Check whether there are pos-channel objects
    if (BomManager::hasList<PosChannel> (iDatePeriod) == false) {
      return;
    }

    // Browse the pos-channel objects
    const PosChannelList_T& lPosChannelList =
      BomManager::getList<PosChannel> (iDatePeriod);
    for (PosChannelList_T::const_iterator itPC = lPosChannelList.begin();
         itPC != lPosChannelList.end(); ++itPC) {
      const PosChannel* lPC_ptr = *itPC;
      assert (lPC_ptr != NULL);
      
      // Display the pos-channel object
      csvPosChannelDisplay (oStream, *lPC_ptr);
    }   
  }
  
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvPosChannelDisplay (std::ostream& oStream,
                                         const PosChannel& iPosChannel) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * PosChannel level (only)
     */
    oStream << "******************************************" << std::endl;
    oStream << "PosChannel: " << iPosChannel.describeKey() << std::endl;
    oStream << "******************************************" << std::endl;

    // Check whether there are time-period objects
    if (BomManager::hasList<TimePeriod> (iPosChannel) == false) {
      return;
    }

    // Browse the time-period objects
    const TimePeriodList_T& lTimePeriodList =
      BomManager::getList<TimePeriod> (iPosChannel);
    for (TimePeriodList_T::const_iterator itTP = lTimePeriodList.begin();
         itTP != lTimePeriodList.end(); ++itTP) {
      const TimePeriod* lTP_ptr = *itTP;
      assert (lTP_ptr != NULL);
      
      // Display the time-period object
      csvTimeDisplay (oStream, *lTP_ptr);
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::csvTimeDisplay (std::ostream& oStream,
                                   const TimePeriod& iTimePeriod) {

    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Time-Period level (only).
     */
    oStream << "----------------------------------------" << std::endl;
    oStream << "TimePeriod: " << iTimePeriod.describeKey() << std::endl;
    oStream << "----------------------------------------" << std::endl;

    // Only one of the fare/yield feature list exists. Each of the following
    // two methods will check for the existence of the list. So, only the
    // existing list will be actually displayed.
    csvFeatureListDisplay<FareFeatures> (oStream, iTimePeriod);
    csvFeatureListDisplay<YieldFeatures> (oStream, iTimePeriod);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename FEATURE_TYPE>
  void BomDisplay::csvFeatureListDisplay (std::ostream& oStream,
                                          const TimePeriod& iTimePeriod) {

    // Check whether there are fare/yield-feature objects
    if (BomManager::hasList<FEATURE_TYPE> (iTimePeriod) == false) {
      return;
    }

    // Browse the fare/yield-feature objects
    typedef typename BomHolder<FEATURE_TYPE>::BomList_T FeaturesList_T;
    const FeaturesList_T& lFeaturesList =
      BomManager::getList<FEATURE_TYPE> (iTimePeriod);
    for (typename FeaturesList_T::const_iterator itFF = lFeaturesList.begin();
         itFF != lFeaturesList.end(); ++itFF) {
      const FEATURE_TYPE* lFF_ptr = *itFF;
      assert (lFF_ptr != NULL);

      // Display the fare-features object
      csvFeaturesDisplay (oStream, *lFF_ptr);
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  template <typename FEATURE_TYPE>
  void BomDisplay::csvFeaturesDisplay (std::ostream& oStream,
                                       const FEATURE_TYPE& iFeatures) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * Fare/yield-Features level (only).
     */
    oStream << "--------------------------------------" << std::endl;
    oStream << "Fare/yield-Features: " << iFeatures.describeKey() << std::endl;
    oStream << "--------------------------------------" << std::endl;
   
    // Check whether there are airlineClassList objects
    if (BomManager::hasList<AirlineClassList> (iFeatures) == false) {
      return;
    }
    
    // Browse the airlineClassList objects
    const AirlineClassListList_T& lAirlineClassListList =
      BomManager::getList<AirlineClassList> (iFeatures);
    for (AirlineClassListList_T::const_iterator itACL =
           lAirlineClassListList.begin();
         itACL != lAirlineClassListList.end(); ++itACL) {
      const AirlineClassList* lACL_ptr = *itACL;
      assert (lACL_ptr != NULL);

      // Display the airlineClassList object
      csvAirlineClassDisplay(oStream, *lACL_ptr);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BomDisplay::
  csvAirlineClassDisplay  (std::ostream& oStream,
                           const AirlineClassList& iAirlineClassList) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    /**
     * AirlineClassList level (only).
     */
    oStream << "------------------------------------" << std::endl;
    oStream << "AirlineClassList: "
            << iAirlineClassList.describeKey() << std::endl;
    oStream << "------------------------------------" << std::endl;
  }
    
}

/*!
 * \endcode
 */
