// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_INTYPES_HPP
#define __STDAIR_BOM_INTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class IN;
  
  /** Define the BomRootStructure. */
  typedef Structure<IN> INStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<IN> INHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<IN> INList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<IN> INMap_T;
  
}
#endif // __STDAIR_BOM_INTYPES_HPP

