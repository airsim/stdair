// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/BomKeyManager.hpp>
#include <stdair/bom/ParsedKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::TravelSolutionStruct() : _chosenFareOption (NULL) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::~TravelSolutionStruct() {
    _chosenFareOption = NULL;
  }

  // ////////////////////////////////////////////////////////////////////
  TravelSolutionStruct::
  TravelSolutionStruct (const TravelSolutionStruct& iTravelSolution)
    : _segmentPath (iTravelSolution._segmentPath),
      _classAvailabilityMapHolder (iTravelSolution._classAvailabilityMapHolder),
      _classObjectIDMapHolder (iTravelSolution._classObjectIDMapHolder),
      _classYieldMapHolder (iTravelSolution._classYieldMapHolder),
      _bidPriceVectorHolder (iTravelSolution._bidPriceVectorHolder),
      _classBpvMapHolder (iTravelSolution._classBpvMapHolder),
      _fareOptionList (iTravelSolution._fareOptionList),
      _chosenFareOption (iTravelSolution._chosenFareOption) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string TravelSolutionStruct::describeSegmentPath() const {
    std::ostringstream oStr;

    //
    oStr << "Segment path: ";
    unsigned short idx = 0;
    for (SegmentPath_T::const_iterator lItSegmentPath = _segmentPath.begin();
         lItSegmentPath != _segmentPath.end(); ++lItSegmentPath, ++idx) {
      if (idx != 0) {
        oStr << " - ";
      }
      const std::string& lSegmentPathString = *lItSegmentPath;
      const stdair::ParsedKey& lSegmentParsedKey =
        stdair::BomKeyManager::extractKeys (lSegmentPathString);
      const std::string& lSegmentKey = lSegmentParsedKey.toString();
      oStr << lSegmentKey;
    }
    return oStr.str();
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
      const std::string& lSegmentPathString = *lItSegmentPath;
      const stdair::ParsedKey& lSegmentParsedKey =
        stdair::BomKeyManager::extractKeys (lSegmentPathString);
      const std::string& lSegmentKey = lSegmentParsedKey.toString();
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
      const std::string& lSegmentPathString = *itSegPath;
      const stdair::ParsedKey& lSegmentParsedKey =
        stdair::BomKeyManager::extractKeys (lSegmentPathString);
      const std::string& lSegmentKey = lSegmentParsedKey.toString();
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
    for (ClassAvailabilityMapHolder_T::const_iterator itSegMap =
           _classAvailabilityMapHolder.begin();
         itSegMap != _classAvailabilityMapHolder.end(); ++itSegMap, ++idx) {
      if (idx != 0) {
        oStr << " ; ";
      }

      // Retrieve the booking class availability map
      const ClassAvailabilityStruct& lClassAvlMap = *itSegMap;
      oStr << "[" << idx << "] ";

      const std::string lClassAvlMapString = lClassAvlMap.describe();
      oStr << lClassAvlMapString;
    }

    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::addSegment (const std::string& iKey) {
    _segmentPath.push_back (iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addClassAvailabilityMap (const ClassAvailabilityMap_T& iClassAvlMap) {
    const ClassAvailabilityStruct lClassAvlStruct (iClassAvlMap);
    _classAvailabilityMapHolder.push_back (lClassAvlStruct);
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addClassObjectIDMap (const ClassObjectIDMap_T& iMap) {
    _classObjectIDMapHolder.push_back (iMap);
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addClassYieldMap (const ClassYieldMap_T& iMap) {
    _classYieldMapHolder.push_back (iMap);
  }

  // ////////////////////////////////////////////////////////////////////
  void TravelSolutionStruct::
  addBidPriceVector (const BidPriceVector_T& iBpv) {
    _bidPriceVectorHolder.push_back (iBpv);
  }

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
