#ifndef __STDAIR_BOM_BUCKETCONTENT_HPP
#define __STDAIR_BOM_BUCKETCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BucketKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline booking class. */
  class BucketContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BucketKey_T Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the booking class key. */
    const Key_T& getKey() const {
      return _key;
    }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

    
  protected:
    /** Default constructors. */
    BucketContent (const Key_T&);
    BucketContent (const BucketContent&);
    /** Destructor. */
    ~BucketContent();

  public:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;
    // test AIRINV
    stdair::Yield_T _yieldRangeUpperValue;
    stdair::CabinCapacity_T _availability;
    stdair::NbOfSeats_T _nbOfSeats;
    stdair::SeatIndex_T _seatIndex;

  };

}
#endif // __STDAIR_BOM_BUCKETCONTENT_HPP
