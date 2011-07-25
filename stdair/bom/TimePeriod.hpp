#ifndef __STDAIR_BOM_FARETIMEPERIOD_HPP
#define __STDAIR_BOM_FARETIMEPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/TimePeriodKey.hpp>
#include <stdair/bom/TimePeriodTypes.hpp>

// Forward declaration
namespace stdair {

  /** Class representing the actual attributes for a fare time-period. */
  class TimePeriod : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef TimePeriodKey Key_T;
  
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
    const Time_T& getTimeRangeStart() const {
      return _key.getTimeRangeStart();
    }
    const Time_T& getTimeRangeEnd() const {
      return _key.getTimeRangeEnd();
    }
    BomAbstract* const getParent() const { return _parent; }
    const HolderMap_T& getHolderMap() const { return _holderMap; }

  public:
    // ////////////// Business methods ///////////////
    /** Check if the given departure time is included in the departure period
        of the segment path. */
    bool isDepartureTimeValid (const Time_T&) const;
    
  protected:
    /** Default constructors. */
    TimePeriod (const Key_T&);
    TimePeriod (const TimePeriod&);
    /** Destructor. */
    virtual ~TimePeriod();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_FARETIMEPERIOD_HPP

