// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
#include <boost/math/distributions/normal.hpp>
#endif // BOOST_VERSION >= 103500
// StdAir
#include <stdair/basic/RandomGeneration.hpp>

namespace stdair {
  
  /**
   * \note As per Boost bug #3516 (https://svn.boost.org/trac/boost/ticket/3516)
   *       the seed should not be set to 0 (at least on versions of Boost
   *       lower than 1.44).
   */
  // //////////////////////////////////////////////////////////////////////
  RandomGeneration::RandomGeneration() : _seed (1), _generator (1) {
  }

  // //////////////////////////////////////////////////////////////////////
  RandomGeneration::RandomGeneration (const RandomSeed_T& iSeed)
    : _seed (iSeed), _generator (iSeed) {
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  RandomGeneration::RandomGeneration (const RandomGeneration& iRandomGeneration)
    : _seed (iRandomGeneration._seed),
      _generator (iRandomGeneration._generator) {
  }

  // //////////////////////////////////////////////////////////////////////
  RandomGeneration::~RandomGeneration() {
  }

  // //////////////////////////////////////////////////////////////////////
  void RandomGeneration::init() {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string RandomGeneration::describe() const {
    std::ostringstream oStr;
    oStr << _seed << ", " << _generator;
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  RealNumber_T RandomGeneration::generateUniform01() {
    UniformGenerator_T lGenerator (_generator, boost::uniform_real<>(0, 1));
    return lGenerator();
  }
  
  // //////////////////////////////////////////////////////////////////////
  RealNumber_T RandomGeneration::generateUniform(const RealNumber_T& iMinValue,
                                                 const RealNumber_T& iMaxValue) {
    const Probability_T lVariateUnif01 = generateUniform01();
    const RealNumber_T lVariateUnif =
      iMinValue + lVariateUnif01 * (iMaxValue - iMinValue);
    return lVariateUnif;
  }

  // //////////////////////////////////////////////////////////////////////
  RealNumber_T RandomGeneration::generateNormal (const RealNumber_T& mu,
                                                 const RealNumber_T& sigma) {
#if BOOST_VERSION >= 103500
    const Probability_T lVariateUnif = generateUniform01();
    const boost::math::normal lNormal (mu, sigma);
    const RealNumber_T lRealNumberOfRequestsToBeGenerated =
      boost::math::quantile (lNormal, lVariateUnif);
#else // BOOST_VERSION >= 103500
    // TODO: rely on GSL when Boost version smaller than 1.35
    const RealNumber_T lRealNumberOfRequestsToBeGenerated = 0.0;
#endif // BOOST_VERSION >= 103500

    return lRealNumberOfRequestsToBeGenerated;
  }
}
