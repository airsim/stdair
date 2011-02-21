// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/bom/VirtualClassStruct.hpp>

namespace stdair {
  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct::VirtualClassStruct (BookingClass& ioBookingClass) {
    _bookingClass = &ioBookingClass;
  }

  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct:: VirtualClassStruct (const VirtualClassStruct& iVC)
    : _bookingClass (iVC._bookingClass), _yield (iVC._yield),
      _mean (iVC._mean), _stdDev (iVC._stdDev) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct::~VirtualClassStruct () {
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
         << ", Demand Mean: " << _mean
         << ", Demand SD: " << _stdDev << std::endl;
    return oStr.str();
  }

}
