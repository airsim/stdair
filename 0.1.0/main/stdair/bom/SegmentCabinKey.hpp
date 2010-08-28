#ifndef __STDAIR_BOM_SEGMENTCABINKEY_HPP
#define __STDAIR_BOM_SEGMENTCABINKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomKey.hpp>

namespace stdair {
  /** Key of segment-cabin. */
  struct SegmentCabinKey_T : public BomKey_T {

  private:
    // /////////// Default constructor //////////
    SegmentCabinKey_T () { };
  public:
    // /////////// Construction ///////////
    /** Constructor. */
    SegmentCabinKey_T (const CabinCode_T& iCabinCode);
    SegmentCabinKey_T (const SegmentCabinKey_T&);
    /** Destructor. */
    ~SegmentCabinKey_T ();
    
    // /////////// Getters //////////
    /** Get the cabin code. */
    const CabinCode_T& getCabinCode () const {
      return _cabinCode;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-cabin. */
    const std::string toString() const;

  private:
    // Attributes
    /** Cabin code. */
    CabinCode_T _cabinCode;
  };

}
#endif // __STDAIR_BOM_SEGMENTCABINKEY_HPP