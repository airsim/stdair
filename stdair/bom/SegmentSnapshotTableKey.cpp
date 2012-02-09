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
#include <stdair/bom/SegmentSnapshotTableKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentSnapshotTableKey::SegmentSnapshotTableKey()
    : _tableID (DEFAULT_TABLE_ID) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentSnapshotTableKey::
  SegmentSnapshotTableKey (const TableID_T& iTableID)
    : _tableID (iTableID) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentSnapshotTableKey::SegmentSnapshotTableKey (const SegmentSnapshotTableKey& iKey)
    : _tableID (iKey._tableID) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentSnapshotTableKey::~SegmentSnapshotTableKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentSnapshotTableKey::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentSnapshotTableKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentSnapshotTableKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentSnapshotTableKey::toString() const {
    std::ostringstream oStr;
    oStr << _tableID;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentSnapshotTableKey::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentSnapshotTableKey::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void SegmentSnapshotTableKey::serialize (Archive& ioArchive,
                                 const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    ioArchive & _tableID;
  }

  // ////////////////////////////////////////////////////////////////////
  // Explicit template instantiation
  namespace ba = boost::archive;
  template void SegmentSnapshotTableKey::
  serialize<ba::text_oarchive> (ba::text_oarchive&, unsigned int);
  template void SegmentSnapshotTableKey::
  serialize<ba::text_iarchive> (ba::text_iarchive&, unsigned int);
  // ////////////////////////////////////////////////////////////////////

}
