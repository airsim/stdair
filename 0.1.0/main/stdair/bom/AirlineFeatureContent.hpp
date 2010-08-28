#ifndef __STDAIR_BOM_AIRLINEFEATURECONTENT_HPP
#define __STDAIR_BOM_AIRLINEFEATURECONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/AirlineFeatureKey.hpp>
#include <stdair/bom/OptimizerStruct.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline booking class. */
  class AirlineFeatureContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef AirlineFeatureKey_T Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the airline feature key. */
    const Key_T& getKey() const {
      return _key;
    }

  public:
    // //////////// Setters //////////
    /** Intialization method. */
    void init (const ForecasterMode_T&, const HistoricalDataLimit_T&,
               const OptimizerStruct_T&, const ControlMode_T&);
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }
    
  protected:
    /** Default constructors. */
    AirlineFeatureContent ();
    AirlineFeatureContent (const AirlineFeatureContent&);
    AirlineFeatureContent (const Key_T&);
    /** Destructor. */
    virtual ~AirlineFeatureContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;

    /** The type of forecaster. */
    ForecasterMode_T _forecasterMode;

    /** The size of the moving average window. */
    HistoricalDataLimit_T _historicalDataLimit;

    /** The type of optimizer. */
    OptimizerStruct_T _optimizerStruct;

    /** The type of inventory control. */
    ControlMode_T _controlMode;
  };

}
#endif // __STDAIR_BOM_AIRLINEFEATURECONTENT_HPP
