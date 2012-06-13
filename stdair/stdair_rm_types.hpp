#ifndef __STDAIR_STDAIR_RM_TYPES_HPP
#define __STDAIR_STDAIR_RM_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
#include <map>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_inventory_types.hpp>

namespace stdair {
  // Forward declarations.
  class BookingClass;

  // //////// Type definitions /////////
  /** Mode of the forecaster. */
  typedef std::string ForecasterMode_T;

  /** Limit of similar flight-dates used in the forecaster. */
  typedef short HistoricalDataLimit_T;

  /** Mode of the forecaster. */
  typedef std::string OptimizerMode_T;

  /** Define the demand for a policy. */
  typedef NbOfBookings_T PolicyDemand_T;

  /** Define the vector of generated demand (for MC integration use).
      <br> It is a vector of double. */
  typedef std::vector<double> GeneratedDemandVector_T;

  /** Define the holder of the generated demand vectors. */
  typedef std::vector<GeneratedDemandVector_T> GeneratedDemandVectorHolder_T;

  /** Define the sellup probability.*/
  typedef double SellupProbability_T;
  
    /** Define the vector of historical unconstrained demand. */
  typedef std::vector<NbOfRequests_T> UncDemVector_T;
  
    /** Define the vector of historical bookings. */
  typedef std::vector<NbOfBookings_T> BookingVector_T;

  /** Define the FRAT5 coefficient. */
  typedef double FRAT5_T;

  /** Define the FRAT5 curve. */
  typedef std::map<const DTD_T, FRAT5_T> FRAT5Curve_T;

  /** Define the fare family disutility curve. */
  typedef std::map<const DTD_T, double> FFDisutilityCurve_T;

  /** Define the sell-up factor curve. */
  typedef std::map<const DTD_T, double> SellUpCurve_T;

  /** Define the dispatching factor curve. */
  typedef std::map<const DTD_T, double> DispatchingCurve_T;

  /** Define the map between class and sell-up factor curve. */
  typedef std::map<BookingClass*, SellUpCurve_T> BookingClassSellUpCurveMap_T;

  /** Define the map between class and dispatching factor curve. */
  typedef std::map<BookingClass*, DispatchingCurve_T> BookingClassDispatchingCurveMap_T;

  /** Define the map between the yield of a class and the demand forecast
      of this class within a policy. */
  typedef std::map<const Yield_T, double> YieldDemandMap_T;

  /** Define the revenue of a policy */
  typedef double Revenue_T;

  /** Define the number of samples for the generated demand of booking class */
  typedef unsigned int NbOfSamples_T;

}
#endif // __STDAIR_STDAIR_RM_TYPES_HPP
