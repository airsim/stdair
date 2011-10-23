#ifndef __STDAIR_BOM_ONDDATE_HPP
#define __STDAIR_BOM_ONDDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir 
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/stdair_rm_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/OnDDateKey.hpp>
#include <stdair/bom/OnDDateTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /**
   * @brief Class representing the actual attributes for an airline
   * flight-date.
   */
  class OnDDate : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef OnDDateKey Key_T;

    
  public:
    // /////////// Getters ///////////////
    /** Get the O&D date key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /**
     * Get the airline code (key of the parent object).
     *
     * \note That method assumes that the parent object derives from
     *       the Inventory class, as it needs to have access to the
     *       getAirlineCode() method.
     */
    const AirlineCode_T& getAirlineCode() const;
    

    /** Get the boarding date. */
    const stdair::Date_T getDate() const {
      return _key.getDate();
    }

    /** Get the origin. */
    const stdair::AirportCode_T getOrigin() const {
      return _key.getOrigin();
    }

    /** Get the destination. */
    const stdair::AirportCode_T getDestination() const {
      return _key.getDestination();
    }
    
    /**
     * Get the map of children holders.
     */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /**
     * Get the map of demand information.
     */
    const StringDemandStructMap_T& getDemandInfoMap () const {
      return _classPathDemandMap;
    }

    /**
     * Get the map of total forecast.
     */
    const CabinForecastMap_T& getTotalForecastMap () const {
      return _cabinForecastMap;
    }

    /**
     * Get the total forecast for a given cabin.
     */
    const WTPDemandPair_T& getTotalForecast (const CabinCode_T& iCC) const {
      assert (_cabinForecastMap.find(iCC)!=_cabinForecastMap.end());
      return _cabinForecastMap.find(iCC)->second;
    }

    /**
     * Get the cabin-class pair out of a string.
     */
    const CabinClassPairList_T& getCabinClassPairList (const std::string& iStr) {
      assert (_stringCabinClassPairListMap.find(iStr)!=_stringCabinClassPairListMap.end());
      return _stringCabinClassPairListMap.find(iStr)->second;
    }

    /**
     * Get the number of segments of the O&D.
     */
    const short getNbOfSegments () const {
      return _key.getNbOfSegments();
    }

  public:
    // /////////// Setters ///////////////
    /** Set demand information. */
    void setDemandInformation (const CabinClassPairList_T&,
                               const YieldDemandPair_T&);
                              

    /** Set forecast information per cabin. */
    void setTotalForecast (const CabinCode_T&,
                           const WTPDemandPair_T&);

    
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
    OnDDate (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~OnDDate();

  private:
    /**
     * Default constructor.
     */
    OnDDate();

    /**
     * Copy constructor.
     */
    OnDDate (const OnDDate&);
    

  protected:
    // ////////// Attributes /////////
    /**
     * Primary key (list of OnD string keys).
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
     * O&D demand information.
     */
    StringDemandStructMap_T _classPathDemandMap;

     /**
     * O&D cabin and associated class map.
     */
    StringCabinClassPairListMap_T _stringCabinClassPairListMap;

    /**
     * O&D demand total forecast.
     */
    CabinForecastMap_T _cabinForecastMap;
  };

}
#endif // __STDAIR_BOM_ONDDATE_HPP
