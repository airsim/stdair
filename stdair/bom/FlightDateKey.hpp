#ifndef __STDAIR_BOM_FLIGHTDATEKEY_HPP
#define __STDAIR_BOM_FLIGHTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /**
   * @brief Key of a given flight-date, made of a flight number and a
   * departure date.
   */
  struct FlightDateKey : public KeyAbstract {
    friend class boost::serialization::access;

    // /////////// Constructors and destructors ///////////
  private:
    /**
     * Default constructor.
     */
    FlightDateKey();

  public:
    /**
     * Constructor.
     */
    FlightDateKey (const FlightNumber_T&, const Date_T&);
    /**
     * Copy constructor.
     */
    FlightDateKey (const FlightDateKey&);
    /**
     * Destructor.
     */
    ~FlightDateKey();


    // /////////// Getters //////////
    /** Get the flight number. */
    const FlightNumber_T& getFlightNumber() const {
      return _flightNumber;
    }

    /** Get the departure date of the (first leg of the) flight. */
    const Date_T& getFlightDate() const {
      return _flightDate;
    }


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
     * Flight number.
     */
    FlightNumber_T _flightNumber;

    /**
     * Departure date of the (first leg of the) flight.
     */
    Date_T _flightDate;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATEKEY_HPP
