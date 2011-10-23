#ifndef __STDAIR_BOM_FAREFAMILYKEY_HPP
#define __STDAIR_BOM_FAREFAMILYKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /**
   * @brief Key of a given fare family, made of a fare family code.
   */
  struct FareFamilyKey : public KeyAbstract {
    friend class boost::serialization::access;
    
    // /////////// Constructors and destructors ///////////
  private:
    /**
     * Default constructor.
     */
    FareFamilyKey();
    
  public:
    /**
     * Constructor.
     */
    FareFamilyKey (const FamilyCode_T& iFamilyCode);

    /**
     * Copy constructor.
     */
    FareFamilyKey (const FareFamilyKey&);

    /**
     * Destructor.
     */
    ~FareFamilyKey();


  public:
    // /////////// Getters //////////
    /** Get the family code. */
    const FamilyCode_T& getFamilyCode () const {
      return _familyCode;
    }
    

  public:
    // /////////// Display support methods /////////
    /**
     * Dump a Business Object Key into an output stream.
     *
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;

    /**
     * Read a Business Object Key from an input stream.
     *
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn);

    /**
     * Get the serialised version of the Business Object Key.
     *
     * That string is unique, at the level of a given Business Object,
     * when among children of a given parent Business Object.
     *
     * For instance, "H" and "K" allow to differentiate among two
     * marketing classes for the same segment-date.
     */
    const std::string toString() const;


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


  private:
    // ///////////////// Attributes ///////////////
    /**
     * Family code.
     */
    FamilyCode_T _familyCode;
  };

}
#endif // __STDAIR_BOM_FAREFAMILYKEY_HPP
