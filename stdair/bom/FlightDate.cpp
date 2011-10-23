// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate()
    : _key (DEFAULT_FLIGHT_NUMBER, DEFAULT_DEPARTURE_DATE), _parent (NULL) {
    // That constructor is used by the serialisation process
  }
  
  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate (const FlightDate&)
    : _key (DEFAULT_FLIGHT_NUMBER, DEFAULT_DEPARTURE_DATE), _parent (NULL) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate (const Key_T& iKey) : _key (iKey), _parent (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate::~FlightDate() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const AirlineCode_T& FlightDate::getAirlineCode() const {
    const Inventory* lInventory_ptr =
      static_cast<const Inventory*> (getParent());
    assert (lInventory_ptr != NULL);
    return lInventory_ptr->getAirlineCode();
  }

  // ////////////////////////////////////////////////////////////////////
  std::string FlightDate::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  LegDate* FlightDate::getLegDate (const std::string& iLegDateKeyStr) const {
    LegDate* oLegDate_ptr =
      BomManager::getObjectPtr<LegDate> (*this, iLegDateKeyStr);
    return oLegDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  LegDate* FlightDate::getLegDate (const LegDateKey& iLegDateKey) const {
    return getLegDate (iLegDateKey.toString());
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate* FlightDate::
  getSegmentDate (const std::string& iSegmentDateKeyStr) const {
    SegmentDate* oSegmentDate_ptr = 
      BomManager::getObjectPtr<SegmentDate> (*this, iSegmentDateKeyStr);
    return oSegmentDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate* FlightDate::
  getSegmentDate (const SegmentDateKey& iSegmentDateKey) const {
    return getSegmentDate (iSegmentDateKey.toString());
  }

}

