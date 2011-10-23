#ifndef __STDAIR_TST_STDAIR_TEST_LIB_HPP
#define __STDAIR_TST_STDAIR_TEST_LIB_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

/**
 * Namespace gathering classes and structures for test purposes
 */
namespace stdair_test {
  
  /** BookingClass */
  struct BookingClass {
    std::string _classCode;
    /** Constructor. */
    BookingClass (const std::string& iClassCode)
      : _classCode (iClassCode) {
    }
    
    /** Display .*/
    std::string toString() const {
      std::ostringstream oStr;
      oStr << _classCode;
      return oStr.str();
    }
  };
  
  /** Cabin */
  struct Cabin {
    BookingClass _bookingClass;
    Cabin (const BookingClass& iBkgClass)
      : _bookingClass (iBkgClass) {
    }
    
    /** Display .*/
    std::string toString() const {
      std::ostringstream oStr;
      oStr << _bookingClass._classCode;
      return oStr.str();
    }
    
    /** Child type. */
    typedef BookingClass child;
  };
}

#endif // __STDAIR_TST_STDAIR_TEST_LIB_HPP
