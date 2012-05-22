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
#include <stdair/bom/NestingStructureKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  NestingStructureKey::NestingStructureKey() : _nestingStructureCode (DEFAULT_NESTING_STRUCTURE_CODE) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  NestingStructureKey::NestingStructureKey (const NestingStructureKey& iNestingStructureKey)
    : _nestingStructureCode (iNestingStructureKey._nestingStructureCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  NestingStructureKey::NestingStructureKey (const NestingStructureCode_T& iNestingStructureCode)
    : _nestingStructureCode (iNestingStructureCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  NestingStructureKey::~NestingStructureKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void NestingStructureKey::toStream (std::ostream& ioOut) const {
    ioOut << "NestingStructureKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void NestingStructureKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string NestingStructureKey::toString() const {
    std::ostringstream oStr;
    oStr << _nestingStructureCode;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void NestingStructureKey::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void NestingStructureKey::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void NestingStructureKey::serialize (Archive& ioArchive,
                                   const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    ioArchive & _nestingStructureCode;
  }

  // ////////////////////////////////////////////////////////////////////
  // Explicit template instantiation
  namespace ba = boost::archive;
  template void NestingStructureKey::serialize<ba::text_oarchive> (ba::text_oarchive&,
                                                             unsigned int);
  template void NestingStructureKey::serialize<ba::text_iarchive> (ba::text_iarchive&,
                                                             unsigned int);
  // ////////////////////////////////////////////////////////////////////

}
