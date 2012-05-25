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

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory() :
    _key (DEFAULT_AIRLINE_CODE),
    _parent (NULL),
    _airlineFeature (NULL) {
    // That constructor is used by the serialisation process
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const Inventory& iInventory)
    : _key (iInventory._key),
      _parent (NULL),
      _airlineFeature (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const Key_T& iKey) :
    _key (iKey),
    _parent (NULL),
    _airlineFeature (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::~Inventory() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string Inventory::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* Inventory::
  getFlightDate (const std::string& iFlightDateKeyStr) const {
    FlightDate* oFlightDate_ptr =
      BomManager::getObjectPtr<FlightDate> (*this, iFlightDateKeyStr);
    return oFlightDate_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate* Inventory::
  getFlightDate (const FlightDateKey& iFlightDateKey) const {
    return getFlightDate (iFlightDateKey.toString());
  }

  // ////////////////////////////////////////////////////////////////////
  ForecastingMethod::EN_ForecastingMethod Inventory::
  getForecastingMethod() const {
    if (_airlineFeature == NULL) {
      return DEFAULT_FORECASTING_METHOD.getMethod();
    }
    assert (_airlineFeature != NULL);
    return _airlineFeature->getForecastingMethod();
  }

  // ////////////////////////////////////////////////////////////////////
  UnconstrainingMethod::EN_UnconstrainingMethod Inventory::
  getUnconstrainingMethod() const {
    if (_airlineFeature == NULL) {
      return DEFAULT_UNCONSTRAINING_METHOD.getMethod();
    }
    assert (_airlineFeature != NULL);
    return _airlineFeature->getUnconstrainingMethod();
  }
  
  // ////////////////////////////////////////////////////////////////////
  PreOptimisationMethod::EN_PreOptimisationMethod Inventory::
  getPreOptimisationMethod() const {
    if (_airlineFeature == NULL) {
      return DEFAULT_PREOPTIMISATION_METHOD.getMethod();
      }
    assert (_airlineFeature != NULL);
    return _airlineFeature->getPreOptimisationMethod();
  }
  
  // ////////////////////////////////////////////////////////////////////
  OptimisationMethod::EN_OptimisationMethod Inventory::
  getOptimisationMethod() const {
    if (_airlineFeature == NULL) {
      return DEFAULT_OPTIMISATION_METHOD.getMethod();
      }
    assert (_airlineFeature != NULL);
    return _airlineFeature->getOptimisationMethod();
  }
  
  // ////////////////////////////////////////////////////////////////////
  PartnershipTechnique::EN_PartnershipTechnique Inventory::
  getPartnershipTechnique() const {
    if (_airlineFeature == NULL) {
      return DEFAULT_PARTNERSHIP_TECHNIQUE.getTechnique();
    }
    assert (_airlineFeature != NULL);
    return _airlineFeature->getPartnershipTechnique();
  }

}

