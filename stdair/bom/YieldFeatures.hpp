#ifndef __STDAIR_BOM_YIELDFEATURES_HPP
#define __STDAIR_BOM_YIELDFEATURES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/YieldFeaturesKey.hpp>
#include <stdair/bom/YieldFeaturesTypes.hpp>

// Forward declaration
namespace stdair {

  /**
   * @brief Class representing the actual attributes for a yield
   *        date-period.
   */
  class YieldFeatures : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // /////// Type definitions
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef YieldFeaturesKey Key_T;
  
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
     * Get the primary key (trip type, cabin code).
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
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /**
     * Get the cabin code.
     */
    const CabinCode_T& getCabinCode() const {
      return _key.getCabinCode();
    }

    /**
     * Get the trip type.
     */
    const TripType_T& getTripType() const {
      return _key.getTripType();
    }


  public:
    // ////////////// Business methods ///////////////
    /**
     * Check whether the fare rule trip type corresponds to the booking
     * request trip type.
     */
    bool isTripTypeValid (const TripType_T&) const;

    
  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    YieldFeatures (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~YieldFeatures();

  private:
    /**
     * Default constructor.
     */
    YieldFeatures();

    /**
     * Default copy constructor.
     */
    YieldFeatures (const YieldFeatures&);


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
#endif // __STDAIR_BOM_YIELDFEATURES_HPP

