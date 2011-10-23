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
#include <stdair/bom/FareFamilyKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FareFamilyKey::FareFamilyKey() : _familyCode (DEFAULT_FARE_FAMILY_CODE) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  FareFamilyKey::FareFamilyKey (const FareFamilyKey& iFareFamilyKey)
    : _familyCode (iFareFamilyKey._familyCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFamilyKey::FareFamilyKey (const FamilyCode_T& iFamilyCode)
    : _familyCode (iFamilyCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  FareFamilyKey::~FareFamilyKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFamilyKey::toStream (std::ostream& ioOut) const {
    ioOut << "FareFamilyKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFamilyKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string FareFamilyKey::toString() const {
    std::ostringstream oStr;
    oStr << _familyCode;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFamilyKey::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void FareFamilyKey::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void FareFamilyKey::serialize (Archive& ioArchive,
                                   const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    ioArchive & _familyCode;
  }

  // ////////////////////////////////////////////////////////////////////
  // Explicit template instantiation
  namespace ba = boost::archive;
  template void FareFamilyKey::serialize<ba::text_oarchive> (ba::text_oarchive&,
                                                             unsigned int);
  template void FareFamilyKey::serialize<ba::text_iarchive> (ba::text_iarchive&,
                                                             unsigned int);
  // ////////////////////////////////////////////////////////////////////

}
