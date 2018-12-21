// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/bom/ClassAvailabilityStruct.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  ClassAvailabilityStruct::ClassAvailabilityStruct() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  ClassAvailabilityStruct::~ClassAvailabilityStruct() {
  }

  // ////////////////////////////////////////////////////////////////////
  ClassAvailabilityStruct::
  ClassAvailabilityStruct (const ClassAvailabilityStruct& iClassAvlStruct)
    : _classAvailabilityStruct (iClassAvlStruct._classAvailabilityStruct) {
  }

  // ////////////////////////////////////////////////////////////////////
  ClassAvailabilityStruct::
  ClassAvailabilityStruct (const ClassAvailabilityMap_T& iClassAvlMap)
    : _classAvailabilityStruct (iClassAvlMap) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void ClassAvailabilityStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void ClassAvailabilityStruct::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string ClassAvailabilityStruct::describe() const {
    std::ostringstream oStr;

    // List (map) of booking class availabilities
    unsigned short jdx = 0;
    for (ClassAvailabilityMap_T::const_iterator itClass =
           _classAvailabilityStruct.begin();
         itClass != _classAvailabilityStruct.end(); ++itClass, ++jdx) {
      if (jdx != 0) {
        oStr << " ";
      }
      const ClassCode_T& lClassCode = itClass->first;
      const Availability_T& lAvl = itClass->second;
      oStr << lClassCode << ":" << lAvl;
    }

    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string ClassAvailabilityStruct::display() const {
    const std::string oString = describe();
    return oString;
  }

}
