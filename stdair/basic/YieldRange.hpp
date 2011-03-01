#ifndef __STDAIR_BAS_YIELDRANGE_HPP
#define __STDAIR_BAS_YIELDRANGE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /** Class representing a range of yields.
      <br>Typically, bookings are priced according to rules (e.g., fare rules),
      leading to slight variations of revenues for a given product.
      The "yield range" captures the extent of revenues earned for a given
      product.
      <br>When no average and lower yields are defined, they are assumed 
      to be equal to the upper yield.
      <br>Note that the lower yield is generally not defined, as it
      corresponds to the upper yield of the lower yield range.
  */
  class YieldRange : public StructAbstract {
  public:
    /** Constructors. */
    YieldRange ();
    YieldRange (const YieldRange&);
    YieldRange (const Yield_T iUpperYield);
    YieldRange (const Yield_T iUpperYield, const Yield_T iAverageYield);
    YieldRange (const Yield_T iUpperYield, const Yield_T iAverageYield,
                const Yield_T iLowerYield);
    
    /** Constructors. */
    virtual ~YieldRange();
    

    // /////////// Getters ////////////
    /** Getter for the upper yield of the range. */
    Yield_T getUpperYield() const {
      return _upperYield;
    }
    /** Getter for the average yield of the range. */
    Yield_T getAverageYield() const {
      return _averageYield;
    }
    /** Getter for the lower yield of the range. */
    Yield_T getLowerYield() const {
      return _lowerYield;
    }
    
    // //////// Setters /////////
    /** Setter for the upper yield of the range. */
    void setUpperYield (const Yield_T iUpperYield) {
      _upperYield = iUpperYield;
    }
    /** Setter for the average yield of the range. */
    void setAverageYield (const Yield_T iAverageYield) {
      _averageYield = iAverageYield;
    }
    /** Setter for the lower yield of the range. */
    void setLowerYield (const Yield_T iLowerYield) {
      _lowerYield = iLowerYield;
    }
    

    // ///////// Display methods ////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream&) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream&);

    /** Display of the structure. */
    const std::string describe() const;

  private:
    // ////////// Attributes /////////
    /** Upper yield. */
    Yield_T _upperYield;

    /** Average yield. */
    Yield_T _averageYield;

    /** Lower yield (most often, not used). */
    Yield_T _lowerYield;
  };
}
#endif // __STDAIR_BAS_YIELDRANGE_HPP
