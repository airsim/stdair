#ifndef __STDAIR_STDAIR_EXCEPTIONS_HPP
#define __STDAIR_STDAIR_EXCEPTIONS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace stdair {

  /**
   * @brief Root of the stdair exceptions.
   *
   * All the stdair exceptions inherit from that root, allowing to
   * catch them and to spot them easily when arising in code wrapping
   * the stdair library.
   */
  class RootException : public std::exception { 
  public:
    /**
     * Main Constructor.
     */
    RootException (const std::string& iWhat) : _what (iWhat) {}
    /**
     * Default constructor.
     */
    RootException() : _what ("No further details") {}
    
    /**
     * Destructor.
     */
    virtual ~RootException() throw() {}
    
    /**
     * Give the details of the exception.
     */
    const char* what() const throw() {
      return _what.c_str();
    }
    
  protected:
    /**
     * Details for the exception.
     */
    std::string _what;
  };
  
  /** File not found. */
  class FileNotFoundException : public RootException { 
  public:
    /** Constructor. */
    FileNotFoundException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  /** Non initialised log service. */
  class NonInitialisedLogServiceException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedLogServiceException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  /** Non initialised service. */
  class NonInitialisedServiceException : public RootException {
  public:
    /** Constructor. */
    NonInitialisedServiceException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  /** Non initialised container. */
  class NonInitialisedContainerException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedContainerException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  /** Non initialised relationship. */
  class NonInitialisedRelationShipException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedRelationShipException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  /** Memory allocation. */
  class MemoryAllocationException : public RootException { 
  public:
    /** Constructor. */
    MemoryAllocationException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  /** Object link. */
  class ObjectLinkingException : public RootException { 
  public:
    /** Constructor. */
    ObjectLinkingException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  /** Document not found. */
  class DocumentNotFoundException : public RootException {
  public:
    /** Constructor. */
    DocumentNotFoundException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  /** Parser. */
  class ParserException : public RootException { 
  public:
    /** Constructor. */
    ParserException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  /** Serialisation. */
  class SerialisationException : public RootException { 
  public:
    /** Constructor. */
    SerialisationException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  /** Not found key. */
  class KeyNotFoundException : public RootException { 
  public:
    /** Constructor. */
    KeyNotFoundException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  /** Code conversion. */
  class CodeConversionException : public ParserException {  
  public:
    /** Constructor. */
    CodeConversionException (const std::string& iWhat)
      : ParserException (iWhat) {}
  };
  
  /** Code duplication. */
  class CodeDuplicationException : public ParserException { 
  public:
    /** Constructor. */
    CodeDuplicationException (const std::string& iWhat)
      : ParserException(iWhat) {}
  };
  
  /** Duplicated object. */
  class ObjectCreationgDuplicationException : public ParserException {
  public:
    /** Constructor. */
    ObjectCreationgDuplicationException (const std::string& iWhat) 
      : ParserException (iWhat) {} 
  };
  
  /** Not found object. */
  class ObjectNotFoundException : public RootException {
  public:
    /** Constructor. */
    ObjectNotFoundException (const std::string& iWhat)
      : RootException (iWhat) {}
  };
  
  /** Database. */
  class SQLDatabaseException : public RootException {
  public:
    /** Constructor. */
    SQLDatabaseException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  /** Non initialised database session. */
  class NonInitialisedDBSessionManagerException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedDBSessionManagerException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  /** Database connection. */
  class SQLDatabaseConnectionImpossibleException : public SQLDatabaseException {
  public:
    /** Constructor. */
    SQLDatabaseConnectionImpossibleException (const std::string& iWhat)
      : SQLDatabaseException (iWhat) {}
  };

  /** Event. */
  class EventException : public RootException { 
  public:
    /** Constructor. */
    EventException (const std::string& iWhat) : RootException (iWhat) {}
  };

}
#endif // __STDAIR_STDAIR_EXCEPTIONS_HPP
