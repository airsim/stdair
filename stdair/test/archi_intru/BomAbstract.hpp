#ifndef __INTRUSIVE_BOM_BOMABSTRACT_HPP
#define __INTRUSIVE_BOM_BOMABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iosfwd>
#include <sstream>
#include <string>
// Boost.Intrusive
#include <boost/functional/hash.hpp>

namespace stdair {

  /** BomAbstract. */
  class BomAbstract {
  public:
    /** Constructors. */
    BomAbstract (const std::string& iKey) : _key (iKey)  {}
    BomAbstract (const int idx) {
      std::ostringstream oStr;
      oStr << idx;
      _key = oStr.str();
    }
    /** Get the key. */
    const std::string& getKey() const {
      return _key;
    }
    
  protected:
    /** Default constructors.
        <br>They are kept private, so as to forbid their use (only the
        public constructors should be used). */
    BomAbstract () {}
    BomAbstract (const BomAbstract&) {}

  public:
    // Comparison operators
    friend bool operator< (const BomAbstract& a, const BomAbstract& b) {
      return a._key < b._key;
    }

    friend bool operator> (const BomAbstract& a, const BomAbstract& b) {
      return a._key > b._key;
    }

    friend bool operator== (const BomAbstract& a, const BomAbstract& b) {
      return a._key == b._key;
    }

    friend bool operator!= (const BomAbstract& a, const BomAbstract& b) {
      return a._key != b._key;
    }

    // The hash function
    friend std::size_t hash_value (const BomAbstract& iBom) {
      return boost::hash<std::string>() (iBom._key);
    }

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
    
  protected:
    std::string _key;
  };

}

/**
   Piece of code given by Nicolai M. Josuttis, Section 13.12.1 "Implementing
   Output Operators" (p653) of his book "The C++ Standard Library: A Tutorial
   and Reference", published by Addison-Wesley.
 */
template <class charT, class traits>
inline
std::basic_ostream<charT, traits>&
operator<< (std::basic_ostream<charT, traits>& ioOut,
            const stdair::BomAbstract& iBom) {
  /**
     string stream:
      - with same format
      - without special field width
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
   Piece of code given by Nicolai M. Josuttis, Section 13.12.1 "Implementing
   Output Operators" (pp655-657) of his book "The C++ Standard Library:
   A Tutorial and Reference", published by Addison-Wesley.
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


/** The disposer object function. */
template <typename BOM>
struct delete_disposer {
  void operator() (BOM* oBOM_ptr) {
    delete oBOM_ptr; oBOM_ptr = NULL;
  }
};

// These compare (STL strings) keys of BOM objects
template <typename BOM>
struct StrExpComp {
  bool operator() (const std::string& iKey, const BOM& iBom) const {
    return (iKey < iBom.getKey());
  }

  bool operator() (const BOM& iBom, const std::string& iKey) const {
    return (iBom.getKey() < iKey);
  }
};

template <typename BOM>
struct StrExpEqual {
   bool operator() (const std::string& iKey, const BOM& iBom) const {
     return (iKey == iBom.getKey());
   }

   bool operator() (const BOM& iBom, const std::string& iKey) const {
     return (iBom.getKey() == iKey);
   }
};

#endif // __INTRUSIVE_BOM_BOMABSTRACT_HPP
