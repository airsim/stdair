#ifndef __STDAIR_BOM_NESTINGNODE_HPP
#define __STDAIR_BOM_NESTINGNODE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cmath>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_rm_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/NestingNodeKey.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {    

  /**
   * Structure holding the elements of a nesting node.
   * A nesting node is a set of booking classes.
   */
  class NestingNode : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef NestingNodeKey Key_T;
      
  public:
    // /////////////////// Getters ////////////////////////
    /** Get the policy key. */
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
    
    /** Getter for the yield. */
    const Yield_T& getYield() const {
      return _yield;
    }
    
  public:
    // ///////////////////// Setters /////////////////////    
    /** Setter for the yield. */
    void setYield (const Yield_T& iYield) {
      _yield = iYield;
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
    // /////////// Constructors and destructor. ////////////
    /**
     * Main constructor.
     */
    NestingNode (const Key_T&);
      
    /**
     * Destructor.
     */
    virtual ~NestingNode();

  private:
    /**
     * Default constructor.
     */
    NestingNode();

    /**
     * Copy constructor.
     */
    NestingNode (const NestingNode&);
    
      
  private:
    // //////////// Attributes ////////////
    /**
     * Primary key (a number).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (SegmentCabin).
     */
    BomAbstract* _parent;

    /**
     * Map holding the children (BookingClass objects).
     */
    HolderMap_T _holderMap;

    /**
     * Yield of the node
     */
    Yield_T _yield;

  };
}
#endif // __STDAIR_BOM_NESTINGNODE_HPP
