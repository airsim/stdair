#ifndef __STDAIR_BAS_RANDOMGENERATION_HPP
#define __STDAIR_BAS_RANDOMGENERATION_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
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

    /**
     * Generate a randomized number following an exponential distribution
     * specified by a mean and a lambda parameter.
     */
    RealNumber_T generateExponential (const RealNumber_T&);

    /**
     * Retrieve the base generator for initialising other random generators.
     */
    BaseGenerator_T& getBaseGenerator () { return _generator; }
    

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

  private:
    /**
     * Copy constructor.
     */
    RandomGeneration (const RandomGeneration&);
    /**
     * Copy operator.
     */
    RandomGeneration& operator= (const RandomGeneration& iRandomGeneration) {
      _generator = iRandomGeneration._generator;
      return *this;
    }      
  public:
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
    void init (const RandomSeed_T&);

    // ////////// Attributes //////////
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
