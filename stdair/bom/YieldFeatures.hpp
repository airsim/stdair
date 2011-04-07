#ifndef __STDAIR_BOM_YIELDFEATURES_HPP
#define __STDAIR_BOM_YIELDFEATURES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/YieldFeaturesKey.hpp>
#include <stdair/bom/YieldFeaturesTypes.hpp>

// Forward declaration
namespace stdair {

  /** Class representing the actual attributes for a yield date-period. */
  class YieldFeatures : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef YieldFeaturesKey Key_T;
  
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
    stdair::BomAbstract* const getParent() const { return _parent; }
    const  stdair::HolderMap_T& getHolderMap() const { return _holderMap; }

    /** Get the cabin. */
    const stdair::CabinCode_T& getCabinCode() const {
      return _key.getCabinCode();
    }
    
    /** Get the yield. */
    const stdair::Yield_T& getYield() const {
      return _key.getYield();
    }

  protected:
    /** Default constructors. */
    YieldFeatures (const Key_T&);
    YieldFeatures (const YieldFeatures&);
    /** Destructor. */
    ~YieldFeatures();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_YIELDFEATURES_HPP

