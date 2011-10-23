#ifndef __STDAIR_BOM_LEGDATE_HPP
#define __STDAIR_BOM_LEGDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir 
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/LegDateKey.hpp>
#include <stdair/bom/LegDateTypes.hpp>

namespace stdair {

  /**
   * Class representing the actual attributes for an airline leg-date.
   */
  class LegDate : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // ////////// Type definitions ////////////
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef LegDateKey Key_T;


  public:
    // /////////// Getters /////////////
    /** Get the leg-date key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /** Get the boarding point (part of the primary key). */
    const AirportCode_T& getBoardingPoint() const {
      return _key.getBoardingPoint();
    }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /** Get the off point. */
    const AirportCode_T& getOffPoint() const {
      return _offPoint;
    }

    /** Get the boarding date. */
    const Date_T& getBoardingDate() const {
      return _boardingDate;
    }

    /** Get the boarding time. */
    const Duration_T& getBoardingTime() const {
      return _boardingTime;
    }

    /** Get the off date. */
    const Date_T& getOffDate() const {
      return _offDate;
    }

    /** Get the off time. */
    const Duration_T& getOffTime() const {
      return _offTime;
    }

    /** Get the elapsed time. */
    const Duration_T& getElapsedTime() const {
      return _elapsedTime;
    }

    /** Get the distance. */
    const Distance_T& getDistance() const {
      return _distance;
    }

    /** Get the leg capacity. */
    const CabinCapacity_T& getCapacity() const {
      return _capacity;
    }

    /** Get the date offset (off date - boarding date). */
    const DateOffset_T getDateOffset() const {
      return _offDate - _boardingDate;
    }

    /** Get the time off set between boarding and off points.
        <br>It is defined as being:
        TimeOffset = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
        - ElapsedTime. */
    const Duration_T getTimeOffset() const;


  public:
    // ///////// Setters //////////
    /** Set the off point. */
    void setOffPoint (const AirportCode_T& iOffPoint) {
      _offPoint = iOffPoint;
    }

    /** Set the boarding date. */
    void setBoardingDate (const Date_T& iBoardingDate) {
      _boardingDate = iBoardingDate;
    }

    /** Set the boarding time. */
    void setBoardingTime (const Duration_T& iBoardingTime) {
      _boardingTime = iBoardingTime;
    }

    /** Set the off date. */
    void setOffDate (const Date_T& iOffDate) {
      _offDate = iOffDate;
    }

    /** Set the off time. */
    void setOffTime (const Duration_T& iOffTime) {
      _offTime = iOffTime;
    }

    /** Set the elapsed time. */
    void setElapsedTime (const Duration_T&);

  private:
    /** Method computing the distance of the segment (in kilometers). */
    void updateDistanceFromElapsedTime();
    

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << toString();
    }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) {
    }

    /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the  key. */
    const std::string describeKey() const {
      return _key.toString();
    }


  protected:
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    LegDate (const Key_T&);
    /** Destructor. */
    virtual ~LegDate();

  private:
    /** Default constructor. */
    LegDate();
    /** Constructor. */
    LegDate (const LegDate&);


  protected:
    // ////////// Attributes /////////
    /** Primary key (origin airport). */
    Key_T _key;

    /** Pointer on the parent class (FlightDate). */
    BomAbstract* _parent;

    /** Map holding the children (LegCabin objects). */
    HolderMap_T _holderMap;

    /** Landing airport. */
    AirportCode_T _offPoint;

    /** Boarding date. */
    Date_T _boardingDate;

    /** Boarding time. */
    Duration_T _boardingTime;

    /** Landing date. */
    Date_T _offDate;

    /** Landing time. */
    Duration_T _offTime;

    /** Trip elapsed time. */
    Duration_T _elapsedTime;

    /** Trip distance. */
    Distance_T _distance;

    /** Aggregated capacity for all the leg-cabins. */
    CabinCapacity_T _capacity;
  };

}
#endif // __STDAIR_BOM_LEGDATE_HPP

