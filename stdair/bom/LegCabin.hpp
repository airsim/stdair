#ifndef __STDAIR_BOM_LEGCABIN_HPP
#define __STDAIR_BOM_LEGCABIN_HPP
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/LegCabinKey.hpp>
#include <stdair/bom/LegCabinTypes.hpp>
#include <stdair/bom/VirtualClassStruct.hpp>
#include <stdair/bom/VirtualClassTypes.hpp>


namespace stdair {

  /**
   * @brief Class representing the actual attributes for an airline
   * leg-cabin.
   */
  class LegCabin : public BomAbstract {
    template <typename BOM> friend class FacBom; 
    template <typename BOM> friend class FacCloneBom;
    friend class FacBomManager;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef LegCabinKey Key_T;

  public:
    // /////////// Getters ////////////
    /**
     * Get the leg-cabin key (cabin code).
     */
    const Key_T& getKey() const {
      return _key;
    }

    /**
     * Get the parent object.
     */
    BomAbstract* const getParent() const {
      return _parent;
    }
    
    /**
     * Get the cabin code (from key).
     */
    const CabinCode_T& getCabinCode() const {
      return _key.getCabinCode();
    }

    /**
     * Get the (leg-date, leg-cabin) key (board point and cabin code).
     *
     * \note That method assumes that the parent object derives from
     *       the SegmentDate class, as it needs to have access to the
     *       describeKey() method.
     */
    const MapKey_T getFullerKey() const;

    /**
     * Get the map of children holders.
     */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /** Get the cabin offered capacity. */
    const CabinCapacity_T& getOfferedCapacity() const {
      return _offeredCapacity;
    }

    /** Get the cabin physical capacity. */
    const CabinCapacity_T& getPhysicalCapacity() const {
      return _physicalCapacity;
    }

    /** Get the number of sold seat. */
    const NbOfSeats_T& getSoldSeat() const {
      return _soldSeat;
    }

    /** Get the value of committed space. */
    const CommittedSpace_T& getCommittedSpace() const {
      return _committedSpace;
    }

    /** Get the value of the availability pool. */
    const Availability_T& getAvailabilityPool() const {
      return _availabilityPool;
    }

    /** Get the value of the availability. */
    const Availability_T& getAvailability() const {
      return _availability;
    }

    /** Get the current Bid-Price. */
    const BidPrice_T& getCurrentBidPrice() const {
      return _currentBidPrice;
    }

    /** Get the previous Bid-Price. */
    const BidPrice_T& getPreviousBidPrice() const {
      return _previousBidPrice;
    }
    
    /** Get the Bid-Price Vector. */
    const BidPriceVector_T& getBidPriceVector() const {
      return _bidPriceVector;
    }

    /** Get the capacity adjustment due to check-in (DCS) regrade. */
    const CapacityAdjustment_T& getRegradeAdjustment() const {
      return _dcsRegrade;
    }

    /** Authorisation Level (AU). */
    const AuthorizationLevel_T& getAuthorizationLevel() const {
      return _au;
    }

    /** Unsold Protection (UPR). */
    const UPR_T& getUPR() const {
      return _upr;
    }

    /** Net Availability (NAV). */
    const Availability_T& getNetAvailability() const {
      return _nav;
    }

    /** Gross Availability (GAV). */
    const Availability_T& getGrossAvailability() const {
      return _gav;
    }

    /** Average Cancellation Percentage (ACP). */
    const OverbookingRate_T& getAvgCancellationPercentage() const {
      return _acp;
    }

    /** Expected to Board (ETB). */
    const NbOfSeats_T& getETB() const {
      return _etb;
    }

    /** Number of staff bookings. */
    const NbOfSeats_T& getStaffNbOfSeats() const {
      return _staffNbOfBookings;
    }

    /** Number of wait-listed bookings. */
    const NbOfSeats_T& getWLNbOfSeats() const {
      return _wlNbOfBookings;
    }

    /** Number of group bookings. */
    const NbOfSeats_T& getGroupNbOfSeats() const {
      return _groupNbOfBookings;
    }

    /** The virtual class list. */
    VirtualClassList_T& getVirtualClassList() {
      return _virtualClassList;
    }

     /** Reset the bid price vector and return it. */
    BidPriceVector_T& getBidPriceVector() {
      return _bidPriceVector;
    }


    /** Get the yield-demand map. */
    const YieldLevelDemandMap_T& getYieldLevelDemandMap() {
      return _yieldLevelDemandMap;
    }


  public:
    // ///////////// Setters ///////////////
    /** Set the offered and physical capacities. */
    void setCapacities (const CabinCapacity_T& iCapacity);
    
    /** Set the number of sold seat. */
    void setSoldSeat (const NbOfSeats_T& iSoldSeat) {
      _soldSeat = iSoldSeat;
    }

    /** Set the value of committed space. */
    void setCommittedSpace (const CommittedSpace_T& iCommittedSpace) {
      _committedSpace = iCommittedSpace;
    }

    /** Set the value of availability pool. */
    void setAvailabilityPool (const Availability_T& iAvailabilityPool) {
      _availabilityPool = iAvailabilityPool;
    }

    /** Set the value of availability. */
    void setAvailability (const Availability_T& iAvailability) {
      _availability = iAvailability;
    }

    /** Set the current Bid-Price. */
    void setCurrentBidPrice (const BidPrice_T& iBidPrice) {
      _currentBidPrice = iBidPrice;
    }

    /** Set the previous Bid-Price. */
    void setPreviousBidPrice (const BidPrice_T& iBidPrice) {
      _previousBidPrice = iBidPrice;
    }

    /** Update the previous bid price value with the current one. */
    void updatePreviousBidPrice () {
      _previousBidPrice = _currentBidPrice;
    }   

    /** Get the capacity adjustment due to check-in (DCS) regrade. */
    void setRegradeAdjustment (const CapacityAdjustment_T& iRegradeAdjustment) {
      _dcsRegrade = iRegradeAdjustment;
    }

    /** Set the Authorisation Level (AU). */
    void setAuthorizationLevel (const AuthorizationLevel_T& iAU) {
      _au = iAU;
    }

    /** Set the Unsold Protection (UPR). */
    void setUPR (const UPR_T& iUPR) {
      _upr = iUPR;
    }

    /** Set the Net Availability (NAV). */
    void setNetAvailability (const Availability_T& iNAV) {
      _nav = iNAV;
    }

    /** Set the Gross Availability (GAV). */
    void setGrossAvailability (const Availability_T& iGAV) {
      _gav = iGAV;
    }

    /** Set the Average Cancellation Percentage (ACP). */
    void setAvgCancellationPercentage (const OverbookingRate_T& iACP) {
      _acp = iACP;
    }

    /** Set the Expected to Board (ETB). */
    void setETB (const NbOfSeats_T& iETB) {
      _etb = iETB;
    }

    /** Set the Number of staff sold seats. */
    void setStaffNbOfSeats (const NbOfSeats_T& iStaffSeats) {
      _staffNbOfBookings = iStaffSeats;
    }

    /** Set the Number of wait-listed sold seats. */
    void setWLNbOfSeats (const NbOfSeats_T& iWLSeats) {
      _wlNbOfBookings = iWLSeats;
    }

    /** Set the Number of group sold seats. */
    void setGroupNbOfSeats (const NbOfSeats_T& iGroupSeats) {
      _groupNbOfBookings = iGroupSeats;
    }

    /** Update the bid price (from bid price vector if not empty). */
    void updateCurrentBidPrice();

    
  public:
    // /////////// Display support methods /////////
    /**
     * Dump a Business Object into an output stream.
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const {
      ioOut << toString();
    }

    /**
     * Read a Business Object from an input stream.
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn) {
    }

    /**
     * Get the serialised version of the Business Object.
     */
    std::string toString() const;
    
    /**
     * Get a string describing the  key.
     */
    const std::string describeKey() const {
      return _key.toString();
    }

    /**
     * Display the virtual class list content.
     */
    const std::string displayVirtualClassList() const;


  public:
    // /////////// Business methods //////////
    /**
     * Register a sale.
     */
    void updateFromReservation (const NbOfBookings_T&);

    /**
     * Add a virtual class to the list.
     */
    void addVirtualClass (const VirtualClassStruct& iVC) {
      _virtualClassList.push_back (iVC);
    }

    /**
     * Empty the virtual class list.
     */
    void emptyVirtualClassList() {
      _virtualClassList.clear();
    }

    /**
     * Empty the bid price vector.
     */
    void emptyBidPriceVector() {
      _bidPriceVector.clear();
    }

    /**
     * Add demand information.
     */
    void addDemandInformation (const YieldValue_T&, const MeanValue_T&,
                               const StdDevValue_T&);

    /**
     * Reset the (yield level,demand) map.
     */
    void emptyYieldLevelDemandMap() {
      _yieldLevelDemandMap.clear();
    }


  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Constructor.
     */
    LegCabin (const Key_T&);
    /**
     * Destructor.
     */
    ~LegCabin();


  private:
    /**
     * Default constructor.
     */
    LegCabin();
    /**
     * Default copy constructor.
     */
    LegCabin (const LegCabin&);


  protected:
    // ////////// Attributes /////////
    /**
     * Primary key (cabin code).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (LegDate).
     */
    BomAbstract* _parent;
    
    /**
     * Map holding the children (Bucket objects).
     */
    HolderMap_T _holderMap;

    /** Saleable capacity of the cabin. */
    CabinCapacity_T _offeredCapacity;

    /** Physical capacity of the cabin. */
    CabinCapacity_T _physicalCapacity;

    /** Aggregated number of sold seats. */
    NbOfSeats_T  _soldSeat;

    /* Committed space. */
    CommittedSpace_T  _committedSpace;

    /** Availability pool. */
    Availability_T _availabilityPool;

    /** Availability. */
    Availability_T _availability;

    /** Current Bid-Price (BP). */
    BidPrice_T _currentBidPrice;

    /** Previous Bid-Price (BP). */
    BidPrice_T _previousBidPrice;
    
    /** Bid-Price Vector (BPV). */
    BidPriceVector_T _bidPriceVector;

    /** List of virtual classes (for revenue management optimisation). */
    VirtualClassList_T _virtualClassList;

    /** Map holding the demand information indexed by yield. */
    YieldLevelDemandMap_T _yieldLevelDemandMap;


  public:
    /** Capacity adjustment of the cabin, due to check-in (DCS) regrade. */
    CapacityAdjustment_T _dcsRegrade;

    /** Authorisation Level (AU). */
    AuthorizationLevel_T _au;

    /** Unsold Protection (UPR). */
    UPR_T _upr;

    /** Net Availability (NAV). */
    Availability_T _nav;

    /** Gross Availability (GAV). */
    Availability_T _gav;

    /** Average Cancellation Percentage (ACP). */
    OverbookingRate_T _acp;

    /** Expected to Board (ETB). */
    NbOfSeats_T _etb;

    /** Number of staff bookings. */
    NbOfSeats_T _staffNbOfBookings;

    /** Number of wait-listed bookings. */
    NbOfSeats_T _wlNbOfBookings;

    /** Number of group bookings. */
    NbOfSeats_T _groupNbOfBookings;
  };

}
#endif // __STDAIR_BOM_LEGCABIN_HPP

