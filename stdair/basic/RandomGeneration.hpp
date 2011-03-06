#ifndef __STDAIR_BAS_RANDOMGENERATION_HPP
#define __STDAIR_BAS_RANDOMGENERATION_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Random
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /**
   * @brief Class holding a random generator.
   */
  struct RandomGeneration : public StructAbstract {
  public:
    // //////////// Business Methods /////////////
    /**
     * Generate a randomised number following a uniform distribution
     * between 0 (included) and 1 (excluded).
     */
    RealNumber_T generateUniform01();

    /**
     * Same as generateUniform01(). That operator is provided for
     * convenient reasons.
     */
    RealNumber_T operator()() {
      return generateUniform01();
    }
    
    /**
     * Generate a randomized number following a uniform distribution
     * between a minimum (included) and a maximum (excluded)
     * value.
     */
    RealNumber_T generateUniform (const RealNumber_T&, const RealNumber_T&);
    
    /**
     * Generate a randomized number following a normal distribution
     * specified by a mean and a standard deviation.
     */
    RealNumber_T generateNormal (const RealNumber_T&, const RealNumber_T&);
    

  public:
    // ////////////// Display Support Methods //////////
    /**
     * Give a description of the structure (for display purposes).
     */
    const std::string describe() const;


  public:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    RandomGeneration (const RandomSeed_T&);
    /**
     * Default constructor.
     */
    RandomGeneration();
    /**
     * Copy constructor.
     */
    RandomGeneration (const RandomGeneration&);
    /**
     * Copy operator.
     */
    RandomGeneration& operator= (const RandomGeneration& iRandomGeneration) {
      _seed = iRandomGeneration._seed;
      _generator = iRandomGeneration._generator;
      return *this;
    }      

    /**
     * Destructor.
     */
    ~RandomGeneration();

    /**
     * Initialise the random generator.
     *
     * A uniform random number distribution is defined, which
     * produces "real" values between 0 and 1 (0 inclusive, 1
     * exclusive).
     */
    void init();

    // ////////// Attributes //////////
    /**
     * The seed of the random generator.
     *
     * The seed is unsigned, otherwise the wrong overload may be
     * selected when using mt19937 as the boost::base_generator_type.
     */
    RandomSeed_T _seed;

    /**
     * Random number generator engine.
     *
     * The random number generator is currently based on boost::minstd_rand.
     * Alternates are boost::mt19937, boost::ecuyer1988.
     */
    BaseGenerator_T _generator;
  };

}
#endif // __STDAIR_BAS_RANDOMGENERATION_HPP
