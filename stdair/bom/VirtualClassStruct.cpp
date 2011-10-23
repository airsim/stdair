// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/bom/VirtualClassStruct.hpp>
#include <stdair/bom/BookingClass.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct::VirtualClassStruct() : _bookingClass (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct::VirtualClassStruct (const VirtualClassStruct& iVC)
    : _bookingClass (iVC._bookingClass), _yield (iVC._yield),
      _mean (iVC._mean), _stdDev (iVC._stdDev) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct::VirtualClassStruct (BookingClass& ioBookingClass) {
    _bookingClass = &ioBookingClass;
  }

  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct::~VirtualClassStruct() {
    _bookingClass = NULL;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void VirtualClassStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void VirtualClassStruct::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string VirtualClassStruct::describe() const {
    std::ostringstream oStr;
    oStr << "Yield: " << _yield
         << ", Demand N (" << _mean << ", " << _stdDev << ")";
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const GeneratedDemandVector_T& VirtualClassStruct::
  getGeneratedDemandVector() const  {
      assert (_bookingClass != NULL);
      return _bookingClass->getGeneratedDemandVector();
  }
}
