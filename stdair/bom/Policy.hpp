#ifndef __STDAIR_BOM_POLICY_HPP
#define __STDAIR_BOM_POLICY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cmath>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_rm_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/PolicyKey.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {    

  /**
   * Structure holding the elements of a policy.
   * A policy is a set of booking classes, each booking class belongs to
   * a different Fare Family.
   */
  class Policy : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef PolicyKey Key_T;
      
  public:
    // /////////////////// Getters ////////////////////////
    /** Get the policy key. */
    const Key_T& getKey() const {
      return _key;
    }

    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /**
     * Get the map of children holders.
     */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }

    /** Getter for the booking classes. */
    const BookingClassList_T& getBookingClassList() const;
    
    /** Getter for the demand. */
    const NbOfBookings_T& getDemand() const {
      return _demand;
    }
    
    /** Getter for the standard deviation demand. */
    const StdDevValue_T& getStdDev() const {
      return _stdDev;
    }
    
    /** Getter for the yield. */
    const Yield_T& getYield() const {
      return _yield;
    }

    /** Get the total revenue of the policy. */
    const Revenue_T getTotalRevenue () const;
    
  public:
    // ///////////////////// Setters /////////////////////
    /** Setter for the unconstraining demand. */
    void setDemand (const NbOfBookings_T& iDemand) {
      _demand = iDemand;
    }
    
    /** Setter for standard deviation demand. */
    void setStdDev (const StdDevValue_T& iStdDev) {
      _stdDev = iStdDev;
    }
    
    /** Setter for the yield. */
    void setYield (const Yield_T& iYield) {
      _yield = iYield;
    }

    /** Reset demand forecast. */
    void resetDemandForecast () {
      _demand = 0.0;
      _stdDev = 0.0;
      _yieldDemandMap.clear();
    }

    /** Add the new pair (yield, demand) to the map. */
    void addYieldDemand (const Yield_T&, const NbOfBookings_T&);  
    
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
     * Serialisation helpers (allows to be sure the template method is
     * instantiated).
     *
     * \note The implementation of these methods is to be found in the
     *       CmdBomSerialiser command.
     */
    void serialisationImplementationExport() const;
    void serialisationImplementationImport();

      
  protected:
    // /////////// Constructors and destructor. ////////////
    /**
     * Main constructor.
     */
    Policy (const Key_T&);
      
    /**
     * Destructor.
     */
    virtual ~Policy();

  private:
    /**
     * Default constructor.
     */
    Policy();

    /**
     * Copy constructor.
     */
    Policy (const Policy&);
    
      
  private:
    // //////////// Attributes ////////////
    /**
     * Primary key (a number).
     */
    Key_T _key;

    /**
     * Pointer on the parent class (SegmentCabin).
     */
    BomAbstract* _parent;

    /**
     * Map holding the children (BookingClass objects).
     */
    HolderMap_T _holderMap;

    /**
     * Demand of the policy
     */
    NbOfBookings_T _demand;

    /**
     * Standard deviation of the demand.
     */
    StdDevValue_T _stdDev;

    /**
     * Adjusted yield of the policy
     */
    Yield_T _yield;

    /**
     * Yield demand map. Used of total demand computation.
     */
    YieldDemandMap_T _yieldDemandMap;

  };
}
#endif // __STDAIR_BOM_POLICY_HPP
