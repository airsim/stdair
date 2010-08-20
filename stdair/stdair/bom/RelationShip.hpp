// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_RELATIONSHIP_HPP
#define __STDAIR_BOM_RELATIONSHIP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
#include <cassert>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/RelationShipAbstract.hpp>
#include <stdair/service/FacSupervisor.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  /** Class which holds the relation ship between different types of objects
      (i.e. Inventory is parent of FlightDate). */
  template <typename PARENT, typename CHILD>
  class RelationShip : public RelationShipAbstract {
    friend class FacSupervisor;
    friend class FacBomManager;

    // //////////////////////////////////////////////////////////////////
    // Internal type definitions.
    typedef std::list<CHILD*> ChildrenList_T;
    typedef std::map<const MapKey_T, CHILD*> ChildrenMap_T;
    typedef std::multimap<const MapKey_T, CHILD*> ChildrenMultimap_T;
    typedef std::map<const PARENT*, ChildrenList_T> ParentChildrentList_T;
    typedef std::map<const PARENT*, ChildrenMap_T> ParentChildrentMap_T;
    typedef std::map<const PARENT*,
                     ChildrenMultimap_T> ParentChildrentMultimap_T;
    typedef std::map<const CHILD*, PARENT*> ChildParentMap_T;
    // //////////////////////////////////////////////////////////////////

  public:
    /** Provide the unique instance.
        <br> The singleton is instatiated when first used.
        @return RelationShip& */
    static RelationShip& instance ();

  public:
    // ////////////////////// Business Methods /////////////////////////
    /** Getter of the children conainter given the PARENT pointer. */
    ChildrenList_T& getChildrenList (const PARENT&);
    ChildrenMap_T& getChildrenMap (const PARENT&);
    ChildrenMultimap_T& getChildrenMultimap (const PARENT&);

    /** Getter of the PARENT given the CHILD. */
    PARENT& getParent (const CHILD&);

    /** Return the CHILD pointer corresponding to the given string key.
        If such a CHILD does not exist, return NULL. */
    CHILD* getChildPtr (const PARENT&, const MapKey_T&);

    /** Return the CHILD corresponding the the given string key. */
    CHILD& getChild (const PARENT&, const MapKey_T&);

  private:
    /** Add the given CHILD to the children containter of the given PARENT. */
    void addChildToTheList (const PARENT&, CHILD&); 
    void addChildToTheMap (const PARENT&, CHILD&); 
    void addChildToTheMap (const PARENT&, CHILD&, const MapKey_T&); 
    void addChildToTheMultimap (const PARENT&, CHILD&); 
    void addChildToTheMultimap (const PARENT&, CHILD&, const MapKey_T&);

    /** Link the CHILD with the PARENT. */
    void linkWithParent (PARENT&, const CHILD&);
    
  private:
    /** Default constructor. */
    RelationShip () { }
    /** Destructor. */
    ~RelationShip () { _instance = NULL; };

  private:
    /** The unique instance. */
    static RelationShip* _instance;
    /** The containers of relation ships. */
    ParentChildrentList_T _parentChildrenList;
    ParentChildrentMap_T _parentChildrenMap;
    ParentChildrentMultimap_T _parentChildrenMultimap;
    ChildParentMap_T _childParentMap;    
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  RelationShip<PARENT, CHILD>* RelationShip<PARENT, CHILD>::_instance = NULL;

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  RelationShip<PARENT, CHILD>& RelationShip<PARENT, CHILD>::instance () {
    if (_instance == NULL) {
      _instance = new RelationShip ();
      assert (_instance != NULL);

      FacSupervisor::instance().registerRelationShip (_instance);
    }
    return *_instance;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  typename RelationShip<PARENT, CHILD>::ChildrenList_T&
  RelationShip<PARENT, CHILD>::getChildrenList (const PARENT& iParent) {
    ParentChildrentList_T& lParentChildrenList = instance()._parentChildrenList;
    typename ParentChildrentList_T::iterator itList =
      lParentChildrenList.find (&iParent);
    
    if (itList == lParentChildrenList.end()) {
      STDAIR_LOG_ERROR ("Cannot find the list within: "<< iParent.describeKey());
      throw NonInitialisedContainerException ();
    }

    return itList->second;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  typename RelationShip<PARENT, CHILD>::ChildrenMap_T&
  RelationShip<PARENT, CHILD>::getChildrenMap (const PARENT& iParent) {
    ParentChildrentMap_T& lParentChildrenMap = instance()._parentChildrenMap;
    typename ParentChildrentMap_T::iterator itMap =
      lParentChildrenMap.find (&iParent);
    
    if (itMap == lParentChildrenMap.end()) {
      STDAIR_LOG_ERROR ("Cannot find the map within: " << iParent.describeKey());
      throw NonInitialisedContainerException ();
    }

    return itMap->second;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  typename RelationShip<PARENT, CHILD>::ChildrenMultimap_T&
  RelationShip<PARENT, CHILD>::getChildrenMultimap (const PARENT& iParent) {
    ParentChildrentMultimap_T& lParentChildrenMultimap = 
      instance()._parentChildrenMultimap;
    typename ParentChildrentMultimap_T::iterator itMultimap =
      lParentChildrenMultimap.find (&iParent);
    
    if (itMultimap == lParentChildrenMultimap.end()) {
      STDAIR_LOG_ERROR ("Cannot find the multimap within: "
                        << iParent.describeKey());
      throw NonInitialisedContainerException ();
    }

    return itMultimap->second;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  PARENT& RelationShip<PARENT, CHILD>::getParent (const CHILD& iChild) {
    ChildParentMap_T& lChildParentMap = instance()._childParentMap;
    typename ChildParentMap_T::iterator itParent = lChildParentMap.find(&iChild);

    if (itParent == lChildParentMap.end()) {
      STDAIR_LOG_ERROR ("Cannot find the parent of: " << iChild.describeKey());
      throw NonInitialisedRelationShip ();
    }
    PARENT* oParent_ptr = itParent->second;
    assert (oParent_ptr != NULL);
    return *oParent_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  CHILD* RelationShip<PARENT, CHILD>::
  getChildPtr (const PARENT& iParent, const MapKey_T& iKey) {
    // Look for the child in the map, then the multimap.
    // 1. Map
    ParentChildrentMap_T lParentChildrenMap = instance()._parentChildrenMap;
    typename ParentChildrentMap_T::iterator itMap =
      lParentChildrenMap.find (&iParent);

    if (itMap != lParentChildrenMap.end()) {
      ChildrenMap_T& lChildrenMap = itMap->second;
      typename ChildrenMap_T::iterator itChild = lChildrenMap.find (iKey);
      if (itChild != lChildrenMap.end()) {
        CHILD* oChild_ptr = itChild->second;
        assert (oChild_ptr);
        return oChild_ptr;
      }
    }

    // 2. Multimap
    ParentChildrentMultimap_T lParentChildrenMultimap =
      instance()._parentChildrenMultimap;
    typename ParentChildrentMultimap_T::iterator itMultimap =
      lParentChildrenMultimap.find (&iParent);

    if (itMultimap != lParentChildrenMultimap.end()) {
      ChildrenMultimap_T& lChildrenMultimap = itMultimap->second;
      typename ChildrenMultimap_T::iterator itChild =
        lChildrenMultimap.find (iKey);
      if (itChild != lChildrenMultimap.end()) {
        CHILD* oChild_ptr = itChild->second;
        assert (oChild_ptr);
        return oChild_ptr;
      }
    }
    
    return NULL;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  CHILD& RelationShip<PARENT, CHILD>::
  getChild (const PARENT& iParent, const MapKey_T& iKey) {
    // Look for the child in the map, then the multimap.
    // 1. Map
    ParentChildrentMap_T lParentChildrenMap = instance()._parentChildrenMap;
    typename ParentChildrentMap_T::iterator itMap =
      lParentChildrenMap.find (&iParent);

    if (itMap != lParentChildrenMap.end()) {
      ChildrenMap_T& lChildrenMap = itMap->second;
      typename ChildrenMap_T::iterator itChild = lChildrenMap.find (iKey);
      if (itChild != lChildrenMap.end()) {
        CHILD* oChild_ptr = itChild->second;
        assert (oChild_ptr);
        return *oChild_ptr;
      }
    }

    // 2. Multimap
    ParentChildrentMultimap_T lParentChildrenMultimap =
      instance()._parentChildrenMultimap;
    typename ParentChildrentMultimap_T::iterator itMultimap =
      lParentChildrenMultimap.find (&iParent);

    if (itMultimap != lParentChildrenMultimap.end()) {
      ChildrenMultimap_T& lChildrenMultimap = itMultimap->second;
      typename ChildrenMultimap_T::iterator itChild =
        lChildrenMultimap.find (iKey);
      if (itChild != lChildrenMultimap.end()) {
        CHILD* oChild_ptr = itChild->second;
        assert (oChild_ptr);
        return *oChild_ptr;
      }
    }

    throw NonInitialisedRelationShip ();
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void RelationShip<PARENT, CHILD>::
  addChildToTheList (const PARENT& iParent, CHILD& ioChild) {
    ParentChildrentList_T& lParentChildrenList = instance()._parentChildrenList;
    lParentChildrenList[&iParent].push_back (&ioChild);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void RelationShip<PARENT, CHILD>::
  addChildToTheMap (const PARENT& iParent, CHILD& ioChild) {
    ParentChildrentMap_T& lParentChildrenMap = instance()._parentChildrenMap;
    
    const MapKey_T& lKey = ioChild.describeKey ();
    bool insertionSucceeded =
      lParentChildrenMap[&iParent].insert (typename ChildrenMap_T::
                                           value_type (lKey, &ioChild)).second;

    if (insertionSucceeded == false) {
      STDAIR_LOG_ERROR ("Cannot add the given object to the map: "
                        << iParent.describeKey() << "; " << lKey)
      throw ObjectLinkingException ();
    }
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void RelationShip<PARENT, CHILD>::
  addChildToTheMap (const PARENT& iParent, CHILD& ioChild,
                    const MapKey_T& iKey) {
    ParentChildrentMap_T& lParentChildrenMap = instance()._parentChildrenMap;
    bool insertionSucceeded =
      lParentChildrenMap[&iParent].insert (typename ChildrenMap_T::
                                           value_type (iKey, &ioChild)).second;

    if (insertionSucceeded == false) {
      STDAIR_LOG_ERROR ("Cannot add the given object to the map: "
                        << iParent.describeKey() << "; " << iKey)
      throw ObjectLinkingException ();
    }
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void RelationShip<PARENT, CHILD>::
  addChildToTheMultimap (const PARENT& iParent, CHILD& ioChild) {
    ParentChildrentMultimap_T& lParentChildrenMultimap =
      instance()._parentChildrenMultimap;
    
    const MapKey_T& lKey = ioChild.describeKey ();
    bool insertionSucceeded = lParentChildrenMultimap[&iParent].
      insert (typename ChildrenMultimap_T::value_type (lKey, &ioChild)).second;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void RelationShip<PARENT, CHILD>::
  addChildToTheMultimap (const PARENT& iParent, CHILD& ioChild,
                         const MapKey_T& iKey) {
    ParentChildrentMultimap_T& lParentChildrenMultimap =
      instance()._parentChildrenMultimap;
    bool insertionSucceeded = lParentChildrenMultimap[&iParent].
      insert (typename ChildrenMultimap_T::value_type (iKey, &ioChild)).second;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void RelationShip<PARENT, CHILD>::
  linkWithParent (PARENT& ioParent, const CHILD& iChild) {
    instance()._childParentMap[&iChild] = &ioParent;
  }
}
#endif // __STDAIR_BOM_RELATIONSHIP_HPP