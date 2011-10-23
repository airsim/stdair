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
    : _key (DEFAULT_FULL_KEY_LIST), _parent (NULL) {
    // That constructor is used by the serialisation process
  }
  
  // ////////////////////////////////////////////////////////////////////
  OnDDate::OnDDate (const OnDDate&)
    : _key (DEFAULT_FULL_KEY_LIST), _parent (NULL) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  OnDDate::OnDDate (const Key_T& iKey) : _key (iKey), _parent (NULL) {
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
                        const Yield_T& iYield,
                        const MeanValue_T& iMean,
                        const StdDevValue_T& iStdDev) {    
    std::ostringstream oStr;
    for(CabinClassPairList_T::const_iterator itCCP = iCabinClassPairList.begin();
        itCCP != iCabinClassPairList.end(); ++itCCP) {
      oStr << itCCP->first << ":" << itCCP->second << ";";
    }
    std::string lCabinClassPath = oStr.str();
    std::map<std::string, DemandStruct>::iterator it =
      _classPathDemandMap.find(lCabinClassPath);
    if (it == _classPathDemandMap.end()) {
      const DemandStruct lDemandStruct (iYield, iMean, iStdDev);
      _classPathDemandMap.insert (std::pair<std::string,DemandStruct> (lCabinClassPath, lDemandStruct));
      _stringCabinClassPairListMap.insert (std::pair<std::string, CabinClassPairList_T> (lCabinClassPath,
                                                                                         iCabinClassPairList));
    } else {
      it->second.setYield (iYield);
      it->second.setDemandMean (iMean);
      it->second.setDemandStdDev (iStdDev);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void OnDDate::setTotalForecast (const CabinCode_T& iCabinCode,
                                  const WTP_T& iMinWTP,
                                  const MeanValue_T& iMean,
                                  const StdDevValue_T& iStdDev){

    CabinForecastMap_T::iterator it =
      _cabinForecastMap.find (iCabinCode);
    if (it == _cabinForecastMap.end()) {
      const ForecastStruct lForecastStruct (iMinWTP, iMean, iStdDev);
      _cabinForecastMap.insert (std::pair<CabinCode_T,ForecastStruct> (iCabinCode,lForecastStruct));
    } else {
      assert (false);
    }
  }
  
}
