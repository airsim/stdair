#ifndef __STDAIR_BOM_SEGMENTDATE_HPP
#define __STDAIR_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/SegmentDateKey.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /// Forward declarations
  struct SegmentCabinKey;
  class SegmentCabin;

  /**
   * @brief Class representing the actual attributes for an airline
   * segment-date.
   */
  class SegmentDate : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;
    
  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef SegmentDateKey Key_T;


  public:
    // /////////// Getters /////////////
    /** Get the segment-date key. */
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

    /** Get the off point (part of the primary key). */
    const AirportCode_T& getOffPoint() const {
      return _key.getOffPoint();
    }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
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

    /** Get the date offset (off date - boarding date). */
    const DateOffset_T getDateOffset() const {
      return _offDate - _boardingDate;
    }

    /**
     * Get the time offset between boarding and off points.
     *
     * It is defined as being:
     *
     * TimeOffset = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
     *              - ElapsedTime.
     */
    const Duration_T getTimeOffset() const;
    
    /**
     * Get a pointer on the SegmentCabin object corresponding to the
     * given key.
     *
     * \note The SegmentCabin object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const std::string& The flight-date key.
     * @return SegmentCabin* Found SegmentCabin object. NULL if not found.
     */
    SegmentCabin* getSegmentCabin (const std::string& iSegmentCabinKeyStr) const;

    /**
     * Get a pointer on the SegmentCabin object corresponding to the
     * given key.
     *
     * \note The SegmentCabin object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const SegmentCabinKey& The flight-date key
     * @return SegmentCabin* Found SegmentCabin object. NULL if not found.
     */
    SegmentCabin* getSegmentCabin (const SegmentCabinKey&) const;

    /**
     * Get the "operating" segment date.
     */
    SegmentDate* getOperatingSegmentDate () const {
      return _operatingSegmentDate;
    }

    /**
     * Check if an other airline is operating.
     */
    bool isOtherAirlineOperating () const {
      return _isOtherAirlineOperating;
    }

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
    void setOffDate (const Date_T& iOffDate) {
      _offDate = iOffDate;
    }

    /** Set the off time. */
    void setOffTime (const Duration_T& iOffTime) {
      _offTime = iOffTime;
    }

    /** Set the elapsed time. */
    void setElapsedTime (const Duration_T& iElapsedTime) {
      _elapsedTime = iElapsedTime;
    }

    /** Set the distance. */
    void setDistance (const Distance_T& iDistance) {
      _distance = iDistance;
    }

    /** Set operating segment date. */
    void linkWithOperating (SegmentDate& iSegmentDate) {
      _operatingSegmentDate = &iSegmentDate;
      _isOtherAirlineOperating = true;
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
    SegmentDate (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~SegmentDate();

  private:
    /**
     * Default constructor.
     */
    SegmentDate();

    /**
     * Default copy constructor.
     */
    SegmentDate (const SegmentDate&);


  protected:
    // ////////// Attributes /////////
    /**
     * Primary key (origin and destination).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (FlightDate).
     */
    BomAbstract* _parent;

    /**
     * Pointer on the operating SegmentDate.
     * Nota:
     * 1. "operating" refers to the codeshare contract seller.
     * 2. the segment date it points to can be a "marketing" segment as well.
     * 3. the pointer will be NULL if the segment date is itself the "operating" one.
     */
    SegmentDate* _operatingSegmentDate;

    /**
     * Flag saying if the "operating" segment is a different one.
     */
    bool _isOtherAirlineOperating;
    
    /**
     * Map holding the children (SegmentCabin objects).
     */
    HolderMap_T _holderMap;

    /**
     * Boarding date.
     */
    Date_T _boardingDate;

    /**
     * Boarding time.
     */
    Duration_T _boardingTime;

    /**
     * Landing date.
     */
    Date_T _offDate;

    /**
     * Landing time.
     */
    Duration_T _offTime;

    /**
     * Trip elapsed time.
     */
    Duration_T _elapsedTime;

    /**
     * Trip distance.
     */
    Distance_T _distance;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATE_HPP

