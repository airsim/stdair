// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost.Serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory() : _key (DEFAULT_AIRLINE_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const Inventory&)
    : _key (DEFAULT_AIRLINE_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  Inventory::Inventory (const Key_T& iKey) : _key (iKey), _parent (NULL) {
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
  void Inventory::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void Inventory::serialize (Archive& ioArchive,
                             const unsigned int iFileVersion) {
    ioArchive & _key;
  }

}

