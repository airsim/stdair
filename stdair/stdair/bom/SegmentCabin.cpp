// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/SegmentCabinStructure.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassList.hpp>
#include <stdair/bom/BookingClassMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::SegmentCabin (BomStructure_T& ioSegmentStructure)
    : _segmentCabinStructure (ioSegmentStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::~SegmentCabin () {
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentCabin::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentCabin::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SegmentCabin::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentCabin::describeKey() const {
    return _segmentCabinStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentCabin::describeShortKey() const {
    return _segmentCabinStructure.describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassList_T SegmentCabin::getBookingClassList () const {
    return _segmentCabinStructure.getChildrenList();
  }

  // //////////////////////////////////////////////////////////////////////
  BookingClassMap_T SegmentCabin::getBookingClassMap () const {
    return _segmentCabinStructure.getChildrenList();
  }
  
}
