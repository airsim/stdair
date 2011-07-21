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
  // TODO (gsabatier): replace the hard-coded constants by BasConst ones.
  YieldFeatures::YieldFeatures()
    : _key ("RT", "Y"), _parent (NULL)  {
    // That constructor is used by the serialisation process
  }

  // ////////////////////////////////////////////////////////////////////
  YieldFeatures::YieldFeatures (const YieldFeatures& iFeatures)
    : _key (iFeatures.getKey()), _parent (NULL)  {
    assert (false);
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

    if (iBookingRequestTripType == "RI" || iBookingRequestTripType == "RO") {
      // Round trip case.
      if (lYieldTripType == "RT") {
        return oIsTripTypeValidFlag;
      }
    }

    oIsTripTypeValidFlag = false;
    return false;
  }

}

