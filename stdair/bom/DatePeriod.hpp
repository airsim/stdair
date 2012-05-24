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

  /**
   * @brief Class representing the actual attributes for a fare date-period.
   */
  class DatePeriod : public BomAbstract {
    template <typename BOM> friend class FacBom; 
    template <typename BOM> friend class FacCloneBom;
    friend class FacBomManager;

  public:
    // //////////// Type definitions //////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef DatePeriodKey Key_T;
  
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
     * Get the primary key (date period).
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
    const  HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
    /**
     * Get the date period.
     */
    const DatePeriod_T& getDatePeriod() const {
      return _key.getDatePeriod();
    }


  public:
    // ////////////// Business methods ///////////////
    /**
     * Check if the given departure date is included in the departure
     * period of the segment path.
     */
    bool isDepartureDateValid (const Date_T&) const;
    
  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    DatePeriod (const Key_T&);
    /**
     * Destructor.
     */
    virtual ~DatePeriod ();

  private:
    /**
     * Default constructor.
     */
    DatePeriod ();
    /**
     * Copy constructor.
     */
    DatePeriod (const DatePeriod&);

  protected:
    // ///////////// Attributes /////////////
    /**
     * Primary key (date period).
     */
    Key_T _key;

    /**
     * Pointer on the parent class.
     */
    BomAbstract* _parent;

    /**
     * Map holding the children.
     */
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_DATEPERIOD_HPP

