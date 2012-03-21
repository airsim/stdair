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
#include <stdair/stdair_date_time_types.hpp>
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
#include <stdair/bom/EventStruct.hpp>
#include <stdair/bom/EventTypes.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/BreakPointStruct.hpp>
#include <stdair/bom/BomJSONExport.hpp>

namespace stdair { 

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::
  jsonExportFlightDateList (std::ostream& oStream, 
			    const BomRoot& iBomRoot,
			    const AirlineCode_T& iAirlineCode,
			    const FlightNumber_T& iFlightNumber) {    

    // Check whether there are Inventory objects
    if (BomManager::hasList<Inventory> (iBomRoot) == false) {
      return;
    }

#if BOOST_VERSION >= 104100 

    // Create empty property tree objects
    bpt::ptree pt;    
    bpt::ptree ptInventoryList;    

    // Browse the inventories
    const InventoryList_T& lInventoryList =
      BomManager::getList<Inventory> (iBomRoot);
    for (InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const Inventory* lInv_ptr = *itInv;
      assert (lInv_ptr != NULL);

      // Retrieve the inventory key (airline code)
      const AirlineCode_T& lAirlineCode = lInv_ptr->getAirlineCode();

      // Display only the requested inventories
      if (iAirlineCode == "all" || iAirlineCode == lAirlineCode) {
	// Flight date array
	// bpt::ptree ptFD;
	// Inventory tree
	bpt::ptree lCurrAirlineTree; 

        // Check whether there are FlightDate objects
        if (BomManager::hasMap<FlightDate> (*lInv_ptr) == false) {
          return;
        }
    
#if BOOST_VERSION >= 104100 

        // Create an empty flight-dates array
        bpt::ptree lFDDatePropertyTree; 

        // Browse the flight-dates
        const FlightDateMap_T& lFlightDateList =
          BomManager::getMap<FlightDate> (*lInv_ptr);
        for (FlightDateMap_T::const_iterator itFD = lFlightDateList.begin();
             itFD != lFlightDateList.end(); ++itFD) {
          const FlightDate* lFD_ptr = itFD->second;
          assert (lFD_ptr != NULL);
      
          // Retrieve the key of the flight-date
          const FlightNumber_T& lFlightNumber = lFD_ptr->getFlightNumber();
          const Date_T& lFlightDateDate = lFD_ptr->getDepartureDate();

          // Display only the requested flight number
          if (iFlightNumber == 0 || iFlightNumber == lFlightNumber) {   
            
            // Create an empty property tree object for the current flight date
            bpt::ptree lCurrFDTree; 

            // Add the airline code to the inventory tree
            lCurrAirlineTree.put ("airline_code", lAirlineCode);  	
            // Put flight number in property tree 
            lCurrFDTree.put ("number", lFlightNumber);
            // Put flight date date in property tree 
            lCurrFDTree.put ("date", lFlightDateDate);
            
            // Put the current flight date tree in the flight date array
            ioFDPropertyTree.push_back(std::make_pair("", lCurrFDTree));
            
          }
        }  
#endif // BOOST_VERSION >= 104100

	// Get the list of flight-dates for that inventory
	// jsonExportFlightDate (ptFD, *lInv_ptr, iFlightNumber);  	

	// Add the flight-dates array to the inventory tree
	// lCurrAirlineTree.add_child ("flights", ptFD);  	
	
	// Put the current inventory tree in the inventory(ies) array
	ptInventoryList.push_back(std::make_pair("", lCurrAirlineTree));

      }
    } 	
    
    // Store the inventory(ies) array tree into the global tree
    pt.add_child ("inventories", ptInventoryList); 
    
    // Write the property tree into the JSON stream.
    write_json (oStream, pt);
#endif // BOOST_VERSION >= 104100
  } 

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonExportFlightDate (bpt::ptree& ioFDPropertyTree,
					    const Inventory& iInventory,
					    const FlightNumber_T& iFlightNumber) {  

    // Check whether there are FlightDate objects
    if (BomManager::hasMap<FlightDate> (iInventory) == false) {
      return;
    }
    
#if BOOST_VERSION >= 104100 

    // Create an empty flight-dates array
    bpt::ptree lFDDatePropertyTree; 

    // Browse the flight-dates
    const FlightDateMap_T& lFlightDateList =
      BomManager::getMap<FlightDate> (iInventory);
    for (FlightDateMap_T::const_iterator itFD = lFlightDateList.begin();
         itFD != lFlightDateList.end(); ++itFD) {
      const FlightDate* lFD_ptr = itFD->second;
      assert (lFD_ptr != NULL);
      
      // Retrieve the key of the flight-date
      const FlightNumber_T& lFlightNumber = lFD_ptr->getFlightNumber();
      const Date_T& lFlightDateDate = lFD_ptr->getDepartureDate();

      // Display only the requested flight number
      if (iFlightNumber == 0 || iFlightNumber == lFlightNumber) {   

	// Create an empty property tree object for the current flight date
	bpt::ptree lCurrFDTree; 

	// Put flight number in property tree 
	lCurrFDTree.put ("number", lFlightNumber);
	// Put flight date date in property tree 
	lCurrFDTree.put ("date", lFlightDateDate);

	// Put the current flight date tree in the flight date array
	ioFDPropertyTree.push_back(std::make_pair("", lCurrFDTree));
           
      }
    }  
#endif // BOOST_VERSION >= 104100

  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::
  jsonExportFlightDateObjects (std::ostream& oStream,
			       const FlightDate& iFlightDate) {

#if BOOST_VERSION >= 104100 

    /**
     * Flight-date level 
     */
    // Create an empty property tree object
    bpt::ptree pt;    

    // Put the airline code in property tree
    const AirlineCode_T& lAirlineCode = iFlightDate.getAirlineCode();
    pt.put ("flight_date.airline_code", lAirlineCode);

    // Put the flight number in property tree
    const FlightNumber_T& lFlightNumber = iFlightDate.getFlightNumber();
    pt.put ("flight_date.flight_number", lFlightNumber);

    // Put the flight departure date in property tree 
    const Date_T& lFlightDateDate = iFlightDate.getDepartureDate();
    const std::string& lDepartureDateStr =
      boost::gregorian::to_simple_string (lFlightDateDate);
    pt.put ("flight_date.departure_date", lDepartureDateStr);    

    /**
     * Legs property tree
     */ 
    // Create an empty legs array
    bpt::ptree ptLegs;    
   
    // Recursively construct the legs array
    jsonExportLegDate (ptLegs, iFlightDate); 
 
    // Add legs tree to the global property tree
    pt.add_child ("flight_date.legs", ptLegs);  

    /**
     * Segments property tree
     */  
    // Create an empty segments array
    bpt::ptree ptSegments;

    // Recursively construct the segments array
    jsonExportSegmentDate (ptSegments, iFlightDate);
   
    // Add segments tree to the global property tree
    pt.add_child ("flight_date.segments", ptSegments); 
    
    // Write the property tree into the JSON stream.
    write_json (oStream, pt);

#endif // BOOST_VERSION >= 104100
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonExportLegDate (bpt::ptree& ioLegDateListTree,
                                         const FlightDate& iFlightDate) { 

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
     
      // Create an empty property tree object for the current leg date
      bpt::ptree lCurrLDTree; 

      // Put boarding point in property tree
      const AirportCode_T& lBoardingPoint = lLD_ptr->getBoardingPoint();
      lCurrLDTree.put ("board_point", lBoardingPoint);
      // Put off point in property tree 
      const AirportCode_T& lOffPoint = lLD_ptr->getOffPoint();
      lCurrLDTree.put ("off_point", lOffPoint);
      // Put boarding date in property tree 
      const Date_T& lBoardingDate = lLD_ptr->getBoardingDate();
      lCurrLDTree.put ("board_date", lBoardingDate);
      // Put off date in property tree
      const Date_T& lOffDate = lLD_ptr->getOffDate();
      lCurrLDTree.put ("off_dDate", lOffDate);
      // Put boarding time in property tree
      const Duration_T& lBoardingTime = lLD_ptr->getBoardingTime();
      lCurrLDTree.put ("board_time", lBoardingTime);
      // Put off time in property tree 
      const Duration_T& lOffTime = lLD_ptr->getOffTime();
      lCurrLDTree.put ("off_time", lOffTime);
      // Put elapsed time in property tree  
      const Duration_T& lElapsedTime = lLD_ptr->getElapsedTime();
      lCurrLDTree.put ("elapsed_time", lElapsedTime);
      // Put date offset in property tree
      const DateOffset_T& lDateOffset = lLD_ptr->getDateOffset();
      lCurrLDTree.put ("date_offset", lDateOffset);
      // Put time offset in property tree
      const Duration_T& lTimeOffset = lLD_ptr->getTimeOffset();
      lCurrLDTree.put ("time_offset", lTimeOffset);
      // Put distance in property tree
      const Distance_T& lDistance = lLD_ptr->getDistance();
      lCurrLDTree.put ("distance", lDistance);
      // Put capacity in property tree 
      const CabinCapacity_T& lCapacity = lLD_ptr->getCapacity();
      lCurrLDTree.put ("capacity", lCapacity);  

      // Create an empty property tree object for the leg cabins array
      // corresponding to the current leg date.
      bpt::ptree lLegCabinArray; 

      // Recursively construct the leg cabins array
      jsonExportLegCabin (lLegCabinArray, *lLD_ptr); 
  
      // Add the leg cabins array to the leg date tree
      lCurrLDTree.add_child ("cabins", lLegCabinArray);  

      // Put the current leg date tree in the leg date list tree
      ioLegDateListTree.push_back(std::make_pair("", lCurrLDTree));

#endif // BOOST_VERSION >= 104100
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonExportLegCabin (bpt::ptree& ioLegCabinListTree,
                                          const LegDate& iLegDate) {

    // Check whether there are LegCabin objects
    if (BomManager::hasList<LegCabin> (iLegDate) == false) {
      return;
    }
        
    // Browse the leg-cabins
    const LegCabinList_T& lLegCabinList =
      BomManager::getList<LegCabin> (iLegDate);
    for (LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
	 itLC != lLegCabinList.end(); ++itLC) {
      const LegCabin* lLC_ptr = *itLC;
      assert (lLC_ptr != NULL); 

#if BOOST_VERSION >= 104100

      // Create an empty property tree object for the current leg cabin
      bpt::ptree lCurrLCTree;

      // Put the cabin code in property tree 
      const CabinCode_T& lCabinCode = lLC_ptr->getCabinCode();
      lCurrLCTree.put ("code", lCabinCode);
      // Put the offered capacity in property tree
      const CabinCapacity_T& lOfferedCapacity = lLC_ptr->getOfferedCapacity();
      lCurrLCTree.put ("offed_cap", lOfferedCapacity);
      // Put the physical capacity in property tree   
      const CabinCapacity_T& lPhysicalCapacity = lLC_ptr->getPhysicalCapacity();
      lCurrLCTree.put ("phy_cap", lPhysicalCapacity);
      // Put regrade adjustment in property tree 
      const CapacityAdjustment_T& lRegradeAdjustment = lLC_ptr->getRegradeAdjustment();
      lCurrLCTree.put ("rgd_adj", lRegradeAdjustment);
      // Put authorization level in property tree
      const AuthorizationLevel_T& lAuthorizationLevel = lLC_ptr->getAuthorizationLevel();
      lCurrLCTree.put ("au", lAuthorizationLevel);
      // Put UPR in property tree
      const UPR_T& lUPR = lLC_ptr->getUPR();
      lCurrLCTree.put ("upr", lUPR);
      // Put sold seats in property tree
      const NbOfSeats_T& lNbOfSoldSeats = lLC_ptr->getSoldSeat();
      lCurrLCTree.put ("ss", lNbOfSoldSeats);
      // Put staff nb of seats in property tree
      const NbOfSeats_T& lStaffNbOfSeats = lLC_ptr->getStaffNbOfSeats();
      lCurrLCTree.put ("staff", lStaffNbOfSeats);
      // Put waiting list nb of seats in property tree
      const NbOfSeats_T& lWLNbOfSeats = lLC_ptr->getWLNbOfSeats();
      lCurrLCTree.put ("wl", lWLNbOfSeats);
      // Put group nb of seats in property tree  
      const NbOfSeats_T& lGroupNbOfSeats = lLC_ptr->getGroupNbOfSeats();
      lCurrLCTree.put ("group", lGroupNbOfSeats);
      // Put committed space in property tree 
      const CommittedSpace_T& lCommittedSpace = lLC_ptr->getCommittedSpace();
      lCurrLCTree.put ("comm_space", lCommittedSpace);
      // Put availability pool in property tree
      const Availability_T& lAvailabilityPool = lLC_ptr->getAvailabilityPool();
      lCurrLCTree.put ("av_pool", lAvailabilityPool);
      // Put availability in property tree
      const Availability_T& lAvailability = lLC_ptr->getAvailability();
      lCurrLCTree.put ("avl", lAvailability);
      // Put net availability in property tree
      const Availability_T& lNetAvailability = lLC_ptr->getNetAvailability();
      lCurrLCTree.put ("nav", lNetAvailability);
      // Put gross availability in property tree
      const Availability_T& lGrossAvailability = lLC_ptr->getGrossAvailability();
      lCurrLCTree.put ("gav", lGrossAvailability);
      // Put avg cancellation percentage in property tree
      const OverbookingRate_T& lAvgCancellationPercentage = 
	lLC_ptr->getAvgCancellationPercentage();
      lCurrLCTree.put ("acp", lAvgCancellationPercentage);
      // Put ETB in property tree
      const NbOfSeats_T& lExpectedToBoard = lLC_ptr->getETB();
      lCurrLCTree.put ("etb", lExpectedToBoard );
      // Put current bid price in property tree 
      const BidPrice_T& lCurrentBidPrice = lLC_ptr->getCurrentBidPrice();
      lCurrLCTree.put ("bid_price", lCurrentBidPrice);  

      // Create an empty property tree object for the buckets array
      // corresponding to the current leg cabin.
      bpt::ptree lBucketTree;   

      // Recursively construct the buckets array
      jsonExportBucket (lBucketTree, *lLC_ptr);   
 
      // Add the buckets array to the leg cabin tree 
      lCurrLCTree.add_child ("buckets", lBucketTree);  
      
      // Put the current leg cabin tree in the leg cabin list tree
      ioLegCabinListTree.push_back(std::make_pair("", lCurrLCTree));

#endif // BOOST_VERSION >= 104100
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonExportBucket (bpt::ptree& ioBucketListTree,
                                        const LegCabin& iLegCabin) {
    
    /**
     * Bucket level (only)
     */ 

    // Check whether there are Bucket objects
    if (BomManager::hasList<Bucket> (iLegCabin) == false) {
      return;
    }

    // Browse the buckets
    const BucketList_T& lBucketList = BomManager::getList<Bucket> (iLegCabin);
    for (BucketList_T::const_iterator itBuck = lBucketList.begin();
	 itBuck != lBucketList.end(); ++itBuck) {
      const Bucket* lBucket_ptr = *itBuck;
      assert (lBucket_ptr != NULL);

#if BOOST_VERSION >= 104100
          
      // Create an empty property tree object for the current bucket
      bpt::ptree lCurrBucketTree;

      // Put yield in property tree 
      const Yield_T& lYieldRangeUpperValue = 
	lBucket_ptr->getYieldRangeUpperValue();
      lCurrBucketTree.put ("yield", lYieldRangeUpperValue);  
      // Put seat_index in property tree
      const SeatIndex_T& lSeatIndex = lBucket_ptr->getSeatIndex();
      lCurrBucketTree.put ("si", lSeatIndex);
      // Put sold_seats in property tree
      const NbOfSeats_T& lSoldSeats = lBucket_ptr->getSoldSeats();
      lCurrBucketTree.put ("ss", lSoldSeats);
      // Put avaibility in property tree
      const CabinCapacity_T& lAvailability = lBucket_ptr->getAvailability();
      lCurrBucketTree.put ("av", lAvailability);

      // Put the current bucket tree in the bucket list tree
      ioBucketListTree.push_back(std::make_pair("", lCurrBucketTree));

#endif // BOOST_VERSION >= 104100
    }
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonExportSegmentDate (bpt::ptree& ioSegmentDateTree,
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
      
#if BOOST_VERSION >= 104100
      
      // Create an empty property tree object for the current segment date
      bpt::ptree lCurrSDTree;  
 
      // Put segment key in property tree
      lCurrSDTree.put ("segment", lSD_ptr->toString());
 
      // Create an empty property tree object for the segment cabin array
      // corresponding to the current segment date
      bpt::ptree lSegmentCabinTree;   

      // Recursively construct the segment cabin array
      jsonExportSegmentCabin (lSegmentCabinTree, *lSD_ptr);   
 
      // Add the segment cabin array to the tree of the current segment date
      lCurrSDTree.add_child ("sub_classes", lSegmentCabinTree);  

      // Put segment date array in property tree  
      ioSegmentDateTree.push_back(std::make_pair("", lCurrSDTree));
      
#endif // BOOST_VERSION >= 104100
    } 
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonExportSegmentCabin (bpt::ptree& ioPropertyTree,
					      const SegmentDate& iSegmentDate) {
  
    // Check whether there are SegmentCabin objects
    if (BomManager::hasList<SegmentCabin> (iSegmentDate) == false) {
      return;
    } 

    // Browse the segment-cabins
    const SegmentCabinList_T& lSegmentCabinList =
      BomManager::getList<SegmentCabin> (iSegmentDate);
    for (SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
	 itSC != lSegmentCabinList.end(); ++itSC) {
      const SegmentCabin* lSC_ptr = *itSC;
      assert (lSC_ptr != NULL);

#if BOOST_VERSION >= 104100
      // Create an empty property tree object for the current segment cabin
      bpt::ptree lSCArray;

      // Put cabin in property tree
      
      lSCArray.put ("cabin_code",lSC_ptr->toString()); 

      // Export the cabin tree to add fare-families and sub-classes details
      jsonExportFareFamily (ioPropertyTree, lSCArray, *lSC_ptr); 
     
#endif // BOOST_VERSION >= 104100

    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonExportFareFamily (bpt::ptree& ioPropertyTree,
					    bpt::ptree& ioSCTree,
                                            const SegmentCabin& iSegmentCabin) {     

    // Check whether there are FareFamily objects
    if (BomManager::hasList<FareFamily> (iSegmentCabin) == true) {
      	
      // Browse the fare-families
      const FareFamilyList_T& lFareFamilyList =
	BomManager::getList<FareFamily> (iSegmentCabin);
      for (FareFamilyList_T::const_iterator itFF = lFareFamilyList.begin();
	 itFF != lFareFamilyList.end(); ++itFF) {
	const FareFamily* lFF_ptr = *itFF;
	assert (lFF_ptr != NULL);  

	// Browse the booking-classes
	const BookingClassList_T& lBookingClassList =
	  BomManager::getList<BookingClass> (*lFF_ptr);
	for (BookingClassList_T::const_iterator itBC =
	       lBookingClassList.begin();
	     itBC != lBookingClassList.end(); ++itBC) {
	  const BookingClass* lBC_ptr = *itBC;
	  assert (lBC_ptr != NULL);

#if BOOST_VERSION >= 104100
	  
	  // Put family code in property tree
	  const FamilyCode_T& lFamilyCode = lFF_ptr->getFamilyCode();
	  ioSCTree.put ("family_code", lFamilyCode); 

	  // Export the cabin tree to add sub-classes details
	  jsonExportBookingClass (ioPropertyTree, ioSCTree, *lBC_ptr);

#endif // BOOST_VERSION >= 104100  

	}
      }
    } else {

      // The fare family code is a fake one ('NoFF'), and therefore
      // does not vary
      const FamilyCode_T lDefaultFamilyCode ("NoFF");

      // Browse the booking-classes, directly from the segment-cabin object
      const BookingClassList_T& lBookingClassList =
	BomManager::getList<BookingClass> (iSegmentCabin);
      for (BookingClassList_T::const_iterator itBC =
	     lBookingClassList.begin();
	   itBC != lBookingClassList.end(); ++itBC) {
	const BookingClass* lBC_ptr = *itBC;
	assert (lBC_ptr != NULL);
	  
#if BOOST_VERSION >= 104100
	
	// Put family code in property tree
	ioSCTree.put ("family_code", lDefaultFamilyCode); 

	// Export the cabin tree to add sub-classes details
	jsonExportBookingClass (ioPropertyTree, ioSCTree, *lBC_ptr); 

#endif // BOOST_VERSION >= 104100
      }
    }
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::jsonExportBookingClass (bpt::ptree& ioPropertyTree,
					      bpt::ptree& ioSCTree,
                                              const BookingClass& iBookingClass) {
 
   /**
     * Booking-class level (only)
     *
     */

#if BOOST_VERSION >= 104100
    
    // Put sub class in property tree
    ioSCTree.put ("class_code", iBookingClass.toString());
    // Put authorization level in property tree 
    std::ostringstream oAUProtStr;
    oAUProtStr << iBookingClass.getAuthorizationLevel()
               << " (" << iBookingClass.getProtection()
	       << ") ";
    ioSCTree.put ("min/au (prot)", oAUProtStr.str());
    // Put negotiated space in property tree
    const NbOfSeats_T& lNegotiatedSpace = 
      iBookingClass.getNegotiatedSpace();
    ioSCTree.put ("nego", lNegotiatedSpace);
    // Put no show percentage in property tree 
    const OverbookingRate_T& lNoShowPercentage = 
      iBookingClass.getNoShowPercentage();
    ioSCTree.put ("ns%", lNoShowPercentage);
    // Put cancellation percentage in property tree 
    const OverbookingRate_T& lCancellationPercentage = 
      iBookingClass.getCancellationPercentage();
    ioSCTree.put ("ob%", lCancellationPercentage);
    // Put sub nb of bookings in property tree 
    const NbOfBookings_T lNbOfBookings = 
      iBookingClass.getNbOfBookings();
    ioSCTree.put ("bkgs", lNbOfBookings);
    // Put nb of group bookings in property tree
    const NbOfBookings_T& lNbOfGroupBookings = 
      iBookingClass.getNbOfGroupBookings();
    ioSCTree.put ("grp_bks (pdg)", lNbOfGroupBookings);
    // Put nb of staff bookings in property tree
    const NbOfBookings_T& lNbOfStaffBookings = 
      iBookingClass.getNbOfStaffBookings();
    ioSCTree.put ("stf_bkgs", lNbOfStaffBookings);
    // Put nb of WL bookings in property tree 
    const NbOfBookings_T& lNbOfWLBookings = 
      iBookingClass.getNbOfWLBookings();
    ioSCTree.put ("wl_bkgs", lNbOfWLBookings);
    // Put ETB in property tree
    const NbOfBookings_T& lETB = iBookingClass.getETB();
    ioSCTree.put ("etb", lETB);
    // Put net class availability in property tree
    const Availability_T& lNetClassAvailability = 
      iBookingClass.getNetClassAvailability();
    ioSCTree.put ("class_avl", lNetClassAvailability);
    // Put segment availability in property tree  
    const Availability_T& lSegmentAvailability = 
      iBookingClass.getSegmentAvailability();
    ioSCTree.put ("seg_avl", lSegmentAvailability);
    // Put net revenue availability in property tree
    const Availability_T& lNetRevenueAvailability =  
      iBookingClass.getNetRevenueAvailability();
    ioSCTree.put ("rev_avl", lNetRevenueAvailability);

    // Add the sub-classe (containing cabin and fare-families information) 
    // to the global tree
    ioPropertyTree.push_back(std::make_pair("", ioSCTree));
      
#endif // BOOST_VERSION >= 104100
  }  

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::
  jsonExportBookingRequestObject (std::ostream& oStream,
				  const EventStruct& iEventStruct) {
   
    // Get the current event type: it should be booking request
    const EventType::EN_EventType& lEventType =
      iEventStruct.getEventType();
    assert (lEventType == EventType::BKG_REQ); 	

    // Get the booking request (the current event type is booking request)
    const BookingRequestStruct& lBookingRequest = 
      iEventStruct.getBookingRequest(); 

#if BOOST_VERSION >= 104100  

    // Create an empty property tree object for the current booking request
    bpt::ptree ptBookingRequest;

    // Put request date time in property tree 
    const DateTime_T& lRequestDateTime = 
      lBookingRequest.getRequestDateTime();	
    ptBookingRequest.put ("time_stamp", lRequestDateTime); 
    // Put event type in property tree 
    ptBookingRequest.put ("event_type", EventType::getLabel(lEventType));		 
    // Put origin in property tree 
    const AirportCode_T& lOrigin = lBookingRequest.getOrigin();
    ptBookingRequest.put ("org", lOrigin);	 
    // Put destination in property tree
    const AirportCode_T& lDestination = lBookingRequest.getDestination();
    ptBookingRequest.put ("des", lDestination);		
    // Put preferred cabin in property tree
    const CabinCode_T& lCabinCode = lBookingRequest.getPreferredCabin();	
    ptBookingRequest.put ("cab", lCabinCode); 
    // Put party size in property tree
    const NbOfSeats_T& lNbOfSeats = lBookingRequest.getPartySize();	
    ptBookingRequest.put ("pax", lNbOfSeats); 	
    // Put point-of-sale in property tree
    const AirportCode_T& lPOS = lBookingRequest.getPOS();
    ptBookingRequest.put ("pos", lPOS);  	 
    // Put channel in property tree
    const ChannelLabel_T& lChannelLabel = 
      lBookingRequest.getBookingChannel();
    ptBookingRequest.put ("cha", lChannelLabel); 	
    // Put WTP in property tree
    const WTP_T& lWTP = lBookingRequest.getWTP();	
    ptBookingRequest.put ("wtp", lWTP); 
    // Put request date in property tree 
    const Date_T& lRequestDate = 
      lRequestDateTime.boost::posix_time::ptime::date();
    ptBookingRequest.put ("bkg_date", lRequestDate); 	
    // Put departure date in property tree 	
    const Date_T& lPreferedDepartureDate = 
      lBookingRequest.getPreferedDepartureDate();
    ptBookingRequest.put ("dep_date", lPreferedDepartureDate);  	
    // Put advance purchase in property tree 
    assert (lPreferedDepartureDate >= lRequestDate);
    const DateOffset_T& lAdvancePurchase = 
      lPreferedDepartureDate - lRequestDate;
    ptBookingRequest.put ("adv_purchase", lAdvancePurchase); 
    // Put stay duration in property tree 
    const DayDuration_T& lStayDuration = 
      lBookingRequest.getStayDuration(); 	
    ptBookingRequest.put ("stay_duration", lStayDuration); 
    //  Put return date in property tree	
    const DateOffset_T lDayDuration (lStayDuration);	
    const Date_T& lReturnDate = 
      lPreferedDepartureDate + lDayDuration;
    ptBookingRequest.put ("return_date", lReturnDate); 	
    // Put cancellation date in property tree  
    // TODO:  cancellation date
    ptBookingRequest.put ("cancel_date", "xxxx-xx-xx"); 	
    // Put preferred departure time in property tree   
    const Duration_T& lPreferredDepartureTime = 
      lBookingRequest.getPreferredDepartureTime();
    ptBookingRequest.put ("dep_time", lPreferredDepartureTime); 	
    // Put preferred return time in property tree 	
    // TODO: preferred return time  
    ptBookingRequest.put ("return_time", "xxPM"); 		
    // Put preferred carriers in property tree   
    // TODO: preferred carriers
    ptBookingRequest.put ("pref_carriers", "XX"); 	
    
    // Write the property tree into the JSON stream.
    write_json (oStream, ptBookingRequest);
  
#endif // BOOST_VERSION >= 104100
  } 

  // ////////////////////////////////////////////////////////////////////
  void BomJSONExport::
  jsonExportBreakPointObject (std::ostream& oStream,
			      const EventStruct& iEventStruct) {
 
    // Get the current event type: it should be break point
    const EventType::EN_EventType& lEventType =
      iEventStruct.getEventType();
    assert (lEventType == EventType::BRK_PT); 	

    // Get the break point (the current event type is break point)
    const BreakPointStruct& lBreakPoint = 
      iEventStruct.getBreakPoint(); 

#if BOOST_VERSION >= 104100  

    // Create an empty property tree object for the current break point
    bpt::ptree ptBreakPoint;     

    // Put break point date time in property tree 
    const DateTime_T& lRequestDateTime = 
      lBreakPoint.getBreakPointTime();	
    ptBreakPoint.put ("time_stamp", lRequestDateTime);  
    // Put event type in property tree 
    ptBreakPoint.put ("event_type", EventType::getLabel(lEventType));		 	   
    
    // Write the property tree into the JSON stream.
    write_json (oStream, ptBreakPoint);


#endif // BOOST_VERSION >= 104100
  }  

}
