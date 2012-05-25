// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_DefaultObject.hpp>
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/FareFeatures.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FareFeatures::FareFeatures()
    : _key (TRIP_TYPE_ONE_WAY,
            NO_ADVANCE_PURCHASE,
            SATURDAY_STAY,
            CHANGE_FEES,
            NON_REFUNDABLE,
            NO_STAY_DURATION),
      _parent (NULL)  {
    // That constructor is used by the serialisation process
  }

  // ////////////////////////////////////////////////////////////////////
  FareFeatures::FareFeatures (const FareFeatures& iFeatures)
    : _key (iFeatures.getKey()), _parent (NULL)  {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFeatures::FareFeatures (const Key_T& iKey)
    : _key (iKey), _parent (NULL)  {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFeatures::~FareFeatures () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string FareFeatures::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  bool FareFeatures::
  isTripTypeValid (const TripType_T& iBookingRequestTripType) const {
    bool oIsTripTypeValidFlag = true;

    const TripType_T& lFareTripType = getTripType();
    // Check whether the fare trip type is the same as the booking request
    // trip type
    if (iBookingRequestTripType == lFareTripType) {
      // One way case
      return oIsTripTypeValidFlag;
    }

    if (iBookingRequestTripType == TRIP_TYPE_INBOUND
        || iBookingRequestTripType == TRIP_TYPE_OUTBOUND) {
      // Round trip case
      if (lFareTripType == TRIP_TYPE_ROUND_TRIP) {
        return oIsTripTypeValidFlag;
      }
    }

    oIsTripTypeValidFlag = false;
    return oIsTripTypeValidFlag;
  }

  // ////////////////////////////////////////////////////////////////////
  bool FareFeatures::
  isStayDurationValid (const DayDuration_T& iStayDuration) const {

    // Check if the stay duration is lower or equal to the minimum one.
    const DayDuration_T& lMinimumDayDuration = getMinimumStay();
    if (lMinimumDayDuration > iStayDuration) {
      return false;
    }

    return true;
  }

  // ////////////////////////////////////////////////////////////////////
  bool FareFeatures::
  isAdvancePurchaseValid (const DateTime_T& iBookingRequestDateTime,
                          const DateTime_T& iFlightDateTime) const {
    bool oIsAdvancePurchaseValidFlag = true;

    // Check whether the departure date is within the date range.
    const DayDuration_T& lAdvancedPurchase = getAdvancePurchase();
    const DateOffset_T lMinimumAdvancedPurchase (lAdvancedPurchase);
    const DateTime_T lCriticalDate = iFlightDateTime - lMinimumAdvancedPurchase;
      
    if (lCriticalDate < iBookingRequestDateTime) {
      oIsAdvancePurchaseValidFlag = false;
      return oIsAdvancePurchaseValidFlag;
    }

    return true;
  }
  
}

