// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/LegDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegDate::LegDate() : _key (DEFAULT_ORIGIN), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  LegDate::LegDate (const LegDate&) : _key (DEFAULT_ORIGIN), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  LegDate::LegDate (const Key_T& iKey) 
    : _key (iKey), _parent (NULL), _distance (DEFAULT_DISTANCE_VALUE),
      _capacity (DEFAULT_CABIN_CAPACITY) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegDate::~LegDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string LegDate::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const Duration_T LegDate::getTimeOffset() const {
    // TimeOffset = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
    //              - ElapsedTime
    Duration_T oTimeOffset = (_offTime - _boardingTime);

    const DateOffset_T& lDateOffset = getDateOffset();

    const Duration_T lDateOffsetInHours (lDateOffset.days() * 24, 0, 0);

    oTimeOffset += lDateOffsetInHours - _elapsedTime;

    return oTimeOffset;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void LegDate::setElapsedTime (const Duration_T& iElapsedTime) {
    // Set Elapsed time
    _elapsedTime = iElapsedTime;

    // Update distance according to the mean plane speed
    updateDistanceFromElapsedTime();
  }

  // ////////////////////////////////////////////////////////////////////
  void LegDate::updateDistanceFromElapsedTime() {
    //
    const double lElapseInHours =
      static_cast<const double> (_elapsedTime.hours());

    // Normally, Distance_T is an unsigned long int
    const Distance_T lDistance =
      static_cast<const Distance_T> (DEFAULT_FLIGHT_SPEED * lElapseInHours);
    
    _distance = lDistance;
  }
  
}

