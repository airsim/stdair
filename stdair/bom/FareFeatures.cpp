// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/FareFeatures.hpp>

namespace stdair {

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
  IsTripTypeValid (const stdair::TripType_T& iBookingRequestTripType) const {

    const stdair::TripType_T& lFareTripType = getTripType ();
    // Check if the fare trip type is the same as the booking request trip type.
    if (iBookingRequestTripType == lFareTripType) {
      // One way case.
      return true;
    } else if (iBookingRequestTripType == "RI" ||
               iBookingRequestTripType == "RO") {
      // Round trip case.
      if (lFareTripType == "RT") {
        return true;
      } else {
        return false;
      }
    }
    return false;
  }

  // ////////////////////////////////////////////////////////////////////
  bool FareFeatures::
  IsStayDurationValid (const stdair::DayDuration_T& iStayDuration) const {

    // Check if the stay duration is lower or equal to the minimum one.
    const stdair::DayDuration_T& lMinimumDayDuration = getMinimumStay ();
    if (lMinimumDayDuration > iStayDuration) {
      return false;
    }

    return true;
  }

  // ////////////////////////////////////////////////////////////////////
  bool FareFeatures::
  IsAdvancePurchaseValid (const stdair::DateTime_T& iBookingRequestDateTime,
                          const stdair::DateTime_T& iFlightDateTime) const {

    // Check if the departure date is within the date range.
    long lAdvancedPurchase = getAdvancePurchase ();
    const stdair::DateOffset_T lMinimumAdvancedPurchase(lAdvancedPurchase);
    const stdair::DateTime_T& lCriticalDate = iFlightDateTime - lMinimumAdvancedPurchase;
      
    if (lCriticalDate < iBookingRequestDateTime) {
       return false;
     }

    return true;
  }
  
}

