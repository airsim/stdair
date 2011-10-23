#ifndef __STDAIR_BAS_SAMPLETYPE_HPP
#define __STDAIR_BAS_SAMPLETYPE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /**
   * @brief Enumeration of BOM sample types.
   *
   * In order to test some components, it is often easier to fill the BOM tree
   * with hard-coded structures than set up CSV input files and parsing them.
   * That enumeration structure tells for which component(s) the sample BOM
   * tree should be built.
   * By default, a BOM sample tree is built for all the components, i.e.,
   * it contains StdAir objects for all the other components (AirInv,
   * AirSched, etc).
   */
  struct SampleType : public StructAbstract {
  public:
    typedef enum { 
      ALL = 0,
      A4P,
      RMS,
      INV,
      SCH,
      RAC,
      FQT,
      CRS,
      DEM,
      EVT,
      CCM,
      LAST_VALUE
    } EN_SampleType;

    /**
     * Get the label as a string (e.g., "Inventory" or "Schedule").
     */
    static const std::string& getLabel (const EN_SampleType&);

    /**
     * Get the label as a single char (e.g., 'I' or 'S').
     */
    static char getTypeLabel (const EN_SampleType&);

    /**
     * Get the label as a string of a single char (e.g., "I" or "S").
     */
    static std::string getTypeLabelAsString (const EN_SampleType&);

    /**
     * List the labels.
     */
    static std::string describeLabels();

    /**
     * Get the enumerated value.
     */
    EN_SampleType getType() const;

    /**
     * Get the enumerated value as a short string (e.g., "I" or "S").
     */
    std::string getTypeAsString() const;
    
    /**
     * Give a description of the structure (e.g., "Inventory" or "Schedule").
     */
    const std::string describe() const;

  public:
    /**
     * Comparison operator.
     */
    bool operator== (const EN_SampleType&) const;
    
  public:
    /**
     * Constructor.
     */
    SampleType (const EN_SampleType&);
    /**
     * Constructor.
     */
    SampleType (const char iType);
    /**
     * Default copy constructor.
     */
    SampleType (const SampleType&);

  private:
    /**
     * Default constructor.
     */
    SampleType();
  

  private:
    /**
     * String version of the enumeration.
     */
    static const std::string _labels[LAST_VALUE];

    /**
     * Type version of the enumeration.
     */
    static const char _typeLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /**
     * Sample type.
     */
    EN_SampleType _type;
  };

}
#endif // __STDAIR_BAS_SAMPLETYPE_HPP
