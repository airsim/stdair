#ifndef __STDAIR_BOM_FLIGHTDATE_HPP
#define __STDAIR_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir 
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/FlightDateTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /// Forward declarations
  struct LegDateKey;
  class LegDate;
  struct SegmentDateKey;
  class SegmentDate;

  /**
   * @brief Class representing the actual attributes for an airline
   * flight-date.
   */
  class FlightDate : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef FlightDateKey Key_T;

    
  public:
    // /////////// Getters ///////////////
    /** Get the flight-date key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }
    
    /** Get the flight number (part of the primary key). */
    const FlightNumber_T& getFlightNumber() const {
      return _key.getFlightNumber();
    }

    /** Get the flight date (part of the primary key). */
    const Date_T& getDepartureDate() const {
      return _key.getDepartureDate();
    }

    /** Get the guilltine block number. */
    const GuillotineNumber_T& getGuillotineBlockNumber() const {
      return _guillotineNumber;
    }

    /**
     * Get the airline code (key of the parent object).
     *
     * \note That method assumes that the parent object derives from
     *       the Inventory class, as it needs to have access to the
     *       getAirlineCode() method.
     */
    const AirlineCode_T& getAirlineCode() const;

    /**
     * Get the map of children holders.
     */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
    /**
     * Get a pointer on the LegDate object corresponding to the
     * given key.
     *
     * \note The LegDate object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const std::string& The leg-date key.
     * @return LegDate* Found LegDate object. NULL if not found.
     */
    LegDate* getLegDate (const std::string& iLegDateKeyStr) const;

    /**
     * Get a pointer on the LegDate object corresponding to the
     * given key.
     *
     * \note The LegDate object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const LegDateKey& The leg-date key
     * @return LegDate* Found LegDate object. NULL if not found.
     */
    LegDate* getLegDate (const LegDateKey&) const;

    /**
     * Get a pointer on the SegmentDate object corresponding to the
     * given key.
     *
     * \note The SegmentDate object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const std::string& The segment-date key.
     * @return SegmentDate* Found SegmentDate object. NULL if not found.
     */
    SegmentDate* getSegmentDate (const std::string& iSegmentDateKeyStr) const;

    /**
     * Get a pointer on the SegmentDate object corresponding to the
     * given key.
     *
     * \note The SegmentDate object can be inherited from, if needed.
     *       In that case, a dynamic_cast<> may be needed.
     *
     * @param const SegmentDateKey& The segment-date key
     * @return SegmentDate* Found SegmentDate object. NULL if not found.
     */
    SegmentDate* getSegmentDate (const SegmentDateKey&) const;

  public:
    // /////////// Setters /////////////
    /** Set the guillotine block number. */
    void setGuillotineBlockNumber (const GuillotineNumber_T& iNumber) {
      _guillotineNumber = iNumber;
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
    FlightDate (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~FlightDate();

  private:
    /**
     * Default constructor.
     */
    FlightDate();

    /**
     * Copy constructor.
     */
    FlightDate (const FlightDate&);
    

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

    /**
     * The guillotine block number.
     */
    GuillotineNumber_T _guillotineNumber;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATE_HPP

