#ifndef __STDAIR_BOM_SIMPLENESTINGSTRUCTURE_HPP
#define __STDAIR_BOM_SIMPLENESTINGSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/NestingNodeTypes.hpp>
#include <stdair/bom/SimpleNestingStructureTypes.hpp>
#include <stdair/bom/NestingStructureKey.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {    

  /**
   * Structure holding a nesting node map according to the yield.
   */
  class SimpleNestingStructure : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef NestingStructureKey Key_T;
      
  public:
    // /////////////////// Getters ////////////////////////
    /** Get the nesting key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /**
     * Get the map of children holders.
     */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
    /**
     * Get the nesting node list
     */
    const NestingNodeList_T& getNestingNodeList() const;
    
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

      
  public:
    // /////////// Constructors and destructor. ////////////
    /**
     * Main constructor.
     */
    SimpleNestingStructure (const Key_T&);
      
    /**
     * Destructor.
     */
    virtual ~SimpleNestingStructure();

  private:
    /**
     * Default constructor.
     */
    SimpleNestingStructure();

    /**
     * Copy constructor.
     */
    SimpleNestingStructure (const SimpleNestingStructure&);
     
  private:
    /**
     * Primary key (a number).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (SegmentCabin).
     */
    BomAbstract* _parent;

    /**
     * Map holding the children (NestingNode objects).
     */
    HolderMap_T _holderMap;
  };
}
#endif // __STDAIR_BOM_SIMPLENESTINGSTRUCTURE_HPP
