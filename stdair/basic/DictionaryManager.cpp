// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/basic/DictionaryManager.hpp>
#include <stdair/basic/BasConst_General.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  const stdair::Probability_T DictionaryManager::
  keyToValue (const DictionaryKey_T iKey) {
    const float lValue =
      static_cast<float> (iKey) / DEFAULT_NUMBER_OF_SUBDIVISIONS;
    const stdair::Probability_T lProbability (lValue);
    return lProbability;
  }

  // ////////////////////////////////////////////////////////////////////
  const DictionaryKey_T DictionaryManager::
  valueToKey (const stdair::Probability_T iValue) {
    const unsigned short lValueMultipliedByThousand =
      static_cast<unsigned short> (iValue) * DEFAULT_NUMBER_OF_SUBDIVISIONS;
    const DictionaryKey_T lDictionaryKey (lValueMultipliedByThousand);
    return lDictionaryKey;
  }

}
