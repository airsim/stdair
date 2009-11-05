// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <algorithm>
// STDAIR
#include <stdair/bom/FlightDateStructure.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate (const BomKey_T& iKey,
                          BomStructure_T& ioFlightStructure)
    : FlightDateContent (iKey), _flightDateStructure (ioFlightStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate::~FlightDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string FlightDate::toString() const {
    std::ostringstream oStr;
    
    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeKey() const {
    return _flightDateStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeShortKey() const {
    return _flightDateStructure.describeShortKey();
  }
  
  // //////////////////////////////////////////////////////////////////////
  SegmentDateList_T FlightDate::getSegmentDateList () const {
    return _flightDateStructure.getChildrenList();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentDateMap_T FlightDate::getSegmentDateMap () const {
    return _flightDateStructure.getChildrenList();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateList_T FlightDate::getLegDateList () const {
    return _flightDateStructure.getSecondChildrenList();
  }

  // //////////////////////////////////////////////////////////////////////
  LegDateMap_T FlightDate::getLegDateMap () const {
    return _flightDateStructure.getSecondChildrenList();
  }
  
}

