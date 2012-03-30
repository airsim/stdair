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
#include <stdair/bom/SegmentSnapshotTable.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentSnapshotTable::SegmentSnapshotTable()
    : _key (DEFAULT_TABLE_ID), _parent (NULL) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentSnapshotTable::SegmentSnapshotTable (const SegmentSnapshotTable&)
    : _key (DEFAULT_TABLE_ID), _parent (NULL) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentSnapshotTable::
  SegmentSnapshotTable (const Key_T& iKey) : _key (iKey), _parent (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentSnapshotTable::~SegmentSnapshotTable() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentSnapshotTable::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentSnapshotTable::
  initSnapshotBlocks (const SegmentCabinIndexMap_T& iSegmentCabinIndexMap,
                      const ClassIndexMap_T& iClassIndexMap) {
    _segmentCabinIndexMap = iSegmentCabinIndexMap;
    _classIndexMap = iClassIndexMap;

    unsigned int lNumberOfSegmentCabins = _segmentCabinIndexMap.size();
    unsigned int lNumberOfClasses = _classIndexMap.size();

    // Initialise the snapshot blocks
    // Normally, the block includes snapshots from DTD MAX to DTD 0, thus
    // DEFAULT_MAX_DTD + 1 values. However, we would like to add the day
    // before DTD MAX (this value will be initialised to zero).
    _bookingSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfClasses]
              [DEFAULT_MAX_DTD + 2]);
    _cancellationSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfClasses]
              [DEFAULT_MAX_DTD + 2]);
    _productOrientedNetBookingSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfClasses]
              [DEFAULT_MAX_DTD + 2]);
    _priceOrientedNetBookingSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfClasses]
              [DEFAULT_MAX_DTD + 2]);
    _productOrientedGrossBookingSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfClasses]
              [DEFAULT_MAX_DTD + 2]);
    _priceOrientedGrossBookingSnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfClasses]
              [DEFAULT_MAX_DTD + 2]);
    _availabilitySnapshotBlock.
      resize (boost::extents[lNumberOfSegmentCabins*lNumberOfClasses]
              [DEFAULT_MAX_DTD + 2]);

  }

  // ////////////////////////////////////////////////////////////////////
  const ClassIndex_T& SegmentSnapshotTable::
  getClassIndex (const MapKey_T& iKey) const {
    ClassIndexMap_T::const_iterator itVTIdx =
      _classIndexMap.find (iKey);
    assert (itVTIdx != _classIndexMap.end());
    return itVTIdx->second;
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentDataID_T& SegmentSnapshotTable::
  getSegmentDataID (const SegmentCabin& iSegmentCabin) const {
    SegmentCabinIndexMap_T::const_iterator itSCIdx =
      _segmentCabinIndexMap.find (&iSegmentCabin);
    assert (itSCIdx != _segmentCabinIndexMap.end());
    return itSCIdx->second;
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _bookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDRangeBookingSnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd +1) * lNbOfClasses;

    return _bookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                         const SegmentDataID_T iSCIdxEnd,
                                         const DTD_T iDTD) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _bookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDRangeBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTDBegin,
                                              const DTD_T iDTDEnd) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _bookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDCancellationSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _cancellationSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDRangeCancellationSnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd +1) * lNbOfClasses;

    return _cancellationSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDCancellationSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                         const SegmentDataID_T iSCIdxEnd,
                                         const DTD_T iDTD) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _cancellationSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDRangeCancellationSnapshotView(const SegmentDataID_T iSCIdxBegin,
                                                  const SegmentDataID_T iSCIdxEnd,
                                                  const DTD_T iDTDBegin,
                                                  const DTD_T iDTDEnd) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _cancellationSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDProductOrientedNetBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _productOrientedNetBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDRangeProductOrientedNetBookingSnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd +1) * lNbOfClasses;

    return _productOrientedNetBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDProductOrientedNetBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                         const SegmentDataID_T iSCIdxEnd,
                                         const DTD_T iDTD) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _productOrientedNetBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDRangeProductOrientedNetBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTDBegin,
                                              const DTD_T iDTDEnd) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _productOrientedNetBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }


  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDPriceOrientedNetBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _priceOrientedNetBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDRangePriceOrientedNetBookingSnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd +1) * lNbOfClasses;

    return _priceOrientedNetBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDPriceOrientedNetBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                         const SegmentDataID_T iSCIdxEnd,
                                         const DTD_T iDTD) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _priceOrientedNetBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDRangePriceOrientedNetBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTDBegin,
                                              const DTD_T iDTDEnd) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _priceOrientedNetBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

    // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDProductOrientedGrossBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _productOrientedGrossBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDRangeProductOrientedGrossBookingSnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd +1) * lNbOfClasses;

    return _productOrientedGrossBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDProductOrientedGrossBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                         const SegmentDataID_T iSCIdxEnd,
                                         const DTD_T iDTD) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _productOrientedGrossBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDRangeProductOrientedGrossBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTDBegin,
                                              const DTD_T iDTDEnd) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _productOrientedGrossBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }


  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDPriceOrientedGrossBookingSnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTD) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _priceOrientedGrossBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDRangePriceOrientedGrossBookingSnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd +1) * lNbOfClasses;

    return _priceOrientedGrossBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDPriceOrientedGrossBookingSnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTD) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _priceOrientedGrossBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDRangePriceOrientedGrossBookingSnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _priceOrientedGrossBookingSnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }
  
  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDAvailabilitySnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTD) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _availabilitySnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  ConstSegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getConstSegmentCabinDTDRangeAvailabilitySnapshotView
  (const SegmentDataID_T iSCIdxBegin, const SegmentDataID_T iSCIdxEnd,
   const DTD_T iDTDBegin, const DTD_T iDTDEnd) const {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd +1) * lNbOfClasses;

    return _availabilitySnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDAvailabilitySnapshotView (const SegmentDataID_T iSCIdxBegin,
                                              const SegmentDataID_T iSCIdxEnd,
                                              const DTD_T iDTD) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _availabilitySnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][iDTD] ];
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinDTDRangeSnapshotView_T SegmentSnapshotTable::
  getSegmentCabinDTDRangeAvailabilitySnapshotView(const SegmentDataID_T iSCIdxBegin,
                                                  const SegmentDataID_T iSCIdxEnd,
                                                  const DTD_T iDTDBegin,
                                                  const DTD_T iDTDEnd) {
    const unsigned int lNbOfClasses = _classIndexMap.size();
    const unsigned int lClassIdxBegin = iSCIdxBegin * lNbOfClasses;
    const unsigned int lClassIdxEnd = (iSCIdxEnd + 1) * lNbOfClasses;

    return _availabilitySnapshotBlock [ boost::indices[SnapshotBlockRange_T(lClassIdxBegin, lClassIdxEnd)][SnapshotBlockRange_T(iDTDBegin, iDTDEnd + 1)] ];
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentSnapshotTable::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentSnapshotTable::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void SegmentSnapshotTable::serialize (Archive& ioArchive,
                                   const unsigned int iFileVersion) {
    ioArchive & _key;
  }

}

