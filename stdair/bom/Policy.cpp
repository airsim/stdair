// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <cassert>
#include <iomanip>
#include <iostream>
//STDAIR
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/Policy.hpp>

namespace stdair {
    
  // ////////////////////////////////////////////////////////////////////
  Policy::Policy () : 
    _key (DEFAULT_POLICY_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  Policy::Policy (const Policy& iPolicy)
  : _key (DEFAULT_POLICY_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  Policy::Policy (const Key_T& iKey) : _key (iKey), _parent (NULL) {
  }
    
  // ////////////////////////////////////////////////////////////////////
  Policy::~Policy() {
  }
    
  // ////////////////////////////////////////////////////////////////////
  std::string Policy::toString () const {
    std::ostringstream oStr;
    oStr << describeKey();
    
    oStr << std::fixed << std::setprecision (2)
         << "; " << _demand  
         << "; " << _stdDev 
         << "; " << _yield << std::endl;
    
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const BookingClassList_T& Policy::getBookingClassList() const {
    return BomManager::getList<BookingClass> (*this);
  }

  // ////////////////////////////////////////////////////////////////////
  const Revenue_T Policy::getTotalRevenue () const {
    Revenue_T oTotalRevenue = 0.0;
    for (YieldDemandMap_T::const_iterator itYD = _yieldDemandMap.begin();
         itYD != _yieldDemandMap.end(); ++itYD) {
      const Yield_T& lYield = itYD->first;
      const double& lDemand = itYD->second;
      oTotalRevenue += lYield*lDemand;
    }

    return oTotalRevenue;
  }

  // ////////////////////////////////////////////////////////////////////
  void Policy::addYieldDemand (const Yield_T& iYield,
                               const NbOfBookings_T& iDemand) {
    YieldDemandMap_T::iterator itYD = _yieldDemandMap.find (iYield);
    if (itYD == _yieldDemandMap.end()) {
        bool insert = _yieldDemandMap.insert (YieldDemandMap_T::value_type
                                              (iYield, iDemand)).second;
        assert (insert == true);
    } else {
      NbOfBookings_T& lDemand = itYD->second;
      lDemand += iDemand;
    }
  }
  
}
