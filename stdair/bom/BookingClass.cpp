// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/bom/BookingClass.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClass::BookingClass() : _key (DEFAULT_CLASS_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClass::BookingClass (const BookingClass&)
    : _key (DEFAULT_CLASS_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClass::BookingClass (const Key_T& iKey)
    : _key (iKey), _parent (NULL), _cumulatedProtection (0.0),
      _protection (0.0), _cumulatedBookingLimit (0.0), _au (0.0), _nego (0.0),
      _noShowPercentage (0.0), _cancellationPercentage (0.0),
      _nbOfBookings (0.0), _groupNbOfBookings (0.0),
      _groupPendingNbOfBookings (0.0), _staffNbOfBookings (0.0),
      _wlNbOfBookings (0.0), _nbOfCancellations (0.), _etb (0.0),
      _netClassAvailability (0.0), _segmentAvailability (0.0),
      _netRevenueAvailability (0.0), _yield (0.0), _mean (0.0), _stdDev (0.0) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClass::~BookingClass() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string BookingClass::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClass::sell (const NbOfBookings_T& iNbOfBookings) {
    _nbOfBookings += iNbOfBookings;
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClass::cancel (const NbOfBookings_T& iNbOfCancellations) {
    _nbOfBookings -= iNbOfCancellations;
    _nbOfCancellations += iNbOfCancellations;
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClass::generateDemandSamples (const int& K) {
    _generatedDemandVector.clear();
    if (_stdDev > 0) {
      RandomGeneration lGenerator (DEFAULT_RANDOM_SEED);
      for (int i = 0; i < K; ++i) {
        RealNumber_T lDemandSample = lGenerator.generateNormal (_mean, _stdDev);
        _generatedDemandVector.push_back (lDemandSample);
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClass::generateDemandSamples (const int& K,
                                            const RandomSeed_T& iSeed) {
    _generatedDemandVector.clear();
    if (_stdDev > 0) {
      RandomGeneration lGenerator (iSeed);
      for (int i = 0; i < K; ++i) {
        RealNumber_T lDemandSample = lGenerator.generateNormal (_mean, _stdDev);
        _generatedDemandVector.push_back (lDemandSample);
      }
    }
  }
  
}

