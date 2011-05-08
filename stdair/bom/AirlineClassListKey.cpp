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
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/AirlineClassListKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineClassListKey::AirlineClassListKey() {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineClassListKey::
  AirlineClassListKey (const AirlineCodeList_T& iAirlineCodeList,
                       const ClassList_StringList_T& iClassCodeList)
    : _airlineCodeList (iAirlineCodeList), _classCodeList (iClassCodeList) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineClassListKey::AirlineClassListKey (const AirlineClassListKey& iKey)
    : _airlineCodeList (iKey._airlineCodeList),
      _classCodeList (iKey._classCodeList) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineClassListKey::~AirlineClassListKey() {
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineClassListKey::toStream (std::ostream& ioOut) const {
    ioOut << "AirlineClassListKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineClassListKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string AirlineClassListKey::toString() const {
    std::ostringstream oStr;
    assert (_airlineCodeList.size() == _classCodeList.size());
    
    unsigned short idx = 0;
    AirlineCodeList_T::const_iterator itAirlineCode = _airlineCodeList.begin();
    for (ClassList_StringList_T::const_iterator itClassCode =
           _classCodeList.begin(); itClassCode != _classCodeList.end();
         ++itClassCode, ++itAirlineCode, ++idx) {
      if (idx != 0) {
        oStr << DEFAULT_KEY_SUB_FLD_DELIMITER << " ";
      }

      const AirlineCode_T& lAirlineCode = *itAirlineCode;
      const ClassCode_T& lClassCode = *itClassCode;
      oStr << lAirlineCode << " " << lClassCode;
    }

    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineClassListKey::serialisationImplementation() {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;

    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void AirlineClassListKey::serialize (Archive& ioArchive,
                                       const unsigned int iFileVersion) {
    /**
     * \note Boost.Serialisation knows how to deal with STL containers
     *       (here, vectors), but not with vectors of std::string
     *       (those must be wrapped within a serializable class).
     *
     *       Moreover, the serialised member should not be const (as,
     *       as far as I understand, they are tracked by Boost.Serialisation).
     */
    AirlineCodeList_T::const_iterator itAirlineCode = _airlineCodeList.begin();
    for (ClassList_StringList_T::const_iterator itClassCode =
           _classCodeList.begin(); itClassCode != _classCodeList.end();
         ++itClassCode, ++itAirlineCode) {
      AirlineCode_T lAirlineCode = *itAirlineCode;
      ClassCode_T lClassCode = *itClassCode;

      ioArchive & lAirlineCode & lClassCode;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  // Explicit template instantiation
  namespace ba = boost::archive;
  template void AirlineClassListKey::
  serialize<ba::text_oarchive> (ba::text_oarchive&, unsigned int);
  template void AirlineClassListKey::
  serialize<ba::text_iarchive> (ba::text_iarchive&, unsigned int);
  // ////////////////////////////////////////////////////////////////////

}
