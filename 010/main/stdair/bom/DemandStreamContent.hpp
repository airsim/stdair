#ifndef __STDAIR_BOM_DEMANDSTREAMCONTENT_HPP
#define __STDAIR_BOM_DEMANDSTREAMCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/basic/DemandCharacteristics.hpp>
#include <stdair/basic/DemandDistribution.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/basic/RandomGenerationContext.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/DemandStreamKey.hpp>

namespace stdair {
  
  /** Class modeling a demand stream. */
  class DemandStreamContent  : public BomContent {

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef DemandStreamKey_T Key_T;

  public:
    // ///////////// Getters ///////////
    /** Get the key */
    const Key_T& getKey () const {
      return _key;
    }
    
    /** Get the total number of requests to be generated. */
    const NbOfRequests_T& getTotalNumberOfRequestsToBeGenerated() const {
      return _totalNumberOfRequestsToBeGenerated;
    }

    /** Get the origin. */
    const AirportCode_T& getOrigin() const {
      return _key.getOrigin();
    }
    
    /** Get the destination. */
    const AirportCode_T& getDestination() const {
      return _key.getDestination();
    }
    
    /** Get the preferred departure date. */
    const Date_T& getPreferredDepartureDate() const {
      return _key.getPreferredDepartureDate();
    }

    /** Get the preferred cabin. */
    const CabinCode_T& getPreferredCabin() const {
      return _key.getPreferredCabin();
    }

    /** Get the arrival pattern. */
    const ContinuousFloatDuration_T& getArrivalPattern() const {
      return _demandCharacteristics._arrivalPattern;
    }

    /** Get the POS probability mass. */
    const POSProbabilityMass_T& getPOSProbabilityMass() const {
      return _demandCharacteristics._posProbabilityMass;
    }

    /** Get the channel probability mass. */
    const ChannelProbabilityMass_T& getChannelProbabilityMass() const {
      return _demandCharacteristics._channelProbabilityMass;
    }

    /** Get the trip type probability mass. */
    const TripTypeProbabilityMass_T& getTripTypeProbabilityMass() const {
      return _demandCharacteristics._tripTypeProbabilityMass;
    }

    /** Get the stay duration probability mass. */
    const StayDurationProbabilityMass_T& getStayDurationProbabilityMass() const {
      return _demandCharacteristics._stayDurationProbabilityMass;
    }

    /** Get the frequent flyer probability mass. */
    const FrequentFlyerProbabilityMass_T& getFrequentFlyerProbabilityMass() const {
      return _demandCharacteristics._frequentFlyerProbabilityMass;
    }

    /** Get the preferred departure time cumulative distribution. */
    const PreferredDepartureTimeCumulativeDistribution_T& getPreferredDepartureTimeCumulativeDistribution () const {
      return _demandCharacteristics._preferredDepartureTimeCumulativeDistribution;
    }
    
    /** Get the WTP cumulative distribution. */
    const WTPCumulativeDistribution_T& getWTPCumulativeDistribution() const {
      return _demandCharacteristics._wtpCumulativeDistribution;
    }

    /** Get the value of time cumulative distribution. */
    const ValueOfTimeCumulativeDistribution_T& getValueOfTimeCumulativeDistribution() const {
      return _demandCharacteristics._valueOfTimeCumulativeDistribution;
    }

    /** Get the mean number of requests. */
    const NbOfRequests_T& getMeanNumberOfRequests() const {
      return _demandDistribution._meanNumberOfRequests;
    }
    
    /** Get the standard deviation of number of requests. */
    const StandardDeviationValue_T& getStandardDeviationNumberOfRequests() const {
      return _demandDistribution._standardDeviationNumberOfRequests;
    }
    
    /** Get the cumulative probability of arrival pattern for last
        request generated so far. */
    const Probability_T& getCumulativeProbabilitySoFar () const {
      return _randomGenerationContext._cumulativeProbabilitySoFar;
    }
    
    /** Get the number of requests generated so far. */
    const Count_T& getNumberOfRequestsGeneratedSoFar() const {
      return _randomGenerationContext._numberOfRequestsGeneratedSoFar;
    }
    
    /** Get the seed of the random generator for the number of requests. */
    const RandomSeed_T& getNumberOfRequestsRandomGeneratorSeed () const {
      return _numberOfRequestsRandomGenerator._seed;
    }

    /** Get the seed of the random generator for the request datetime. */
    const RandomSeed_T& getRequestDateTimeRandomGeneratorSeed () const {
      return _requestDateTimeRandomGenerator._seed;
    }

    /** Get the seed of the random generator for the demand characteristics. */
    const RandomSeed_T& getDemandCharacteristicsRandomGeneratorSeed () const {
      return _demandCharacteristicsRandomGenerator._seed;
    }

    /** Get the demand characteristics. */
    const DemandCharacteristics& getDemandCharacteristics () const {
      return _demandCharacteristics;
    }

    /** Get the demand distribution. */
    const DemandDistribution& getDemandDistribution () const {
      return _demandDistribution;
    }

  public:
    // //////////////// Setters //////////////////
    /** Set the cumulative probability of arrival pattern for last
        request generated so far. */
    void setCumulativeProbabilitySoFar (const Probability_T& iCumulativeProbability) {
      _randomGenerationContext._cumulativeProbabilitySoFar = 
        iCumulativeProbability;
    }
    
    /** Set the number of requests generated so far. */
    void setNumberOfRequestsGeneratedSoFar (const Count_T& iNumberOfRequests) {
      _randomGenerationContext._numberOfRequestsGeneratedSoFar =
        iNumberOfRequests;
    }
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

  public:
    // /////////////// Business Methods //////////
    /** Increment counter of requests generated so far */
    void incrementGeneratedRequestsCounter () {
      _randomGenerationContext.incrementGeneratedRequestsCounter();
    }

    
    /** Generate a randomized number following a uniform distribution
        between 0 (included) and 1 (excluded). */
    RealNumber_T generateUniform01WithNumberOfRequestRandomGenerator () {
      return _numberOfRequestsRandomGenerator.generateUniform01();
    }
    RealNumber_T generateUniform01WithRequestDateTimeRandomGenerator() {
      return _requestDateTimeRandomGenerator.generateUniform01();
    }
    RealNumber_T generateUniform01WithDemandCharacteristicsRandomGenerator() {
      return _demandCharacteristicsRandomGenerator.generateUniform01();
    }
    
    /** Generate a randomized number following a uniform distribution
        between a minimum (included) and a maximum (excluded)
        value. */
    RealNumber_T generateUniformWithNumberOfRequestRandomGenerator (const RealNumber_T& iMinValue, const RealNumber_T& iMaxValue) {
      return _numberOfRequestsRandomGenerator.generateUniform (iMinValue,
                                                               iMaxValue);
    }
    RealNumber_T generateUniformWithRequestDateTimeRandomGenerator(const RealNumber_T& iMinValue, const RealNumber_T& iMaxValue) {
      return _requestDateTimeRandomGenerator.generateUniform (iMinValue,
                                                              iMaxValue);
    }
    RealNumber_T generateUniformWithDemandCharacteristicsRandomGenerator(const RealNumber_T& iMinValue, const RealNumber_T& iMaxValue) {
      return _demandCharacteristicsRandomGenerator.generateUniform (iMinValue,
                                                                    iMaxValue);
    }
    
    /** Generate a randomized number following a normal distribution
        specified by a mean and a standard deviation. */
    RealNumber_T generateNormalWithNumberOfRequestRandomGenerator (const RealNumber_T& mu, const RealNumber_T& sigma) {
      return _numberOfRequestsRandomGenerator.generateNormal (mu, sigma);
    }
    RealNumber_T generateNormalWithRequestDateTimeRandomGenerator(const RealNumber_T& mu, const RealNumber_T& sigma) {
      return _requestDateTimeRandomGenerator.generateNormal (mu, sigma);
    }
    RealNumber_T generateNormalWithDemandCharacteristicsRandomGenerator(const RealNumber_T& mu, const RealNumber_T& sigma) {
      return _demandCharacteristicsRandomGenerator.generateNormal (mu, sigma);
    }
       
  protected:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    DemandStreamContent (const Key_T&,
                         const ArrivalPatternCumulativeDistribution_T&,
                         const POSProbabilityMassFunction_T&,
                         const ChannelProbabilityMassFunction_T&,
                         const TripTypeProbabilityMassFunction_T&,
                         const StayDurationProbabilityMassFunction_T&,
                         const FrequentFlyerProbabilityMassFunction_T&,
                         const PreferredDepartureTimeContinuousDistribution_T&,
                         const WTPContinuousDistribution_T&,
                         const ValueOfTimeContinuousDistribution_T&,
                         const DemandDistribution&,
                         const RandomSeed_T& iNumberOfRequestsSeed,
                         const RandomSeed_T& iRequestDateTimeSeed,
                         const RandomSeed_T& iDemandCharacteristicsSeed);
    /** Default constructors. */
    DemandStreamContent ();
    DemandStreamContent (const DemandStreamContent&);
    /** Initialization. */
    void init();
    /** Destructor. */
    ~DemandStreamContent ();

    
  protected:
    // ////////// Attributes //////////
    /** Key */
    Key_T _key;
    
    /** Demand characteristics */
    DemandCharacteristics _demandCharacteristics;

    /** Demand distribution */
    DemandDistribution _demandDistribution;
    
    /** Total number of requests to be generated*/
    NbOfRequests_T _totalNumberOfRequestsToBeGenerated;

    /** Random generation context */
    RandomGenerationContext _randomGenerationContext;
  
    /** Random generator for number of requests */
    RandomGeneration _numberOfRequestsRandomGenerator;
    
    /** Random generator for request datetime */
    RandomGeneration _requestDateTimeRandomGenerator;
    
    /** Random generator for demand characteristics */
    RandomGeneration _demandCharacteristicsRandomGenerator;
  };

}
#endif // __STDAIR_BOM_DEMANDSTREAMCONTENT_HPP