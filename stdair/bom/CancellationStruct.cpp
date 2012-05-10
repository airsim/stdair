// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/bom/CancellationStruct.hpp>
#include <stdair/bom/BookingClass.hpp>

namespace stdair {
  // ////////////////////////////////////////////////////////////////////
  CancellationStruct::CancellationStruct (const SegmentPath_T& iSegPath,
                                          const ClassList_String_T& iList,
                                          const PartySize_T& iSize,
                                          const DateTime_T& iDateTime)
    : _segmentPath (iSegPath), _classList (iList), _partySize (iSize),
      _datetime (iDateTime) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  CancellationStruct::CancellationStruct (const SegmentPath_T& iSegPath,
					  const BookingClassIDList_T& iIDList,
                                          const PartySize_T& iSize,
                                          const DateTime_T& iDateTime)
    : _segmentPath (iSegPath), _classIDList (iIDList), _partySize (iSize), 
      _datetime (iDateTime) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  CancellationStruct::~CancellationStruct() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void CancellationStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void CancellationStruct::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string CancellationStruct::describe() const {
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
    if (_classList == "") {
      oStr << ";";
      BookingClassIDList_T::const_iterator lItBookingClassIDList =  
        _classIDList.begin();
      idx = 0;
      for (; lItBookingClassIDList != _classIDList.end(); 
            ++lItBookingClassIDList, ++idx) {
        if (idx != 0) {
          oStr << "-";
        }
        const BookingClassID_T& lBookingClassID = *lItBookingClassIDList;
        const BookingClass& lBookingClass = lBookingClassID.getObject();
        const ClassCode_T& lClassCode = lBookingClass.getClassCode();
        oStr << lClassCode;
      }
      oStr << ";" << _partySize << ";" << _datetime;
    } else {
      oStr << ";" << _classList << ";" << _partySize << ";" << _datetime;
    }
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string CancellationStruct::display() const {
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
    if (_classList == "") {
      oStr << ";";
      BookingClassIDList_T::const_iterator lItBookingClassIDList =  
        _classIDList.begin();
      idx = 0;
      for (; lItBookingClassIDList != _classIDList.end(); 
            ++lItBookingClassIDList, ++idx) {
        if (idx != 0) {
          oStr << "-";
        }
        const BookingClassID_T& lBookingClassID = *lItBookingClassIDList;
        const BookingClass& lBookingClass = lBookingClassID.getObject();
        const ClassCode_T& lClassCode = lBookingClass.getClassCode();
        oStr << lClassCode;
      }
      oStr << ";" << _partySize << ";" << _datetime;
    } else {
      oStr << ";" << _classList << ";" << _partySize << ";" << _datetime;
    }
    return oStr.str();
  }
}
