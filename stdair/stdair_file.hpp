#ifndef __STDAIR_STDAIR_FILE_HPP
#define __STDAIR_STDAIR_FILE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost
#include <boost/utility.hpp>
// StdAir
#include <stdair/stdair_basic_types.hpp>

namespace stdair {

  /**
   * @brief Root of the input and output files. 
   *
   * All the files inherit from that root.
   *
   */
  class RootFilePath { 
  public:
    /**
     * Main Constructor.
     */
    RootFilePath (const Filename_T& iFilename) :
      _filename (iFilename) {}
    /**
     * Default constructor.
     */
    RootFilePath () : _filename ("MyFilename") {}
    
    /**
     * Destructor.
     */
    virtual ~RootFilePath() {}
    
    /**
     * Give the details of the exception.
     */
    const char * name() const {
      return _filename.c_str();
    }
    
  protected:
    /**
     * Name of the file.
     */
    const Filename_T _filename;
  };

  /** Input File. */
  class InputFilePath : public RootFilePath { 
  public:
    /** Constructor. */
    InputFilePath (const Filename_T& iFilename) :
      RootFilePath (iFilename) {}
  };
  
}
#endif // __STDAIR_STDAIR_FILE_HPP
