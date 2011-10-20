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
    : _OnDStringList (DEFAULT_OND_STRING_LIST) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  OnDDateKey::OnDDateKey (const OnDStringList_T& iOnDStringList)
    : _OnDStringList (iOnDStringList) {
  }

  // ////////////////////////////////////////////////////////////////////
  OnDDateKey::OnDDateKey (const OnDDateKey& iKey)
    : _OnDStringList (iKey._OnDStringList) {
  }

  // ////////////////////////////////////////////////////////////////////
  OnDDateKey::~OnDDateKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  const Date_T OnDDateKey::getDate() const {
    assert(!_OnDStringList.empty());
    OnDString_T lFrontOnDString = _OnDStringList.front();
    return BomKeyManager::extractFlightDateKey (lFrontOnDString).getDepartureDate();
  }
  
  // ////////////////////////////////////////////////////////////////////
  const AirportCode_T OnDDateKey::getOrigin() const {
    assert(!_OnDStringList.empty());
    OnDString_T lFrontOnDString = _OnDStringList.front();
    return BomKeyManager::extractSegmentDateKey (lFrontOnDString).getBoardingPoint();
  }

  // ////////////////////////////////////////////////////////////////////
  const AirportCode_T OnDDateKey::getDestination() const {
    assert(!_OnDStringList.empty());
    OnDString_T lLastOnDString = _OnDStringList.back();
    return BomKeyManager::extractSegmentDateKey (lLastOnDString).getOffPoint();
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
    for (OnDStringList_T::const_iterator itOnDString = _OnDStringList.begin();
         itOnDString != _OnDStringList.end(); ++itOnDString){
      oStr << *itOnDString << " ";
    }
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void OnDDateKey::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void OnDDateKey::serialisationImplementationImport() {
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
