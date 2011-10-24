// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_ONDDATETYPES_HPP
#define __STDAIR_BOM_ONDDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// Stdair
#include <stdair/bom/key_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_demand_types.hpp>

namespace stdair {

  // Forward declarations.
  class OnDDate;

  /** Define the O&D date list. */
  typedef std::list<OnDDate*> OnDDateList_T;

  /** Define the OnD date map. */
  typedef std::map<const MapKey_T, OnDDate*> OnDDateMap_T;

  /**
   * Define the yield mean and standard deviation for a certain cabin/class path.
   * This map is mandatory when using the default BOM tree.
   * This map can be empty if yields are charged otherwise (input file, ...)
   */
  typedef std::pair<std::string, YieldDemandPair_T> StringDemandStructPair_T;
  typedef std::map<std::string, YieldDemandPair_T> StringDemandStructMap_T;

  /**
   * Define the string matching a (cabin,class) path.
   * (i.e, the string is "Y:M;" for a one leg O&D with the cabin Y and the class M;
   * the string is "Y:M;Y:Y;" for a two legs O&D with the cabin Y and the class M
   * for the first leg, and the cabin Y and the class Y for the second leg).
   */
  typedef std::map<std::string, CabinClassPairList_T> StringCabinClassPairListMap_T;
  typedef std::pair<std::string, CabinClassPairList_T> StringCabinClassPair_T;

  /**
   * Define the WTP mean and standard deviation for a certain cabin code.
   * This information is needed to forecast O&D demand per cabin. 
   */
  typedef std::map<CabinCode_T, WTPDemandPair_T> CabinForecastMap_T;
  typedef std::pair<CabinCode_T, WTPDemandPair_T> CabinForecastPair_T;

}
#endif // __STDAIR_BOM_ONDDATETYPES_HPP
