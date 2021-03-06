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
#include <stdair/service/Logger.hpp>
#include <stdair/bom/AirlineClassList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineClassList::AirlineClassList()
    : _key (DEFAULT_AIRLINE_CODE_LIST, DEFAULT_CLASS_CODE_LIST),
      _parent (NULL)  {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineClassList::AirlineClassList (const AirlineClassList& iACL)
    : _key (iACL._key),
      _parent (NULL),
      _yield(iACL._yield),
      _fare(iACL._fare) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineClassList::AirlineClassList (const Key_T& iKey)
    : _key (iKey), _parent (NULL)  {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineClassList::~AirlineClassList() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string AirlineClassList::toString() const {
    std::ostringstream oStr;
    oStr << describeKey() << ", " << _yield <<  ", " << _fare;
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineClassList::serialisationImplementationExport() const {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << *this;
  }

  // ////////////////////////////////////////////////////////////////////
  void AirlineClassList::serialisationImplementationImport() {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> *this;
  }

  // ////////////////////////////////////////////////////////////////////
  template<class Archive>
  void AirlineClassList::serialize (Archive& ioArchive,
                                    const unsigned int iFileVersion) {
    ioArchive & _key & _yield & _fare;
  }

}



