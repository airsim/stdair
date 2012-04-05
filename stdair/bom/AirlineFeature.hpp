#ifndef __STDAIR_BOM_AIRLINEFEATURE_HPP
#define __STDAIR_BOM_AIRLINEFEATURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_rm_types.hpp>
#include <stdair/basic/UnconstrainingMethod.hpp>
#include <stdair/basic/PartnershipTechnique.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/AirlineFeatureKey.hpp>
#include <stdair/bom/AirlineFeatureTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline booking class. */
  class AirlineFeature : public BomAbstract {
    template <typename BOM> friend class FacBom;
    
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef AirlineFeatureKey Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the airline feature key. */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the unconstraining method. */
    UnconstrainingMethod::EN_UnconstrainingMethod getUnconstrainingMethod() const {
      return _unconstrainingMethod.getMethod();
    }

    /** Get the partnership method. */
    PartnershipTechnique::EN_PartnershipTechnique getPartnershipTechnique() const {
      return _partnershipTechnique.getTechnique();
    }  

  public:
    // //////////// Setters //////////
    /** Intialization method. */
    void init (const ForecasterMode_T&,
               const UnconstrainingMethod&,
               const HistoricalDataLimit_T&,
               const ControlMode_T&,
               const PartnershipTechnique&);
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the key. */
    const std::string describeKey() const { return _key.toString(); }
    
  protected:
    /** Default constructors. */
    AirlineFeature ();
    AirlineFeature (const AirlineFeature&);
    AirlineFeature (const Key_T&);
    /** Destructor. */
    virtual ~AirlineFeature();

  protected:
    // Attributes
    /** The key of both structure and  objects. */
    Key_T _key;

    /** The type of forecaster. */
    ForecasterMode_T _forecasterMode;

    /** The size of the moving average window. */
    HistoricalDataLimit_T _historicalDataLimit;

    /** The type of inventory control. */
    ControlMode_T _controlMode;

    /** The type of unconstraining method. */
    UnconstrainingMethod _unconstrainingMethod;

    /** The type of partnership technique. */
    PartnershipTechnique _partnershipTechnique;
 
  };

}
#endif // __STDAIR_BOM_AIRLINEFEATURE_HPP

