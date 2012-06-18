#ifndef __STDAIR_BOM_FRAT5CURVEHOLDERSTRUCT_HPP
#define __STDAIR_BOM_FRAT5CURVEHOLDERSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_rm_types.hpp>
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {
  // Type definition for the holder of Frat5 curves.
  typedef std::map<const std::string, FRAT5Curve_T> FRAT5CurveHolder_T;

  /** Structure holding the elements of a snapshot . */
  struct FRAT5CurveHolderStruct : public StructAbstract {
  public:
    // /////////////// Getters /////////////////
    /** Get the FRAT5 curve corresponding to the given key. */
    const FRAT5Curve_T& getFRAT5Curve (const std::string&) const;

    // ///////////// Business Methods //////////
    /** Add a new curve to the holder. */
    void addCurve (const std::string&, const FRAT5Curve_T&);
    
    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;

    
    // /////////////// Constructors and Destructors /////////////////
  public:
    /** Constructor. */
    FRAT5CurveHolderStruct ();

    /** Copy constructor. */
    FRAT5CurveHolderStruct (const FRAT5CurveHolderStruct&);

  public:
    /** Destructor. */
    ~FRAT5CurveHolderStruct();
    

  private:
    // /////////////// Attributes /////////////////
    /** Frat5 curve holder. */
    FRAT5CurveHolder_T _frat5CurveHolder;
  };

}
#endif // __STDAIR_BOM_FRAT5CURVEHOLDERSTRUCT_HPP
