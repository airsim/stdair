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
  VirtualClassStruct::VirtualClassStruct() {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct::VirtualClassStruct (const VirtualClassStruct& iVC)
    : _bookingClassList (iVC._bookingClassList), _yield (iVC._yield),
      _mean (iVC._mean), _stdDev (iVC._stdDev) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct::
  VirtualClassStruct (const BookingClassList_T& ioBookingClassList) {
    _bookingClassList = ioBookingClassList;
  }

  // ////////////////////////////////////////////////////////////////////
  VirtualClassStruct::~VirtualClassStruct() {

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
  const GeneratedDemandVector_T VirtualClassStruct::
  getGeneratedDemandVector() const  {
      GeneratedDemandVector_T lDemandVector;
      const bool isBookingClassListEmpty = _bookingClassList.empty();
      if (isBookingClassListEmpty == false) {
        assert (isBookingClassListEmpty == false);
        BookingClassList_T::const_iterator itBC = _bookingClassList.begin();
        BookingClass* lBC_ptr = *itBC;
        const GeneratedDemandVector_T& lFirstDemandVector = 
          lBC_ptr->getGeneratedDemandVector();
        const unsigned int lFirstDemandVectorSize = lFirstDemandVector.size();
        for (unsigned int i = 0; i < lFirstDemandVectorSize; ++i) {
          const double& lDemand = lFirstDemandVector[i];
          lDemandVector.push_back(lDemand);
        }
        const unsigned int& lDemandVectorSize = lDemandVector.size();
        ++itBC;
        for (; itBC != _bookingClassList.end(); ++ itBC) {
          lBC_ptr = *itBC;
          assert(lBC_ptr != NULL);
          const GeneratedDemandVector_T& lCurrentDemandVector = 
            lBC_ptr->getGeneratedDemandVector();
          const unsigned int& lCurrentDemandVectorSize = 
            lCurrentDemandVector.size();
          assert(lDemandVectorSize == lCurrentDemandVectorSize);
          for (unsigned int i = 0; i < lDemandVectorSize; ++i) {
            lDemandVector[i] += lCurrentDemandVector[i];
          }
        }
      }
      return lDemandVector;
  }
}
