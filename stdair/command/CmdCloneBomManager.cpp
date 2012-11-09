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
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/factory/FacCloneBom.hpp>
#include <stdair/command/CmdCloneBomManager.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/BomRetriever.hpp>

namespace stdair {  
  
  // ////////////////////////////////////////////////////////////////////
  void CmdCloneBomManager::cloneBomRoot (const BomRoot& iBomRoot,
                                         BomRoot& ioCloneBomRoot) {

    /**
     * Bom root level (only)
     * Nothing to do: the root has already be cloned by construction.
     */
                           
    // Check whether there are Inventory objects
    const bool hasInventoryList = BomManager::hasList<Inventory> (iBomRoot);
    if (hasInventoryList == true) {
    
      // Browse the inventories
      const InventoryList_T& lInventoryList =
	BomManager::getList<Inventory> (iBomRoot);
      for (InventoryList_T::const_iterator itInv = lInventoryList.begin();
	   itInv != lInventoryList.end(); ++itInv) {
	const Inventory* lInv_ptr = *itInv;
	assert (lInv_ptr != NULL);

	// Clone the current inventory
	Inventory& lCloneInventory = cloneInventory (*lInv_ptr, ioCloneBomRoot);
	FacBomManager::addToListAndMap (ioCloneBomRoot, lCloneInventory);
	FacBomManager::linkWithParent (ioCloneBomRoot, lCloneInventory);
      }
    }

    // Check whether there are Airport Pair objects
    const bool hastAirportPairList = 
      BomManager::hasList<AirportPair> (iBomRoot);
    if (hastAirportPairList == true) {
    
      // Browse the airport pairs
      const AirportPairList_T& lAirportPairList =
	BomManager::getList<AirportPair> (iBomRoot);
      for (AirportPairList_T::const_iterator itAirportPair =
             lAirportPairList.begin();
	   itAirportPair != lAirportPairList.end(); ++itAirportPair) {
	const AirportPair* lAirportPair_ptr = *itAirportPair;
	assert (lAirportPair_ptr != NULL);

	// Clone the current airport pair
	AirportPair& lCloneAirportPair = cloneAirportPair (*lAirportPair_ptr);
	FacBomManager::addToListAndMap (ioCloneBomRoot, lCloneAirportPair);
	FacBomManager::linkWithParent (ioCloneBomRoot, lCloneAirportPair);
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory& CmdCloneBomManager::cloneInventory (const Inventory& iInventory,
                                                 BomRoot& ioCloneBomRoot) { 

    /**
     * Inventory level (only)
     */
    Inventory& lCloneInventory = 
      FacCloneBom<Inventory>::instance().clone (iInventory); 

    // Check whether there are FlightDate objects
    const bool hasFlighDateList = BomManager::hasList<FlightDate> (iInventory);
    if (hasFlighDateList == true) {    
      // Browse the flight-dates
      const FlightDateList_T& lFlightDateList =
	BomManager::getList<FlightDate> (iInventory);
      for (FlightDateList_T::const_iterator itFD = lFlightDateList.begin();
	   itFD != lFlightDateList.end(); ++itFD) {
	const FlightDate* lFD_ptr = *itFD;
	assert (lFD_ptr != NULL);
      
	// Clone the current flight-date
	FlightDate& lCloneFD = cloneFlightDate (*lFD_ptr);
	FacBomManager::addToListAndMap (lCloneInventory, lCloneFD);
	FacBomManager::linkWithParent (lCloneInventory, lCloneFD);
      }
    }

    // Check if the inventory contains a list of partners
    const bool hasPartnerList = BomManager::hasList<Inventory> (iInventory);
    if (hasPartnerList == true) {
    
      // Browse the partner's inventories
      const InventoryList_T& lPartnerInventoryList =
        BomManager::getList<Inventory> (iInventory);
      
      for (InventoryList_T::const_iterator itInv =
             lPartnerInventoryList.begin();
           itInv != lPartnerInventoryList.end(); ++itInv) {           
        const Inventory* lInv_ptr = *itInv;
        assert (lInv_ptr != NULL);
	
        // Clone the current partnership inventory
        Inventory& lClonePartnerInventory = cloneInventory (*lInv_ptr,
                                                            ioCloneBomRoot);  
	FacBomManager::addToListAndMap (lCloneInventory,
                                        lClonePartnerInventory);
	FacBomManager::linkWithParent (lCloneInventory,
                                       lClonePartnerInventory);   
      }
    }

    // Check whether there are O&D date objects
    const bool hasOnDList = BomManager::hasList<OnDDate> (iInventory);
    if (hasOnDList == true){

      //Browse the O&Ds
      const OnDDateList_T& lOnDDateList =
        BomManager::getList<OnDDate> (iInventory);

      for (OnDDateList_T::const_iterator itOnD = lOnDDateList.begin();
           itOnD != lOnDDateList.end(); ++itOnD) {
        const OnDDate* lOnDDate_ptr = *itOnD;
        assert (lOnDDate_ptr != NULL);

        // Clone the current O&D date
	OnDDate& lCloneOnDDate = cloneOnDDate (*lOnDDate_ptr);
	FacBomManager::addToListAndMap (lCloneInventory, lCloneOnDDate);
	FacBomManager::linkWithParent (lCloneInventory, lCloneOnDDate);
      }
    } 

    // Check whether there are Flight Period objects
    const bool hasFlightPeriodList = 
      BomManager::hasList<FlightPeriod> (iInventory);
    if (hasFlightPeriodList == true) {
    
      // Browse the flight-periods
      const FlightPeriodList_T& lFlightPeriodList =
	BomManager::getList<FlightPeriod> (iInventory);
      for (FlightPeriodList_T::const_iterator itFlightPeriod =
             lFlightPeriodList.begin();
	   itFlightPeriod != lFlightPeriodList.end(); ++itFlightPeriod) {
	const FlightPeriod* lFlightPeriod_ptr = *itFlightPeriod;
	assert (lFlightPeriod_ptr != NULL);

	// Clone the current flight period
	FlightPeriod& lCloneFlightPeriod = cloneFlightPeriod (*lFlightPeriod_ptr);
	FacBomManager::addToListAndMap (lCloneInventory, lCloneFlightPeriod);
	FacBomManager::linkWithParent (lCloneInventory, lCloneFlightPeriod);
      }
    }

    // Check whether there is an airline feature object
    const AirlineFeature* lAirlineFeature_ptr =
      BomManager::getObjectPtr<AirlineFeature,Inventory> (iInventory,
                                                          iInventory.getAirlineCode());
    if (lAirlineFeature_ptr != NULL) {
      // Clone the current airline feature object
      AirlineFeature& lCloneAirlineFeature =
        cloneAirlineFeature (*lAirlineFeature_ptr);
      FacBomManager::setAirlineFeature (lCloneInventory, lCloneAirlineFeature);
      FacBomManager::linkWithParent (lCloneInventory, lCloneAirlineFeature);
      // Link the airline feature object with the top of the BOM tree
      FacBomManager::addToListAndMap (ioCloneBomRoot, lCloneAirlineFeature);
    }

    return lCloneInventory;
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeature& CmdCloneBomManager::
  cloneAirlineFeature (const AirlineFeature& iAirlineFeature) {   

    /**
     * O&D-date level (only)
     */ 
    AirlineFeature& lCloneAirlineFeature = 
      FacCloneBom<AirlineFeature>::instance().clone (iAirlineFeature);  

    return lCloneAirlineFeature;
  } 
 

  // ////////////////////////////////////////////////////////////////////
  OnDDate& CmdCloneBomManager::cloneOnDDate (const OnDDate& iOnDDate) {   

    /**
     * O&D-date level (only)
     */ 
    OnDDate& lCloneOnDDate = 
      FacCloneBom<OnDDate>::instance().clone (iOnDDate);  

    return lCloneOnDDate;
  } 

  // ////////////////////////////////////////////////////////////////////
  FlightDate& CmdCloneBomManager::
  cloneFlightDate (const FlightDate& iFlightDate) { 

    /**
     * FlightDate level (only)
     */ 
    FlightDate& lCloneFlightDate = 
      FacCloneBom<FlightDate>::instance().clone (iFlightDate);   
    
    // Check whether there are LegDate objects
    const bool hasLegDateList = BomManager::hasList<LegDate> (iFlightDate);
    if (hasLegDateList == true) {

      // Browse the leg-dates
      const LegDateList_T& lLegDateList =
	BomManager::getList<LegDate> (iFlightDate);
      for (LegDateList_T::const_iterator itLD = lLegDateList.begin();
	   itLD != lLegDateList.end(); ++itLD) {
	const LegDate* lLD_ptr = *itLD;
	assert (lLD_ptr != NULL); 

	// Clone the current leg-date
	LegDate& lCloneLegDate = cloneLegDate (*lLD_ptr);
	FacBomManager::addToListAndMap (lCloneFlightDate, lCloneLegDate);
	FacBomManager::linkWithParent (lCloneFlightDate, lCloneLegDate);
      }  
    }

    // Check whether there are SegmentDate objects
    const bool hasSegmentDateList = 
      BomManager::hasList<SegmentDate> (iFlightDate);
    if (hasSegmentDateList == true) {
    
      // Browse the segment-dates
      const SegmentDateList_T& lSegmentDateList =
	BomManager::getList<SegmentDate> (iFlightDate);
      for (SegmentDateList_T::const_iterator itSD = lSegmentDateList.begin();
	   itSD != lSegmentDateList.end(); ++itSD) {
	const SegmentDate* lSD_ptr = *itSD;
	assert (lSD_ptr != NULL);	

	// Clone the current segment-date
	SegmentDate& lCloneSegmentDate = cloneSegmentDate (*lSD_ptr);
	FacBomManager::addToListAndMap (lCloneFlightDate, lCloneSegmentDate);
	FacBomManager::linkWithParent (lCloneFlightDate, lCloneSegmentDate);

      }
    }
      
    return lCloneFlightDate; 
  } 

  // ////////////////////////////////////////////////////////////////////
  LegDate& CmdCloneBomManager::cloneLegDate (const LegDate& iLegDate) { 

    /**
     * Leg Date level (only)
     */ 
    LegDate& lCloneLegDate = 
      FacCloneBom<LegDate>::instance().clone (iLegDate);

    // Check whether there are LegCabin objects
    const bool hasLegCabinList = BomManager::hasList<LegCabin> (iLegDate);
    if (hasLegCabinList == true) {
      // Browse the leg-cabins
      const LegCabinList_T& lLegCabinList =
        BomManager::getList<LegCabin> (iLegDate);
      for (LegCabinList_T::const_iterator itLC = lLegCabinList.begin();
           itLC != lLegCabinList.end(); ++itLC) {
        const LegCabin* lLC_ptr = *itLC;
        assert (lLC_ptr != NULL);

        // Clone the current leg-cabin	
        LegCabin& lCloneLegCabin = cloneLegCabin (*lLC_ptr);
	FacBomManager::addToListAndMap (lCloneLegDate, lCloneLegCabin);
	FacBomManager::linkWithParent (lCloneLegDate, lCloneLegCabin);
      }
    }

    return lCloneLegDate;
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabin& CmdCloneBomManager::cloneLegCabin (const LegCabin& iLegCabin) { 

    /**
     * Leg Cabin level (only)
     */ 
    LegCabin& lCloneLegCabin = 
      FacCloneBom<LegCabin>::instance().clone (iLegCabin);

    // Check whether there are Bucket objects
    const bool hasBucketList = BomManager::hasList<Bucket> (iLegCabin);
    if (hasBucketList == true) {
      // Browse the buckets
      const BucketList_T& lBucketList =
        BomManager::getList<Bucket> (iLegCabin);
      for (BucketList_T::const_iterator itBucket = lBucketList.begin();
           itBucket != lBucketList.end(); ++itBucket) {
        const Bucket* lBucket_ptr = *itBucket;
        assert (lBucket_ptr != NULL);

        // Clone the current bucket
        Bucket& lCloneBucket = cloneBucket (*lBucket_ptr);
	FacBomManager::addToListAndMap (lCloneLegCabin, lCloneBucket);
	FacBomManager::linkWithParent (lCloneLegCabin, lCloneBucket);
      }  
    }

    return lCloneLegCabin;
  }

  // ////////////////////////////////////////////////////////////////////
  Bucket& CmdCloneBomManager::cloneBucket (const Bucket& iBucket) { 

    /**
     * Leg Cabin level (only)
     */ 
    Bucket& lCloneBucket = 
      FacCloneBom<Bucket>::instance().clone (iBucket);  

    return lCloneBucket;
  } 

  // ////////////////////////////////////////////////////////////////////
  SegmentDate& CmdCloneBomManager::
  cloneSegmentDate (const SegmentDate& iSegmentDate) { 

    /**
     * Segment Date level (only)
     */ 
    SegmentDate& lCloneSegmentDate = 
      FacCloneBom<SegmentDate>::instance().clone (iSegmentDate);

    // Check whether there are SegmentCabin objects
    const bool hasSegmentCabinList = 
      BomManager::hasList<SegmentCabin> (iSegmentDate);
    if (hasSegmentCabinList == true) {
      // Browse the segment-cabins
      const SegmentCabinList_T& lSegmentCabinList =
        BomManager::getList<SegmentCabin> (iSegmentDate);
      for (SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
           itSC != lSegmentCabinList.end(); ++itSC) {
        const SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);

        // Clone the current segment-cabin	
        SegmentCabin& lCloneSegmentCabin = cloneSegmentCabin (*lSC_ptr);
	FacBomManager::addToListAndMap (lCloneSegmentDate, lCloneSegmentCabin);
	FacBomManager::linkWithParent (lCloneSegmentDate, lCloneSegmentCabin);
   
	linkBookingClassesWithSegment (lCloneSegmentDate,
				       lCloneSegmentCabin);

      }
    }
    return lCloneSegmentDate;
  } 

  // ////////////////////////////////////////////////////////////////////
  void CmdCloneBomManager::
  linkBookingClassesWithSegment (SegmentDate& iCloneSegmentDate,
				 SegmentCabin& iCloneSegmentCabin) { 	

    // Browse the fare families to link the booking-classes to the 
    // segment-cabin and to the segment-date 
    const bool hasFareFamilyList = 
      BomManager::hasList<FareFamily> (iCloneSegmentCabin);
    if (hasFareFamilyList == true) {
      const FareFamilyList_T& lCloneFFList =
	BomManager::getList<FareFamily> (iCloneSegmentCabin);
      for (FareFamilyList_T::const_iterator itCloneFF = lCloneFFList.begin();
	   itCloneFF != lCloneFFList.end(); ++itCloneFF) {
	const FareFamily* lCloneFF_ptr = *itCloneFF;
	assert (lCloneFF_ptr != NULL);

	// Browse the list of booking classes 
	const bool hasBookingClasslist = 
	  BomManager::hasList<BookingClass> (*lCloneFF_ptr);
	if (hasBookingClasslist == true) {
	  const BookingClassList_T& lCloneBCList =
	    BomManager::getList<BookingClass> (*lCloneFF_ptr);
	  for (BookingClassList_T::const_iterator itCloneBC =
		 lCloneBCList.begin();
	       itCloneBC != lCloneBCList.end(); ++itCloneBC) {
	    const BookingClass* lCloneBC_ptr = *itCloneBC;
	    assert (lCloneBC_ptr != NULL);
		
	    // Link the booking-class to the segment-cabin
	    stdair::FacBomManager::addToListAndMap (iCloneSegmentCabin, 
						    *lCloneBC_ptr);

	    // Link the booking-class to the segment-date
	    stdair::FacBomManager::addToListAndMap (iCloneSegmentDate, 
						    *lCloneBC_ptr);
	  }
	}
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin& CmdCloneBomManager::
  cloneSegmentCabin (const SegmentCabin& iSegmentCabin) { 

    /**
     * Segment Cabin level (only)
     */ 
    SegmentCabin& lCloneSegmentCabin = 
      FacCloneBom<SegmentCabin>::instance().clone (iSegmentCabin);

    // Check whether there are fare family objects 
    const bool hasFareFamilyList = 
      BomManager::hasList<FareFamily> (iSegmentCabin);
    if (hasFareFamilyList == true) {
      // Browse the fare families
      const FareFamilyList_T& lFareFamilyList =
        BomManager::getList<FareFamily> (iSegmentCabin);
      for (FareFamilyList_T::const_iterator itFF = lFareFamilyList.begin();
           itFF != lFareFamilyList.end(); ++itFF) {
        const FareFamily* lFF_ptr = *itFF;
        assert (lFF_ptr != NULL);

        // Clone the current fare-family	
        FareFamily& lCloneFareFamily = cloneFareFamily (*lFF_ptr);
	FacBomManager::addToListAndMap (lCloneSegmentCabin, lCloneFareFamily);
	FacBomManager::linkWithParent (lCloneSegmentCabin, lCloneFareFamily);
      }
    }
    
    return lCloneSegmentCabin;
  }

  // ////////////////////////////////////////////////////////////////////
  FareFamily& CmdCloneBomManager::
  cloneFareFamily (const FareFamily& iFareFamily) {
    /**
     * Fare Family level (only)
     */ 
    FareFamily& lCloneFareFamily = 
      FacCloneBom<FareFamily>::instance().clone (iFareFamily);

    // Check whether there are booking classes objects
    const bool hasBookingClassList = 
      BomManager::hasList<BookingClass> (iFareFamily);
    if (hasBookingClassList == true) {
      // Browse the list of booking classes
      const BookingClassList_T& lBookingClassList =
        BomManager::getList<BookingClass> (iFareFamily);
      for (BookingClassList_T::const_iterator itBookingClass =
             lBookingClassList.begin();
           itBookingClass != lBookingClassList.end(); ++itBookingClass) {
        const BookingClass* lBC_ptr = *itBookingClass;
        assert (lBC_ptr != NULL);

        // Clone the current booking class
        BookingClass& lCloneBookingClass = cloneBookingClass (*lBC_ptr);
        FacBomManager::addToListAndMap (lCloneFareFamily, lCloneBookingClass);
        FacBomManager::linkWithParent (lCloneFareFamily, lCloneBookingClass);
      }
    }

    return lCloneFareFamily;
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClass& CmdCloneBomManager::
  cloneBookingClass (const BookingClass& iBookingClass) {
    
    /**
     * Booking Class level (only)
     */ 
    BookingClass& lCloneBookingClass = 
      FacCloneBom<BookingClass>::instance().clone (iBookingClass);

    return lCloneBookingClass;
  }

  // ////////////////////////////////////////////////////////////////////
  AirportPair& CmdCloneBomManager::
  cloneAirportPair (const AirportPair& iAirportPair) {

    /**
     * Airport Pair level (only)
     */ 
    AirportPair& lCloneAirportPair = 
      FacCloneBom<AirportPair>::instance().clone (iAirportPair);

    // Check whether there are date-period objects
    const bool hasDatePeriodList = 
      BomManager::hasList<DatePeriod> (iAirportPair);
    if (hasDatePeriodList == true) {
      // Browse the date-periods
      const DatePeriodList_T& lDatePeriodList =
        BomManager::getList<DatePeriod> (iAirportPair);
      for (DatePeriodList_T::const_iterator itDatePeriod =
             lDatePeriodList.begin();
           itDatePeriod != lDatePeriodList.end(); ++itDatePeriod) {
        const DatePeriod* lDatePeriod_ptr = *itDatePeriod;
        assert (lDatePeriod_ptr != NULL);

        // Clone the current date-period	
        DatePeriod& lCloneDatePeriod = cloneDatePeriod (*lDatePeriod_ptr);
	FacBomManager::addToListAndMap (lCloneAirportPair, lCloneDatePeriod);
	FacBomManager::linkWithParent (lCloneAirportPair, lCloneDatePeriod);
      }
    }

    return lCloneAirportPair;
  } 

  // ////////////////////////////////////////////////////////////////////
  DatePeriod& CmdCloneBomManager::
  cloneDatePeriod (const DatePeriod& iDatePeriod) {

    /**
     * Date Period level (only)
     */ 
    DatePeriod& lCloneDatePeriod = 
      FacCloneBom<DatePeriod>::instance().clone (iDatePeriod);  

    // Check whether there are pos-channel objects
    const bool hasPosChannelList = 
      BomManager::hasList<PosChannel> (iDatePeriod);
    if (hasPosChannelList == true) {
      // Browse the pos-channels
      const PosChannelList_T& lPosChannelList =
        BomManager::getList<PosChannel> (iDatePeriod);
      for (PosChannelList_T::const_iterator itPosChannel =
             lPosChannelList.begin();
           itPosChannel != lPosChannelList.end(); ++itPosChannel) {
        const PosChannel* lPosChannel_ptr = *itPosChannel;
        assert (lPosChannel_ptr != NULL);

        // Clone the current pos-channel	
        PosChannel& lClonePosChannel = clonePosChannel (*lPosChannel_ptr);
	FacBomManager::addToListAndMap (lCloneDatePeriod, lClonePosChannel);
	FacBomManager::linkWithParent (lCloneDatePeriod, lClonePosChannel);
      }
    }

    return lCloneDatePeriod;
  }
  
  
  // ////////////////////////////////////////////////////////////////////
  PosChannel& CmdCloneBomManager::
  clonePosChannel (const PosChannel& iPosChannel) {
    
    /**
     * Pos Channel level (only)
     */ 
    PosChannel& lClonePosChannel = 
      FacCloneBom<PosChannel>::instance().clone (iPosChannel);

    // Check whether there are time-period objects
    const bool hasTimePeriodList = 
      BomManager::hasList<TimePeriod> (iPosChannel);
    if (hasTimePeriodList == true) {
      // Browse the time-periods
      const TimePeriodList_T& lTimePeriodList =
        BomManager::getList<TimePeriod> (iPosChannel);
      for (TimePeriodList_T::const_iterator itTimePeriod =
             lTimePeriodList.begin();
           itTimePeriod != lTimePeriodList.end(); ++itTimePeriod) {
        const TimePeriod* lTimePeriod_ptr = *itTimePeriod;
        assert (lTimePeriod_ptr != NULL);

        // Clone the current time-period	
        TimePeriod& lCloneTimePeriod = cloneTimePeriod (*lTimePeriod_ptr);
	FacBomManager::addToListAndMap (lClonePosChannel, lCloneTimePeriod);
	FacBomManager::linkWithParent (lClonePosChannel, lCloneTimePeriod);
      }
    }

    return lClonePosChannel;
  }
  
  // ////////////////////////////////////////////////////////////////////
  TimePeriod& CmdCloneBomManager::
  cloneTimePeriod (const TimePeriod& iTimePeriod) {
    
    /**
     * Time Period level (only)
     */ 
    TimePeriod& lCloneTimePeriod = 
      FacCloneBom<TimePeriod>::instance().clone (iTimePeriod);

    // Check whether there are fare-feature objects
    const bool hasFareFeaturesList = 
      BomManager::hasList<FareFeatures> (iTimePeriod);
    if (hasFareFeaturesList == true) {
      // Browse the fare-features
      const FareFeaturesList_T& lFareFeaturesList =
        BomManager::getList<FareFeatures> (iTimePeriod);
      for (FareFeaturesList_T::const_iterator itFF = lFareFeaturesList.begin();
           itFF != lFareFeaturesList.end(); ++itFF) {
        const FareFeatures* lFF_ptr = *itFF;
        assert (lFF_ptr != NULL);

        // Clone the current fare-feature	
        FareFeatures& lCloneFareFeatures = 
	  cloneFeatures<FareFeatures> (*lFF_ptr);
	FacBomManager::addToListAndMap (lCloneTimePeriod, lCloneFareFeatures);
	FacBomManager::linkWithParent (lCloneTimePeriod, lCloneFareFeatures);
      }
    }

    // Check whether there are yield-feature objects  
    const bool hasYieldFeaturesList = 
      BomManager::hasList<YieldFeatures> (iTimePeriod);
    if (hasYieldFeaturesList == true) {
      // Browse the yield-features
      const YieldFeaturesList_T& lYieldFeaturesList =
        BomManager::getList<YieldFeatures> (iTimePeriod);
      for (YieldFeaturesList_T::const_iterator itYF =
             lYieldFeaturesList.begin();
           itYF != lYieldFeaturesList.end(); ++itYF) {
        const YieldFeatures* lYF_ptr = *itYF;
        assert (lYF_ptr != NULL);

        // Clone the current yield-feature	
        YieldFeatures& lCloneYieldFeatures = 
	  cloneFeatures<YieldFeatures> (*lYF_ptr);
	FacBomManager::addToListAndMap (lCloneTimePeriod, lCloneYieldFeatures);
	FacBomManager::linkWithParent (lCloneTimePeriod, lCloneYieldFeatures);
      }
    }

    return lCloneTimePeriod;
  }
  
  // ////////////////////////////////////////////////////////////////////  
  template <typename FEATURE_TYPE>
  FEATURE_TYPE& CmdCloneBomManager::
  cloneFeatures (const FEATURE_TYPE& iFeatures) {

    /**
     *  Features level (only)
     */ 
    FEATURE_TYPE& lCloneFeatures = 
      FacCloneBom<FEATURE_TYPE>::instance().clone (iFeatures);

    // Check whether there are airline-class list objects
    const bool hasAirlineClassListList = 
      BomManager::hasList<AirlineClassList> (iFeatures);
    if (hasAirlineClassListList == true) {
      // Browse the airline-class lists
      const AirlineClassListList_T& lAirlineClassList =
        BomManager::getList<AirlineClassList> (iFeatures);
      for (AirlineClassListList_T::const_iterator itACList =
             lAirlineClassList.begin();
           itACList != lAirlineClassList.end(); ++itACList) {
        const AirlineClassList* lACList_ptr = *itACList;
        assert (lACList_ptr != NULL);

        // Clone the current airline-class list	
        AirlineClassList& lCloneAirlineClassList =
          cloneAirlineClassList (*lACList_ptr);
	FacBomManager::addToListAndMap (lCloneFeatures,
                                        lCloneAirlineClassList);
	FacBomManager::linkWithParent (lCloneFeatures,
                                       lCloneAirlineClassList);
      }
    }
    
    return lCloneFeatures;
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirlineClassList& CmdCloneBomManager::
  cloneAirlineClassList (const AirlineClassList& iAirlineClassList) {
    
    /**
     * Airline-class list level (only)
     */ 
    AirlineClassList& lCloneAirlineClassList = 
      FacCloneBom<AirlineClassList>::instance().clone (iAirlineClassList);

    return lCloneAirlineClassList;
  }  

  // ////////////////////////////////////////////////////////////////////
  FlightPeriod& CmdCloneBomManager::
  cloneFlightPeriod (const FlightPeriod& iFlightPeriod) {
    
    /**
     * Flight Period level (only)
     */ 
    FlightPeriod& lCloneFlightPeriod = 
      FacCloneBom<FlightPeriod>::instance().clone (iFlightPeriod);

    // Check whether there are airline-class list objects
    const bool hasSegmentPeriodList = 
      BomManager::hasList<SegmentPeriod> (iFlightPeriod);
    if (hasSegmentPeriodList == true) {
      // Browse the airline-class lists
      const SegmentPeriodList_T& lSegmentPeriodList =
        BomManager::getList<SegmentPeriod> (iFlightPeriod);
      for (SegmentPeriodList_T::const_iterator itSegmentPeriod =
             lSegmentPeriodList.begin();
           itSegmentPeriod != lSegmentPeriodList.end(); ++itSegmentPeriod) {
        const SegmentPeriod* lSegmentPeriod_ptr = *itSegmentPeriod;
        assert (lSegmentPeriod_ptr != NULL);

        // Clone the current airline-class list	
        SegmentPeriod& lCloneSegmentPeriod =
          cloneSegmentPeriod (*lSegmentPeriod_ptr);
	FacBomManager::addToListAndMap (lCloneFlightPeriod,
                                        lCloneSegmentPeriod);
	FacBomManager::linkWithParent (lCloneFlightPeriod,
                                       lCloneSegmentPeriod);
      }
    }
    
    return lCloneFlightPeriod;
  } 

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriod& CmdCloneBomManager::
  cloneSegmentPeriod (const SegmentPeriod& iSegmentPeriod) {
    
    /**
     * Segment Period level (only)
     */ 
    SegmentPeriod& lCloneSegmentPeriod = 
      FacCloneBom<SegmentPeriod>::instance().clone (iSegmentPeriod);

    return lCloneSegmentPeriod;
  }

}

/*!
 * \endcode
 */
