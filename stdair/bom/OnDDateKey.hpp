#ifndef __STDAIR_BOM_ONDDATEKEY_HPP
#define __STDAIR_BOM_ONDDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

namespace stdair {

  /**
   * @brief Key of a given O&D-date, made of a list of full keys.
   * a full key is a string containing the airline code, flight number,
   * date and segment (origin and destination).
   */
  struct OnDDateKey : public KeyAbstract {
    friend class boost::serialization::access;

    // /////////// Constructors and destructors ///////////
  private:
    /**
     * Default constructor.
     */
    OnDDateKey();

  public:
    /**
     * Constructor.
     */
    OnDDateKey (const FullKeyList_T&);

    /**
     * Copy constructor.
     */
    OnDDateKey (const OnDDateKey&);

    /**
     * Destructor.
     */
    ~OnDDateKey();


  public:
    // /////////// Getters //////////
    /** Get the boarding date. */
    const Date_T getDate() const;
    /** Get the origin. */
    const AirportCode_T getOrigin() const;
    /** Get the destination. */
    const AirportCode_T getDestination() const;
    /** Get the number of segments. */
    const short getNbOfSegments () const {
      return _fullKeyList.size();
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
     * marketing classes for the same segment-date.
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
    FullKeyList_T _fullKeyList;
    
  };

}
#endif // __STDAIR_BOM_ONDDATEKEY_HPP
