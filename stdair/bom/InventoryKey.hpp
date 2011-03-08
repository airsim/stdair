#ifndef __STDAIR_BOM_INVENTORYKEY_HPP
#define __STDAIR_BOM_INVENTORYKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// Boost.Serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

namespace stdair {
  
  /**
   * @brief Key of a given inventory, made of the airline code.
   */
  struct InventoryKey : public KeyAbstract {
    friend class boost::serialization::access;
    
    // /////////// Constructors and destructors ///////////
  private:
    /**
     * Default constructor.
     */
    InventoryKey();
    
  public:
    // /////////// Construction ///////////
    /**
     * Constructor.
     */
    InventoryKey (const AirlineCode_T& iAirlineCode);
    /**
     * Copy constructor.
     */
    InventoryKey (const InventoryKey&);
    /**
     * Destructor.
     */
    ~InventoryKey();
    

    // /////////// Getters //////////
    /**
     * Get the airline code.
     */
    const AirlineCode_T& getAirlineCode() const {
      return _airlineCode;
    }


  public:
    // /////////// Display support methods /////////
    /**
     * Dump a Business Object Key into an output stream.
     *
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;
    
    /**
     * Read a Business Object Key from an input stream.
     *
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn);
      
   /**
    * Get the serialised version of the Business Object Key.
    *
    * That string is unique, at the level of a given Business Object,
    * when among children of a given parent Business Object.
    *
    * For instance, "H" and "K" allow to differentiate among two
    * marketing classes for the same segment-date.
    */
    const std::string toString() const;


  public:
    // /////////// (Boost) Serialisation support methods /////////
    /**
     * Serialisation.
     */
    template<class Archive>
    void serialize (Archive& ar, const unsigned int iFileVersion) {
      ar & _airlineCode;
    }


  private:
    // ///////////////// Attributes ///////////////
    /**
     * Airline code.
     */
    AirlineCode_T _airlineCode;
  };

}
#endif // __STDAIR_BOM_INVENTORYKEY_HPP
