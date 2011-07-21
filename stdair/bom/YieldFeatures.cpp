// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/YieldFeatures.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  YieldFeatures::YieldFeatures (const Key_T& iKey)
    : _key (iKey), _parent (NULL)  {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldFeatures::~YieldFeatures () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string YieldFeatures::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  bool YieldFeatures::
  IsTripTypeValid (const stdair::TripType_T& iBookingRequestTripType) const {

    const stdair::TripType_T& lYieldTripType = getTripType ();
    // Check if the yield trip type is the same as the booking request trip type.
    if (iBookingRequestTripType == lYieldTripType) {
      // One way case.
      return true;
    } else if (iBookingRequestTripType == "RI" ||
               iBookingRequestTripType == "RO") {
      // Round trip case.
      if (lYieldTripType == "RT") {
        return true;
      } else {
        return false;
      }
    }
    return false;
  }


}

