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
#include <stdair/bom/LegCabinKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegCabinKey::LegCabinKey() : _cabinCode (DEFAULT_CABIN_CODE) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinKey::LegCabinKey (const CabinCode_T& iCabinCode)
    : _cabinCode (iCabinCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinKey::LegCabinKey (const LegCabinKey& iKey)
    : _cabinCode (iKey._cabinCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinKey::~LegCabinKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void LegCabinKey::toStream (std::ostream& ioOut) const {
    ioOut << "LegCabinKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void LegCabinKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string LegCabinKey::toString() const {
    std::ostringstream oStr;
    oStr << _cabinCode;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void LegCabinKey::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void LegCabinKey::serialize (Archive& ioArchive,
                               const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    ioArchive & _cabinCode;
  }

}
