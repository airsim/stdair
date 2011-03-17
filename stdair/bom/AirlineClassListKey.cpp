// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// STDAIR
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/bom/AirlineClassListKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineClassListKey::
  AirlineClassListKey (const AirlineCodeList_T& iAirlineCodeList,
                       const ClassList_StringList_T& iClassCodeList)
    : _airlineCodeList (iAirlineCodeList), _classCodeList (iClassCodeList) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineClassListKey::AirlineClassListKey (const AirlineClassListKey& iKey)
    : _airlineCodeList (iKey._airlineCodeList), _classCodeList (iKey._classCodeList) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineClassListKey::~AirlineClassListKey () {
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
    assert(_airlineCodeList.size() == _classCodeList.size());
    AirlineCodeList_T::const_iterator lItAirlineCode =
      _airlineCodeList.begin();
    for (ClassList_StringList_T::const_iterator lItClassCode =
           _classCodeList.begin();
         lItClassCode != _classCodeList.end();
         lItClassCode++) {
      oStr << *lItAirlineCode << " " << *lItClassCode
           << DEFAULT_KEY_SUB_FLD_DELIMITER << " ";
      lItAirlineCode++;
    }
    oStr << std::endl; 
    return oStr.str();
  }

}
