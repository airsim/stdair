// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/OnDDate.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  OnDDate::OnDDate()
    : _key (DEFAULT_OND_STRING_LIST), _parent (NULL) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  OnDDate::OnDDate (const OnDDate& iOnDDate)
    : _key (iOnDDate.getKey()), _parent (NULL) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  OnDDate::OnDDate (const Key_T& iKey)
  : _key (iKey), _parent (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  OnDDate::~OnDDate() {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string OnDDate::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const AirlineCode_T& OnDDate::getAirlineCode() const {
    const Inventory* lInventory_ptr =
      static_cast<const Inventory*> (getParent());
    assert (lInventory_ptr != NULL);
    return lInventory_ptr->getAirlineCode();
  }

  // ////////////////////////////////////////////////////////////////////
  void OnDDate::
  setDemandInformation (const CabinClassPairList_T& iCabinClassPairList,
                        const YieldDemandPair_T& iYieldDemandPair) {    
    std::ostringstream oStr;
    for(CabinClassPairList_T::const_iterator itCCP = iCabinClassPairList.begin();
        itCCP != iCabinClassPairList.end(); ++itCCP) {
      oStr << itCCP->first << ":" << itCCP->second << ";";
    }
    std::string lCabinClassPath = oStr.str();
    StringDemandStructMap_T::iterator it =
      _classPathDemandMap.find(lCabinClassPath);
    if (it == _classPathDemandMap.end()) {
      const StringDemandStructPair_T lPairStringDemandChar (lCabinClassPath,
                                                            iYieldDemandPair);
      _classPathDemandMap.insert (lPairStringDemandChar);
      const StringCabinClassPair_T lStringCabinClassPair (lCabinClassPath,
                                                          iCabinClassPairList);
      _stringCabinClassPairListMap.insert (lStringCabinClassPair);
    } else {
        it->second = iYieldDemandPair;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void OnDDate::setTotalForecast (const CabinCode_T& iCabinCode,
                                  const WTPDemandPair_T& iWTPDemandPair) {

    CabinForecastMap_T::iterator it =
      _cabinForecastMap.find (iCabinCode);
    if (it == _cabinForecastMap.end()) {
      const CabinForecastPair_T lPairCabinForecastChar (iCabinCode,
                                                        iWTPDemandPair);
      _cabinForecastMap.insert (lPairCabinForecastChar);
    } else {
      assert (false);
    }
  }
  
}
