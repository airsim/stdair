#ifndef __STDAIR_BOM_AIRLINECLASSLIST_HPP
#define __STDAIR_BOM_AIRLINECLASSLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/AirlineClassListKey.hpp>
#include <stdair/bom/AirlineClassListTypes.hpp>

// Forward declaration
namespace stdair {

  /** Class representing the actual attributes for a segment-features. */
  class AirlineClassList : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef AirlineClassListKey Key_T;
  
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
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return _key.toString(); }

  public:
    // ////////// Getters ////////////
    const Key_T& getKey() const { return _key; }
    const AirlineCodeList_T& getAirlineCodeList() const {
      return _key.getAirlineCodeList();
    }
    const ClassList_StringList_T& getClassCodeList() const {
      return _key.getClassCodeList();
    }
    BomAbstract* const getParent() const { return _parent; }
    const  HolderMap_T& getHolderMap() const { return _holderMap; }
    
  protected:
    /** Default constructors. */
    AirlineClassList (const Key_T&);
    AirlineClassList (const AirlineClassList&);
    /** Destructor. */
    ~AirlineClassList();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_AIRLINECLASSLIST_HPP

