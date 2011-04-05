#ifndef __STDAIR_BOM_BOMMANAGER_HPP
#define __STDAIR_BOM_BOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#include <list>
#include <map>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BomHolder.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {
  
  /**
   * @brief Utility class for StdAir-based objects.
   *
   * Most of those methods work for objects specified and
   * instantianted outside StdAir, as long as those objects inherit
   * from StdAir objects.
   */
  class BomManager {
    friend class FacBomManager;
    
  public:
    /**
     * Get the container (STL list) of OBJECT2 objects within the OBJECT1 object.
     */
    template <typename OBJECT2, typename OBJECT1>
    static const typename BomHolder<OBJECT2>::BomList_T& getList(const OBJECT1&);

    /**
     * Get the container (STL map) of OBJECT2 objects within the OBJECT1 object.
     */
    template <typename OBJECT2, typename OBJECT1>
    static const typename BomHolder<OBJECT2>::BomMap_T& getMap (const OBJECT1&);

    /**
     * Check if the list of object2 has been initialised.
     */
    template <typename OBJECT2, typename OBJECT1>
    static bool hasList (const OBJECT1&);

    /**
     * Check if the map of object2 has been initialised.
     */
    template <typename OBJECT2, typename OBJECT1>
    static bool hasMap (const OBJECT1&);

    /**
     * Get the PARENT of the given CHILD.
     *
     * If the types do not match, NULL is returned.
     */
    template <typename PARENT, typename CHILD>
    static PARENT* getParentPtr (const CHILD&);

    /**
     * Get the PARENT of the given CHILD.
     */
    template <typename PARENT, typename CHILD>
    static PARENT& getParent (const CHILD&);

    /**
     * Get the OBJECT2 pointer corresponding to the given string key.
     *
     * If such a OBJECT2 does not exist, return NULL.
     */
    template <typename OBJECT2, typename OBJECT1>
    static OBJECT2* getObjectPtr (const OBJECT1&, const MapKey_T&);

    /**
     * Get the OBJECT2 corresponding the the given string key.
     */
    template <typename OBJECT2, typename OBJECT1>
    static OBJECT2& getObject (const OBJECT1&, const MapKey_T&);


  private:
    /**
     * Get the holder of object2 within the object1. If the holder does not
     * exist, then throw an exception.
     */
    template <typename OBJECT2, typename OBJECT1>
    static const BomHolder<OBJECT2>& getBomHolder (const OBJECT1&);
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1> 
  const BomHolder<OBJECT2>& BomManager::getBomHolder (const OBJECT1& iObject1) {

    const HolderMap_T& lHolderMap = iObject1.getHolderMap();
    
    HolderMap_T::const_iterator itHolder = lHolderMap.find (&typeid (OBJECT2));
    
    if (itHolder == lHolderMap.end()) {
      const std::string lName (typeid (OBJECT2).name());
      throw NonInitialisedContainerException ("Cannot find the holder of type "
                                              + lName + " within: "
                                              + iObject1.describeKey());
    } 
    
    const BomHolder<OBJECT2>* lBomHolder_ptr = 
      static_cast<const BomHolder<OBJECT2>*> (itHolder->second);
    assert (lBomHolder_ptr != NULL);

    return *lBomHolder_ptr;
  }
  
  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1>
  const typename BomHolder<OBJECT2>::BomList_T& BomManager::
  getList (const OBJECT1& iObject1) {
    const BomHolder<OBJECT2>& lBomHolder = getBomHolder<OBJECT2> (iObject1);
    return lBomHolder._bomList;
  }
  
  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1>
  const typename BomHolder<OBJECT2>::BomMap_T& BomManager::
  getMap (const OBJECT1& iObject1) {
    const BomHolder<OBJECT2>& lBomHolder = getBomHolder<OBJECT2> (iObject1);
    return lBomHolder._bomMap;
  }
  
  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1>
  bool BomManager::hasList (const OBJECT1& iObject1) {
    const HolderMap_T& lHolderMap = iObject1.getHolderMap();
    HolderMap_T::const_iterator itHolder = lHolderMap.find (&typeid (OBJECT2));
    
    if (itHolder == lHolderMap.end()) {
      return false;
    }
    const BomHolder<OBJECT2>* lBomHolder_ptr = 
      static_cast<const BomHolder<OBJECT2>*> (itHolder->second);
    assert (lBomHolder_ptr != NULL);

    return !lBomHolder_ptr->_bomList.empty();
  }
  
  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1>
  bool BomManager::hasMap (const OBJECT1& iObject1) {
    const HolderMap_T& lHolderMap = iObject1.getHolderMap();
    HolderMap_T::const_iterator itHolder = lHolderMap.find (&typeid (OBJECT2));
    
    if (itHolder == lHolderMap.end()) {
      return false;
    }
    const BomHolder<OBJECT2>* lBomHolder_ptr = 
      static_cast<const BomHolder<OBJECT2>*> (itHolder->second);
    assert (lBomHolder_ptr != NULL);

    return !lBomHolder_ptr->_bomMap.empty();
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  PARENT* BomManager::getParentPtr (const CHILD& iChild) {
    PARENT* const lParent_ptr = static_cast<PARENT* const> (iChild.getParent());
    return lParent_ptr; 
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  PARENT& BomManager::getParent (const CHILD& iChild) {
    PARENT* const lParent_ptr = getParentPtr<PARENT> (iChild);
    assert (lParent_ptr != NULL);
    return *lParent_ptr; 
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1>
  OBJECT2* BomManager::getObjectPtr (const OBJECT1& iObject1,
                                     const MapKey_T& iKey) {
    OBJECT2* oBom_ptr = NULL;
    
    const HolderMap_T& lHolderMap = iObject1.getHolderMap();

    typename HolderMap_T::const_iterator itHolder = 
      lHolderMap.find (&typeid (OBJECT2));
    
    if (itHolder != lHolderMap.end()) {
    
      BomHolder<OBJECT2>* const lBomHolder_ptr = 
        static_cast<BomHolder<OBJECT2>* const> (itHolder->second);
      assert (lBomHolder_ptr != NULL);

      //
      typedef typename BomHolder<OBJECT2>::BomMap_T BomMap_T;
      BomMap_T& lBomMap =  lBomHolder_ptr->_bomMap;
      typename BomMap_T::iterator itBom = lBomMap.find (iKey);

      if (itBom != lBomMap.end()) {
        oBom_ptr = itBom->second;
        assert (oBom_ptr != NULL);
      }
    }

    return oBom_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1>
  OBJECT2& BomManager::getObject (const OBJECT1& iObject1,
                                  const MapKey_T& iKey) {
    OBJECT2* oBom_ptr = NULL;
    
    typedef std::map<const MapKey_T, OBJECT2*> BomMap_T;
    const BomMap_T& lBomMap = getMap<OBJECT2> (iObject1);
    
    typename BomMap_T::const_iterator itBom = lBomMap.find (iKey);

    if (itBom == lBomMap.end()) {
      const std::string lName (typeid (OBJECT2).name());
      
      STDAIR_LOG_ERROR ("Cannot find the objet of type " << lName
                        << " with key " << iKey << " within: " 
                        << iObject1.describeKey());
      assert (false);
    }
    
    oBom_ptr = itBom->second;
    assert (oBom_ptr != NULL);

    return *oBom_ptr;
  }
  
}
#endif // __STDAIR_BOM_BOMMANAGER_HPP
