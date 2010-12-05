#ifndef __STDAIR_BOM_SEGMENTDATE_HPP
#define __STDAIR_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline segment-date. */
  class SegmentDate : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentDateKey Key_T;

  public:
    // /////////// Getters /////////////
    /** Get the segment-date key. */
    const Key_T& getKey() const { return _key; }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }
    
    /** Get the boarding point (part of the primary key). */
    const AirportCode_T& getBoardingPoint () const {
      return _key.getBoardingPoint();
    }

    /** Get the off point (part of the primary key). */
    const AirportCode_T& getOffPoint () const { return _key.getOffPoint(); }

    /** Get the boarding date. */
    const Date_T& getBoardingDate () const { return _boardingDate; }

    /** Get the boarding time. */
    const Duration_T& getBoardingTime () const { return _boardingTime; }

    /** Get the off date. */
    const Date_T& getOffDate () const {return _offDate; }

    /** Get the off time. */
    const Duration_T& getOffTime () const { return _offTime; }

    /** Get the elapsed time. */
    const Duration_T& getElapsedTime() const { return _elapsedTime; }

    /** Get the distance. */
    const Distance_T& getDistance() const { return _distance; }

    /** Get the date offset (off date - boarding date). */
    const DateOffset_T getDateOffset () const { return _offDate - _boardingDate;}

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const { return _holderMap; }

    /** Get the time offset between boarding and off points.
        <br>It is defined as being:
        TimeOffset = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
        - ElapsedTime. */
    const Duration_T getTimeOffset() const;
    
  public:
    // ///////// Setters //////////
    /** Set the boarding date. */
    void setBoardingDate (const Date_T& iBoardingDate) {
      _boardingDate = iBoardingDate;
    }

    /** Set the boarding time. */
    void setBoardingTime (const Duration_T& iBoardingTime) {
      _boardingTime = iBoardingTime;
    }

    /** Set the off date. */
    void setOffDate (const Date_T& iOffDate) { _offDate = iOffDate; }

    /** Set the off time. */
    void setOffTime (const Duration_T& iOffTime) { _offTime = iOffTime; }

    /** Set the elapsed time. */
    void setElapsedTime (const Duration_T& iElapsedTime) {
      _elapsedTime = iElapsedTime;
    }

    /** Set the distance. */
    void setDistance (const Distance_T& iDistance) { _distance = iDistance; }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return _key.toString(); }

    
  protected:
    /** Default constructors. */
    SegmentDate (const Key_T&);
    SegmentDate (const SegmentDate&);
    /** Destructor. */
    ~SegmentDate();

  protected:
    // Attributes
    /** The key of both structure and  objects. */
    Key_T _key;
    BomAbstract* _parent;
    Date_T _boardingDate;
    Duration_T _boardingTime;
    Date_T _offDate;
    Duration_T _offTime;
    Duration_T _elapsedTime;
    Distance_T _distance;
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_SEGMENTDATE_HPP
