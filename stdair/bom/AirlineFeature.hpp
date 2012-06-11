#ifndef __STDAIR_BOM_AIRLINEFEATURE_HPP
#define __STDAIR_BOM_AIRLINEFEATURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_rm_types.hpp>
#include <stdair/basic/UnconstrainingMethod.hpp>
#include <stdair/basic/ForecastingMethod.hpp>
#include <stdair/basic/PreOptimisationMethod.hpp>
#include <stdair/basic/OptimisationMethod.hpp>
#include <stdair/basic/PartnershipTechnique.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/AirlineFeatureKey.hpp>
#include <stdair/bom/AirlineFeatureTypes.hpp>

namespace stdair {

  /**
   * @brief Class representing the actual attributes for an airline booking class.
   */
  class AirlineFeature : public BomAbstract {
    template <typename BOM> friend class FacBom;
    template <typename BOM> friend class FacCloneBom;
    friend class FacBomManager;	
    
  public:
    // //////////// Type definitions //////////////
    /**
     * Definition allowing to retrieve the associated BOM key type.
     */
    typedef AirlineFeatureKey Key_T;

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
    // /////////// Getters ////////////
    /**
     * Get the airline feature primary key (airline code).
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
    const  HolderMap_T& getHolderMap() const {
      return _holderMap;
    }
    
    /**
     * Get the forecasting method.
     */
    ForecastingMethod::EN_ForecastingMethod getForecastingMethod() const {
      return _forecastingMethod.getMethod();
    }
    
    /**
     * Get the unconstraining method.
     */
    UnconstrainingMethod::EN_UnconstrainingMethod getUnconstrainingMethod() const {
      return _unconstrainingMethod.getMethod();
    }

    /**
     * Get the partnership method.
     */
    PartnershipTechnique::EN_PartnershipTechnique getPartnershipTechnique() const {
      return _partnershipTechnique.getTechnique();
    }     

    /**
     * Get the pre-optimisation method.
     */
    PreOptimisationMethod::EN_PreOptimisationMethod getPreOptimisationMethod() const {
      return _preOptimisationMethod.getMethod();
    }   

    /**
     * Get the optimisation method.
     */
    OptimisationMethod::EN_OptimisationMethod getOptimisationMethod() const {
      return _optimisationMethod.getMethod();
    }  


  public:
    // //////////// Setters //////////
    /**
     * Initialization method. 
     * @param const ForecastingMethod& Forecasting method.
     * @param const UnconstrainingMethod& Unconstraining method.
     * @param const PreOptimisationMethod& Pre-optimisation method.
     * @param const OptimisationMethodGet& Optimisation method.
     * @param const HistoricalDataLimit_T& Historical Data Limit
     * @param const ControlMode_T& Control Mode
     * @param const PartnershipTechnique& Partnership method.
     */
    void init (const ForecastingMethod&,
               const UnconstrainingMethod&,
	       const PreOptimisationMethod&,
	       const OptimisationMethod&,
               const HistoricalDataLimit_T&,
               const ControlMode_T&,
               const PartnershipTechnique&);

  protected:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    AirlineFeature (const Key_T&);
    /**
     * Destructor.
     */
    virtual ~AirlineFeature ();

  private:
    /**
     * Default constructor.
     */
    AirlineFeature ();
    /**
     * Copy constructor.
     */
     AirlineFeature (const AirlineFeature&);
    
  protected:
    // ///////////// Attributes /////////////
    /**
     * Primary key (date period).
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

    /**
     * The type of forecaster.
     */
    ForecastingMethod _forecastingMethod;

    /**
     * The size of the moving average window.
     */
    HistoricalDataLimit_T _historicalDataLimit;

    /**
     * The type of inventory control.
     */
    ControlMode_T _controlMode;

    /**
     * The type of unconstraining method.
     */
    UnconstrainingMethod _unconstrainingMethod;   

    /**
     * The type of pre-optimisation method.
     */
    PreOptimisationMethod _preOptimisationMethod;  

    /**
     * The type of optimisation method.
     */
    OptimisationMethod _optimisationMethod;

    /**
     * The type of partnership technique.
     */
    PartnershipTechnique _partnershipTechnique;
 
  };

}
#endif // __STDAIR_BOM_AIRLINEFEATURE_HPP

