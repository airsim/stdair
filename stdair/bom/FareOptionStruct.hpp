#ifndef __STDAIR_BOM_FAREOPTIONSTRUCT_HPP
#define __STDAIR_BOM_FAREOPTIONSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {

  /**
   * @brief Structure holding the elements of a fare option.
   */
  struct FareOptionStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get the class-path. */
    const ClassList_StringList_T& getClassPath() const {
      return _classPath;
    }

    /** Get the fare value. */
    const Fare_T& getFare() const {
      return _fare;
    }

    /** Get the availability. */
    const Availability_T& getAvailability() const {
      return _avl;
    }
    
    /** Get the change fees. */
    const ChangeFees_T getChangeFees() const {
      return _changeFee;
    }

    /** State whether the ticket is refundable. */
    const NonRefundable_T getNonRefundable() const {
      return _nonRefundable;
    }

    /** State whether there is a condition on the saturday night stay. */
    const SaturdayStay_T getSaturdayStay() const {
      return _saturdayStay;
    }


  public:
    // /////////// Setters ///////////////
    /** Set the class-path. */
    void addClassList (const std::string);

    /** Set the fare value. */
    void setFare (const Fare_T& iFare) {
      _fare = iFare;
    }

    /** Set the availability. */
    void setAvailability (const Availability_T& iAvl) {
      _avl = iAvl;
    }

    /** Set the change fees. */
    void setChangeFees (const ChangeFees_T iRes) {
      _changeFee = iRes;
    }

    /** Set the flag for the ticket refundability. */
    void setNonRefundable (const NonRefundable_T iRes) {
      _nonRefundable = iRes;
    }

    /** Set the flag for the saturday night stay condition. */
    void setSaturdayStay (const SaturdayStay_T iRes) {
      _saturdayStay = iRes;
    }
        

  public:
    // /////////// Display support method /////////////
    /**
     * Dump a Business Object into an output stream.
     *
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;

    /**
     * Read a Business Object from an input stream.
     *
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn);

    /**
     * Display of the structure.
     */
    const std::string describe() const;
  
    /**
     * Display of the structure.
     */
    const std::string display() const;
  

  public:
    // //////////// Constructors & Destructor ///////////////
    /**
     * Default constructor.
     */
    FareOptionStruct();

    /**
     * Main constructor.
     */
    FareOptionStruct (const std::string& iClassPath,
                      const Fare_T&, const ChangeFees_T&,
                      const NonRefundable_T&, const SaturdayStay_T&);

    /**
     * Destructor.
     */
    ~FareOptionStruct();
    

  private:
    // ///////////////////// Attributes //////////////////////
    /**
     * The class path.
     */
    ClassList_StringList_T _classPath;

    /**
     * Fare.
     */
    Fare_T _fare;

    /**
     * Avalability.
     */
    Availability_T _avl;

    /**
     * Change fees.
     */
    ChangeFees_T _changeFee;

    /**
     * State whether the ticket is refundable.
     */
    NonRefundable_T _nonRefundable;

    /**
     * State whether there is a condition on the saturday night stay.
     */
    SaturdayStay_T _saturdayStay;
  };

}
#endif // __STDAIR_BOM_FAREOPTIONSTRUCT_HPP
