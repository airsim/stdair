#ifndef __STDAIR_BOM_FAREFEATURES_HPP
#define __STDAIR_BOM_FAREFEATURES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/FareFeaturesKey.hpp>
#include <stdair/bom/FareFeaturesTypes.hpp>

// Forward declaration
namespace stdair {

  /**
   * @brief Class representing the actual attributes for a fare date-period.
   */
  class FareFeatures : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // //////////// Type definitions //////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef FareFeaturesKey Key_T;
  
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
    // ////////// Getters ////////////
    /**
     * Get the primary key (trip type, cabin code).
     */
    const Key_T& getKey() const {
      return _key;
    }

    /**
     * Get a reference on the parent object instance.
     */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /**
     * Get a reference on the children holder.
     */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /**
     * Get the trip type.
     */
    const TripType_T& getTripType() const {
      return _key.getTripType();
    }

    /**
     * Get the fare day duration.
     */
    const DayDuration_T& getAdvancePurchase() const {
      return _key.getAdvancePurchase();
    }

    /**
     * Get the fare saturday stay option.
     */
    const SaturdayStay_T& getSaturdayStay() const {
      return _key.getSaturdayStay();
    }   

    /**
     * Get the change fees criterion.
     */
    const ChangeFees_T& getChangeFees() const {
      return _key.getChangeFees();
    }

    /**
     * Get the refundable option.
     */
    const NonRefundable_T& getRefundableOption() const {
      return _key.getRefundableOption();
    }

    /**
     * Get the minimum stay.
     */
    const DayDuration_T& getMinimumStay() const {
      return _key.getMinimumStay();
    }


  public:
    // ////////////// Business methods ///////////////
    /**
     * Check whether the fare rule trip type corresponds to the booking
     * request trip type.
     */
    bool isTripTypeValid (const TripType_T&) const;
    
    /**
     * Check whether a given stay duration is greater or equal to
     * the minimum stay of the fare rule.
     */
    bool isStayDurationValid (const DayDuration_T&) const;

    /**
     * Check whether a booking request date is valid compared the required
     * advance purchase number of days of the fare rule.
     */
    bool isAdvancePurchaseValid (const DateTime_T& iBookingRequestDateTime,
                                 const DateTime_T& iFlightDateTime) const;
    

  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    FareFeatures (const Key_T&);
    /**
     * Destructor.
     */
    virtual ~FareFeatures();

  private:
    /**
     * Default constructor.
     */
    FareFeatures();
    /**
     * Copy constructor.
     */
    FareFeatures (const FareFeatures&);


  protected:
    // ///////////// Attributes /////////////
    /**
     * Primary key (flight number and departure date).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (Inventory).
     */
    BomAbstract* _parent;

    /**
     * Map holding the children (SegmentDate and LegDate objects).
     */
    HolderMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_FAREFEATURES_HPP

