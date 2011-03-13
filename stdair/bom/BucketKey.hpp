#ifndef __STDAIR_BOM_BUCKETKEY_HPP
#define __STDAIR_BOM_BUCKETKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {
  
  /**
   * @brief Key of booking-class.
   */
  struct BucketKey : public KeyAbstract {
    friend class boost::serialization::access;
    
    // /////////// Constructors and destructors ///////////
  private:
    /**
     * Default constructor.
     */
    BucketKey();

  public:
    /**
     * Main constructor.
     */
    BucketKey (const SeatIndex_T&);
    /**
     * Copy constructor.
     */
    BucketKey (const BucketKey&);
    /**
     * Destructor.
     */
    ~BucketKey();
    

  public:
    // /////////// Getters //////////
    /** Get the seat index. */
    const SeatIndex_T& getSeatIndex() const {
      return _seatIndex;
    }


  public:
    // /////////// Display support methods /////////
    /**
     * Dump a Business Object Key into an output stream.
     *
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;

    /**
     * Read a Business Object Key from an input stream.
     *
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn);

    /**
     * Get the serialised version of the Business Object Key.
     *
     * That string is unique, at the level of a given Business Object,
     * when among children of a given parent Business Object.
     *
     * For instance, "H" and "K" allow to differentiate among two
     * marketing classes for the same segment-cabin.
     */
    const std::string toString() const;


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


  private:
    // ///////////////// Attributes ///////////////
    /**
     * Seat index.
     */
    SeatIndex_T _seatIndex;
  };

}
#endif // __STDAIR_BOM_BUCKETKEY_HPP
