#ifndef __STDAIR_BAS_PARTNERSHIPTECHNIQUE_HPP
#define __STDAIR_BAS_PARTNERSHIPTECHNIQUE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /**
   * @brief Enumeration of partnership techniques.
   */
  struct PartnershipTechnique : public StructAbstract {
  public:
    typedef enum {
      NONE = 0,
      RAE_DA,
      RAE_YP,
      IBP_DA,
      IBP_YP,
      IBP_YP_U,
      RMC,
      A_RMC,
      LAST_VALUE
    } EN_PartnershipTechnique;

    /**
     * Get the label as a string (e.g., "RevenueManagementCooperation").
     */
    static const std::string& getLabel (const EN_PartnershipTechnique&);

    /**
     * Get the technique value from parsing a single char (e.g., 'r' or 'C').
     */
    static EN_PartnershipTechnique getTechnique (const char);

    /**
     * Get the label as a single char (e.g., 'r' or 'C').
     */
    static char getTechniqueLabel (const EN_PartnershipTechnique&);

    /**
     * Get the label as a string of a single char (e.g., "r" or "C").
     */
    static std::string getTechniqueLabelAsString (const EN_PartnershipTechnique&);

    /**
     * List the labels.
     */
    static std::string describeLabels();

    /**
     * Get the enumerated value.
     */
    EN_PartnershipTechnique getTechnique() const;

    /**
     * Get the enumerated value as a char (e.g., 'r' or 'C').
     */
    char getTechniqueAsChar() const;
    
    /**
     * Get the enumerated value as a short string (e.g., "r" or "C").
     */
    std::string getTechniqueAsString() const;
    
    /**
     * Give a description of the structure (e.g., "RevenueManagementCooperation" or
     * "InterlineBidPriceYieldProration").
     */
    const std::string describe() const;

  public:
    /**
     * Comparison operator.
     */
    bool operator== (const EN_PartnershipTechnique&) const;
    
  public:
    /**
     * Main constructor.
     */
    PartnershipTechnique (const EN_PartnershipTechnique&);
    /**
     * Alternative constructor.
     */
    PartnershipTechnique (const char iTechnique);
    /**
     * Alternative constructor.
     */
    PartnershipTechnique (const std::string& iTechnique);
    
    /**
     * Default copy constructor.
     */
    PartnershipTechnique (const PartnershipTechnique&);

  private:
    /**
     * Default constructor.
     */
    PartnershipTechnique();


  private:
    /**
     * String version of the enumeration.
     */
    static const std::string _labels[LAST_VALUE];
    /**
     * Technique version of the enumeration.
     */
    static const char _techniqueLabels[LAST_VALUE];

  private:
    // //////// Attributes /////////
    /**
     * Partnership techniques.
     */
    EN_PartnershipTechnique _technique;
  };

}
#endif // __STDAIR_BAS_PARTNERSHIPTECHNIQUE_HPP
