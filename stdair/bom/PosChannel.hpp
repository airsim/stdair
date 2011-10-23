#ifndef __STDAIR_BOM_POSCHANNEL_HPP
#define __STDAIR_BOM_POSCHANNEL_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/PosChannelKey.hpp>
#include <stdair/bom/PosChannelTypes.hpp>

// Forward declaration
namespace stdair {
  template <typename BOM> class FacBom;
  class FacBomManager;

  /** Class representing the actual attributes for a fare point of sale. */
  class PosChannel : public stdair::BomAbstract {
    template <typename BOM> friend class stdair::FacBom;
    friend class stdair::FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef PosChannelKey Key_T;
  
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
    const CityCode_T& getPos() const {
      return _key.getPos();
    }
    const ChannelLabel_T& getChannel() const {
      return _key.getChannel();
    }
    BomAbstract* const getParent() const { return _parent; }
    const  stdair::HolderMap_T& getHolderMap() const { return _holderMap; }
    
  protected:
    /** Default constructors. */
    PosChannel (const Key_T&);
    PosChannel (const PosChannel&);
    /** Destructor. */
    ~PosChannel();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_POSCHANNEL_HPP

