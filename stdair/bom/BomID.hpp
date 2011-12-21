#ifndef __STDAIR_BOM_BOMID_HPP
#define __STDAIR_BOM_BOMID_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>

namespace stdair {

  /**
   * @brief Class wrapper of bom ID (e.g. pointer to object).
   */
  template <typename BOM>
  struct BomID {
    
  public:
    // ////////// Getters ////////////
    /**
     * Retrieve the object.
     */
    BOM& getObject () const;

  public:
    // ////////// Constructors and destructors /////////
    /**
     * Main constructor.
     */
    BomID (BOM& iBOM);
    
    /**
     * Copy constructor.
     */
    BomID (const BomID&);

    /**
     * Destructor.
     */
    ~BomID();

  private:
    /**
     * Default constructor.
     */
    BomID();

  private:
    // /////////////// Attributes ////////////////
    /**
     * Pointer to the BOM.
     */
    BOM* _id;
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> BomID<BOM>::BomID (BOM& iBOM): _id (&iBOM) { }

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> BomID<BOM>::BomID (const BomID& iBomID)
    : _id (iBomID._id) { }

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> BomID<BOM>::~BomID () { }

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> BOM& BomID<BOM>::getObject () const {
    assert (_id != NULL);
    return *_id;
  }
}
#endif // __STDAIR_BOM_BOMID_HPP
