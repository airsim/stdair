// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <ostream>
#if BOOST_VERSION >= 103400
// Boost ForEach
#include <boost/foreach.hpp>
#endif // BOOST_VERSION >= 103400
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
#include <stdair/bom/BomJSONExport.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonExport (std::ostream& oStream,
                                  const FlightDate& iFlightDate) {

    // Create an empty property tree object
    bpt::ptree pt;

#if BOOST_VERSION >= 104100
    /**
     * Flight-date level (only)
     */
    const AirlineCode_T& lAirlineCode = iFlightDate.getAirlineCode();
    const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    const Date_T& lFlightDateDate = iFlightDate.getDepartureDate();

    // Put airline code in property tree
    pt.put ("flight_date.airline_code", lAirlineCode);

    // Put flight number level in property tree
    pt.put ("flight_date.flight_number", lFlightNumber);

    // Put the flight departure date in property tree
    const std::string& lDepartureDateStr =
      boost::gregorian::to_simple_string (lFlightDateDate);
    pt.put ("flight_date.departure_date", lDepartureDateStr);
#endif // BOOST_VERSION >= 104100

    //
    jsonLegDateExport (pt, iFlightDate);

    //
    jsonLegCabinExport (pt, iFlightDate);

    //
    jsonBucketExport (pt, iFlightDate);

    //
    jsonSegmentDateExport (pt, iFlightDate);

    //
    jsonSegmentCabinExport (pt, iFlightDate);

    //
    jsonFareFamilyExport (pt, iFlightDate);

    //
    jsonBookingClassExport (pt, iFlightDate);

#if BOOST_VERSION >= 104100
    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
#endif // BOOST_VERSION >= 104100
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonLegDateExport (bpt::ptree& ioPropertyTree,
                                         const FlightDate& iFlightDate) {
    /**
     * Leg-date level (only).
     */

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
      
#if BOOST_VERSION >= 104100
      
      //
      bpt::ptree lLegDateArray;

      // Put boarding point in property tree
      lLegDateArray.put ("BoardPoint", lLD_ptr->getBoardingPoint());
      // Put off point in property tree
      lLegDateArray.put ("OffPoint", lLD_ptr->getOffPoint());
      // Put boarding date in property tree
      lLegDateArray.put ("BoardDate", lLD_ptr->getBoardingDate());
      // Put off date in property tree
      lLegDateArray.put ("OffDate", lLD_ptr->getOffDate());
      // Put boarding time in property tree
      lLegDateArray.put ("BoardTime", lLD_ptr->getBoardingTime());
      // Put off time in property tree
      lLegDateArray.put ("OffTime", lLD_ptr->getOffTime());
      // Put elapsed time in property tree
      lLegDateArray.put ("Elapsed", lLD_ptr->getElapsedTime());
      // Put date offset in property tree
      lLegDateArray.put ("Date_Offset", lLD_ptr->getDateOffset());
      // Put time offset in property tree
      lLegDateArray.put ("Time_Offset", lLD_ptr->getTimeOffset());
      // Put distance in property tree
      lLegDateArray.put ("Distance", lLD_ptr->getDistance());
      // Put capacity in property tree
      lLegDateArray.put ("Capacity", lLD_ptr->getCapacity());

      // Put leg date array in property tree
      std::ostringstream oStream;
      oStream << "flight_date.leg_" << lLD_ptr->getBoardingPoint();
      ioPropertyTree.put_child(oStream.str(),lLegDateArray);

#endif // BOOST_VERSION >= 104100
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonLegCabinExport (bpt::ptree& ioPropertyTree,
                                          const FlightDate& iFlightDate) {
    /**
     * Leg-cabin level (only)
     */
    
    // Check whether there are LegDate objects
    if (BomManager::hasList<LegDate> (iFlightDate) == false) {
      return;
    }

    const LegDateList_T& lLegDateList =
      BomManager::getList<LegDate> (iFlightDate);
    for (LegDateList_T::const_iterator itLD = lLegDateList.begin();
         itLD != lLegDateList.end(); ++itLD) {
      const LegDate* lLD_ptr = *itLD;
      assert (lLD_ptr != NULL);
      
      // Browse the leg-cabins
      const LegCabinList_T& lLegCabinList =
        BomManager::getList<LegCabin> (*lLD_ptr);
      for (LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
           itLC != lLegCabinList.end(); ++itLC) {
        const LegCabin* lLC_ptr = *itLC;
        assert (lLC_ptr != NULL);
      
#if BOOST_VERSION >= 104100

        //
        bpt::ptree lLegCabinArray;

        // Put the offered capacity in property tree
        lLegCabinArray.put ("OffedCAP", lLC_ptr->getOfferedCapacity());
        // Put the physical capacity in property tree
        lLegCabinArray.put ("PhyCAP", lLC_ptr->getPhysicalCapacity());
        // Put regrade adjustment in property tree
        lLegCabinArray.put ("RgdADJ", lLC_ptr->getRegradeAdjustment());
        // Put authorization level in property tree
        lLegCabinArray.put ("AU", lLC_ptr->getAuthorizationLevel());
        // Put UPR in property tree
        lLegCabinArray.put ("UPR", lLC_ptr->getUPR());
        // Put sold seats in property tree
        lLegCabinArray.put ("SS", lLC_ptr->getSoldSeat());
        // Put staff nb of seats in property tree
        lLegCabinArray.put ("Staff", lLC_ptr->getStaffNbOfSeats());
        // Put waiting list nb of seats in property tree
        lLegCabinArray.put ("WL", lLC_ptr->getWLNbOfSeats());
        // Put group nb of seats in property tree
        lLegCabinArray.put ("Group", lLC_ptr->getGroupNbOfSeats());
        // Put committed space in property tree
        lLegCabinArray.put ("CommSpace", lLC_ptr->getCommittedSpace());
        // Put availability pool in property tree
        lLegCabinArray.put ("AvPool", lLC_ptr->getAvailabilityPool());
        // Put availability in property tree
        lLegCabinArray.put ("Avl", lLC_ptr->getAvailability());
        // Put net availability in property tree
        lLegCabinArray.put ("NAV", lLC_ptr->getNetAvailability());
        // Put gross availability in property tree
        lLegCabinArray.put ("GAV", lLC_ptr->getGrossAvailability());
        // Put avg cancellation percentage in property tree
        lLegCabinArray.put ("ACP", lLC_ptr->getAvgCancellationPercentage());
        // Put ETB in property tree
        lLegCabinArray.put ("ETB", lLC_ptr->getETB());
        // Put current bid price in property tree
        lLegCabinArray.put ("BidPrice", lLC_ptr->getCurrentBidPrice());
      
        // Put leg cabin array in property tree
        std::ostringstream oStream;
        oStream << "flight_date"
                << ".leg_" << lLD_ptr->getBoardingPoint()
                << ".cabin_" << lLC_ptr->toString();
        ioPropertyTree.put_child (oStream.str(), lLegCabinArray);

#endif // BOOST_VERSION >= 104100
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonBucketExport (bpt::ptree& ioPropertyTree,
                                        const FlightDate& iFlightDate) {
    /**
     * Bucket level (only)
     */
    
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

      // Browse the leg-cabins
      const LegCabinList_T& lLegCabinList =
        BomManager::getList<LegCabin> (*lLD_ptr);
      for (LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
           itLC != lLegCabinList.end(); ++itLC) {
        const LegCabin* lLC_ptr = *itLC;
        assert (lLC_ptr != NULL);

        // Check whether there are bucket objects
        if (BomManager::hasList<Bucket> (*lLC_ptr) == false) {
          return;
        }

        // Browse the buckets
        const BucketList_T& lBucketList = BomManager::getList<Bucket> (*lLC_ptr);
        for (BucketList_T::const_iterator itBuck = lBucketList.begin();
             itBuck != lBucketList.end(); ++itBuck) {
          const Bucket* lBucket_ptr = *itBuck;
          assert (lBucket_ptr != NULL);

#if BOOST_VERSION >= 104100
          
          //
          bpt::ptree lLegBucketArray;

          // Put yield in property tree
          lLegBucketArray.put ("Yield", lBucket_ptr->getYieldRangeUpperValue());  
          // Put seat_index in property tree
          lLegBucketArray.put ("SI", lBucket_ptr->getSeatIndex());
          // Put sold_seats in property tree
          lLegBucketArray.put ("SS", lBucket_ptr->getSoldSeats());
          // Put avaibility in property tree
          lLegBucketArray.put ("AV", lBucket_ptr->getAvailability());

          // Put bucket array in property tree
          std::ostringstream oStream;
          oStream << "flight_date"
                  << ".leg_" << lLD_ptr->getBoardingPoint()
                  << ".cabin_" << lLC_ptr->toString()
                  << ".bucket_" << lBucket_ptr->toString();
          ioPropertyTree.put_child (oStream.str(),lLegBucketArray);

#endif // BOOST_VERSION >= 104100
        }
      }
    }
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonSegmentDateExport (bpt::ptree& ioPropertyTree,
                                                  const FlightDate& iFlightDate) {

    /**
     * Segment-date level (only).
     */

    // Check whether there are SegmentDate objects
    if (BomManager::hasList<SegmentDate> (iFlightDate) == false) {
      return;
    }
    
    // Browse the segment-dates
    unsigned short idx = 0;
    const SegmentDateList_T& lSegmentDateList =
      BomManager::getList<SegmentDate> (iFlightDate);
    for (SegmentDateList_T::const_iterator itSD = lSegmentDateList.begin();
         itSD != lSegmentDateList.end(); ++itSD, ++idx) {
      const SegmentDate* lSD_ptr = *itSD;
      assert (lSD_ptr != NULL);
      
#if BOOST_VERSION >= 104100
      
      //
      bpt::ptree lSegmentDateArray;
      
      // Put boarding point in property tree
      lSegmentDateArray.put ("BoardPoint", lSD_ptr->getBoardingPoint());
      // Put off point in property tree
      lSegmentDateArray.put ("OffPoint", lSD_ptr->getOffPoint());
      // Put boarding date in property tree
      lSegmentDateArray.put ("BoardDate", lSD_ptr->getBoardingDate());
      // Put off date in property tree
      lSegmentDateArray.put ("OffDate", lSD_ptr->getOffDate());
      // Put boarding time in property tree
      lSegmentDateArray.put ("BoardTime", lSD_ptr->getBoardingTime());
      // Put off time in property tree
      lSegmentDateArray.put ("OffTime", lSD_ptr->getOffTime());
      // Put elapsed time in property tree
      lSegmentDateArray.put ("Elapsed", lSD_ptr->getElapsedTime());
      // Put date offset in property tree
      lSegmentDateArray.put ("Date_Offset", lSD_ptr->getDateOffset());
      // Put time offset in property tree
      lSegmentDateArray.put ("Time_Offset", lSD_ptr->getTimeOffset());
      // Put distance in property tree
      lSegmentDateArray.put ("Distance", lSD_ptr->getDistance());

      // Put segment date array in property tree
      std::ostringstream oStream;
      oStream << "flight_date.segment_" << lSD_ptr->getBoardingPoint()
              << "_" << lSD_ptr->getOffPoint();
      ioPropertyTree.put_child(oStream.str(),lSegmentDateArray);
      
#endif // BOOST_VERSION >= 104100
    } 
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonSegmentCabinExport (bpt::ptree& ioPropertyTree,
                                              const FlightDate& iFlightDate) {
    /**
     * Segment-cabin level (only)
     */
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonFareFamilyExport (bpt::ptree& ioPropertyTree,
                                            const FlightDate& iFlightDate) {
    /**
     * Fare family level (only)
     */

    // Check whether there are SegmentDate objects
    if (BomManager::hasList<SegmentDate> (iFlightDate) == false) {
      return;
    }
    
    // Browse the segment-dates
    unsigned short idx = 0;
    const SegmentDateList_T& lSegmentDateList =
      BomManager::getList<SegmentDate> (iFlightDate);
    for (SegmentDateList_T::const_iterator itSD = lSegmentDateList.begin();
         itSD != lSegmentDateList.end(); ++itSD, ++idx) {
      const SegmentDate* lSD_ptr = *itSD;
      assert (lSD_ptr != NULL);
      
      // Browse the segment-cabins
      const SegmentCabinList_T& lSegmentCabinList =
        BomManager::getList<SegmentCabin> (*lSD_ptr);
      for (SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
           itSC != lSegmentCabinList.end(); ++itSC) {
        const SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);
        
        // Check whether there are fare family objects
        if (BomManager::hasList<FareFamily> (*lSC_ptr) == false) {
          continue;
        }
    
        // Browse the fare families
        unsigned short ffIdx = 0;
        const FareFamilyList_T& lFareFamilyList =
          BomManager::getList<FareFamily> (*lSC_ptr);
        for (FareFamilyList_T::const_iterator itFF = lFareFamilyList.begin();
             itFF != lFareFamilyList.end(); ++itFF, ++ffIdx) {
          const FareFamily* lFF_ptr = *itFF;
          assert (lFF_ptr != NULL);

#if BOOST_VERSION >= 104100
          //
          bpt::ptree lFFArray;

          // Put cabin in property tree
          lFFArray.put ("cabin",lSC_ptr->toString());
          // Put fare family in property tree
          lFFArray.put ("code", lFF_ptr->getFamilyCode());
          // Put MIN in property tree
          lFFArray.put ("MIN", lSC_ptr->getMIN());
          // Put UPR in property tree
          lFFArray.put ("UPR", lSC_ptr->getUPR());
          // Put committed Ssace in property tree
          lFFArray.put ("CommSpace", lSC_ptr->getCommittedSpace());
          // Put availability pool in property tree
          lFFArray.put ("AvPool", lSC_ptr->getAvailabilityPool());
          // Put current bid price in property tree
          lFFArray.put ("BP", lSC_ptr->getCurrentBidPrice());

          std::ostringstream oStream;
          oStream << "flight_date.segment_" << lSD_ptr->getBoardingPoint()
                  << "_" << lSD_ptr->getOffPoint()
                  << ".fare_family_" << lFF_ptr->toString();
          ioPropertyTree.put_child (oStream.str(), lFFArray);
#endif // BOOST_VERSION >= 104100
        }
      }
    }
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonBookingClassExport (bpt::ptree& ioPropertyTree,
                                              const BookingClass& iBookingClass,
                                              const std::string& iLeadingString) {
    /**
     * Booking-class level (only)
     *
     * See the method below (jsonBookingClassExport() at FlightDate level)
     * for the details of the header.
     */
    std::ostringstream oStream;
    oStream << iLeadingString;
    oStream << ".class_" << iBookingClass.toString();

#if BOOST_VERSION >= 104100

    bpt::ptree lBookingClassArray;
    
    // Put sub class in property tree
    lBookingClassArray.put ("Subclass", iBookingClass.getSubclassCode());
    // Put authorization level in property tree
    std::ostringstream oAUProtStr;
    oAUProtStr << iBookingClass.getAuthorizationLevel()
               << " (" << iBookingClass.getProtection()
               << ") ";
    lBookingClassArray.put ("MIN/AU (Prot)", oAUProtStr.str());
    // Put negotiated space in property tree
    lBookingClassArray.put ("Nego", iBookingClass.getNegotiatedSpace());
    // Put no show percentage in property tree
    lBookingClassArray.put ("NS%", iBookingClass.getNoShowPercentage());
    // Put cancellation percentage in property tree
    lBookingClassArray.put ("OB%", iBookingClass.getCancellationPercentage());
    // Put sub nb of bookings in property tree
    lBookingClassArray.put ("Bkgs", iBookingClass.getNbOfBookings());
    // Put nb of group bookings in property tree
    lBookingClassArray.put ("GrpBks (pdg)", iBookingClass.getNbOfGroupBookings());
    // Put nb of staff bookings in property tree
    lBookingClassArray.put ("StfBkgs", iBookingClass.getNbOfStaffBookings());
    // Put nb of WL bookings in property tree
    lBookingClassArray.put ("WLBkgs", iBookingClass.getNbOfWLBookings());
    // Put ETB in property tree
    lBookingClassArray.put ("ETB", iBookingClass.getETB());
    // Put net class availability in property tree
    lBookingClassArray.put ("ClassAvl", iBookingClass.getNetClassAvailability());
    // Put segment availability in property tree
    lBookingClassArray.put ("SegAvl", iBookingClass.getSegmentAvailability());
    // Put net revenue availability in property tree
    lBookingClassArray.put ("RevAvl", iBookingClass.getNetRevenueAvailability());

    //
    ioPropertyTree.put_child (oStream.str(), lBookingClassArray);
      
#endif // BOOST_VERSION >= 104100
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonBookingClassExport (bpt::ptree& ioPropertyTree,
                                              const FlightDate& iFlightDate) {
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

      // Build the leading string to be displayed
      std::ostringstream oLeadingStr;
      // Begin completed the leading string to be displayed
      oLeadingStr << "flight_date.segment_" << lSD_ptr->getBoardingPoint()
                  << "_" << lSD_ptr->getOffPoint();
      
      // Browse the segment-cabins
      const SegmentCabinList_T& lSegmentCabinList =
        BomManager::getList<SegmentCabin> (*lSD_ptr);
      for (SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
           itSC != lSegmentCabinList.end(); ++itSC) {
        const SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);

        // Check whether there are FareFamily objects
        if (BomManager::hasList<FareFamily> (*lSC_ptr) == true) {

          // Browse the fare families
          const FareFamilyList_T& lFareFamilyList =
            BomManager::getList<FareFamily> (*lSC_ptr);
          for (FareFamilyList_T::const_iterator itFF = lFareFamilyList.begin();
               itFF != lFareFamilyList.end(); ++itFF) {
            const FareFamily* lFF_ptr = *itFF;
            assert (lFF_ptr != NULL);
            
            oLeadingStr << ".fare_family_" << lFF_ptr->toString();
            
            // Browse the booking-classes
            const BookingClassList_T& lBookingClassList =
              BomManager::getList<BookingClass> (*lFF_ptr);
            for (BookingClassList_T::const_iterator itBC =
                   lBookingClassList.begin();
                 itBC != lBookingClassList.end(); ++itBC) {
              const BookingClass* lBC_ptr = *itBC;
              assert (lBC_ptr != NULL);

              //
              jsonBookingClassExport (ioPropertyTree, *lBC_ptr,
                                      oLeadingStr.str());
            }
          }
        } else {

          // The fare family code is a fake one ('NoFF'), and therefore
          // does not vary
          FamilyCode_T lDefaultFamilyCode ("NoFF");
          oLeadingStr << ".fare_family_" << lDefaultFamilyCode ;

          // Browse the booking-classes, directly from the segment-cabin object
          const BookingClassList_T& lBookingClassList =
            BomManager::getList<BookingClass> (*lSC_ptr);
          for (BookingClassList_T::const_iterator itBC =
                 lBookingClassList.begin();
               itBC != lBookingClassList.end(); ++itBC) {
            const BookingClass* lBC_ptr = *itBC;
            assert (lBC_ptr != NULL);

            //
            jsonBookingClassExport (ioPropertyTree, *lBC_ptr, oLeadingStr.str());
          }
        }
      }
    }
  }
}
