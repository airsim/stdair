// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost
#include <boost/multi_array.hpp>
// Boost.Serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/GuillotineBlock.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  GuillotineBlock::GuillotineBlock()
    : _key (DEFAULT_GUILLOTINE_NUMBER), _parent (NULL) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  GuillotineBlock::GuillotineBlock (const GuillotineBlock&)
    : _key (DEFAULT_GUILLOTINE_NUMBER), _parent (NULL) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  GuillotineBlock::
  GuillotineBlock (const Key_T& iKey) : _key (iKey), _parent (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  GuillotineBlock::~GuillotineBlock() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string GuillotineBlock::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void GuillotineBlock::
  initSnapshotBlocks (const SegmentCabinIndexMap_T& iSegmentCabinIndexMap,
                      const ValueTypeIndexMap_T& iValueTypeIndexMap) {
    _segmentCabinIndexMap = iSegmentCabinIndexMap;
    _valueTypesIndexMap = iValueTypeIndexMap;

    unsigned int lNumberOfSegmentCabins = _segmentCabinIndexMap.size();
    unsigned int lNumberOfValueTypes = _valueTypesIndexMap.size();

    // Initialise the snapshot blocks
    _bookingSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfValueTypes]
              [DEFAULT_MAX_DTD + 1]);

  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T GuillotineBlock::
  getConstSegmentCabinDTDBookingSnapshotView (const BlockNumber_T iSCIdxBegin,
                                              const BlockNumber_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _bookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T GuillotineBlock::
  getConstSegmentCabinDTDRangeBookingSnapshotView
  (const BlockNumber_T iSCIdxBegin, const BlockNumber_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd +1) * lNbOfValueTypes;

    return _bookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T GuillotineBlock::
  getSegmentCabinDTDBookingSnapshotView (const BlockNumber_T iSCIdxBegin,
                                         const BlockNumber_T iSCIdxEnd,
                                         const DTD_T iDTD) {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _bookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T GuillotineBlock::
  getSegmentCabinDTDRangeBookingSnapshotView (const BlockNumber_T iSCIdxBegin,
                                              const BlockNumber_T iSCIdxEnd,
                                              const DTD_T iDTDBegin,
                                              const DTD_T iDTDEnd) {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _bookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  void GuillotineBlock::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void GuillotineBlock::serialize (Archive& ioArchive,
                                   const unsigned int iFileVersion) {
    ioArchive & _key;
  }

}

