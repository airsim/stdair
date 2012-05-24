#ifndef __STDAIR_BOM_BUCKET_HPP
#define __STDAIR_BOM_BUCKET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir 
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BucketKey.hpp>
#include <stdair/bom/BucketTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /**
   * @brief Class representing the actual attributes for an airline
   * booking class.
   */
  class Bucket : public BomAbstract {
    template <typename BOM> friend class FacBom;    
    template <typename BOM> friend class FacCloneBom;
    friend class FacBomManager;
    friend class boost::serialization::access;
    
  public:
    // //////////////// Type definitions //////////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef BucketKey Key_T;

  public:
    // /////////// Getters ////////////
    /**
     * Get the primary key of the bucket.
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

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /** Get the seat index (part of the primary key). */
    const SeatIndex_T& getSeatIndex() const {
      return _key.getSeatIndex();
    }

    /** Get the upper yield range. */
    const Yield_T& getYieldRangeUpperValue() const {
      return _yieldRangeUpperValue;
    }

    /** Get the availability. */
    const CabinCapacity_T& getAvailability() const {
      return _availability;
    }

    /** Get the number of seats already sold. */
    const NbOfSeats_T& getSoldSeats() const {
      return _soldSeats;
    }


    // /////////// Setters ////////////
    /** Set the upper yield range. */
    void setYieldRangeUpperValue (const Yield_T& iYield) {
      _yieldRangeUpperValue = iYield;
    }

    /** Set the availability. */
    void setAvailability (const CabinCapacity_T& iAvl) {
      _availability = iAvl;
    }

    /** Set the number of seats already sold. */
    void setSoldSeats (const NbOfSeats_T& iSoldSeats) {
      _soldSeats = iSoldSeats;
    }


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
     * Get a string describing the key.
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
     * Default constructor.
     */
    Bucket (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~Bucket();

  private:
    /**
     * Default constructor.
     */
    Bucket();

    /**
     * Copy constructor.
     */
    Bucket (const Bucket&);


  protected:
    // //////////////////// Children ///////////////////
    /**
     * Primary key (upper yield range).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (LegCabin).
     */
    BomAbstract* _parent;

    /**
     * Map holding the children (empty for now).
     */
    HolderMap_T _holderMap;


  protected:
    // //////////////////// Attributes ///////////////////
    /**
     * Upper yield range.
     */
    Yield_T _yieldRangeUpperValue;

    /**
     * Availability.
     */
    CabinCapacity_T _availability;

    /**
     * Number of seats already sold.
     */
    NbOfSeats_T _soldSeats;
  };

}
#endif // __STDAIR_BOM_BUCKET_HPP

