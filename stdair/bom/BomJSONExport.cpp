// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <ostream>
// Boost Property Tree
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
// Boost ForEach
#include <boost/foreach.hpp>
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

namespace bpt = boost::property_tree;

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
  void BomJSONExport::jsonExport (std::ostream& oStream,
                                  const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Create an empty property tree object
    bpt::ptree pt;

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

    //
    jsonLegDateExport (oStream, iFlightDate);

    //
    //jsonLegCabinExport (oStream, iFlightDate);

    //
    //jsonBucketExport (oStream, iFlightDate);

    //
    //jsonFareFamilyExport (oStream, iFlightDate);

    //
    //jsonBookingClassExport (oStream, iFlightDate);

    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonLegDateExport (std::ostream& oStream,
                                         const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Create an empty property tree object
    bpt::ptree pt;

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
      
      // Put boarding point in property tree
      pt.put ("flight_date.leg.board_point", lLD_ptr->getBoardingPoint());
      // Put off point in property tree
      pt.put ("flight_date.leg.off_point", lLD_ptr->getOffPoint());
      // Put boarding date in property tree
      pt.put ("flight_date.leg.board_date", lLD_ptr->getBoardingDate());
      // Put off date in property tree
      pt.put ("flight_date.leg.off_date", lLD_ptr->getOffDate());
      // Put boarding time in property tree
      pt.put ("flight_date.leg.board_time", lLD_ptr->getBoardingTime());
      // Put off time in property tree
      pt.put ("flight_date.leg.off_time", lLD_ptr->getOffTime());
      // Put elapsed time in property tree
      pt.put ("flight_date.leg.elapsed_time", lLD_ptr->getElapsedTime());
      // Put date offset in property tree
      pt.put ("flight_date.leg.date_offset", lLD_ptr->getDateOffset());
      // Put time offset in property tree
      pt.put ("flight_date.leg.time_offset", lLD_ptr->getTimeOffset());
      // Put distance in property tree
      pt.put ("flight_date.leg.distance", lLD_ptr->getDistance());
      // Put capacity in property tree
      pt.put ("flight_date.leg.capacity", lLD_ptr->getCapacity());
    }

    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonSegmentDateExport (std::ostream& oStream,
                                             const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Create an empty property tree object
    bpt::ptree pt;

    /**
     * Segment-date level (only)
     */

    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonLegCabinExport (std::ostream& oStream,
                                          const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Create an empty property tree object
    bpt::ptree pt;

    /**
     * Leg-cabin level (only)
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

    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonSegmentCabinExport (std::ostream& oStream,
                                              const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Create an empty property tree object
    bpt::ptree pt;

    /**
     * Segment-cabin level (only)
     */

    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonFareFamilyExport (std::ostream& oStream,
                                            const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Create an empty property tree object
    bpt::ptree pt;

    /**
     * Fare family level (only)
     */

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
        const FareFamilyList_T& lFareFamilyList =
          BomManager::getList<FareFamily> (*lSC_ptr);
        for (FareFamilyList_T::const_iterator itFF = lFareFamilyList.begin();
             itFF != lFareFamilyList.end(); ++itFF) {
          const FareFamily* lFF_ptr = *itFF;
          assert (lFF_ptr != NULL);

          oStream << lFF_ptr->getFamilyCode() << ", ";

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

    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonBucketExport (std::ostream& oStream,
                                        const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Create an empty property tree object
    bpt::ptree pt;

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
          continue;
        }

        // Browse the buckets
        const BucketList_T& lBucketList = BomManager::getList<Bucket> (*lLC_ptr);
        for (BucketList_T::const_iterator itBuck = lBucketList.begin();
             itBuck != lBucketList.end(); ++itBuck) {
          const Bucket* lBucket_ptr = *itBuck;
          assert (lBucket_ptr != NULL);

          oStream << lBucket_ptr->getYieldRangeUpperValue() << ", "
                  << lBucket_ptr->getSeatIndex() << ", "
                  << lBucket_ptr->getSoldSeats() << ", "
                  << lBucket_ptr->getAvailability() << ", ";
          oStream << std::endl;
        }
      }
    }

    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonBookingClassExport (std::ostream& oStream,
                                           const BookingClass& iBookingClass,
                                           const std::string& iLeadingString) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Create an empty property tree object
    bpt::ptree pt;

    /**
     * Booking-class level (only)
     *
     * See the method below (jsonBookingClassExport() at FlightDate level)
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

    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonBookingClassExport (std::ostream& oStream,
                                              const FlightDate& iFlightDate) {
    // Save the formatting flags for the given STL output stream
    FlagSaver flagSaver (oStream);

    // Create an empty property tree object
    bpt::ptree pt;

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
      
      // Browse the segment-cabins
      const SegmentCabinList_T& lSegmentCabinList =
        BomManager::getList<SegmentCabin> (*lSD_ptr);
      for (SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
           itSC != lSegmentCabinList.end(); ++itSC) {
        const SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);
        
        // Build the leading string to be displayed
        std::ostringstream oLeadingStr;

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
              jsonBookingClassExport (oStream, *lBC_ptr, oLeadingStr.str());
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
          jsonBookingClassExport (oStream, *lBC_ptr, oLeadingStr.str());
        }
      }
    }

    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
  }

}
