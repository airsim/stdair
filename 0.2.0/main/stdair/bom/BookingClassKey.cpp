// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BookingClassKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClassKey_T::BookingClassKey_T (const ClassCode_T& iClassCode)
    : _classCode (iClassCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassKey_T::~BookingClassKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClassKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "BookingClassKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClassKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string BookingClassKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _classCode;
    return oStr.str();
  }

}
