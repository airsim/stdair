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

  /** Define the demand characteristics type.*/
  typedef std::pair<Yield_T, MeanStdDevPair_T> DemandCharacteristics_T;

  /** Define the forecast characteristics type.*/
  typedef std::pair<WTP_T, MeanStdDevPair_T> ForecastCharacteristics_T;

  /** Define the <string of (cabin,class) list,demand characteristics> pair and map. */
  typedef std::pair<std::string, DemandCharacteristics_T> StringDemandStructPair_T;
  typedef std::map<std::string, DemandCharacteristics_T> StringDemandStructMap_T;

  /** Define the <cabin code,forecast characteristics> pair and map. */
  typedef std::map<CabinCode_T, ForecastCharacteristics_T> CabinForecastMap_T;
  typedef std::pair<CabinCode_T, ForecastCharacteristics_T> CabinForecastPair_T;

  /** Define the <string of (cabin,class) list, (cabin,class) list> pair and map. */
  typedef std::map<std::string, CabinClassPairList_T> StringCabinClassPairListMap_T;
  typedef std::pair<std::string, CabinClassPairList_T> StringCabinClassPair_T;

}
#endif // __STDAIR_BOM_ONDDATETYPES_HPP
