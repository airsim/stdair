#ifndef __STDAIR_BOM_SEGMENTSNAPSHOTTABLEKEY_HPP
#define __STDAIR_BOM_SEGMENTSNAPSHOTTABLEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/bom/KeyAbstract.hpp>

/// Forward declarations
namespace boost {
  namespace serialization {
    class access;
  }
}

namespace stdair {

  /**
   * @brief Key of a given guillotine block, made of a guillotine number.
   */
  struct SegmentSnapshotTableKey : public KeyAbstract {
    friend class boost::serialization::access;

    // /////////// Constructors and destructors ///////////
  private:
    /**
     * Default constructor.
     */
    SegmentSnapshotTableKey();

  public:
    /**
     * Constructor.
     */
    SegmentSnapshotTableKey (const TableID_T&);

    /**
     * Copy constructor.
     */
    SegmentSnapshotTableKey (const SegmentSnapshotTableKey&);

    /**
     * Destructor.
     */
    ~SegmentSnapshotTableKey();


  public:
    // /////////// Getters //////////
    /** Get the table ID. */
    const TableID_T& getTableID() const {
      return _tableID;
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
     * marketing classes for the same segment-block.
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
     * Table ID (number).
     */
    TableID_T _tableID;

  };

}
#endif // __STDAIR_BOM_SEGMENTSNAPSHOTTABLEKEY_HPP
