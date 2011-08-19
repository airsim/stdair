#ifndef __STDAIR_BAS_CONTINUOUSATTRIBUTELITE_HPP
#define __STDAIR_BAS_CONTINUOUSATTRIBUTELITE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iosfwd>
#include <string>
#include <vector>
#include <map>
// StdAir
#include <stdair/stdair_basic_types.hpp>
// TraDemGen
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/DictionaryManager.hpp>

namespace stdair {

  /**
   * @brief Class modeling the distribution of values that can be
   * taken by a continuous attribute.
   */
  template <typename T>
  struct ContinuousAttributeLite {
  public:
    // ///////////////////// Type definitions ///////////////////////
    /**
     * Type for the probability mass function.
     */
    typedef std::map<T, stdair::Probability_T> ContinuousDistribution_T;
    
  public:
    // ////////////////////// Business Methods ////////////////////
    /**
     * Get value from inverse cumulative distribution.
     */
    const T getValue(const stdair::Probability_T& iCumulativeProbability) const{
      const DictionaryKey_T& lKey =
        DictionaryManager::valueToKey (iCumulativeProbability);

      // Find the first cumulative probablity value greater or equal to lKey.
      unsigned int idx = 0;
      for (; idx < _size; ++idx) {
        if (_cumulativeDistribution.at(idx) > lKey) {
          break;
        }
      }

      if (idx == 0) {
        return _valueArray.at(idx);
      }
      if (idx == _size) {
        return _valueArray.at(idx-1);
      }

      //
      const stdair::Probability_T& lCumulativeCurrentPoint =
        DictionaryManager::keyToValue (_cumulativeDistribution.at(idx));
      const T& lValueCurrentPoint = _valueArray.at(idx);

      //
      const stdair::Probability_T& lCumulativePreviousPoint =
        DictionaryManager::keyToValue (_cumulativeDistribution.at(idx-1));
      const T& lValuePreviousPoint = _valueArray.at(idx-1);

      if (lCumulativePreviousPoint == lCumulativeCurrentPoint) {
        return lValuePreviousPoint;
      }

      T oValue= lValuePreviousPoint + (lValueCurrentPoint - lValuePreviousPoint)
        * (iCumulativeProbability - lCumulativePreviousPoint)
        / (lCumulativeCurrentPoint - lCumulativePreviousPoint);

      return oValue;
    }

  public:
    // ////////////////////// Business Methods ////////////////////
    /**
     * Get remaining proportion from cumulative distribution.
     */
    const stdair::Probability_T getRemainingProportion(const T& iValue) const {     

      // Find the first value greater than iValue.
      unsigned int idx = 0;
      for (; idx < _size; ++idx) {
        if (_valueArray.at(idx) > iValue) {
          break;
        }
      }
      if (idx == 0) {
        const stdair::Probability_T& oCumulativeProbability =
          DictionaryManager::keyToValue (_cumulativeDistribution.at(idx));
        return 1 - oCumulativeProbability;
      }
      if (idx == _size) {
        const stdair::Probability_T& oCumulativeProbability =
          DictionaryManager::keyToValue (_cumulativeDistribution.at(idx-1));
        return 1 - oCumulativeProbability;        
      }

      //
      const stdair::Probability_T& lCumulativeCurrentPoint =
        DictionaryManager::keyToValue (_cumulativeDistribution.at(idx));
      const T& lValueCurrentPoint = _valueArray.at(idx);

      //
      const stdair::Probability_T& lCumulativePreviousPoint =
        DictionaryManager::keyToValue (_cumulativeDistribution.at(idx-1));
      const T& lValuePreviousPoint = _valueArray.at(idx-1);

      if (lValuePreviousPoint == lValueCurrentPoint) {
        return 1 - lCumulativePreviousPoint;
      }

      const stdair::Probability_T& oCumulativeProbability =
        lCumulativePreviousPoint + (lCumulativeCurrentPoint - lCumulativePreviousPoint)
        * (iValue - lValuePreviousPoint)
        / (lValueCurrentPoint - lValuePreviousPoint);

      return 1 - oCumulativeProbability;
    }

  public:
    // ////////////////////// Business Methods ////////////////////
    /**
     * Get the value of the derivative function in a key point.
     */
    const double getDerivativeValue(const T iKey) const{

      // Find the first key value greater or equal to iKey.
      unsigned int idx = 0;
      for (; idx < _size; ++idx) {
        if (_valueArray.at(idx) > iKey) {
          break;
        }
      }
      assert (idx != 0);
      assert (idx != _size);

      // 
      const stdair::Probability_T& lCumulativeCurrentPoint =
        DictionaryManager::keyToValue (_cumulativeDistribution.at(idx));
      const T& lValueCurrentPoint = _valueArray.at(idx);

      //
      const stdair::Probability_T& lCumulativePreviousPoint =
        DictionaryManager::keyToValue (_cumulativeDistribution.at(idx-1));
      const T& lValuePreviousPoint = _valueArray.at(idx-1);
      assert (lValueCurrentPoint != lValuePreviousPoint);
      
      const double oValue= (lCumulativeCurrentPoint - lCumulativePreviousPoint)
        / (lValueCurrentPoint - lValuePreviousPoint);

      return oValue;
    }

    /**
     * Get the upper bound.
     */
    const T getUpperBound (const T iKey) const {
      // Find the first key value greater or equal to iKey.
      unsigned int idx = 0;
      for (; idx < _size; ++idx) {
        if (_valueArray.at(idx) > iKey) {
          break;
        }
      }
      assert (idx != 0);
      assert (idx != _size);

      return _valueArray.at (idx);
    }
    
  public:
    // ////////////// Display Support Methods ////////////////
    /**
     * Display cumulative distribution.
     */
    const std::string displayCumulativeDistribution() const {
      std::ostringstream oStr;
      
      for (unsigned int idx = 0; idx < _size; ++idx) {
        if (idx != 0) {
          oStr << ", ";
        }

        const stdair::Probability_T& lProbability =
          DictionaryManager::keyToValue (_cumulativeDistribution.at(idx));
      
        oStr << _valueArray.at(idx) << ":" << lProbability;
      }
      return oStr.str();
    }


  public:
    // ////////// Constructors and destructors //////////////
    /**
     * Constructor.
     */
    ContinuousAttributeLite (const ContinuousDistribution_T& iValueMap)
      : _size (iValueMap.size()) {
      init (iValueMap);
    }
    
    /**
     * Copy constructor.
     */
    ContinuousAttributeLite (const ContinuousAttributeLite& iCAL)
      : _size (iCAL._size),
        _cumulativeDistribution (iCAL._cumulativeDistribution),
        _valueArray (iCAL._valueArray) {
    }

    /**
     * Copy operator.
     */
    ContinuousAttributeLite& operator= (const ContinuousAttributeLite& iCAL) {
      _size = iCAL._size;
      _cumulativeDistribution = iCAL._cumulativeDistribution;
      _valueArray = iCAL._valueArray;
      return *this;
    }

    /**
     * Destructor.
     */
    virtual ~ContinuousAttributeLite() {
    }

  private:
    /**
     * Default constructor.
     */
    ContinuousAttributeLite() : _size(1) {
    }

    /**
     * Determine inverse cumulative distribution from cumulative
     * distribution (initialisation).
     */
    void init (const ContinuousDistribution_T& iValueMap) {
      //
      const unsigned int lSize = iValueMap.size();
      _cumulativeDistribution.reserve (lSize);
      _valueArray.reserve (lSize);

      // Browse the map to retrieve the values and cumulative probabilities.
      for (typename ContinuousDistribution_T::const_iterator it =
             iValueMap.begin(); it != iValueMap.end(); ++it) {
        
        const T& attributeValue = it->first;
        const DictionaryKey_T& lKey = DictionaryManager::valueToKey (it->second);
        
        // Build the two arrays.
        _cumulativeDistribution.push_back (lKey);
        _valueArray.push_back (attributeValue);
      }
    }
  

  private:
    // ////////// Attributes //////////
    /**
     * Size of the two arrays.
     */
    unsigned int _size;
    
    /**
     * Cumulative dictionary-coded distribution.
     */
    std::vector<DictionaryKey_T> _cumulativeDistribution;

    /**
     * The corresponding values.
     */
    std::vector<T> _valueArray;
  };
  
}
#endif // __STDAIR_BAS_CONTINUOUSATTRIBUTELITE_HPP
