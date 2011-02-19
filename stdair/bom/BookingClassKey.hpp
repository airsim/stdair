#ifndef __STDAIR_BOM_BOOKINGCLASSKEY_HPP
#define __STDAIR_BOM_BOOKINGCLASSKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

namespace stdair {
  
  /**
   * Key of a given leg-cabin, made of a cabin code.
   */
  struct BookingClassKey : public KeyAbstract {
    
    // /////////// Constructors and destructors ///////////
  private:
    /** Default constructor. */
    BookingClassKey();

  public:
    /** Constructor. */
    BookingClassKey (const ClassCode_T& iClassCode);
    /** Default copy constructor. */
    BookingClassKey (const BookingClassKey&);
    /** Destructor. */
    ~BookingClassKey();
    

    // /////////// Getters //////////
    /** Get the class code. */
    const ClassCode_T& getClassCode () const {
      return _classCode;
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
    // ///////////////// Attributes ///////////////
    /** Cabin code. */
    ClassCode_T _classCode;
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASSKEY_HPP
