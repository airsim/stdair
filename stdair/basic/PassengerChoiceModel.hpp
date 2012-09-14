#ifndef __STDAIR_BAS_PASSENGERCHOICEMODEL_HPP
#define __STDAIR_BAS_PASSENGERCHOICEMODEL_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /** Enumeration of passenger choice models. */
  struct PassengerChoiceModel : public stdair::StructAbstract {
  public:
    typedef enum {
      HARD_RESTRICTION = 0,
      PRICE_ORIENTED,
      HYBRID,
      LAST_VALUE
    } EN_PassengerChoiceModel;

    /** Get the label as a string (e.g., HardRestrictionModel",
        "PriceOrientedModel" or "HybridModel"). */
    static const std::string& getLabel (const EN_PassengerChoiceModel&);

    /** Get the label as a single char (e.g., 'R', 'P' or 'H'). */
    static char getModelLabel (const EN_PassengerChoiceModel&);

    /** Get the label as a string of a single char (e.g., "R", "P" or "H"). */
    static std::string getModelLabelAsString (const EN_PassengerChoiceModel&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_PassengerChoiceModel getModel() const;

    /** Get the enumerated value as a short string (e.g., "R", "P" or "H"). */
    std::string getModelAsString() const;
    
    /** Give a description of the structure (e.g., HardRestrictionModel",
        "PriceOrientedModel" or "HybridModel"). */
    const std::string describe() const;

  public:
    /** Comparaison operator. */
    bool operator== (const EN_PassengerChoiceModel&) const;
    
  public:
    /** Constructor. */
    PassengerChoiceModel (const EN_PassengerChoiceModel&);
    /** Constructor. */
    PassengerChoiceModel (const char iModel);
    /** Default copy constructor. */
    PassengerChoiceModel (const PassengerChoiceModel&);

  private:
    /** Default constructor. */
    PassengerChoiceModel();
  

  private:
    /** String version of the enumeration. */    
    static const std::string _labels[LAST_VALUE];
    /** Model version of the enumeration. */    
    static const char _modelLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /** Passenger choice model. */
    EN_PassengerChoiceModel _model;
  };
}
  
#endif // __STDAIR_BAS_PASSENGERCHOICEMODEL_HPP
