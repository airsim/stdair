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

  /** Define the sellup probability vector.*/
  typedef std::vector<SellupProbability_T> SellupProbabilityVector_T;

  /** Define the holder of sellup factors (used for computing Q-eq bookings)*/
  typedef std::vector<double> SellupFactorHolder_T;
  
    /** Define the vector of historical unconstrained demand. */
  typedef std::vector<NbOfRequests_T> UncDemVector_T;
  
    /** Define the vector of historical bookings. */
  typedef std::vector<NbOfBookings_T> BookingVector_T;

  /** Define the map betweent the booking class and it's corresponding
      unconstrained demand vector. */
  typedef std::map<BookingClass*, UncDemVector_T>BookingClassUncDemVectorMap_T;

  /** Define the map betweent the booking class and it's corresponding
      unconstrained demand. */
  typedef std::map<BookingClass*, NbOfRequests_T>BookingClassUncDemMap_T;

  /** Define the FRAT5 curve. */
  typedef std::map<const DTD_T, double> FRAT5Curve_T;

  /** Define the (cumulative) unconstrained demand curve. */
  typedef std::vector<NbOfRequests_T> UncDemCurve_T;

  /** Define the holder of unconstrained demand curves. */
  typedef std::vector<UncDemCurve_T> UncDemCurveHolder_T;

  /** Define the map between booking class and holder of unconstrained
      demand curve. */
  typedef std::map<BookingClass*, UncDemCurveHolder_T> BookingClassUncDemCurveHolderMap_T;

  /** Define the sell-up factor curve. */
  typedef std::vector<double> SellUpCurve_T;

  /** Define the map between class and sell-up factor curve. */
  typedef std::map<BookingClass*, SellUpCurve_T> BookingClassSellUpCurveMap_T;

}
#endif // __STDAIR_STDAIR_RM_TYPES_HPP
