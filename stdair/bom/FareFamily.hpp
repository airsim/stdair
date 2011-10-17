#ifndef __STDAIR_BOM_FAREFAMILY_HPP
#define __STDAIR_BOM_FAREFAMILY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir 
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/FareFamilyKey.hpp>
#include <stdair/bom/FareFamilyTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /**
   * @brief Class representing the actual attributes for a family fare.
   */
  class FareFamily : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef FareFamilyKey Key_T;


  public:
    // /////////// Getters ////////////
    /** Get the family fare key. */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /** Get the family fare code (part of the primary key). */
    const FamilyCode_T& getFamilyCode() const {
      return _key.getFamilyCode();
    }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
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
     */
    void serialisationImplementationExport() const;
    void serialisationImplementationImport();


  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Constructor.
     */
    FareFamily (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~FareFamily();

  private:
    /**
     * Default constructor.
     */
    FareFamily();

    /**
     * Copy constructor.
     */
    FareFamily (const FareFamily&);


  public:
    // ////////// Attributes /////////
    /**
     * Primary key (fare family code).
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
  };

}
#endif // __STDAIR_BOM_FAREFAMILY_HPP

