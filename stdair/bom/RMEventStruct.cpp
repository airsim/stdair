// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/bom/RMEventStruct.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  RMEventStruct::RMEventStruct() {
    assert (false);
  }
    
  // //////////////////////////////////////////////////////////////////////
  RMEventStruct::
  RMEventStruct (const RMEventStruct& iRMEvent)
    : _airlineCode (iRMEvent._airlineCode),
      _flightDateDescription (iRMEvent._flightDateDescription),
      _snapshotTime (iRMEvent._snapshotTime) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  RMEventStruct::
  RMEventStruct (const AirlineCode_T& iAirlineCode,
                  const KeyDescription_T& iFlightDateDescription,
                  const DateTime_T& iRMEventTime)
    : _airlineCode (iAirlineCode),
      _flightDateDescription (iFlightDateDescription),
      _snapshotTime (iRMEventTime) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  RMEventStruct::~RMEventStruct() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void RMEventStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // //////////////////////////////////////////////////////////////////////
  void RMEventStruct::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string RMEventStruct::describe() const {
    std::ostringstream oStr;
    oStr << _airlineCode << ", " << _flightDateDescription << ", "
         << _snapshotTime;
    return oStr.str();
  }

}
