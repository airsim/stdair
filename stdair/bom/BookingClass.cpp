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
  BookingClass::BookingClass (const Key_T& iKey) : _key (iKey), _parent (NULL) {
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

