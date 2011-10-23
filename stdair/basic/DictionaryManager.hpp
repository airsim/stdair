// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BASIC_DICTIONARYMANAGER_HPP
#define __STDAIR_BASIC_DICTIONARYMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_maths_types.hpp>

namespace stdair {

  // //////////// Type definitions /////////////////
  /** Dictionary key. */
  typedef unsigned short DictionaryKey_T;
  
  /**
   * @brief Class wrapper of dictionary business methods.
   */
  class DictionaryManager {
  public:
    // //////////// Business methods /////////////////
    /**
     * Convert from key to value.
     */
    static const stdair::Probability_T keyToValue (const DictionaryKey_T);
    
    /**
     * Convert from value to key.
     */
    static const DictionaryKey_T valueToKey (const stdair::Probability_T);
  };
}
#endif // __STDAIR_BASIC_DICTIONARYMANAGER_HPP
