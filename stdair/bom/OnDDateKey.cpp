// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost Date-Time
#include <boost/date_time/gregorian/formatters.hpp>
// Boost.Serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/OnDDateKey.hpp>
#include <stdair/bom/BomKeyManager.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/BomDisplay.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  OnDDateKey::OnDDateKey()
    : _fullKeyList (DEFAULT_FULL_KEY_LIST) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  OnDDateKey::OnDDateKey (const FullKeyList_T& iFullKeyList)
    : _fullKeyList (iFullKeyList) {
  }

  // ////////////////////////////////////////////////////////////////////
  OnDDateKey::OnDDateKey (const OnDDateKey& iKey)
    : _fullKeyList (iKey._fullKeyList) {
  }

  // ////////////////////////////////////////////////////////////////////
  OnDDateKey::~OnDDateKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  const Date_T OnDDateKey::getDate() const {
    assert(!_fullKeyList.empty());
    FullKey_T lFK = _fullKeyList.front();
    return BomKeyManager::extractFlightDateKey (lFK).getDepartureDate();
  }
  
  // ////////////////////////////////////////////////////////////////////
  const AirportCode_T OnDDateKey::getOrigin() const {
    assert(!_fullKeyList.empty());
    FullKey_T lFK = _fullKeyList.front();
    return BomKeyManager::extractSegmentDateKey (lFK).getBoardingPoint();
  }

  // ////////////////////////////////////////////////////////////////////
  const AirportCode_T OnDDateKey::getDestination() const {
    assert(!_fullKeyList.empty());
    FullKey_T lLK = _fullKeyList.back();
    return BomKeyManager::extractSegmentDateKey (lLK).getOffPoint();
  }
  
  // ////////////////////////////////////////////////////////////////////
  void OnDDateKey::toStream (std::ostream& ioOut) const {
    ioOut << "OnDDateKey: " << toString();
  }

  // ////////////////////////////////////////////////////////////////////
  void OnDDateKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string OnDDateKey::toString() const {
    std::ostringstream oStr;
    for (FullKeyList_T::const_iterator itKL = _fullKeyList.begin();
         itKL != _fullKeyList.end(); ++itKL){
      oStr << *itKL << " ";
    }
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void OnDDateKey::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void OnDDateKey::serialize (Archive& ioArchive,
                              const unsigned int iFileVersion) {
    /**
     * \note The serialised member should not be const (as, as far as
     *       I understand, they are tracked by Boost.Serialisation).
     */
    
  }

  // ////////////////////////////////////////////////////////////////////
  // Explicit template instantiation
  namespace ba = boost::archive;
  template void OnDDateKey::serialize<ba::text_oarchive> (ba::text_oarchive&,
                                                             unsigned int);
  template void OnDDateKey::serialize<ba::text_iarchive> (ba::text_iarchive&,
                                                             unsigned int);
  // ////////////////////////////////////////////////////////////////////
  
}
