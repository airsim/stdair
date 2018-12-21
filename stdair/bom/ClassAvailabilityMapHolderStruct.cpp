// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/bom/ClassAvailabilityMapHolderStruct.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  ClassAvailabilityMapHolderStruct::ClassAvailabilityMapHolderStruct() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  ClassAvailabilityMapHolderStruct::~ClassAvailabilityMapHolderStruct() {
  }

  // ////////////////////////////////////////////////////////////////////
  ClassAvailabilityMapHolderStruct::
  ClassAvailabilityMapHolderStruct (const ClassAvailabilityMapHolderStruct& iClassAvailabilityMapHolder)
    : _classAvailabilityMapHolder (iClassAvailabilityMapHolder._classAvailabilityMapHolder) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void ClassAvailabilityMapHolderStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void ClassAvailabilityMapHolderStruct::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string ClassAvailabilityMapHolderStruct::describe() const {
    std::ostringstream oStr;

    // List of booking class availability maps: one map per segment
    unsigned short idx = 0;
    for (ClassAvailabilityMapHolder_T::const_iterator itSegMap =
           _classAvailabilityMapHolder.begin();
         itSegMap != _classAvailabilityMapHolder.end(); ++itSegMap, ++idx) {
      if (idx != 0) {
        oStr << " ; ";
      }
      // Retrieve the booking class availability map
      const ClassAvailabilityMap_T& lClassAvlMap = *itSegMap;
      oStr << "[" << idx << "] ";
      
      // List (map) of booking class availabilities
      unsigned short jdx = 0;
      for (ClassAvailabilityMap_T::const_iterator itClass = lClassAvlMap.begin();
           itClass != lClassAvlMap.end(); ++itClass, ++jdx) {
        if (jdx != 0) {
          oStr << " ";
        }
        const ClassCode_T& lClassCode = itClass->first;
        const Availability_T& lAvl = itClass->second;
        oStr << lClassCode << ":" << lAvl;
      }
    }

    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string ClassAvailabilityMapHolderStruct::display() const {
    const std::string oString = describe();
    return oString;
  }

  // ////////////////////////////////////////////////////////////////////
  void ClassAvailabilityMapHolderStruct::
  addClassAvailabilityMap (const ClassAvailabilityMap_T& iMap) {
    _classAvailabilityMapHolder.push_back (iMap);
  }

}
