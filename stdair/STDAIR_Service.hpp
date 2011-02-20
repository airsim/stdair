/**
 * @brief Handle on the StdAir library context
 * @author Anh Quan Nguyen <quannaus@users.sourceforge.net>
 * @date 20/01/2010
 * @detail StdAir aims at providing a clean API, and the corresponding
 *         C++ implementation, for the basis of Airline IT Business Object
 *         Model (BOM), that is, to be used by several other Open Source
 *         projects, such as RMOL and OpenTREP.
 *
 *         Install the StdAir library for Airline IT Standard C++ fundaments.
 */
#ifndef __STDAIR_STDAIR_HPP
#define __STDAIR_STDAIR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/stdair_service_types.hpp>

namespace stdair {

  /// Forward declarations
  class BomRoot;
  
  /**
   * @brief Interface for the STDAIR Services
   */
  class STDAIR_Service {
  public:
    // ////////// Constructors and destructors //////////
    /**
     * @brief Default constructor.
     */
    STDAIR_Service();

    /**
     * @brief Constructor.
     *
     * The init() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, a reference on an output stream is given, so
     * that log outputs can be directed onto that stream.
     *
     * @param[in] const BasLogParams& Parameters for the output log stream.
     */
    STDAIR_Service (const BasLogParams&);

    /**
     * @brief Constructor.
     *
     * The init() method is called; see the corresponding
     * documentation for more details.
     *
     * A reference on an output stream is given, so
     * that log outputs can be directed onto that stream.
     *
     * Moreover, database connection parameters are given, so
     * that database requests can use the corresponding access.
     *
     * @param[in] const BasLogParams& Parameters for the output log stream.
     * @param[in] const BasDBParams& Parameters for the database session.
     */
    STDAIR_Service (const BasLogParams&, const BasDBParams&);

    /**
     * @brief Destructor.
     */
    ~STDAIR_Service();
    
    /**
     * Build a sample BOM tree, and attach it to the BomRoot instance.
     *
     * As for now, two inventories (one for BA, another for AF) are
     * built, each containing one flight. One of those flights has two
     * legs (and therefore three segments).
     */
    void buildSampleBom();


  public:
    // //////////////// Display support methods /////////////////
    /**
     * Recursively display (dump in the returned string) the objects
     * of the BOM tree.
     *
     * @return std::string Output string in which the BOM tree is
     *        logged/dumped.
     */
    std::string csvDisplay() const;


  public:
    // ///////////////// Getters ///////////////////
    /**
     * @brief Get a reference on the BomRoot object.
     *
     * If the service context has not been initialised, that
     * method throws an exception (failing assertion).
     *
     * @param[out] BomRoot& Reference on the BomRoot.
     */
    BomRoot& getBomRoot() const {
      return _bomRoot;
    }
    

  private:
    // /////// Construction and Destruction helper methods ///////
    /**
     * @brief Default copy constructor.
     *
     * @param[in] const STDAIR_Service& Reference on the
     *            STDAIR_Service handler to be copied.
     */
    STDAIR_Service (const STDAIR_Service&);
    
    /**
     * @brief Initialise the log.
     *
     * @param[in] const BasLogParams& Parameters for the output log stream.
     */
    void logInit (const BasLogParams&);
    
    /**
     * @brief Initialise the database session.
     *
     * @param[in] const BasDBParams& Parameters for the database session.
     */
    void dbInit (const BasDBParams&);
    
    /**
     * @brief Initialise.
     *
     * The static instance of the log service (Logger object) is created.
     *
     * The static instance of the database session manager
     * (DBSessionManager object) is created.
     *
     * The static instance of the FacSupervisor object, itself referencing
     * all the other objects (factories and BOM), is created.
     *
     * As those three objects are static, there is no need to store them
     * in any service context. However, some lock mechanism may be needed
     * in order to secure the access to the corresponding resources.
     */
    void init();
    
    /**
     * @brief Finalise.
     */
    void finalise();
    

  private:
    // /////////////// Attributes ///////////////
    /**
     * @brief Root of the BOM tree.
     */
    BomRoot& _bomRoot;
  };
}
#endif // __STDAIR_STDAIR_HPP
