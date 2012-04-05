#ifndef __STDAIR_BOM_INVENTORY_HPP
#define __STDAIR_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/basic/UnconstrainingMethod.hpp>
#include <stdair/basic/PartnershipTechnique.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/InventoryTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {
  
  /// Forward declarations
  struct FlightDateKey;
  class FlightDate;

  /**
   * @brief Class representing the actual attributes for an airline inventory
   */
  class Inventory : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public :
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef InventoryKey Key_T;


  public:
    // ////////// Getters ////////////
    /** Get the inventory key (airline code). */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the airline code (inventory/primary key). */
    const AirlineCode_T& getAirlineCode() const {
      return _key.getAirlineCode();
    }

    /** Get the unconstraining method. */
    UnconstrainingMethod::EN_UnconstrainingMethod getUnconstrainingMethod() const {
      if (_airlineFeature == NULL) {
        return DEFAULT_UNCONSTRAINING_METHOD.getMethod();
      }
      assert (_airlineFeature != NULL);
      return _airlineFeature->getUnconstrainingMethod();
    }

    /** Get the partnership technique. */
    PartnershipTechnique::EN_PartnershipTechnique getPartnershipTechnique() const {
      if (_airlineFeature == NULL) {
        return DEFAULT_PARTNERSHIP_TECHNIQUE.getTechnique();
      }
      assert (_airlineFeature != NULL);
      return _airlineFeature->getPartnershipTechnique();
    }
    
    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /** Get the map of children. */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
    /**
     * Get a pointer on the FlightDate object corresponding to the
     * given key.
     *
     * \note The FlightDate object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const std::string& The flight-date key.
     * @return FlightDate* Found FlightDate object. NULL if not found.
     */
    FlightDate* getFlightDate (const std::string& iFlightDateKeyStr) const;

    /**
     * Get a pointer on the FlightDate object corresponding to the
     * given key.
     *
     * \note The FlightDate object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const FlightDateKey& The flight-date key
     * @return FlightDate* Found FlightDate object. NULL if not found.
     */
    FlightDate* getFlightDate (const FlightDateKey&) const;


  public:
    // /////////// Setters ////////////
    /** Set the airline feature. */
    void setAirlineFeature (const AirlineFeature* ioAirlineFeaturePtr) {
      _airlineFeature = ioAirlineFeaturePtr;
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
     * Constructor.
     */
    Inventory (const Key_T&);
    /**
     * Destructor.
     */
    ~Inventory();

  private:
    /**
     * Default constructor.
     */
    Inventory();
    /**
     * Default copy constructor.
     */
    Inventory (const Inventory&);

    
  protected:
    // ////////// Attributes /////////
    /**
     * Primary key (airline code).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (BomRoot).
     */
    BomAbstract* _parent;

    /**
     * Features specific to the airline.
     */
    const AirlineFeature* _airlineFeature;

    /**
     * Map holding the children (FlightDate objects).
     */
    HolderMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_INVENTORY_HPP

