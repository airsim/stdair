#ifndef __STDAIR_BOM_BREAKPOINTSTRUCT_HPP
#define __STDAIR_BOM_BREAKPOINTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BreakPointTypes.hpp>

namespace stdair {

  /** Structure holding the elements of a break point. */
  struct BreakPointStruct : public StructAbstract {
  public:
    // /////////////// Getters /////////////////
    /** Get the break point action time. */
    const DateTime_T& getBreakPointTime() const {
      return _breakPointTime;
    }
    
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
    BreakPointStruct (const DateTime_T&); 

    /** Constructor. */
    BreakPointStruct (const Date_T&);

    /** Copy constructor. */
    BreakPointStruct (const BreakPointStruct&);

  private:
    /** Default constructor.
        <br>It is private so that it can not be used. */
    BreakPointStruct ();

  public:
    /** Destructor. */
    ~BreakPointStruct();
    

  private:
    // /////////////// Attributes /////////////////    
    /** BreakPoint time. */
    const DateTime_T _breakPointTime;
  };

}
#endif // __STDAIR_BOM_BREAKPOINTSTRUCT_HPP
