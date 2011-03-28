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
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/GuillotineBlockKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  GuillotineBlockKey::GuillotineBlockKey()
    : _guillotineNumber (DEFAULT_GUILLOTINE_NUMBER) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  GuillotineBlockKey::
  GuillotineBlockKey (const GuillotineNumber_T& iGuillotineNumber)
    : _guillotineNumber (iGuillotineNumber) {
  }

  // ////////////////////////////////////////////////////////////////////
  GuillotineBlockKey::GuillotineBlockKey (const GuillotineBlockKey& iKey)
    : _guillotineNumber (iKey._guillotineNumber) {
  }

  // ////////////////////////////////////////////////////////////////////
  GuillotineBlockKey::~GuillotineBlockKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void GuillotineBlockKey::toStream (std::ostream& ioOut) const {
    ioOut << "GuillotineBlockKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void GuillotineBlockKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string GuillotineBlockKey::toString() const {
    std::ostringstream oStr;
    oStr << _guillotineNumber;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void GuillotineBlockKey::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void GuillotineBlockKey::serialize (Archive& ioArchive,
                                 const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    ioArchive & _guillotineNumber;
  }

}
