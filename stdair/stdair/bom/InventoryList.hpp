#ifndef __STDAIR_BOM_INVENTORYLIST_HPP
#define __STDAIR_BOM_INVENTORYLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomRootTypes.hpp>
#include <stdair/bom/InventoryTypes.hpp>

namespace stdair {
  
// Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;

  /** Structure which handles the iterators for a flight-date list. */
  struct InventoryList_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the flight-date list iterators. */
    typedef BomIterator_T<Inventory,
                          InventoryStructureList_T::const_iterator> iterator;
    typedef BomIterator_T<Inventory,
                          InventoryStructureList_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////

  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on flight date:
        return the iterator at the begining of the list. */
    iterator begin () const;
    
    /** Initialise the internal iterator on flight date:
        return the iterator at the end of the list. */
    iterator end () const;

    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the rbegining of the list. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the end of the list. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    InventoryList_T ();
    InventoryList_T (const InventoryList_T&);
    InventoryList_T (const BomStructureRoot_T&);

    /** Destructor. */
    virtual ~InventoryList_T();

  private:
    // Attributes
    /** Reference structure. */
    const BomStructureRoot_T& _bomStructureRoot;
  };

}
#endif // __STDAIR_BOM_INVENTORYLIST_HPP

