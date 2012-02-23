#ifndef __STDAIR_STDAIR_JSON_HPP
#define __STDAIR_STDAIR_JSON_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <iosfwd>

namespace stdair {

  /**
   * @brief JSON-formatted string.
   *
   */
  class JSONString { 
  public:
    /**
     * Main Constructor.
     */
    JSONString (const std::string& iJsonString) :
      _jsonString (iJsonString) {}
    /**
     * Default constructor.
     */
    JSONString () : _jsonString ("") {}
    
    /**
     * Destructor.
     */
    virtual ~JSONString() {}
    
    /**
     * Get the string value.
     */
    const std::string& getString() const {
      return _jsonString;
    }
    
  protected:
    /**
     * 
     */
    std::string _jsonString;
  };

}
#endif // __STDAIR_STDAIR_JSON_HPP
