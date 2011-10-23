#ifndef __STDAIR_BOM_SEGMENTCABIN_HPP
#define __STDAIR_BOM_SEGMENTCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/SegmentCabinKey.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /**
   * @brief Class representing the actual attributes for an airline
   * segment-cabin.
   */
  class SegmentCabin : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;
    
  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef SegmentCabinKey Key_T;


  public:
    // /////////// Getters ///////////// 
    /**
     * Get the segment-cabin key (cabin code).
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
     * Get the cabin code (primary key).
     */
    const CabinCode_T& getCabinCode() const {
      return _key.getCabinCode();
    }
    
    /**
     * Get the (segment-date, segment-cabin) key (board point, off
     * point and cabin code).
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

    /** Get the guilltine block number. */
    const GuillotineNumber_T& getGuillotineBlockNumber() const {
      return _guillotineNumber;
    }

    /** Get the cabin capacity. */
    const CabinCapacity_T& getCapacity() const {
      return _capacity;
    }

    /** Get the blocked number of bookings. */
    const BlockSpace_T& getBlockSpace() const {
      return _blockSpace;
    }

    /** Get the blocked number of bookings. */
    const BlockSpace_T& getMIN() const {
      return _min;
    }

    /** Unsold Protection (UPR). */
    const UPR_T& getUPR() const {
      return _upr;
    }

    /** Get the booking counter. */
    const NbOfBookings_T& getBookingCounter() const {
      return _bookingCounter;
    }

    /** Get the committed Space value. */
    const CommittedSpace_T& getCommittedSpace() const {
      return _committedSpace;
    }

    /** Get the availability pool value. */
    const Availability_T& getAvailabilityPool() const {
      return _availabilityPool;
    }

    /** Retrive the current Bid-Price. */
    const BidPrice_T& getCurrentBidPrice() const {
      return _currentBidPrice;
    }

    /** Retrive the Bid-Price Vector. */
    const BidPriceVector_T& getBidPriceVector() const {
      return _bidPriceVector;
    }


  public:
    // ///////// Setters //////////
    /** Set the guillotine block number. */
    void setGuillotineBlockNumber (const GuillotineNumber_T& iNumber) {
      _guillotineNumber = iNumber;
    }

    /** Set the cabin capacity. */
    void setCapacity (const CabinCapacity_T& iCapacity) {
      _capacity = iCapacity;
    }

    /** Set the blocked number of seats. */
    void setBlockSpace (const BlockSpace_T& iBlockSpace) {
      _blockSpace = iBlockSpace;
    }

    /** Set the blocked number of seats. */
    void setMIN (const BlockSpace_T& iMIN) {
      _min = iMIN;
    }

    /** Set the Unsold Protection (UPR). */
    void setUPR (const UPR_T& iUPR) {
      _upr = iUPR;
    }

    /** Set the total number of bookings. */
    void setBookingCounter (const NbOfBookings_T& iBookingCounter) {
      _bookingCounter = iBookingCounter;
    }

    /** Set the value of committed space. */
    void setCommittedSpace (const CommittedSpace_T& iCommittedSpace) {
      _committedSpace = iCommittedSpace;
    }

    /** Set the value of availability pool. */
    void setAvailabilityPool (const Availability_T& iAvailabilityPool) {
      _availabilityPool = iAvailabilityPool;
    }

    /** Set the Bid-Price Vector. */
    void setBidPriceVector (const BidPriceVector_T& iBPV) {
      _bidPriceVector = iBPV;
    }


  public:
    // /////////// Business methods //////////
    /** Register a sale. */
    void updateFromReservation (const NbOfBookings_T&);

    
  public:
    // /////////// Display support methods /////////
    /**
     * Dump a Business Object into an output stream.
     *
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const {
      ioOut << toString();
    }

    /**
     * Read a Business Object from an input stream.
     *
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

    
  public:
    // /////////// (Boost) Serialisation support methods /////////
    /**
     * Serialisation.
     */
    template<class Archive>
    void serialize (Archive& ar, const unsigned int iFileVersion);

  private:
    /**
     * Serialisation helper (allows to be sure the template method is
     * instantiated).
     */
    void serialisationImplementation();


  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Constructor.
     */
    SegmentCabin (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~SegmentCabin();

  private:
    /**
     * Default constructor.
     */
    SegmentCabin();

    /**
     * Copy constructor.
     */
    SegmentCabin (const SegmentCabin&);


  protected:
    // ////////// Attributes /////////
    /**
     * Primary key (cabin code).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (SegmentDate).
     */
    BomAbstract* _parent;
    
    /**
     * Map holding the children (FareFamily or BookingClass objects).
     */
    HolderMap_T _holderMap;

    /**
     * The guillotine block number used for Revenue Management activities.
     */
    GuillotineNumber_T _guillotineNumber;

    /** Capacity of the cabin. */
    CabinCapacity_T _capacity;

    /** Blocked capacity. */
    BlockSpace_T _blockSpace;     

    /** Blocked number of seats. */
    BlockSpace_T _min;

    /** Unsold Protection (UPR). */
    UPR_T _upr;

    /** Aggregated number of bookings. */
    NbOfBookings_T _bookingCounter;

    /** Aggreated committed space. */
    CommittedSpace_T _committedSpace;

    /** Aggregated availability pool. */
    Availability_T _availabilityPool;

    /** Bid-Price Vector (BPV). */
    BidPriceVector_T _bidPriceVector;

    /** Current Bid-Price (BP). */
    BidPrice_T _currentBidPrice;
  };

}
#endif // __STDAIR_BOM_SEGMENTCABIN_HPP

