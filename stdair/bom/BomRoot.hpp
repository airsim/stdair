#ifndef __STDAIR_BOM_BOMROOT_HPP
#define __STDAIR_BOM_BOMROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BomRootKey.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /// Forward declarations
  struct InventoryKey;
  class Inventory;

  /**
   * @brief Class representing the actual attributes for the Bom root.
   */
  class BomRoot : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;
    
  public:
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef BomRootKey Key_T;


  public:
    // ////////// Getters ////////////
    /** Get the inventory key (airline code). */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the map of children. */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /**
     * Get a pointer on the Inventory object corresponding to the
     * given key.
     *
     * \note The Inventory object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const std::string& The flight-date key.
     * @return Inventory* Found Inventory object. NULL if not found.
     */
    Inventory* getInventory (const std::string& iInventoryKeyStr) const;

    /**
     * Get a pointer on the Inventory object corresponding to the
     * given key.
     *
     * \note The Inventory object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const InventoryKey& The flight-date key
     * @return Inventory* Found Inventory object. NULL if not found.
     */
    Inventory* getInventory (const InventoryKey&) const;


  public:
    // /////////// Display support methods /////////
    /**
     * Dump a Business Object into an output stream.
     * 
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const {
      ioOut << toString();
    }

    /**
     * Read a Business Object from an input stream.
     *
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn) {
    }

    /**
     * Get the serialised version of the Business Object.
     */
    std::string toString() const;
    
    /**
     * Get a string describing the  key.
     */
    const std::string describeKey() const {
      return _key.toString();
    }
    

  public:
    // /////////// (Boost) Serialisation support methods /////////
    /**
     * Serialisation.
     */
    template<class Archive>
    void serialize (Archive& ar, const unsigned int iFileVersion);

  private:
    /**
     * Serialisation helper (allows to be sure the template method is
     * instantiated).
     */
    void serialisationImplementation();


  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Default constructor.
     */
    BomRoot();

    /**
     * Copy constructor.
     */
    BomRoot (const BomRoot&);

    /**
     * Main constructor.
     */
    BomRoot (const Key_T& iKey);

    /**
     * Destructor.
     */
    ~BomRoot();


  protected:
    // /////////////// Attributes ////////////////
    /**
     * Primary key.
     */
    Key_T _key;

    /**
     * Map holding the children (Inventory objects).
     */
    HolderMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_BOMROOT_HPP
