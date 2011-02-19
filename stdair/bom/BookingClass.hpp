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
      return _cumulatedProtection;
    }

    /** Get the protection. */
    const AuthorizationLevel_T& getProtection() const {
      return _protection;
    }

    /** Get the negotiated space. */
    const NbOfSeats_T& getNegotiatedSpace() const {
      return _nego;
    }

    /** Get the overbooking rate. */
    const OverbookingRate_T& getNoShowPercentage() const {
      return _noShowPercentage;
    }

    /** Get the overbooking percentage. */
    const OverbookingRate_T& getOverbookingPercentage() const {
      return _overbookingPercentage;
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
    // ////////////// Business Methodes /////////////////
    /** Register a sale. */
    void sell (const NbOfBookings_T&);


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


  public:
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
    AuthorizationLevel_T _cumulatedProtection;

    /** Protection. */
    AuthorizationLevel_T _protection;

    /** Negotiated space. */
    NbOfSeats_T _nego;

    /** Overbooking rate. */
    OverbookingRate_T _noShowPercentage;

    /** Overbooking percentage. */
    OverbookingRate_T _overbookingPercentage;

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

    /** Expected to board (ETB). */
    NbOfBookings_T _etb;

    /** Net segment class availability. */
    Availability_T _netClassAvailability;

    /** Segment class availability. */
    Availability_T _segmentAvailability;

    /** Net revenue availability. */
    Availability_T _netRevenueAvailability;
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASS_HPP

