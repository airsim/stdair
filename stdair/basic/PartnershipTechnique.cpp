// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/PartnershipTechnique.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PartnershipTechnique::_labels[LAST_VALUE] =
    { "None",
      "RevenueAvailabilityExchangeDemandAggregation", "RevenueAvailabilityExchangeYieldProration",
      "InterlineBidPriceDemandAggregation", "InterlineBidPriceYieldProration",
      "NonProtectionistInterlineBidPriceYieldProration",
      "RevenueManagementCooperation", "AdvancedRevenueManagementCooperation"};

  // //////////////////////////////////////////////////////////////////////
  const char PartnershipTechnique::_techniqueLabels[LAST_VALUE] = { 'N',
                                                                    'r', 'R',
                                                                    'i', 'I', 'U',
                                                                    'C', 'A'};

  
  // //////////////////////////////////////////////////////////////////////
  PartnershipTechnique::PartnershipTechnique() : _technique (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  PartnershipTechnique::
  PartnershipTechnique (const PartnershipTechnique& iPartnershipTechnique)
    : _technique (iPartnershipTechnique._technique) {
  }

  // //////////////////////////////////////////////////////////////////////
  PartnershipTechnique::
  PartnershipTechnique (const EN_PartnershipTechnique& iPartnershipTechnique)
    : _technique (iPartnershipTechnique) {
  }

  // //////////////////////////////////////////////////////////////////////
  PartnershipTechnique::EN_PartnershipTechnique
  PartnershipTechnique::getTechnique (const char iTechniqueChar) {
    EN_PartnershipTechnique oTechnique;
    switch (iTechniqueChar) {
    case 'N': oTechnique = NONE; break;
    case 'r': oTechnique = RAE_DA; break;
    case 'R': oTechnique = RAE_YP; break;
    case 'i': oTechnique = IBP_DA; break;
    case 'I': oTechnique = IBP_YP; break;
    case 'U': oTechnique = IBP_YP_U; break;
    case 'C': oTechnique = RMC; break;
    case 'A': oTechnique = A_RMC; break;
    default: oTechnique = LAST_VALUE; break;
    }

    if (oTechnique == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The partnership technique '"
               << iTechniqueChar
               << "' is not known. Known partnership techniques: "
               << lLabels;
      throw CodeConversionException (oMessage.str());
    }

    return oTechnique;
  }
  
  // //////////////////////////////////////////////////////////////////////
  PartnershipTechnique::PartnershipTechnique (const char iTechniqueChar)
    : _technique (getTechnique (iTechniqueChar)) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  PartnershipTechnique::
  PartnershipTechnique (const std::string& iTechniqueStr) {
    // 
    const size_t lSize = iTechniqueStr.size();
    assert (lSize == 1);
    const char lTechniqueChar = iTechniqueStr[0];
    _technique = getTechnique (lTechniqueChar);
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string& PartnershipTechnique::
  getLabel (const EN_PartnershipTechnique& iTechnique) {
    return _labels[iTechnique];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char PartnershipTechnique::
  getTechniqueLabel (const EN_PartnershipTechnique& iTechnique) {
    return _techniqueLabels[iTechnique];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string PartnershipTechnique::
  getTechniqueLabelAsString (const EN_PartnershipTechnique& iTechnique) {
    std::ostringstream oStr;
    oStr << _techniqueLabels[iTechnique];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string PartnershipTechnique::describeLabels() {
    std::ostringstream ostr;
    for (unsigned short idx = 0; idx != LAST_VALUE; ++idx) {
      if (idx != 0) {
        ostr << ", ";
      }
      ostr << _labels[idx];
    }
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  PartnershipTechnique::EN_PartnershipTechnique
  PartnershipTechnique::getTechnique() const {
    return _technique;
  }
  
  // //////////////////////////////////////////////////////////////////////
  char PartnershipTechnique::getTechniqueAsChar() const {
    const char oTechniqueChar = _techniqueLabels[_technique];
    return oTechniqueChar;
  }

  // //////////////////////////////////////////////////////////////////////
  std::string PartnershipTechnique::getTechniqueAsString() const {
    std::ostringstream oStr;
    oStr << _techniqueLabels[_technique];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PartnershipTechnique::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_technique];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool PartnershipTechnique::
  operator== (const EN_PartnershipTechnique& iTechnique) const {
    return (_technique == iTechnique);
  }
  
}
