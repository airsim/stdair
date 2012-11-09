#ifndef __STDAIR_CMD_CMDCLONEBOMMANAGER_HPP
#define __STDAIR_CMD_CMDCLONEBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/command/CmdAbstract.hpp>
// StdAir Bom
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/OnDDate.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/Bucket.hpp>
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
#include <stdair/bom/SegmentPeriod.hpp>
#include <stdair/bom/FlightPeriod.hpp>

namespace stdair {

  /**
   * Class wrapping utility functions for handling the BOM tree
   * objects.
   */
  class CmdCloneBomManager : public CmdAbstract {
    //
    friend class STDAIR_Service;
  private:
  
    /**
     * Recursively clone the children of the BOM tree.
     *
     * @param const BomRoot& Root of the BOM tree to be cloned.  
     * @param BomRoot& Root of the cloned BOM tree.
     */
    static void cloneBomRoot (const BomRoot&, BomRoot&);
 
    /**
     * Recursively clone the children of an inventory.
     *
     * @param const Inventory& Root of the BOM tree to be cloned.
     *
     * @return Inventory& Root of the cloned BOM tree.
     * @param BomRoot& Root of the cloned BOM tree.
     */
    static Inventory& cloneInventory (const Inventory&, BomRoot&);

    /**
     * Clone an airline feature object.
     *
     * @param const AirlineFeature& Airline feature to be cloned. 
     * 
     * @return AirlineFeature& Cloned airline feature.
     */
    static AirlineFeature& cloneAirlineFeature (const AirlineFeature&);
  
    /**
     * Recursively clone the children of an OnD.
     *
     * @param const OnDDate& Root of the BOM tree to be cloned. 
     * 
     * @return OnDDate& Root of the cloned BOM tree.
     */
    static OnDDate& cloneOnDDate (const OnDDate&);
  
    /**
     * Recursively clone the children of a flight date.
     *
     * @param const FlightDate& Root of the BOM tree to be cloned. 
     * 
     * @return FlightDate& Root of the cloned BOM tree.
     */
    static FlightDate& cloneFlightDate (const FlightDate&);  
 
    /**
     * Recursively clone the children of a leg date.
     *
     * @param const LegDate& Root of the BOM tree to be cloned. 
     * 
     * @return LegDate& Root of the cloned BOM tree.
     */
    static LegDate& cloneLegDate (const LegDate&);
  
    /**
     * Recursively clone the children of a leg cabin.
     *
     * @param const LegCabin& Root of the BOM tree to be cloned. 
     * 
     * @return LegCabin& Root of the cloned BOM tree.
     */
    static LegCabin& cloneLegCabin (const LegCabin&);
 
    /**
     * Clone a bucket object.
     *
     * @param const Bucket& Bucket to be cloned. 
     * 
     * @return Bucket& Cloned bucket.
     */
    static Bucket& cloneBucket (const Bucket&);
 
    /**
     * Recursively clone the children of a segment date.
     *
     * @param const SegmentDate& Root of the BOM tree to be cloned. 
     * 
     * @return SegmentDate& Root of the cloned BOM tree.
     */
    static SegmentDate& cloneSegmentDate (const SegmentDate&); 

    /**
     * Link all the booking classes with their corresponding segmentDate and 
     * segmentCabin.
     *
     * @param SegmentDate& Segment date to be linked with booking classes.
     * @param SegmentCabin& Segment cabin to be linked with booking classes.
     */
    static void linkBookingClassesWithSegment (SegmentDate&,
					       SegmentCabin&);
 
    /**
     * Recursively clone the children of a segment cabin.
     *
     * @param const SegmentCabin& Root of the BOM tree to be cloned. 
     * 
     * @return SegmentCabin& Root of the cloned BOM tree.
     */
    static SegmentCabin& cloneSegmentCabin (const SegmentCabin&);
  
    /**
     * Recursively clone the children of a fare family.
     *
     * @param const FareFamily& Root of the BOM tree to be cloned. 
     * 
     * @return FareFamily& Root of the cloned BOM tree.
     */
    static FareFamily& cloneFareFamily (const FareFamily&);
     
    /**
     * Recursively clone the children of a booking class.
     *
     * @param const BookingClass& Root of the BOM tree to be cloned. 
     * 
     * @return BookingClass& Root of the cloned BOM tree.
     */
    static BookingClass& cloneBookingClass (const BookingClass&);
    
    /**
     * Recursively clone the children of an airport pair.
     *
     * @param const AirportPair& Root of the BOM tree to be cloned. 
     * 
     * @return AirportPair& Root of the cloned BOM tree.
     */
    static AirportPair& cloneAirportPair (const AirportPair&);
  
    /**
     * Recursively clone the children of a pos channel.
     *
     * @param const PosChannel& Root of the BOM tree to be cloned. 
     * 
     * @return PosChannel& Root of the cloned BOM tree.
     */
    static PosChannel& clonePosChannel (const PosChannel&);
      
    /**
     * Recursively clone the children of a date period.
     *
     * @param const DatePeriod& Root of the BOM tree to be cloned. 
     * 
     * @return DatePeriod& Root of the cloned BOM tree.
     */
    static DatePeriod& cloneDatePeriod (const DatePeriod&);
      
    /**
     * Recursively clone the children of a time period.
     *
     * @param const TimePeriod& Root of the BOM tree to be cloned. 
     * 
     * @return TimePeriod& Root of the cloned BOM tree.
     */
    static TimePeriod& cloneTimePeriod (const TimePeriod&);
       
    /**
     * Recursively clone the children of a fare or yield features object.
     *
     * @param const FEATURE_TYPE& Root of the BOM tree to be cloned. 
     * 
     * @return FEATURE_TYPE& Root of the cloned BOM tree.
     */
    template <typename FEATURE_TYPE>
    static FEATURE_TYPE& cloneFeatures (const FEATURE_TYPE&);
       
    /**
     * Clone an airline class list object.
     *
     * @param AirlineClassList& Airline class list to be cloned. 
     * 
     * @return AirlineClassList& Cloned airline class list.
     */
    static AirlineClassList& cloneAirlineClassList (const AirlineClassList&);
  
    /**
     * Recursively clone the children of a flight period.
     *
     * @param const FlightPeriod& Root of the BOM tree to be cloned. 
     * 
     * @return FlightPeriod& Root of the cloned BOM tree.
     */
    static FlightPeriod& cloneFlightPeriod (const FlightPeriod&);

    /**
     * Clone an segment period object.
     *
     * @param SegmentPeriod& Segment period to be cloned. 
     * 
     * @return SegmentPeriod& Cloned segment period.
     */
    static SegmentPeriod& cloneSegmentPeriod (const SegmentPeriod&);

  };
}
#endif // ___STDAIR_CMD_CMDCLONEBOMMANAGER_HPP
