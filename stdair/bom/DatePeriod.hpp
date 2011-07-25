#ifndef __STDAIR_BOM_DATEPERIOD_HPP
#define __STDAIR_BOM_DATEPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/DatePeriodKey.hpp>
#include <stdair/bom/DatePeriodTypes.hpp>

// Forward declaration
namespace stdair {

  /** Class representing the actual attributes for a fare date-period. */
  class DatePeriod : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef DatePeriodKey Key_T;
  
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
    const DatePeriod_T& getDatePeriod() const {
      return _key.getDatePeriod();
    }
    BomAbstract* const getParent() const { return _parent; }
    const  HolderMap_T& getHolderMap() const { return _holderMap; }

  public:
    // ////////////// Business methods ///////////////
    /** Check if the given departure date is included in the departure period
        of the segment path. */
    bool isDepartureDateValid (const Date_T&) const;
    
  protected:
    /** Default constructors. */
    DatePeriod (const Key_T&);
    DatePeriod (const DatePeriod&);
    /** Destructor. */
    virtual ~DatePeriod();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_DATEPERIOD_HPP

