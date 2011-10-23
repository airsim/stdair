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
#include <stdair/bom/SegmentDateKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey::SegmentDateKey()
    : _boardingPoint (DEFAULT_ORIGIN), _offPoint (DEFAULT_DESTINATION) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey::SegmentDateKey (const AirportCode_T& iBoardingPoint,
                                  const AirportCode_T& iOffPoint)
    : _boardingPoint (iBoardingPoint), _offPoint (iOffPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey::SegmentDateKey (const SegmentDateKey& iKey)
    : _boardingPoint (iKey._boardingPoint), _offPoint (iKey._offPoint) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateKey::~SegmentDateKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDateKey::toStream (std::ostream& ioOut) const {
    ioOut << "SegmentDateKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDateKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentDateKey::toString() const {
    std::ostringstream oStr;
    oStr << _boardingPoint << "." << _offPoint;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDateKey::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void SegmentDateKey::serialize (Archive& ioArchive,
                                 const unsigned int iFileVersion) {
    ioArchive & _boardingPoint & _offPoint;
  }

}
