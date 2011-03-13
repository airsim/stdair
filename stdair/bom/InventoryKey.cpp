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
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/InventoryKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  InventoryKey::InventoryKey() : _airlineCode (DEFAULT_AIRLINE_CODE) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryKey::InventoryKey (const AirlineCode_T& iAirlineCode)
    : _airlineCode (iAirlineCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryKey::InventoryKey (const InventoryKey& iKey)
    : _airlineCode (iKey._airlineCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  InventoryKey::~InventoryKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void InventoryKey::toStream (std::ostream& ioOut) const {
    ioOut << "InventoryKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void InventoryKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string InventoryKey::toString() const {
    std::ostringstream oStr;
    oStr << _airlineCode;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void InventoryKey::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void InventoryKey::serialize (Archive& ioArchive,
                                const unsigned int iFileVersion) {
    ioArchive & _airlineCode;
  }

}
