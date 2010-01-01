#ifndef __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
#define __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/bom/StructAbstract.hpp>

namespace stdair {

  /** Structure holding the elements of a booking request. */
  struct BookingRequestStruct : public StructAbstract {
  public:

    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << describe();
    }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) {
    }

    /** Display of the structure. */
    const std::string describe() const {
      return "";
    }


  private:

  };

}
#endif // __STDAIR_BOM_BOOKINGREQUESTSTRUCT_HPP
