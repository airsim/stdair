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
#include <stdair/bom/NestingNodeKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  NestingNodeKey::NestingNodeKey() : _nestingNodeCode (DEFAULT_POLICY_CODE) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  NestingNodeKey::NestingNodeKey (const NestingNodeKey& iNestingNodeKey)
    : _nestingNodeCode (iNestingNodeKey._nestingNodeCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  NestingNodeKey::NestingNodeKey (const NestingNodeCode_T& iNestingNodeCode)
    : _nestingNodeCode (iNestingNodeCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  NestingNodeKey::~NestingNodeKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void NestingNodeKey::toStream (std::ostream& ioOut) const {
    ioOut << "NestingNodeKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void NestingNodeKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string NestingNodeKey::toString() const {
    std::ostringstream oStr;
    oStr << _nestingNodeCode;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void NestingNodeKey::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void NestingNodeKey::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void NestingNodeKey::serialize (Archive& ioArchive,
                                   const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    ioArchive & _nestingNodeCode;
  }

  // ////////////////////////////////////////////////////////////////////
  // Explicit template instantiation
  namespace ba = boost::archive;
  template void NestingNodeKey::serialize<ba::text_oarchive> (ba::text_oarchive&,
                                                             unsigned int);
  template void NestingNodeKey::serialize<ba::text_iarchive> (ba::text_iarchive&,
                                                             unsigned int);
  // ////////////////////////////////////////////////////////////////////

}
