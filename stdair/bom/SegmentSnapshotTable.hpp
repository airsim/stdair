#ifndef __STDAIR_BOM_SEGMENTSNAPSHOTTABLE_HPP
#define __STDAIR_BOM_SEGMENTSNAPSHOTTABLE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir 
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/SegmentSnapshotTableKey.hpp>
#include <stdair/bom/SegmentSnapshotTableTypes.hpp>

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
   * segment data tables.
   */
  class SegmentSnapshotTable : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef SegmentSnapshotTableKey Key_T;

    
  public:
    // /////////// Getters ///////////////
    /** Get the segment data table key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }
    
    /** Get the table ID (part of the primary key). */
    const TableID_T& getTableID() const {
      return _key.getTableID();
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

    /** Get the class index map. */
    const ClassIndexMap_T& getClassIndexMap() const {
      return _classIndexMap;
    }

    /** Get the index corresponding to the given class. */
    const ClassIndex_T& getClassIndex (const MapKey_T&) const;

    /** Get the segment data ID corresponding to the givent segment-cabin. */
    const SegmentDataID_T& getSegmentDataID (const SegmentCabin&) const;

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDBookingSnapshotView (const SegmentDataID_T,
                                                const SegmentDataID_T,
                                                const DTD_T) const;

    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangeBookingSnapshotView (const SegmentDataID_T,
                                                     const SegmentDataID_T,
                                                     const DTD_T,
                                                     const DTD_T) const;

    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDBookingSnapshotView (const SegmentDataID_T,
                                           const SegmentDataID_T, const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangeBookingSnapshotView (const SegmentDataID_T,
                                                const SegmentDataID_T,
                                                const DTD_T, const DTD_T);

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDCancellationSnapshotView (const SegmentDataID_T,
                                                const SegmentDataID_T,
                                                const DTD_T) const;

    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangeCancellationSnapshotView (const SegmentDataID_T,
                                                          const SegmentDataID_T,
                                                          const DTD_T,
                                                          const DTD_T) const;

    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDCancellationSnapshotView (const SegmentDataID_T,
                                                const SegmentDataID_T,
                                                const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangeCancellationSnapshotView (const SegmentDataID_T,
                                                     const SegmentDataID_T,
                                                     const DTD_T, const DTD_T);

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDProductOrientedNetBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T) const;

    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangeProductOrientedNetBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T, const DTD_T) const;

    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDProductOrientedNetBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangeProductOrientedNetBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T, const DTD_T);

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDPriceOrientedNetBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T) const;

    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangePriceOrientedNetBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T, const DTD_T) const;

    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDPriceOrientedNetBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangePriceOrientedNetBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T, const DTD_T);
    

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDProductOrientedGrossBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T) const;

    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangeProductOrientedGrossBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T, const DTD_T) const;

    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDProductOrientedGrossBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangeProductOrientedGrossBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T, const DTD_T);

    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDPriceOrientedGrossBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T) const;

    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangePriceOrientedGrossBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T, const DTD_T) const;

    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDPriceOrientedGrossBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangePriceOrientedGrossBookingSnapshotView
    (const SegmentDataID_T, const SegmentDataID_T, const DTD_T, const DTD_T);


    /** Get the const view of snapshots for a given DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDSnapshotView_T
    getConstSegmentCabinDTDAvailabilitySnapshotView (const SegmentDataID_T,
                                                     const SegmentDataID_T,
                                                     const DTD_T) const;
    
    /** Get the const view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    ConstSegmentCabinDTDRangeSnapshotView_T
    getConstSegmentCabinDTDRangeAvailabilitySnapshotView (const SegmentDataID_T,
                                                          const SegmentDataID_T,
                                                          const DTD_T,
                                                          const DTD_T) const;
    
    /** Get the view of snapshots for a given DTD and a range of
        segment-cabins. */
    SegmentCabinDTDSnapshotView_T
    getSegmentCabinDTDAvailabilitySnapshotView (const SegmentDataID_T,
                                                const SegmentDataID_T,
                                                const DTD_T);

    /** Get the view of snapshots for a given range of DTD and a range of
        segment-cabins. */
    SegmentCabinDTDRangeSnapshotView_T
    getSegmentCabinDTDRangeAvailabilitySnapshotView (const SegmentDataID_T,
                                                     const SegmentDataID_T,
                                                     const DTD_T, const DTD_T);


  public:
    // //////////// Setters /////////////
    /** Set the segment-cabin and value type index maps and initialise
        the snapshot blocks. */
    void initSnapshotBlocks (const SegmentCabinIndexMap_T&,
                             const ClassIndexMap_T&);
    
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
     * Serialisation helpers (allows to be sure the template method is
     * instantiated).
     */
    void serialisationImplementationExport() const;
    void serialisationImplementationImport();


  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    SegmentSnapshotTable (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~SegmentSnapshotTable();

  private:
    /**
     * Default constructor.
     */
    SegmentSnapshotTable();

    /**
     * Copy constructor.
     */
    SegmentSnapshotTable (const SegmentSnapshotTable&);
    

  protected:
    // ////////// Attributes /////////
    /** Primary key (table ID and departure block). */
    Key_T _key;

    /** Pointer on the parent class (Inventory). */
    BomAbstract* _parent;

    /** Map holding the children. */
    HolderMap_T _holderMap;

    /** Map holding the segment-cabin position within the snapshot blocks. */
    SegmentCabinIndexMap_T _segmentCabinIndexMap;

    /** Map holding the value type (class, etc) within a
        a segment-cabin inside the snapshot blocks. */
    ClassIndexMap_T _classIndexMap;

    /** Booking snapshot block. */
    SnapshotBlock_T _bookingSnapshotBlock;

    /** Cancellation snapshot block. */
    SnapshotBlock_T _cancellationSnapshotBlock;

    /** Product oriented net booking block. */
    SnapshotBlock_T _productOrientedNetBookingSnapshotBlock;

    /** Price oriented net booking block. */
    SnapshotBlock_T _priceOrientedNetBookingSnapshotBlock;

    /** Product oriented gross booking block. */
    SnapshotBlock_T _productOrientedGrossBookingSnapshotBlock;

    /** Price oriented gross booking block. */
    SnapshotBlock_T _priceOrientedGrossBookingSnapshotBlock;

    /** Availability block. */
    SnapshotBlock_T _availabilitySnapshotBlock;
  };

}
#endif // __STDAIR_BOM_SEGMENTSNAPSHOTTABLE_HPP

