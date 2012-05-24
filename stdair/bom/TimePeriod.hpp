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

  /**
   * @brief Class representing the actual attributes for a fare time-period.
   */
  class TimePeriod : public BomAbstract {
    template <typename BOM> friend class FacBom;  
    template <typename BOM> friend class FacCloneBom;
    friend class FacBomManager;

  public:
    // //////////// Type definitions //////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef TimePeriodKey Key_T;
  
  public:
    // /////////// Display support methods /////////
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
     * Get a string describing the key.
     */
    const std::string describeKey() const {
      return _key.toString();
    }

  public:
    // ////////// Getters ////////////
    /**
     * Get the primary key (time range start, time range end).
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
     * Get the time range start.
     */
    const Time_T& getTimeRangeStart() const {
      return _key.getTimeRangeStart();
    }
    
    /**
     * Get the time range end
     */
    const Time_T& getTimeRangeEnd() const {
      return _key.getTimeRangeEnd();
    }

  public:
    // ////////////// Business methods ///////////////
    /**
     * Check if the given departure time is included in the departure
     * period of the segment path.
     */
    bool isDepartureTimeValid (const Time_T&) const;

  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    TimePeriod (const Key_T&);  
    /**
     * Destructor.
     */
    virtual ~TimePeriod();

  private:
    /**
     * Default constructor.
     */
    TimePeriod(); 
    /**
     * Copy constructor.
     */
    TimePeriod (const TimePeriod&);

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
     * Map holding the children.
     */
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_FARETIMEPERIOD_HPP

