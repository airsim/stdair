#ifndef __STDAIR_BOM_CONFIGHOLDERSTRUCT_HPP
#define __STDAIR_BOM_CONFIGHOLDERSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#if BOOST_VERSION >= 104100
// Boost Property Tree
#include <boost/property_tree/ptree.hpp>
#endif // BOOST_VERSION >= 104100
// StdAir
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/ConfigHolderTypes.hpp>

#if BOOST_VERSION >= 104100
namespace bpt = boost::property_tree;
#else // BOOST_VERSION >= 104100
namespace bpt {
  typedef char ptree;
}
#endif // BOOST_VERSION >= 104100

namespace stdair {

  /**
   * Structure holding the configuration of the simulation.
   */
  struct ConfigHolderStruct : public StructAbstract {
  public:
    // /////////////// Getters /////////////////

    // ///////////// Business Methods //////////
    /**
     * Merge the given property tree with the existing configuration 
     * property tree gathering all the configuration information.
     *
     * @param const bpt::ptree& Property tree to add to the configuration tree.
     */
    void add (const bpt::ptree&);   

    /**
     * Create the given specified path in the configuration tree and add the 
     * corresponding given value (or replace the value if the path already 
     * exists).
     * 
     * @param const std::string& Value to add at the given path.
     * @param const std::string& Path to create (or to look for).
     */
    void addValue (const std::string& iValue, 
		   const std::string& iPath);

  private:   
    /**
     * Helping method for the merge.
     */
    void add (const bpt::ptree&, 
	      const std::string&);
    
    // /////////// Display support method /////////////
    /**
     * Dump a Business Object into an output stream.
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;

    /**
     * Read a Business Object from an input stream.
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn);

    /**
     * Display of the structure.
     */
    const std::string describe() const;

    
    // /////////////// Constructors and Destructors /////////////////
  public:
    /**
     * Constructor.
     */
    ConfigHolderStruct ();

    /**
     * Copy constructor.
     */
    ConfigHolderStruct (const ConfigHolderStruct&);

  public:
    /**
     * Destructor.
     */
    ~ConfigHolderStruct();
    

  private:
    // /////////////// Attributes /////////////////
    /**
     * Property tree holding the configuration.
     */
    bpt::ptree _pt;
  };

}
#endif // __STDAIR_BOM_CONFIGHOLDERSTRUCT_HPP
