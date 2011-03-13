// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>

namespace stdair {
  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::TravelSolutionStruct() : _chosenFareOption (NULL) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::~TravelSolutionStruct() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string TravelSolutionStruct::describe() const {
    std::ostringstream oStr;

    oStr << "Segment path: ";
    unsigned short idx = 0;
    for (SegmentPath_T::const_iterator lItSegmentPath = _segmentPath.begin();
         lItSegmentPath != _segmentPath.end(); ++lItSegmentPath, ++idx) {
      if (idx != 0) {
        oStr << "-";
      }
      const std::string& lSegmentKey = *lItSegmentPath;
      oStr << lSegmentKey;
    }

    oStr << "; fare options: ";
    idx = 0;
    for (FareOptionList_T::const_iterator lItFareOption= _fareOptionList.begin();
         lItFareOption != _fareOptionList.end(); ++lItFareOption, ++idx) {
      if (idx != 0) {
        oStr << " , ";
      }
      const FareOptionStruct& lFareOption = *lItFareOption;
      oStr << lFareOption.describe();
    }
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string TravelSolutionStruct::display() const {
    std::ostringstream oStr;

    unsigned short idx = 0;
    for (SegmentPath_T::const_iterator lItSegmentPath = _segmentPath.begin();
         lItSegmentPath != _segmentPath.end(); ++lItSegmentPath, ++idx) {
      if (idx != 0) {
        oStr << "-";
      }
      const std::string& lSegmentKey = *lItSegmentPath;
      oStr << lSegmentKey;
    }

    oStr << " --- ";
    idx = 0;
    for (FareOptionList_T::const_iterator lItFareOption= _fareOptionList.begin();
         lItFareOption != _fareOptionList.end(); ++lItFareOption, ++idx) {
      if (idx != 0) {
        oStr << " , ";
      }
      const FareOptionStruct& lFareOption = *lItFareOption;
      oStr << lFareOption.display();
    }
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::addSegment (const std::string& iKey) {
    _segmentPath.push_back (iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addClassAvailabilityMap (const ClassAvailabilityMap_T& iMap) {
    _classAvailabilityMapHolder.push_back (iMap);
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addFareOption (const FareOptionStruct& iFareOption) {
    _fareOptionList.push_back (iFareOption);
  }

}
