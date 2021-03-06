// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/bom/AirlineStruct.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineStruct::AirlineStruct () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirlineStruct::AirlineStruct (const AirlineStruct& iAirlineStruct) 
    : _code (iAirlineStruct._code), _name (iAirlineStruct._name) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  AirlineStruct::AirlineStruct (const AirlineCode_T& iAirlineCode,
                                const std::string& iAirlineName)
    : _code (iAirlineCode), _name (iAirlineName) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineStruct::~AirlineStruct () {
  }
      
  // //////////////////////////////////////////////////////////////////////
  void AirlineStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // //////////////////////////////////////////////////////////////////////
  void AirlineStruct::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string AirlineStruct::describe() const {
    std::ostringstream oStr;
    oStr << _code << " " << _name;
    return oStr.str();
  }

}
