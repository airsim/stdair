// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/YieldFeatures.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  YieldFeatures::YieldFeatures()
    : _key (TRIP_TYPE_ONE_WAY,
            DEFAULT_PREFERRED_CABIN),
      _parent (NULL)  {
    // That constructor is used by the serialisation process
  }

  // ////////////////////////////////////////////////////////////////////
  YieldFeatures::YieldFeatures (const YieldFeatures& iFeatures)
    : _key (iFeatures.getKey()), _parent (NULL)  {
  }

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
  isTripTypeValid (const TripType_T& iBookingRequestTripType) const {
    bool oIsTripTypeValidFlag = true;

    // Check whether the yield trip type is the same as the booking request
    // trip type
    const TripType_T& lYieldTripType = getTripType();
    if (iBookingRequestTripType == lYieldTripType) {
      // One way case
      return oIsTripTypeValidFlag;
    }

    if (iBookingRequestTripType == TRIP_TYPE_INBOUND ||
        iBookingRequestTripType == TRIP_TYPE_OUTBOUND) {
      // Round trip case.
      if (lYieldTripType == TRIP_TYPE_ROUND_TRIP) {
        return oIsTripTypeValidFlag;
      }
    }

    oIsTripTypeValidFlag = false;
    return false;
  }

}

