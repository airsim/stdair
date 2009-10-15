#ifndef __STDAIR_BOM_BOMROOTCONTENT_HPP
#define __STDAIR_BOM_BOMROOTCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>

namespace stdair {
  /** Class representing the actual attributes for the Bom root. */
  class BomRootContent : public BomContent {

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    virtual const std::string describeKey() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    virtual const std::string describeShortKey() const = 0;
    
  protected:
    /** Default constructors. */
    BomRootContent ();
    BomRootContent (const BomRootContent&);

    /** Destructor. */
    virtual ~BomRootContent();

  protected:
    // Attributes

  };

}
#endif // __STDAIR_BOM_BOMROOTCONTENT_HPP
