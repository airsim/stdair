#ifndef __STDAIR_BOM_VIRTUALCLASSSTRUCT_HPP
#define __STDAIR_BOM_VIRTUALCLASSSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#include <vector>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_rm_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {
  // Forward declarations.
  class BookingClass;

  /** Structure holding the elements of a virtual class. */
  struct VirtualClassStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get the list of booking class. */
    const BookingClassList_T& getBookingClassList() const {
      return _bookingClassList;
    }

    /** Get the yield (average price paid for that virtual class). */
    const Yield_T& getYield() const {
      return _yield;
    }

    /** Get the mean value of the demand distribution. */
    const MeanValue_T& getMean() const {
      return _mean;
    }

    /** Get the standard deviation of the demand distribution. */
    const StdDevValue_T& getStdDev() const {
      return _stdDev;
    }

    /** Get the booking limit of the class. */
    const BookingLimit_T& getCumulatedBookingLimit () const {
      return _cumulatedBookingLimit;
    }

    /** Get the protection level of the class. */
    const ProtectionLevel_T& getCumulatedProtection () const {
      return _cumulatedProtection;
    }

    /** Get the generated demand sample vector for Monte-Carlo method. */
    const GeneratedDemandVector_T getGeneratedDemandVector () const;
    
  public:
    // /////////// Setters ///////////////
    /** Set the yield (average price paid for that virtual class). */
    void setYield (const Yield_T& iYield) {
      _yield = iYield;
    }

    /** Set the mean value of the demand distribution. */
    void setMean (const MeanValue_T& iMean) {
      _mean = iMean;
    }

    /** Set the standard deviation of the demand distribution. */
    void setStdDev (const StdDevValue_T& iStdDev) {
      _stdDev = iStdDev;
    }
    
    /** Set the booking limit of the class. */
    void setCumulatedBookingLimit (const BookingLimit_T& iBL) {
      _cumulatedBookingLimit = iBL;
    }
    
    /** Set the protection level of the class. */
    void setCumulatedProtection (const ProtectionLevel_T& iP) {
      _cumulatedProtection = iP;
    }

    /** Add a booking class to the list of booking classes. 
     *  Note: it is not a link Parent/Child so we don't use the FacBom.
     *        The Virtual Classes are not bom objects because the
     *        optimiser needs to build them before each optimisation.
     */
    void addBookingClass (BookingClass& iBookingClass) {
      _bookingClassList.push_back(&iBookingClass);
    }
    
  public:
    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;
  

  public:
    // //////////// Constructors & Destructor ///////////////
    /** Default copy constructor. */
    VirtualClassStruct (const VirtualClassStruct&);
    /** Constructor. */
    VirtualClassStruct (const BookingClassList_T&);
    /** Destructor. */
    ~VirtualClassStruct();
    
  private:
    /** Default constructor. */
    VirtualClassStruct();


  private:
    // ///////////////////// Attributes //////////////////////
    /** List of pointers on the booking classes. */
    BookingClassList_T _bookingClassList;

    /** Yield. */
    Yield_T _yield;

    /** Mean value of the demand distribution. */
    MeanValue_T _mean;

    /** Standard deviation of the demand distribution. */
    StdDevValue_T _stdDev;

    /** Booking limit. */
    BookingLimit_T _cumulatedBookingLimit;

    /** Protection level. */
    ProtectionLevel_T _cumulatedProtection;
  };

}
#endif // __STDAIR_BOM_VIRTUALCLASSSTRUCT_HPP
