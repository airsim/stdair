// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost.Serialization
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
//#include <boost/serialization/assume_abstract.hpp>
// StdAir
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomArchive.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  void BomArchive::archive (const BomRoot& iBomRoot) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string BomArchive::archive (const Inventory& iInventory) {
    std::ostringstream oStr;
    boost::archive::text_oarchive oa (oStr);
    oa << iInventory;
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomArchive::restore (const std::string& iArchive,
                            Inventory& ioInventory) {
    std::istringstream iStr;
    boost::archive::text_iarchive ia (iStr);
    ia >> ioInventory;
  }
    
  // ////////////////////////////////////////////////////////////////////
  void BomArchive::archive (const FlightDate& iFlightDate) {
  }
    
}
