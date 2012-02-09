#ifndef __STDAIR_BOM_BOOKINGCLASS_HPP
#define __STDAIR_BOM_BOOKINGCLASS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_rm_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BookingClassKey.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {

  /**
   * Class representing the actual attributes for an airline booking
   * class.
   */
  class BookingClass : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // ////////// Type definitions ////////////
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BookingClassKey Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the booking class key. */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the booking code (part of the primary key). */
    const ClassCode_T& getClassCode() const {
      return _key.getClassCode();
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /** Get teh sub-class code. */
    const SubclassCode_T& getSubclassCode() const {
      return _subclassCode;
    }

    /** Get the authorisation level (AU, i.e., cumulated protection). */
    const AuthorizationLevel_T& getAuthorizationLevel() const {
      return _au;
    }

    /** Get the protection. */
    const ProtectionLevel_T& getProtection() const {
      return _protection;
    }

    /** Get the cumulated protection. */
    const ProtectionLevel_T& getCumulatedProtection() const {
      return _cumulatedProtection;
    }

    /** Get the cumulated booking limit. */
    const BookingLimit_T& getCumulatedBookingLimit() const {
      return _cumulatedBookingLimit;
    }

    /** Get the negotiated space. */
    const NbOfSeats_T& getNegotiatedSpace() const {
      return _nego;
    }

    /** Get the no-show rate. */
    const OverbookingRate_T& getNoShowPercentage() const {
      return _noShowPercentage;
    }

    /** Get the cancellation rate. */
    const OverbookingRate_T& getCancellationPercentage() const {
      return _cancellationPercentage;
    }

    /** Get the number of bookings. */
    const NbOfBookings_T& getNbOfBookings() const {
      return _nbOfBookings;
    }

    /** Get the number of group bookings. */
    const NbOfBookings_T& getNbOfGroupBookings() const {
      return _groupNbOfBookings;
    }

    /** Get the number of pending group bookings. */
    const NbOfBookings_T& getNbOfPendingGroupBookings() const {
      return _groupPendingNbOfBookings;
    }

    /** Get the number of staff bookings. */
    const NbOfBookings_T& getNbOfStaffBookings() const {
      return _staffNbOfBookings;
    }

    /** Get the number of wait-list bookings. */
    const NbOfBookings_T& getNbOfWLBookings() const {
      return _wlNbOfBookings;
    }

    /** Get the number of cancellations. */
    const NbOfCancellations_T& getNbOfCancellations() const {
      return _nbOfCancellations;
    }

    /** Get the expected number of passengers to board (ETB). */
    const NbOfBookings_T& getETB() const {
      return _etb;
    }

    /** Get the net segment class availability. */
    const Availability_T& getNetClassAvailability() const {
      return _netClassAvailability;
    }

    /** Get the segment class availability. */
    const Availability_T& getSegmentAvailability() const {
      return _segmentAvailability;
    }

    /** Net revenue availability. */
    const Availability_T& getNetRevenueAvailability() const {
      return _netRevenueAvailability;
    }

    /** Yield. */
    const Yield_T& getYield () const { return _yield; }
    
    /** Demand distribution. */
    const MeanValue_T& getMean () const { return _mean; }
    const StdDevValue_T& getStdDev () const {return _stdDev; }

    /** Generated demand vector. */
    const GeneratedDemandVector_T& getGeneratedDemandVector () const {
      return _generatedDemandVector;
    }
  
  public:
    // /////////// Setters ////////////
    /** Cumulated protection. */
    void setCumulatedProtection (const ProtectionLevel_T& iPL) {
      _cumulatedProtection = iPL;
    }

    /** Protection. */
    void setProtection (const ProtectionLevel_T& iPL) {
      _protection = iPL;
    }
    
    /** Cumulated booking limit. */
    void setCumulatedBookingLimit (const BookingLimit_T& iBL) {
      _cumulatedBookingLimit = iBL;
    }

    /** Authorization level. */
    void setAuthorizationLevel (const AuthorizationLevel_T& iAU) {
      _au = iAU;
    }

    /** Set availability. */
    void setSegmentAvailability (const Availability_T& iAvl) {
      _segmentAvailability = iAvl;
    }

    /** Yield. */
    void setYield (const Yield_T& iYield) { _yield = iYield; }
    
    /** Demand distribution. */
    void setMean (const MeanValue_T& iMean) { _mean = iMean; }
    void setStdDev (const StdDevValue_T& iStdDev) { _stdDev = iStdDev; }

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

  public:
    // ////////////// Business Methods /////////////////
    /** Register a sale. */
    void sell (const NbOfBookings_T&);
    
    /** Register a cancellation. */
    void cancel (const NbOfBookings_T&);

    /** Generate demand samples for Monte-Carlo method with the default
        random seed. */
    void generateDemandSamples (const int&);

    /** Generate demand samples for Monte-Carlo method with the given
        random seed. */
    void generateDemandSamples (const int&, const RandomSeed_T&);

  protected:
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    BookingClass (const Key_T&);
    /** Destructor. */
    virtual ~BookingClass();

  private:
    /** Default constructor. */
    BookingClass();
    /** Default copy constructor. */
    BookingClass (const BookingClass&);


  protected:
    // ////////// Attributes /////////
    /** Primary key (booking class code). */
    Key_T _key;

    /** Pointer on the parent class (SegmentCabin). */
    BomAbstract* _parent;

    /** Map holding the children (SegmentDate and LegDate objects). */
    HolderMap_T _holderMap;

    /** Sub-class code. */
    SubclassCode_T _subclassCode;

    /** Cumulated protection. */
    ProtectionLevel_T _cumulatedProtection;

    /** Protection. */
    ProtectionLevel_T _protection;

    /** Cumulated booking limit. */
    BookingLimit_T _cumulatedBookingLimit;

    /** Authorization level. */
    AuthorizationLevel_T _au;

    /** Negotiated space. */
    NbOfSeats_T _nego;

    /** Overbooking rate. */
    OverbookingRate_T _noShowPercentage;

    /** Cancellation rate. */
    OverbookingRate_T _cancellationPercentage;

    /** Number of bookings. */
    NbOfBookings_T _nbOfBookings;

    /** Number of group bookings. */
    NbOfBookings_T _groupNbOfBookings;

    /** Number of pending group bookings. */
    NbOfBookings_T _groupPendingNbOfBookings;

    /** Number of staff bookings. */
    NbOfBookings_T _staffNbOfBookings;

    /** Number of wait-list bookings. */
    NbOfBookings_T _wlNbOfBookings;

    /** Number of cancellations. */
    NbOfCancellations_T _nbOfCancellations;

    /** Expected to board (ETB). */
    NbOfBookings_T _etb;

    /** Net segment class availability. */
    Availability_T _netClassAvailability;

    /** Segment class availability. */
    Availability_T _segmentAvailability;

    /** Net revenue availability. */
    Availability_T _netRevenueAvailability;

    /** Yield. */
    Yield_T _yield;

    /** Achievable demand distribution forecast. */
    MeanValue_T _mean;
    StdDevValue_T _stdDev;

    /** Vector of number of demand samples drawn from the demand distribution.*/
    GeneratedDemandVector_T _generatedDemandVector;
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASS_HPP
