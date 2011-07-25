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

  /** Class representing the actual attributes for an airport-pair. */
  class AirportPair : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager; 

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef AirportPairKey Key_T;
  
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the key. */
    const std::string describeKey() const { return _key.toString(); }

  public:
    // ////////// Getters ////////////
    const Key_T& getKey() const { return _key; }
    const AirportCode_T& getBoardingPoint() const {
      return _key.getBoardingPoint();
    }
    const AirportCode_T& getOffPoint() const {
      return _key.getOffPoint();
    }
    BomAbstract* const getParent() const { return _parent; }
    const HolderMap_T& getHolderMap() const { return _holderMap; }
    
  protected:
    /** Default constructors. */
    AirportPair (const Key_T&);
    AirportPair (const AirportPair&);
    /** Destructor. */
    virtual ~AirportPair();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_AIRPORTPAIR_HPP

