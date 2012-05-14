#ifndef __STDAIR_BOM_POLICYSTRUCT_HPP
#define __STDAIR_BOM_POLICYSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cmath>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_rm_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {    

  /**
   * Structure holding the elements of a policy.
   * A policy is a set of booking classes, each booking class belongs to
   * a different Fare Family.
   */
  struct PolicyStruct : public StructAbstract {
      
  public:
    // /////////////////// Getters ////////////////////////
    /** Getter for the booking classes. */
    const BookingClassList_T& getBookingClasses() const {
      return _bookingClassList;
    }
    /** Getter for the demand. */
    const NbOfBookings_T& getDemand() const {
      return _demand;
    }
    /** Getter for the yield. */
    const Yield_T& getYield() const {
      return _yield;
    }    
    /** Getter for the revenue. */
    const Revenue_T getRevenue() const {
      return _yield * _demand;
    }
    /** Getter for the standard deviation demand. */
    const StdDevValue_T& getStdDev() const {
      return _stdDev;
    }
    
  public:
    // ///////////////////// Setters /////////////////////
    /** Setter for the unconstraining demand. */
    void setDemand (const NbOfBookings_T& iDemand) {
      _demand = iDemand;
    }
    /** Setter for the yield. */
    void setYield (const Yield_T& iYield) {
      _yield = iYield;
    }
    /** Setter for standard deviation demand. */
    void setStdDev (const StdDevValue_T& iStdDev) {
      _stdDev = iStdDev;
    }
    

  public:
    // ///////// Display Methods //////////
    /**
     * Dump a Business Object into an output stream.
     * @param ostream& the output stream
     * @return ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;
    
    /**
     * Give a description of the structure (for display purposes).
     */
    const std::string describe() const;
      
    /**
     * Display on standard output.
     */
    void display () const;
      
  public:
    // /////////// Constructors and destructor. ////////////
    /**
     * Main constructor.
     */
    PolicyStruct (const BookingClassList_T&, 
                  const NbOfBookings_T&,
                  const Yield_T&,
                  const StdDevValue_T&);

    /**
     * Copy constructor.
     */
    PolicyStruct (const PolicyStruct&);
      
    /**
     * Destructor.
     */
    virtual ~PolicyStruct();

  private:
    /**
     * Default constructor.
     */
    PolicyStruct();
    
      
  private:
    // //////////// Attributes ////////////
    /**
     * Booking classes of the policy.
     */
    BookingClassList_T _bookingClassList;

    /**
     * Demand of the policy, or adjusted demand of the hull.
     */
    NbOfBookings_T _demand;

    /**
     * Yield of the policy, or adjusted yield of the hull.
     */
    Yield_T _yield;

    /**
     * Standard deviation of the demand.
     */
    StdDevValue_T _stdDev;

  };
}
#endif // __STDAIR_BOM_POLICYSTRUCT_HPP
