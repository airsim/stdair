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
    /** Getter for the attributes. */
    const Yield_T& getYield () const { return _yield; }
    const MeanValue_T& getMean () const { return _mean; }
    const StdDevValue_T& getStdDev () const {return _stdDev; }
    
  public:
    // /////////// Setters ///////////////
    /** Setter for the attributes (except the origin booking class pointer). */
    void setYield (const Yield_T& iYield) { _yield = iYield; }
    void setMean (const MeanValue_T& iMean) { _mean = iMean; }
    void setStdDev (const StdDevValue_T& iStdDev) { _stdDev = iStdDev; }

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
    /** Main constructors. */
    VirtualClassStruct ();
    VirtualClassStruct (BookingClass&);
    VirtualClassStruct (const VirtualClassStruct&);
    /** Destructor. */
    ~VirtualClassStruct ();
    
  private:
    // ///////////////////// Attributes //////////////////////
    /** The origin booking class. */
    BookingClass* _bookingClass;

    /** Yield. */
    Yield_T _yield;

    /** Demand distribution. */
    MeanValue_T _mean;
    StdDevValue_T _stdDev;
  };

}
#endif // __STDAIR_BOM_VIRTUALCLASSSTRUCT_HPP
