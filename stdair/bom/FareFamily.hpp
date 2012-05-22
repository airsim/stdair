#ifndef __STDAIR_BOM_FAREFAMILY_HPP
#define __STDAIR_BOM_FAREFAMILY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_rm_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/FareFamilyKey.hpp>
#include <stdair/bom/FareFamilyTypes.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /**
   * @brief Class representing the actual attributes for a family fare.
   */
  class FareFamily : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    friend class boost::serialization::access;

  public:
    // ////////// Type definitions ////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef FareFamilyKey Key_T;


  public:
    // /////////// Getters ////////////
    /** Get the family fare key. */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the parent object. */
    BomAbstract* const getParent() const {
      return _parent;
    }

    /** Get the family fare code (part of the primary key). */
    const FamilyCode_T& getFamilyCode() const {
      return _key.getFamilyCode();
    }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
    /** Get the FRAT5 Curve. */
    const FRAT5Curve_T& getFrat5Curve () const {
      return _frat5Curve;
    }
        
    /** Get the Disutility Curve. */
    const FFDisutility_T& getDisutilityCurve () const {
      return _disutilityCurve;
    }
    
    /** Demand distribution. */
    const MeanValue_T& getMean () const { return _mean; }
    const StdDevValue_T& getStdDev () const {return _stdDev; }

    /** Demand distribution. */
    const MeanStdDevPairVector_T& getMeanStdDev () const {return _meanStdDev; }


  public:
    // /////////// Setters ////////////
    /** FRAT5 Curve. */
    void setFrat5Curve (const FRAT5Curve_T& iFRAT5Curve) {
      _frat5Curve = iFRAT5Curve;
    }
    
    /** Disutility Curve. */
    void setDisutilityCurve (const FFDisutility_T& iDisutilityCurve) {
      _disutilityCurve = iDisutilityCurve;
    }
    
    /** Demand distribution. */
    void setMean (const MeanValue_T& iMean) { _mean = iMean; }
    void setStdDev (const StdDevValue_T& iStdDev) { _stdDev = iStdDev; }
    
    /** Demand distribution. */
    void setMeanStdDev (const MeanStdDevPairVector_T& iMeanStdDev){ 
      _meanStdDev = iMeanStdDev; 
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
     * Serialisation helpers (allows to be sure the template method is
     * instantiated).
     */
    void serialisationImplementationExport() const;
    void serialisationImplementationImport();
 

  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Constructor.
     */
    FareFamily (const Key_T&);

    /**
     * Destructor.
     */
    virtual ~FareFamily();


  private:
    /**
     * Default constructor.
     */
    FareFamily();

    /**
     * Copy constructor.
     */
    FareFamily (const FareFamily&);


  public:
    // ////////// Attributes /////////
    /**
     * Primary key (fare family code).
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
     * The associated FRAT5 curve. 
     */
    FRAT5Curve_T _frat5Curve;

    /**
     * The associated disutility for the next higher fare family.
     */
    FFDisutility_T _disutilityCurve;

    /** Demand distribution forecast. */
    MeanValue_T _mean;
    StdDevValue_T _stdDev;

    /**
     * Achievable demand distribution forecast.
     */
    MeanStdDevPairVector_T _meanStdDev;
  };

}
#endif // __STDAIR_BOM_FAREFAMILY_HPP

