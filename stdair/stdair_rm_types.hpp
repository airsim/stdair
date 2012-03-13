#ifndef __STDAIR_STDAIR_RM_TYPES_HPP
#define __STDAIR_STDAIR_RM_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// StdAir
#include <stdair/stdair_basic_types.hpp>

namespace stdair {

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

}
#endif // __STDAIR_STDAIR_RM_TYPES_HPP
