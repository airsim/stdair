#ifndef __STDAIR_BOM_GUILLOTINEBLOCK_HPP
#define __STDAIR_BOM_GUILLOTINEBLOCK_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir 
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/GuillotineBlockKey.hpp>
#include <stdair/bom/GuillotineBlockTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {
  // Forward declarations
  class SegmentCabin;

  /**
   * @brief Class representing the actual attributes for an airline
   * guillotine-block.
   */
  class GuillotineBlock : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef GuillotineBlockKey Key_T;

    
  public:
    // /////////// Getters ///////////////
    /** Get the guillotine-block key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }
    
    /** Get the guillotine number (part of the primary key). */
    const GuillotineNumber_T& getGuillotineNumber() const {
      return _key.getGuillotineNumber();
    }

    /**
     * Get the map of children holders.
     */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /** Get the segment-cabin index map. */
    const SegmentCabinIndexMap_T& getSegmentCabinIndexMap() const {
      return _segmentCabinIndexMap;
    }

    /** Get the value type index map. */
    const ValueTypeIndexMap_T& getValueTypeIndexMap() const {
      return _valueTypesIndexMap;
    }

    /** Get the block index corresponding to the given value type. */
    const BlockIndex_T& getBlockIndex (const MapKey_T&) const;

    /** Get the block number corresponding to the givent segment-cabin. */
    const BlockNumber_T& getBlockNumber (const SegmentCabin&) const;

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDBookingSnapshotView (const BlockNumber_T,
                                                const BlockNumber_T,
                                                const DTD_T) const;

    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangeBookingSnapshotView (const BlockNumber_T,
                                                     const BlockNumber_T,
                                                     const DTD_T,
                                                     const DTD_T) const;

    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDBookingSnapshotView (const BlockNumber_T,
                                           const BlockNumber_T, const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangeBookingSnapshotView (const BlockNumber_T,
                                                const BlockNumber_T,
                                                const DTD_T, const DTD_T);

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDCancellationSnapshotView (const BlockNumber_T,
                                                const BlockNumber_T,
                                                const DTD_T) const;

    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangeCancellationSnapshotView (const BlockNumber_T,
                                                          const BlockNumber_T,
                                                          const DTD_T,
                                                          const DTD_T) const;

    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDCancellationSnapshotView (const BlockNumber_T,
                                                const BlockNumber_T,
                                                const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangeCancellationSnapshotView (const BlockNumber_T,
                                                     const BlockNumber_T,
                                                     const DTD_T, const DTD_T);

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDProductAndPriceOrientedBookingSnapshotView
    (const BlockNumber_T, const BlockNumber_T, const DTD_T) const;

    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangeProductAndPriceOrientedBookingSnapshotView
    (const BlockNumber_T, const BlockNumber_T, const DTD_T, const DTD_T) const;

    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDProductAndPriceOrientedBookingSnapshotView
    (const BlockNumber_T, const BlockNumber_T, const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangeProductAndPriceOrientedBookingSnapshotView
    (const BlockNumber_T, const BlockNumber_T, const DTD_T, const DTD_T);

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDAvailabilitySnapshotView (const BlockNumber_T,
                                                     const BlockNumber_T,
                                                     const DTD_T) const;
    
    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangeAvailabilitySnapshotView (const BlockNumber_T,
                                                          const BlockNumber_T,
                                                          const DTD_T,
                                                          const DTD_T) const;
    
    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDAvailabilitySnapshotView (const BlockNumber_T,
                                                const BlockNumber_T,
                                                const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangeAvailabilitySnapshotView (const BlockNumber_T,
                                                     const BlockNumber_T,
                                                     const DTD_T, const DTD_T);


  public:
    // //////////// Setters /////////////
    /** Set the segment-cabin and value type index maps and initialise
        the snapshot blocks. */
    void initSnapshotBlocks (const SegmentCabinIndexMap_T&,
                             const ValueTypeIndexMap_T&);
    
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
     * Main constructor.
     */
    GuillotineBlock (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~GuillotineBlock();

  private:
    /**
     * Default constructor.
     */
    GuillotineBlock();

    /**
     * Copy constructor.
     */
    GuillotineBlock (const GuillotineBlock&);
    

  protected:
    // ////////// Attributes /////////
    /** Primary key (guillotine number and departure block). */
    Key_T _key;

    /** Pointer on the parent class (Inventory). */
    BomAbstract* _parent;

    /** Map holding the children. */
    HolderMap_T _holderMap;

    /** Map holding the segment-cabin position within the snapshot blocks. */
    SegmentCabinIndexMap_T _segmentCabinIndexMap;

    /** Map holding the value type (class, Q-equivalent, etc) within a
        a segment-cabin inside the snapshot blocks. */
    ValueTypeIndexMap_T _valueTypesIndexMap;

    /** Booking snapshot block. */
    SnapshotBlock_T _bookingSnapshotBlock;

    /** Cancellation snapshot block. */
    SnapshotBlock_T _cancellationSnapshotBlock;

    /** Price & product oriented booking block. */
    SnapshotBlock_T _productAndPriceOrientedBookingSnapshotBlock;

    /** Availability block. */
    SnapshotBlock_T _availabilitySnapshotBlock;
  };

}
#endif // __STDAIR_BOM_GUILLOTINEBLOCK_HPP

