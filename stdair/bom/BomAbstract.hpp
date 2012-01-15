/**
 * @page BomAbstract
 * @brief Abstract part of the Business Object Model (BOM)
 * @author Anh Quan Nguyen <quannaus@users.sourceforge.net>
 * @date 20/01/2010
 */
#ifndef __STDAIR_BOM_BOMABSTRACT_HPP
#define __STDAIR_BOM_BOMABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#include <map>
#include <typeinfo>

namespace stdair {

  /**
   * @brief Base class for the Business Object Model (BOM) layer
   */
  class BomAbstract {
  public:
    // /////////// Display support methods /////////
    /**
     * Dump a Business Object into an output stream.
     *
     * @param ostream& The input/output stream.
     */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /**
     * Read a Business Object from an input stream.
     *
     * @param istream& The input stream.
     */
    virtual void fromStream (std::istream& ioIn) = 0;

    /**
     * Get the serialised version of the Business Object.
     *
     * @return std::string The output string
     */
    virtual std::string toString() const = 0;

    
  protected:
    /**
     * Protected Default Constructor to ensure this class is abtract.
     */
    BomAbstract() {}
    BomAbstract(const BomAbstract&) {}
  public:
    /**
     * Destructor.
     */
    virtual ~BomAbstract() {}
  };

  /* Define the map of object holder type. */
  typedef std::map<const std::type_info*, BomAbstract*> HolderMap_T;
}

/**
 * Piece of code given by Nicolai M. Josuttis, Section 13.12.1 "Implementing
 * Output Operators" (p653) of his book "The C++ Standard Library: A Tutorial
 * and Reference", published by Addison-Wesley.
 */
template <class charT, class traits>
inline
std::basic_ostream<charT, traits>&
operator<< (std::basic_ostream<charT, traits>& ioOut,
            const stdair::BomAbstract& iBom) {
  /**
   * string stream:
   *  - with same format
   *  - without special field width
   */
  std::basic_ostringstream<charT,traits> ostr;
  ostr.copyfmt (ioOut);
  ostr.width (0);

  // Fill string stream
  iBom.toStream (ostr);

  // Print string stream
  ioOut << ostr.str();

  return ioOut;
}

/**
 * Piece of code given by Nicolai M. Josuttis, Section 13.12.1 "Implementing
 * Output Operators" (pp655-657) of his book "The C++ Standard Library:
 * A Tutorial and Reference", published by Addison-Wesley.
 */
template <class charT, class traits>
inline
std::basic_istream<charT, traits>&
operator>> (std::basic_istream<charT, traits>& ioIn,
            stdair::BomAbstract& ioBom) {
  // Fill Bom object with input stream
  ioBom.fromStream (ioIn);
  return ioIn;
}

#endif // __STDAIR_BOM_BOMABSTRACT_HPP
