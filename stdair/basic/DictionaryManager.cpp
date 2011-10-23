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
      static_cast<float> (iKey) / HIGHER_VALUE_PER_THOUSAND;
    const stdair::Probability_T lProbability (lValue);
    return lProbability;
  }

  // ////////////////////////////////////////////////////////////////////
  const DictionaryKey_T DictionaryManager::
  valueToKey (const stdair::Probability_T iValue) {
    const unsigned short lValueMultipliedByThousand =
      iValue * HIGHER_VALUE_PER_THOUSAND;
    const DictionaryKey_T lDictionaryKey (lValueMultipliedByThousand);
    return lDictionaryKey;
  }
}
