#ifndef __STDAIR_BAS_BASDBPARAMS_HPP
#define __STDAIR_BAS_BASDBPARAMS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// Stdair
#include <stdair/stdair_db.hpp>
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /**
   * @brief Structure holding the parameters for connection to a database.
   */
  struct BasDBParams : public StructAbstract {
  public:
    // ///////// Getters ////////
    /** Get the database user name. */
    const std::string& getUser() const {
      return _user;
    }
    
    /** Get the database user password. */
    const std::string& getPassword() const {
      return _passwd;
    }
    
    /** Get the database host name. */
    const std::string& getHost() const {
      return _host;
    }
    
    /** Get the database port number. */
    const std::string& getPort() const {
      return _port;
    }
    
    /** Get the database name. */
    const std::string& getDBName() const {
      return _dbname;
    }
    
    
    // ///////// Setters //////////
    /** Set the database user name. */
    void setUser (const std::string& iUser) {
      _user = iUser;
    }

    /** Set the database password. */
    void setPassword (const std::string& iPasswd) {
      _passwd = iPasswd;
    }

    /** Set the database host name. */
    void setHost (const std::string& iHost) {
      _host = iHost;
    }

    /** Set the database port number. */
    void setPort (const std::string& iPort) {
      _port = iPort;
    }

    /** Set the database name. */
    void setDBName (const std::string& iDBName) {
      _dbname = iDBName;
    }

    
  public:
    // ///////// Busines methods ////////
    /**
     * Check that all the parameters are fine.
     */
    bool check() const;

    
  public:
    // ///////// Display methods ////////
    /**
     * Get the serialised version of the DBParams structure.
     */
    const std::string describe() const;

    /**
     * Get a short display of the DBParams structure.
     */
    std::string toShortString() const;
    
    /**
     * Get the serialised version of the DBParams structure.
     */
    std::string toString() const;

    
  public:
    /**
     * Main Constructor.
     */
    BasDBParams (const std::string& iDBUser, const std::string& iDBPasswd,
                 const std::string& iDBHost, const std::string& iDBPort,
                 const std::string& iDBName);

    /**
     * Default Constructor.
     */
    BasDBParams();

    /**
     * Default copy constructor.
     */
    BasDBParams (const BasDBParams&);

    /**
     * Destructor.
     */
    ~BasDBParams();
    
    
  private:
    // /////// Attributes /////////
    /** Database user name. */
    std::string _user;
    /** Database user password. */
    std::string _passwd;
    /** Database host name. */
    std::string _host;
    /** Database port number. */
    std::string _port;
    /** Database name. */
    std::string _dbname;
  };

}
#endif // __STDAIR_BAS_BASDBPARAMS_HPP
