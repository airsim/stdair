#ifndef __STDAIR_BOM_AIRLINECLASSLIST_HPP
#define __STDAIR_BOM_AIRLINECLASSLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/AirlineClassListKey.hpp>
#include <stdair/bom/AirlineClassListTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /**
   * @brief Class representing the actual attributes for a segment-features.
   */
  class AirlineClassList : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef AirlineClassListKey Key_T;
  

  public:
    // ////////// Getters ////////////
    /** Get the airline class list key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /** Get the airline code list (part of the primary key). */
    const AirlineCodeList_T& getAirlineCodeList() const {
      return _key.getAirlineCodeList();
    }

    /** Get the class code list (part of the primary key). */
    const ClassList_StringList_T& getClassCodeList() const {
      return _key.getClassCodeList();
    }

    /** Get the map of children holders. */
    const  HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
    /** Get the yield. */
    const stdair::Yield_T& getYield() const {
      return _yield;
    }

  public:
    // /////////// Setters //////////////
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
     * Serialisation helper (allows to be sure the template method is
     * instantiated).
     */
    void serialisationImplementation();


  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    AirlineClassList (const Key_T&);
    /**
     * Destructor.
     */
    ~AirlineClassList();

  private:
    /**
     * Default constructor.
     */
    AirlineClassList();

    /**
     * Copy constructor.
     */
    AirlineClassList (const AirlineClassList&);


  protected:
    // ////////// Attributes /////////
    /**
     * Primary key (flight number and departure date).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (Inventory).
     */
    BomAbstract* _parent;

    /**
     * Map holding the children (SegmentDate and LegDate objects).
     */
    HolderMap_T _holderMap;
 
    /*
     * Yield value.
     */
    stdair::Yield_T _yield;
  };

}
#endif // __STDAIR_BOM_AIRLINECLASSLIST_HPP

