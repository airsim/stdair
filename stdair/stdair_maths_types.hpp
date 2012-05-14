#ifndef __STDAIR_STDAIR_MATHS_TYPES_HPP
#define __STDAIR_STDAIR_MATHS_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
#include <map>
// Boost Random
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/variate_generator.hpp>

namespace stdair {

  // //////// Type definitions /////////
  /**
   * Define the replication number.
   */
  typedef unsigned int ReplicationNumber_T;

  /**
   * Define the seed type of an Exponential function.
   */
  typedef unsigned long int ExponentialSeed_T;

  /**
   * Define the seed type of an Uniform function.
   */
  typedef unsigned long int UniformSeed_T;

  /**
   * Seed for the random generation, so that it can be reproductible.
   */
  typedef unsigned long int RandomSeed_T;
  
  /**
   * Random number generator.
   */
  typedef boost::minstd_rand BaseGenerator_T;

  /**
   * Uniform distribution of real numbers (by default, double).
   */
  typedef boost::uniform_real<> UniformDistribution_T;

  /**
   * Uniform random generator.
   */
  typedef boost::variate_generator<BaseGenerator_T&,
                                   UniformDistribution_T> UniformGenerator_T;

  /**
   * Normal distribution of real numbers (by default, double).
   */
  typedef boost::normal_distribution<> NormalDistribution_T;

  /**
   * Nornal random generator.
   */
  typedef boost::variate_generator<BaseGenerator_T&,
                                   NormalDistribution_T> NormalGenerator_T;

  /** Type definiton for the exponential distribution (characteristics). */
  typedef boost::exponential_distribution<> ExponentialDistribution_T;


  /** Type definition for the exponential distribution random generator. */
  typedef boost::variate_generator<BaseGenerator_T&,
                                   ExponentialDistribution_T> ExponentialGenerator_T;

  /**
   * Define a mean value (e.g., 20.2).
   */
  typedef double MeanValue_T;

  /**
   * Define a standard deviation value (e.g., 1.5).
   */
  typedef double StdDevValue_T;

  /**
   * Define a couple (mean, standart deviation) (e.g., (20.2,1.5)).
   */
  typedef std::pair<MeanValue_T, StdDevValue_T> MeanStdDevPair_T;

  /**
   * Define a vector of couple (mean, standart deviation)
   */ 
  typedef std::vector<MeanStdDevPair_T> MeanStdDevPairVector_T;

  /**
   * Probability.
   */
  typedef float Probability_T; 
  
}
#endif // __STDAIR_STDAIR_MATHS_TYPES_HPP
