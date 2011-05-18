#ifndef __STDAIR_BOM_FAREFEATURES_HPP
#define __STDAIR_BOM_FAREFEATURES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/FareFeaturesKey.hpp>
#include <stdair/bom/FareFeaturesTypes.hpp>

// Forward declaration
namespace stdair {

  /** Class representing the actual attributes for a fare date-period. */
  class FareFeatures : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FareFeaturesKey Key_T;
  
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

  public:
    // ////////// Getters ////////////
    const Key_T& getKey() const { return _key; }
    stdair::BomAbstract* const getParent() const { return _parent; }
    const  stdair::HolderMap_T& getHolderMap() const { return _holderMap; }

    /** Get the fare day duration. */
    const stdair::DayDuration_T& getAdvancePurchase() const {
      return _key.getAdvancePurchase();
    }

    /** Get the fare saturday stay option. */
    const stdair::SaturdayStay_T& getSaturdayStay() const {
      return _key.getSaturdayStay();
    }   

    /** Get the change fees criterion. */
    const stdair::ChangeFees_T& getChangeFees() const {
      return _key.getChangeFees();
    }

    /** Get the refundable option. */
    const stdair::NonRefundable_T& getRefundableOption() const {
      return _key.getRefundableOption();
    }

    /** Get the minimum stay. */
    const stdair::DayDuration_T& getMinimumStay() const {
      return _key.getMinimumStay();
    }

  public:
    // ////////////// Business methods ///////////////
    /** Check if a given stay duration is greater or equal to
        the minimum stay of the fare rule. */
    bool IsStayDurationValid (const DayDuration_T&) const;

    /** Check if a booking request date is valid compared the required
        advance purchase number of days of the fare rule. */
    bool IsAdvancePurchaseValid (const DateTime_T&,
                                 const DateTime_T&) const;
    
  protected:
    /** Default constructors. */
    FareFeatures (const Key_T&);
    FareFeatures (const FareFeatures&);
    /** Destructor. */
    ~FareFeatures();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_FAREFEATURES_HPP

