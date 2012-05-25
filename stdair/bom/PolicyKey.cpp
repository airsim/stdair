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
#include <stdair/bom/PolicyKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  PolicyKey::PolicyKey() : _policyCode (DEFAULT_POLICY_CODE) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  PolicyKey::PolicyKey (const PolicyKey& iPolicyKey)
    : _policyCode (iPolicyKey._policyCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  PolicyKey::PolicyKey (const PolicyCode_T& iPolicyCode)
    : _policyCode (iPolicyCode) {
  }

  // ////////////////////////////////////////////////////////////////////
  PolicyKey::~PolicyKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void PolicyKey::toStream (std::ostream& ioOut) const {
    ioOut << "PolicyKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void PolicyKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string PolicyKey::toString() const {
    std::ostringstream oStr;
    oStr << _policyCode;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void PolicyKey::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void PolicyKey::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void PolicyKey::serialize (Archive& ioArchive,
                                   const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    ioArchive & _policyCode;
  }

  // ////////////////////////////////////////////////////////////////////
  // Explicit template instantiation
  namespace ba = boost::archive;
  template void PolicyKey::serialize<ba::text_oarchive> (ba::text_oarchive&,
                                                             unsigned int);
  template void PolicyKey::serialize<ba::text_iarchive> (ba::text_iarchive&,
                                                             unsigned int);
  // ////////////////////////////////////////////////////////////////////

}
