#ifndef __STDAIR_BOM_AIRPORTPAIR_HPP
#define __STDAIR_BOM_AIRPORTPAIR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/AirportPairKey.hpp>
#include <stdair/bom/AirportPairTypes.hpp>

// Forward declaration
namespace stdair {

  /**
   * @brief Class representing the actual attributes for an airport-pair.
   */
  class AirportPair : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager; 

  public:
    // //////////// Type definitions //////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef AirportPairKey Key_T;
  
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
     * Get a string describing the key.
     */
    const std::string describeKey() const {
      return _key.toString();
    }

  public:
    // ////////// Getters ////////////
    /**
     * Get the primary key (origin airport, destination airport).
     */
    const Key_T& getKey() const {
      return _key;
    }
    
    /**
     * Get the origin airport. 
     */
    const AirportCode_T& getBoardingPoint() const {
      return _key.getBoardingPoint();
    }

    /**
     * Get the destination airport. 
     */
    const AirportCode_T& getOffPoint() const {
      return _key.getOffPoint();
    }

    /**
     * Get a reference on the parent object instance.
     */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /**
     * Get a reference on the children holder.
     */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    AirportPair (const Key_T&);  
    /**
     * Destructor.
     */
    virtual ~AirportPair();

  private:
    /**
     * Default constructor.
     */
    AirportPair(); 
    /**
     * Copy constructor.
     */
    AirportPair (const AirportPair&);

  protected:
    // ///////////// Attributes /////////////
    /**
     * Primary key (flight number and departure date).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (Inventory).
     */
    BomAbstract* _parent;

    /**
     * Map holding the children.
     */
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_AIRPORTPAIR_HPP

