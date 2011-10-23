// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/AirportPair.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirportPair::AirportPair()
    : _key (DEFAULT_ORIGIN, DEFAULT_DESTINATION),
      _parent (NULL)  {
    // That constructor is used by the serialisation process
  }

  // ////////////////////////////////////////////////////////////////////
  AirportPair::AirportPair (const AirportPair& iAirportPair)
    : _key (iAirportPair.getKey()), _parent (NULL)  {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AirportPair::AirportPair (const Key_T& iKey)
    : _key (iKey), _parent (NULL)  {
  }

  // ////////////////////////////////////////////////////////////////////
  AirportPair::~AirportPair () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string AirportPair::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }
}


