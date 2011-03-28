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
  initSnapshotBlocks (const FlightDateIndexMap_T& iFlightDateIndexMap,
                      const ValueTypeIndexMap_T& iValueTypeIndexMap) {
    _flightDateIndexMap = iFlightDateIndexMap;
    _valueTypesIndexMap = iValueTypeIndexMap;

    unsigned int lNumberOfFlightDates = _flightDateIndexMap.size();
    unsigned int lNumberOfValueTypes = _valueTypesIndexMap.size();

    // Initialise the snapshot blocks
    _bookingSnapshotBlock.
      resize (boost::extents[lNumberOfFlightDates*lNumberOfValueTypes][366]);

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

