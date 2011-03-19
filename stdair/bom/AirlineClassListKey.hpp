#ifndef __STDAIR_BOM_AIRLINECLASSLISTKEY_HPP
#define __STDAIR_BOM_AIRLINECLASSLISTKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair  {

  /**
   * @brief Key of airport-pair.
   */
  struct AirlineClassListKey : public KeyAbstract {
    friend class boost::serialization::access;

    // /////////// Constructors and destructors ///////////
  private:
    /**
     * Default constructor.
     */
    AirlineClassListKey();

  public:
    /**
     * Constructor.
     */
    AirlineClassListKey (const AirlineCodeList_T&,
                         const ClassList_StringList_T&);

    /**
     * Copy constructor.
     */
    AirlineClassListKey (const AirlineClassListKey&);

    /**
     * Destructor.
     */
    ~AirlineClassListKey();
    

  public:
    // /////////// Getters //////////
    /** Get the airline code list. */
    const AirlineCodeList_T& getAirlineCodeList() const {
      return _airlineCodeList;
    }

    /** Get the class code list. */
    const ClassList_StringList_T& getClassCodeList() const {
      return _classCodeList;
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
    /**
     * Airline code List.
     */
    AirlineCodeList_T _airlineCodeList;

    /**
     * Classe code List.
     */
    ClassList_StringList_T _classCodeList;
  };

}
#endif // __STDAIR_BOM_AIRLINECLASSLISTKEY_HPP
