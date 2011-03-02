// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/FareOptionStruct.hpp>

namespace stdair {
  // ////////////////////////////////////////////////////////////////////
  FareOptionStruct::FareOptionStruct () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  FareOptionStruct::~FareOptionStruct () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void FareOptionStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void FareOptionStruct::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string FareOptionStruct::describe() const {
    std::ostringstream oStr;
    oStr  << "\n    Class path: ";
    for (ClassList_String_T::const_iterator lItClassPath = _classPath.begin();
         lItClassPath != _classPath.end();
         lItClassPath ++) {
      oStr << *lItClassPath << " ";
    }
    oStr << "\n    Fare:       ";
    oStr << _fare
         << "\n    Conditions: "
         << _changeFee  << " "
         << _nonRefundable << " "
         << _saturdayStay;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void FareOptionStruct::addClass (const std::string iClassCodeList) {
    _classPath.append (iClassCodeList);
  }

}
