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

    //
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
    oStr << " ### ";

    //
    if (_chosenFareOption != NULL) {
      oStr << "Chosen fare option: " << _chosenFareOption->describe()
           << " ## Among: ";
    } else {
      oStr << "Fare options: ";
    }

    //
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

    // List of segment keys (one per segment)
    unsigned short idx = 0;
    for (SegmentPath_T::const_iterator itSegPath = _segmentPath.begin();
         itSegPath != _segmentPath.end(); ++itSegPath, ++idx) {
      if (idx != 0) {
        oStr << " ; ";
      }
      const std::string& lSegmentKey = *itSegPath;
      oStr << "[" << idx << "] " << lSegmentKey;
    }

    // List of fare options (for the whole O&D)
    oStr << " --- ";
    idx = 0;
    for (FareOptionList_T::const_iterator itFareOption = _fareOptionList.begin();
         itFareOption != _fareOptionList.end(); ++itFareOption, ++idx) {
      if (idx != 0) {
        oStr << " , ";
      }
      const FareOptionStruct& lFareOption = *itFareOption;
      oStr << lFareOption.display();
    }

    // List of booking class availability maps: one map per segment
    oStr << " --- ";
    idx = 0;
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
  void TravelSolutionStruct::addSegment (const std::string& iKey) {
    _segmentPath.push_back (iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addClassAvailabilityMap (const ClassAvailabilityMap_T& iMap) {
    _classAvailabilityMapHolder.push_back (iMap);
  }

  //MODIF
  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addClassYieldMap (const ClassYieldMap_T& iMap) {
    _classYieldMapHolder.push_back (iMap);
  }

  //MODIF
  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addBidPriceVector (const BidPriceVector_T& iBpv) {
    _bidPriceVectorHolder.push_back (iBpv);
  }

  //MODIF
  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addClassBpvMap (const ClassBpvMap_T& iMap) {
    _classBpvMapHolder.push_back (iMap);
  }
  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addFareOption (const FareOptionStruct& iFareOption) {
    _fareOptionList.push_back (iFareOption);
  }

}
