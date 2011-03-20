#ifndef __STDAIR_FAC_FACBOMMANAGER_HPP
#define __STDAIR_FAC_FACBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <list>
#include <map>
// STDAIR
#include <stdair/bom/BomHolder.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/factory/FacAbstract.hpp>
#include <stdair/factory/FacBom.hpp>

namespace stdair {
  
  /** Utility class for STDAIR objects. */
  class FacBomManager : public FacAbstract {
  public:
    // ///////////// Business methods. ////////////
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacBom& */
    static FacBomManager& instance();
    
    /** Add an object to the dedicated containers with another object. */
    template <typename OBJECT1, typename OBJECT2>
    void addToList (OBJECT1&, OBJECT2&);
    template <typename OBJECT1, typename OBJECT2>
    void addToMap (OBJECT1&, OBJECT2&);
    template <typename OBJECT1, typename OBJECT2>
    void addToMap (OBJECT1&, OBJECT2&, const MapKey_T&);
    template <typename OBJECT1, typename OBJECT2>
    void addToListAndMap (OBJECT1&, OBJECT2&);
    template <typename OBJECT1, typename OBJECT2>
    void addToListAndMap (OBJECT1&, OBJECT2&, const MapKey_T&);
    
    /** Link the CHILD with the PARENT. */
    template <typename PARENT, typename CHILD>
    void linkWithParent (PARENT&, CHILD&);

    /** Clone the holder between two objects. */
    template <typename OBJECT2, typename OBJECT1>
    void cloneHolder (OBJECT1&, const OBJECT1&);

  private:
    /** Get the holder of object2 within the object1. If the holder does not
        exist, then create one. */
    template <typename OBJECT2, typename OBJECT1>
    BomHolder<OBJECT2>& getBomHolder (OBJECT1&);
  
  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is . */
    FacBomManager() { }
  public:
    /** Destructor. */
    ~FacBomManager() { }
    
  private:
    /** The unique instance.*/
    static FacBomManager* _instance;
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1> 
  BomHolder<OBJECT2>& FacBomManager::getBomHolder (OBJECT1& ioObject1) {
    
    BomHolder<OBJECT2>* lBomHolder_ptr = NULL;

    // Find the corresponding BomHolder within the object1. If it does
    // not exist, then create one.
    HolderMap_T::const_iterator itHolder =
      ioObject1._holderMap.find (&typeid (OBJECT2));
    
    if (itHolder == ioObject1._holderMap.end()) {
      lBomHolder_ptr = &FacBom<BomHolder<OBJECT2> >::instance().create();
      ioObject1._holderMap.insert (typename HolderMap_T::
                                   value_type (&typeid(OBJECT2),lBomHolder_ptr));
    } else {
      lBomHolder_ptr = static_cast<BomHolder<OBJECT2>*> (itHolder->second);
    }
    
    assert (lBomHolder_ptr != NULL);

    return *lBomHolder_ptr;
  }
  
  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2> void FacBomManager::
  addToList (OBJECT1& ioObject1, OBJECT2& ioObject2) {
    BomHolder<OBJECT2>& lBomHolder = instance().getBomHolder<OBJECT2>(ioObject1);
    lBomHolder._bomList.push_back (&ioObject2);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2> void FacBomManager::
  addToMap (OBJECT1& ioObject1, OBJECT2& ioObject2, const MapKey_T& iKey) {
    BomHolder<OBJECT2>& lBomHolder = instance().getBomHolder<OBJECT2>(ioObject1);
    const bool insertionSucceeded =
      lBomHolder._bomMap.insert (typename std::map<const MapKey_T, OBJECT2*>::
                                 value_type (iKey, &ioObject2)).second;

    if (insertionSucceeded == false) {
      STDAIR_LOG_ERROR ("Cannot add the given object to the map: "
                        << ioObject1.describeKey() << "; " << iKey);
      STDAIR_LOG_DEBUG ("Map contain: ");
      for (typename std::map<const MapKey_T, OBJECT2*>::const_iterator iter =
             lBomHolder._bomMap.begin(); 
           iter != lBomHolder._bomMap.end(); ++iter) {
        const OBJECT2* lCurrentObject_ptr = iter->second;
        assert (lCurrentObject_ptr != NULL);
        STDAIR_LOG_DEBUG (lCurrentObject_ptr->describeKey() << "; ");
      }
      throw ObjectLinkingException ("");
    }    
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2> void FacBomManager::
  addToMap (OBJECT1& ioObject1, OBJECT2& ioObject2) {
    const MapKey_T& lKey = ioObject2.describeKey();
    instance().addToMap (ioObject1, ioObject2, lKey);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2> void FacBomManager::
  addToListAndMap (OBJECT1& ioObject1, OBJECT2& ioObject2, const MapKey_T& iKey){
    BomHolder<OBJECT2>& lBomHolder = instance().getBomHolder<OBJECT2>(ioObject1);

    const bool insertionSucceeded =
      lBomHolder._bomMap.insert (typename std::map<const MapKey_T, OBJECT2*>::
                                 value_type (iKey, &ioObject2)).second;

    if (insertionSucceeded == false) {
      std::ostringstream oStr;
      oStr << "Cannot add the given object (key: '" << iKey
           << "') to the map of the object whose key is '"
           << ioObject1.describeKey()
           << "'. Indeed, that latter's map probably already contains that key. "
           << "Following are the keys already held by the map '";

      unsigned short idx = 0;
      for (typename std::map<const MapKey_T, OBJECT2*>::const_iterator iter =
             lBomHolder._bomMap.begin(); 
           iter != lBomHolder._bomMap.end(); ++iter, ++idx) {
        const OBJECT2* lCurrentObject_ptr = iter->second;
        assert (lCurrentObject_ptr != NULL);

        if (idx != 0) {
          oStr << "; ";
        }
        oStr << lCurrentObject_ptr->describeKey();
      }
      oStr << "'";

      STDAIR_LOG_ERROR (oStr.str());
      throw ObjectLinkingException (oStr.str());
    }

    lBomHolder._bomList.push_back (&ioObject2);    
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2> void FacBomManager::
  addToListAndMap (OBJECT1& ioObject1, OBJECT2& ioObject2) {
    const MapKey_T& lKey = ioObject2.describeKey();
    instance().addToListAndMap (ioObject1, ioObject2, lKey);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void FacBomManager::
  linkWithParent (PARENT& ioParent,  CHILD& ioChild) {
    ioChild._parent = &ioParent;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1> void FacBomManager::
  cloneHolder (OBJECT1& ioDest, const OBJECT1& iOri) {
    const BomHolder<OBJECT2>& lOriginHolder = 
      BomManager::getBomHolder<OBJECT2> (iOri);
    BomHolder<OBJECT2>& lDestHolder = instance().getBomHolder<OBJECT2> (ioDest);
    lDestHolder._bomList = lOriginHolder._bomList;
    lDestHolder._bomMap = lOriginHolder._bomMap;
  }
  
}

#endif // __STDAIR_FAC_FACBOMMANAGER_HPP
