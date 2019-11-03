#ifndef __STDAIR_BOM_CONFIGHOLDERSTRUCT_HPP
#define __STDAIR_BOM_CONFIGHOLDERSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// Boost
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#if BOOST_VERSION_MACRO >= 104100
// Boost Property Tree
#include <boost/property_tree/ptree.hpp>
#endif // BOOST_VERSION_MACRO >= 104100
// StdAir
#include <stdair/stdair_file.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/ConfigHolderTypes.hpp>

#if BOOST_VERSION_MACRO >= 104100
namespace bpt = boost::property_tree;
#else // BOOST_VERSION_MACRO >= 104100
namespace bpt {
  typedef char ptree;
}
#endif // BOOST_VERSION_MACRO >= 104100

namespace stdair {

  /// Forward declarations
  class BomRoot;

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
    bool addValue (const std::string& iValue, 
		   const std::string& iPath);   

    /**
     * Look for the specified path in the configuration tree and,
     * if existing, try to extract the corresponding value.
     * The type of the value to extract is a template parameter.
     * 
     * @param ValueType& Value to add in the configuration tree. 
     * @param const std::string& Path to look for.
     */    
    template <typename ValueType> 
    bool exportValue (ValueType& ioValue, const std::string& iPath) const;

    /**
     * Update the airline features objects thanks to the configuration
     * holder.  
     *
     * @param BomRoot& Reference on the BomRoot to update.
     */
    void updateAirlineFeatures (BomRoot&);

  private: 
    /**
     * Helping method for the merge.
     */
    void add (const bpt::ptree&, 
	      const std::string&);
    
  public:     
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

    /**
     * Display of the configuration in a JSON-ified format.
     */
    const std::string jsonExport() const;

    
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

  // ////////////////////////////////////////////////////////////////////
  template <typename ValueType> 
  bool ConfigHolderStruct::exportValue (ValueType& ioValue,
					const std::string& iPath) const {
  
    bool hasValueBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION_MACRO >= 104100
    try {
      // Get the value.
      // If the path key is not found, an exception is thrown.
      const std::string lPrefix ("config.");
      const std::string lFinalPath = lPrefix + iPath;
      ioValue = _pt.get<ValueType> (lFinalPath);
    
    } catch (bpt::ptree_error& bptException) {
      hasValueBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION_MACRO >= 104100
    
    return hasValueBeenSuccessfullyRetrieved;
    
  }
  
  // ////////////////////////////////////////////////////////////////////
  //
  // Specialization of the template method exportValue above for the type
  // Date_T.
  //
  // ////////////////////////////////////////////////////////////////////

  template<>
  inline bool ConfigHolderStruct::exportValue<Date_T> 
  (Date_T& ioValue,
   const std::string& iPath) const {     

    bool hasValueBeenSuccessfullyRetrieved = true;

#if BOOST_VERSION_MACRO >= 104100
    
    try { 

      // Get the string date value. 
      // If the path key is not found, an exception is thrown.
      const std::string lPrefix ("config.");
      const std::string lFinalPath = lPrefix + iPath;
      const std::string& lDateStr =
        _pt.get<std::string> (lFinalPath);
      
      // Convert the string into a Date_T.
      ioValue = 
	boost::gregorian::from_simple_string (lDateStr);
    
    } catch (bpt::ptree_error& bptException) {
      hasValueBeenSuccessfullyRetrieved = false;
    }
#endif // BOOST_VERSION_MACRO >= 104100
    
    return hasValueBeenSuccessfullyRetrieved;

    
  }

}

#endif // __STDAIR_BOM_CONFIGHOLDERSTRUCT_HPP
