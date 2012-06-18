#ifndef __STDAIR_BOM_FFDISUTILITYCURVEHOLDERSTRUCT_HPP
#define __STDAIR_BOM_FFDISUTILITYCURVEHOLDERSTRUCT_HPP

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
  // Type definition for the holder of disutility curves.
  typedef std::map<const std::string, FFDisutilityCurve_T> FFDisutilityCurveHolder_T;

  /** Structure holding the elements of a snapshot . */
  struct FFDisutilityCurveHolderStruct : public StructAbstract {
  public:
    // /////////////// Getters /////////////////
    /** Get the FFDisutility curve corresponding to the given key. */
    const FFDisutilityCurve_T& getFFDisutilityCurve (const std::string&) const;

    // ///////////// Business Methods //////////
    /** Add a new curve to the holder. */
    void addCurve (const std::string&, const FFDisutilityCurve_T&);
    
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
    FFDisutilityCurveHolderStruct ();

    /** Copy constructor. */
    FFDisutilityCurveHolderStruct (const FFDisutilityCurveHolderStruct&);

  public:
    /** Destructor. */
    ~FFDisutilityCurveHolderStruct();
    

  private:
    // /////////////// Attributes /////////////////
    /** Disutility curve holder. */
    FFDisutilityCurveHolder_T _disutilityCurveHolder;
  };

}
#endif // __STDAIR_BOM_FFDISUTILITYCURVEHOLDERSTRUCT_HPP
