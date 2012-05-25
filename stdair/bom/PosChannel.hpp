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

  /**
   * @brief Class representing the actual attributes for a fare point of
   * sale.
   */
  class PosChannel : public BomAbstract {
    template <typename BOM> friend class FacBom;  
    template <typename BOM> friend class FacCloneBom;
    friend class FacBomManager;

  public:
    // /////// Type definitions
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef PosChannelKey Key_T;
  
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
    // ////////// Getters ////////////
    /**
     * Get the primary key (pos, channel).
     */
    const Key_T& getKey() const {
      return _key;
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
    const  stdair::HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
    /**
     * Get the point-of-sale.
     */
    const CityCode_T& getPos() const {
      return _key.getPos();
    }

    /**
     * Get the channel.
     */
    const ChannelLabel_T& getChannel() const {
      return _key.getChannel();
    }
    
  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    PosChannel (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~PosChannel();

  private:
    /**
     * Default constructor.
     */
    PosChannel ();

    /**
     * Default copy constructor.
     */
    PosChannel (const PosChannel&);

  protected:
    // ////////// Attributes /////////
    /**
     * Primary key (flight number and departure date).
     */
    Key_T _key;
    
    /**
     * Pointer on the parent class.
     */
    BomAbstract* _parent;

    /**
     * Map holding the children.
     */
    HolderMap_T _holderMap;

  };

}
#endif // __STDAIR_BOM_POSCHANNEL_HPP

