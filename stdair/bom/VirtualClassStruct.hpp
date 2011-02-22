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
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {
  // Forward declarations.
  class BookingClass;

  /** Structure holding the elements of a virtual class. */
  struct VirtualClassStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
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
    /** Constructor. */
    VirtualClassStruct (const VirtualClassStruct&);
    /** Default copy constructor. */
    VirtualClassStruct (BookingClass&);
    /** Destructor. */
    ~VirtualClassStruct();
    
  private:
    /** Default constructor. */
    VirtualClassStruct();


  private:
    // ///////////////////// Attributes //////////////////////
    /** Pointer on the origin booking class. */
    BookingClass* _bookingClass;

    /** Yield. */
    Yield_T _yield;

    /** Mean value of the demand distribution. */
    MeanValue_T _mean;

    /** Standard deviation of the demand distribution. */
    StdDevValue_T _stdDev;
  };

}
#endif // __STDAIR_BOM_VIRTUALCLASSSTRUCT_HPP
