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
  FareOptionStruct::FareOptionStruct()
    : _fare (DEFAULT_FARE_VALUE), _avl (DEFAULT_AVAILABILITY) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  FareOptionStruct::FareOptionStruct (const FareOptionStruct& iFO)
    : _classPath (iFO._classPath),
      _fare (iFO._fare), _avl (iFO._avl), _changeFee (iFO._changeFee),
      _nonRefundable (iFO._nonRefundable), _saturdayStay (iFO._saturdayStay) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareOptionStruct::FareOptionStruct (const std::string& iClassPath,
                                      const Fare_T& iFare,
                                      const ChangeFees_T& iChangeFee,
                                      const NonRefundable_T& iNonRefundable,
                                      const SaturdayStay_T& iSaturdayNightStay)
    : _fare (iFare), _avl (DEFAULT_AVAILABILITY),
      _changeFee (iChangeFee), _nonRefundable (iNonRefundable),
      _saturdayStay (iSaturdayNightStay) {
    _classPath.push_back (iClassPath);
  }

  // ////////////////////////////////////////////////////////////////////
  FareOptionStruct::~FareOptionStruct() {
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

    oStr  << "Class path: ";
    unsigned short idx = 0;
    for (ClassList_StringList_T::const_iterator itClassPath =
           _classPath.begin(); itClassPath != _classPath.end();
         ++itClassPath, ++idx) {
      if (idx != 0) {
        oStr << "-";
      }
      const std::string& lClassPath = *itClassPath;
      oStr << lClassPath;
    }

    oStr << "; " << _fare << " EUR";
    oStr << "; conditions: " << _changeFee  << " " << _nonRefundable
         << " " << _saturdayStay;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string FareOptionStruct::display() const {
    std::ostringstream oStr;

    unsigned short idx = 0;
    for (ClassList_StringList_T::const_iterator itClassPath =
           _classPath.begin(); itClassPath != _classPath.end();
         ++itClassPath, ++idx) {
      if (idx != 0) {
        oStr << "-";
      }
      const std::string& lClassPath = *itClassPath;
      oStr << lClassPath;
    }

    oStr << ", " << _fare << ", " << _changeFee  << " " << _nonRefundable
         << " " << _saturdayStay;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void FareOptionStruct::addClassList (const std::string iClassCodeList) {
    _classPath.push_back (iClassCodeList);
  }

  // ////////////////////////////////////////////////////////////////////
  void FareOptionStruct::emptyClassList () {
    _classPath.clear();
  }

}
