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
#include <stdair/bom/FRAT5CurveHolderStruct.hpp>
#include <stdair/bom/FFDisutilityCurveHolderStruct.hpp>

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
    template <typename BOM> friend class FacCloneBom;
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
    
    /** Get the FRAT5 curve corresponding to the given key. */
    const FRAT5Curve_T& getFRAT5Curve (const std::string& iKey) const {
      return _frat5CurveHolder.getFRAT5Curve (iKey);
    }

    /** Get the FFDisutility curve corresponding to the given key. */
    const FFDisutilityCurve_T& getFFDisutilityCurve (const std::string& iKey) const{
      return _ffDisutilityCurveHolder.getFFDisutilityCurve (iKey);
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

    // ///////////// Business Methods //////////
    /** Add a new FRAT5 curve to the holder. */
    void addFRAT5Curve (const std::string& iKey, const FRAT5Curve_T& iCurve) {
      _frat5CurveHolder.addCurve (iKey, iCurve);
    }
    
    /** Add a new FF disutility curve to the holder. */
    void addFFDisutilityCurve (const std::string& iKey,
                               const FFDisutilityCurve_T& iCurve) {
      _ffDisutilityCurveHolder.addCurve (iKey, iCurve);
    }


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
     *
     * That method is used both for serialisation a BOM tree (into a
     * backup file/stream), as well as re-instantiating a BOM tree
     * from a back-up file/stream.
     *
     * \note The implementation of that method is to be found in the
     *       CmdBomSerialiser command.
     */
    template<class Archive>
    void serialize (Archive& ar, const unsigned int iFileVersion);

  private:
    /**
     * Serialisation helpers (allows to be sure the template method is
     * instantiated).
     *
     * \note The implementation of these methods is to be found in the
     *       CmdBomSerialiser command.
     */
    void serialisationImplementationExport() const;
    void serialisationImplementationImport();


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

    /**
     * Holder of FRAT5 curves.
     */
    FRAT5CurveHolderStruct _frat5CurveHolder;

    /**
     * Holder of fare family disutility curves.
     */
    FFDisutilityCurveHolderStruct _ffDisutilityCurveHolder;
  };

}
#endif // __STDAIR_BOM_BOMROOT_HPP
