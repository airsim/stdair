#ifndef __STDAIR_BOM_NESTINGNODEKEY_HPP
#define __STDAIR_BOM_NESTINGNODEKEY_HPP

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
   * @brief Key of a given policy, made of a policy code.
   */
  struct NestingNodeKey : public KeyAbstract {
    friend class boost::serialization::access;
    
    // /////////// Constructors and destructors ///////////
  private:
    /**
     * Default constructor.
     */
    NestingNodeKey();
    
  public:
    /**
     * Constructor.
     */
    NestingNodeKey (const NestingNodeCode_T& iNestingNodeCode);

    /**
     * Copy constructor.
     */
    NestingNodeKey (const NestingNodeKey&);

    /**
     * Destructor.
     */
    ~NestingNodeKey();


  public:
    // /////////// Getters //////////
    /** Get the policy code. */
    const NestingNodeCode_T& getNestingNodeCode () const {
      return _nestingNodeCode;
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
     * Serialisation helpers (allows to be sure the template method is
     * instantiated).
     */
    void serialisationImplementationExport() const;
    void serialisationImplementationImport();


  private:
    // ///////////////// Attributes ///////////////
    /**
     * Policy code.
     */
    NestingNodeCode_T _nestingNodeCode;
  };

}
#endif // __STDAIR_BOM_NESTINGNODEKEY_HPP
