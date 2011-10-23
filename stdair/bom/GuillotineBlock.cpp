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
    // Normally, the block includes snapshots from DTD MAX to DTD 0, thus
    // DEFAULT_MAX_DTD + 1 values. However, we would like to add the day
    // before DTD MAX (this value will be initialised to zero).
    _bookingSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfValueTypes]
              [DEFAULT_MAX_DTD + 2]);
    _cancellationSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfValueTypes]
              [DEFAULT_MAX_DTD + 2]);
    _productAndPriceOrientedBookingSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfValueTypes]
              [DEFAULT_MAX_DTD + 2]);
    _availabilitySnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfValueTypes]
              [DEFAULT_MAX_DTD + 2]);

  }

  // ////////////////////////////////////////////////////////////////////
  const BlockIndex_T& GuillotineBlock::
  getBlockIndex (const MapKey_T& iKey) const {
    ValueTypeIndexMap_T::const_iterator itVTIdx =
      _valueTypesIndexMap.find (iKey);
    assert (itVTIdx != _valueTypesIndexMap.end());
    return itVTIdx->second;
  }

  // ////////////////////////////////////////////////////////////////////
  const BlockNumber_T& GuillotineBlock::
  getBlockNumber (const SegmentCabin& iSegmentCabin) const {
    SegmentCabinIndexMap_T::const_iterator itSCIdx =
      _segmentCabinIndexMap.find (&iSegmentCabin);
    assert (itSCIdx != _segmentCabinIndexMap.end());
    return itSCIdx->second;
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
  ConstSegmentCabinDTDSnapshotView_T GuillotineBlock::
  getConstSegmentCabinDTDCancellationSnapshotView (const BlockNumber_T iSCIdxBegin,
                                              const BlockNumber_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _cancellationSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T GuillotineBlock::
  getConstSegmentCabinDTDRangeCancellationSnapshotView
  (const BlockNumber_T iSCIdxBegin, const BlockNumber_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd +1) * lNbOfValueTypes;

    return _cancellationSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T GuillotineBlock::
  getSegmentCabinDTDCancellationSnapshotView (const BlockNumber_T iSCIdxBegin,
                                         const BlockNumber_T iSCIdxEnd,
                                         const DTD_T iDTD) {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _cancellationSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T GuillotineBlock::
  getSegmentCabinDTDRangeCancellationSnapshotView(const BlockNumber_T iSCIdxBegin,
                                                  const BlockNumber_T iSCIdxEnd,
                                                  const DTD_T iDTDBegin,
                                                  const DTD_T iDTDEnd) {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _cancellationSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T GuillotineBlock::
  getConstSegmentCabinDTDProductAndPriceOrientedBookingSnapshotView (const BlockNumber_T iSCIdxBegin,
                                              const BlockNumber_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _productAndPriceOrientedBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T GuillotineBlock::
  getConstSegmentCabinDTDRangeProductAndPriceOrientedBookingSnapshotView
  (const BlockNumber_T iSCIdxBegin, const BlockNumber_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd +1) * lNbOfValueTypes;

    return _productAndPriceOrientedBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T GuillotineBlock::
  getSegmentCabinDTDProductAndPriceOrientedBookingSnapshotView (const BlockNumber_T iSCIdxBegin,
                                         const BlockNumber_T iSCIdxEnd,
                                         const DTD_T iDTD) {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _productAndPriceOrientedBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T GuillotineBlock::
  getSegmentCabinDTDRangeProductAndPriceOrientedBookingSnapshotView (const BlockNumber_T iSCIdxBegin,
                                              const BlockNumber_T iSCIdxEnd,
                                              const DTD_T iDTDBegin,
                                              const DTD_T iDTDEnd) {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _productAndPriceOrientedBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T GuillotineBlock::
  getConstSegmentCabinDTDAvailabilitySnapshotView (const BlockNumber_T iSCIdxBegin,
                                              const BlockNumber_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _availabilitySnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T GuillotineBlock::
  getConstSegmentCabinDTDRangeAvailabilitySnapshotView
  (const BlockNumber_T iSCIdxBegin, const BlockNumber_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd +1) * lNbOfValueTypes;

    return _availabilitySnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T GuillotineBlock::
  getSegmentCabinDTDAvailabilitySnapshotView (const BlockNumber_T iSCIdxBegin,
                                              const BlockNumber_T iSCIdxEnd,
                                              const DTD_T iDTD) {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _availabilitySnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T GuillotineBlock::
  getSegmentCabinDTDRangeAvailabilitySnapshotView(const BlockNumber_T iSCIdxBegin,
                                                  const BlockNumber_T iSCIdxEnd,
                                                  const DTD_T iDTDBegin,
                                                  const DTD_T iDTDEnd) {
    const unsigned int lNbOfValueTypes = _valueTypesIndexMap.size();
    const unsigned int lValueIdxBegin = iSCIdxBegin * lNbOfValueTypes;
    const unsigned int lValueIdxEnd = (iSCIdxEnd + 1) * lNbOfValueTypes;

    return _availabilitySnapshotBlock [ boost::indices[SnapshotBlockRange_T(lValueIdxBegin, lValueIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
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

