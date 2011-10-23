#ifndef __STDAIR_FAC_FACBOMMANAGER_HPP
#define __STDAIR_FAC_FACBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <list>
#include <map>
// StdAir
#include <stdair/bom/BomHolder.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/factory/FacAbstract.hpp>
#include <stdair/factory/FacBom.hpp>

namespace stdair {

  /**
   * @brief Utility class for linking StdAir-based objects.
   */
  class FacBomManager : public FacAbstract {
  public:
    // ///////////// Business methods. ////////////
    /**
     * Retrieve a pointer on the holder of children (OBJECT2 type) for
     * the parent (OBJECT1 type). If the holder does not exist,
     * return NULL.
     *
     * @param typename OBJECT1& Parent object.
     * @return typename BomHolder<OBJECT2>* BomHolder for the children objects.
     */
    template <typename OBJECT2, typename OBJECT1>
    static BomHolder<OBJECT2>* getBomHolderPtr (OBJECT1&);

    /**
     * Instantiate a BomHolder<OBJECT2> object, add it to the
     * OBJECT1-typed object, given as parameter, and return a
     * reference on that newly created BomHolder.
     *
     * @param typename OBJECT1& Parent object.
     * @return typename BomHolder<OBJECT2>& Just created BomHolder
     *         (e.g., for the children objects).
     */
    template <typename OBJECT2, typename OBJECT1> 
    static BomHolder<OBJECT2>& addBomHolder (OBJECT1&);

    /**
     * Add an OBJECT2-typed object (typically, a child) to the
     * dedicated list held by the OBJECT1-typed object (typically, a
     * parent).
     *
     * \note The underlying list is actually stored within an object
     *       of type BomHolder<OBJECT2>.
     *
     * @param typename OBJECT1& Parent object.
     * @param typename OBJECT2& Child object.
     */
    template <typename OBJECT1, typename OBJECT2>
    static void addToList (OBJECT1&, OBJECT2&);

    /**
     * Add an OBJECT2-typed object (typically, a child) to the
     * dedicated map held by the OBJECT1-typed object (typically, a
     * parent).
     *
     * \note The underlying map is actually stored within an object
     *       of type BomHolder<OBJECT2>.
     *
     * @param typename OBJECT1& Parent object.
     * @param typename OBJECT2& Child object.
     * @param const MapKey_T&
     */
    template <typename OBJECT1, typename OBJECT2>
    static void addToMap (OBJECT1&, OBJECT2&, const MapKey_T&);

    /**
     * Add an OBJECT2-typed object (typically, a child) to the
     * dedicated map held by the OBJECT1-typed object (typically, a
     * parent).
     *
     * \note The underlying map is actually stored within an object
     *       of type BomHolder<OBJECT2>.
     *
     * @param typename OBJECT1& Parent object.
     * @param typename OBJECT2& Child object.
     */
    template <typename OBJECT1, typename OBJECT2>
    static void addToMap (OBJECT1&, OBJECT2&);

    /**
     * Add an OBJECT2-typed object (typically, a child) to the
     * dedicated containers (list and map) held by the OBJECT1-typed
     * object (typically, a parent).
     *
     * \note The underlying containers are actually stored within an
     *       object of type BomHolder<OBJECT2>.
     *
     * @param typename OBJECT1& Parent object.
     * @param typename OBJECT2& Child object.
     */
    template <typename OBJECT1, typename OBJECT2>
    static void addToListAndMap (OBJECT1&, OBJECT2&);

    /**
     * Add an OBJECT2-typed object (typically, a child) to the
     * dedicated containers (list and map) held by the OBJECT1-typed
     * object (typically, a parent).
     *
     * \note The underlying containers are actually stored within an
     *       object of type BomHolder<OBJECT2>.
     *
     * @param typename OBJECT1& Parent object.
     * @param typename OBJECT2& Child object.
     * @param const MapKey_T&
     */
    template <typename OBJECT1, typename OBJECT2>
    static void addToListAndMap (OBJECT1&, OBJECT2&, const MapKey_T&);

    /**
     * Allow the CHILD object to store a pointer on its PARENT object.
     *
     * @param typename PARENT& Parent object.
     * @param typename CHILD& Child object.
     */
    template <typename PARENT, typename CHILD>
    static void linkWithParent (PARENT&, CHILD&);

    /**
     * Clone the underlying containers (held by the
     * BomHolder<OBJECT2>-typed holder) of the OBJECT1-typed object.
     *
     * \note The underlying containers are actually stored within an
     *       object of type BomHolder<OBJECT2>.
     *
     * @param typename OBJECT1& Parent object.
     * @param typename OBJECT2& Child object.
     */
    template <typename OBJECT2, typename OBJECT1>
    static void cloneHolder (OBJECT1&, const OBJECT1&);


  private:
    /**
     * Add an OBJECT2-typed object (typically, a child) to the
     * dedicated list held by the OBJECT1-typed object (typically, a
     * parent).
     *
     * \note The underlying list is actually stored within the given
     *       object of type BomHolder<OBJECT2>. Passing that object
     *       allows avoiding having to retrieve it once again.
     *
     * @param typename OBJECT1& Parent object.
     * @param typename OBJECT2& Child object.
     */
    template <typename OBJECT1, typename OBJECT2>
    static void addToList (BomHolder<OBJECT2>&, OBJECT1&, OBJECT2&);

    /**
     * Add an OBJECT2-typed object (typically, a child) to the
     * dedicated map held by the OBJECT1-typed object (typically, a
     * parent).
     *
     * \note The underlying map is actually stored within the given
     *       object of type BomHolder<OBJECT2>. Passing that object
     *       allows avoiding having to retrieve it once again.
     *
     * @param typename OBJECT1& Parent object.
     * @param typename OBJECT2& Child object.
     * @param const MapKey_T&
     */
    template <typename OBJECT1, typename OBJECT2>
    static void addToMap (BomHolder<OBJECT2>&, OBJECT1&, OBJECT2&,
                          const MapKey_T&);

    /**
     * Retrieve a reference on the holder of children (OBJECT2 type)
     * for the parent (OBJECT1 type). If the holder does not exist,
     * one is created.
     *
     * @param typename OBJECT1& Parent object.
     * @return typename BomHolder<OBJECT2>& BomHolder for the children objects.
     */
    template <typename OBJECT2, typename OBJECT1>
    static BomHolder<OBJECT2>& getBomHolder (OBJECT1&);


  protected:
    /**
     * Default Constructor.
     *
     * This constructor is protected to comply with the singleton pattern.
     */
    FacBomManager() { }

  public:
    /**
     * Destructor.
     */
    ~FacBomManager() { }
  };


  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1> 
  BomHolder<OBJECT2>& FacBomManager::addBomHolder (OBJECT1& ioObject1) {

    BomHolder<OBJECT2>* lBomHolder_ptr =
      &FacBom<BomHolder<OBJECT2> >::instance().create();

    const bool hasInsertBeenSuccessful =
      ioObject1._holderMap.insert (typename HolderMap_T::
                                   value_type (&typeid (OBJECT2),
                                               lBomHolder_ptr)).second;
    assert (hasInsertBeenSuccessful == true);

    return *lBomHolder_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1> 
  BomHolder<OBJECT2>* FacBomManager::getBomHolderPtr (OBJECT1& ioObject1) {

    BomHolder<OBJECT2>* lBomHolder_ptr = NULL;

    // Find the corresponding BomHolder within the object1, if existing.
    HolderMap_T::const_iterator itHolder =
      ioObject1._holderMap.find (&typeid (OBJECT2));

    if (itHolder != ioObject1._holderMap.end()) {
      lBomHolder_ptr = static_cast<BomHolder<OBJECT2>*> (itHolder->second);
    }

    return lBomHolder_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT2, typename OBJECT1> 
  BomHolder<OBJECT2>& FacBomManager::getBomHolder (OBJECT1& ioObject1) {

    BomHolder<OBJECT2>* lBomHolder_ptr = NULL;

    // Find the corresponding BomHolder within the object1. If it does
    // not exist, then create one.
    HolderMap_T::const_iterator itHolder =
      ioObject1._holderMap.find (&typeid (OBJECT2));

    if (itHolder == ioObject1._holderMap.end()) {
      lBomHolder_ptr = &addBomHolder<OBJECT2, OBJECT1> (ioObject1);

    } else {
      lBomHolder_ptr = static_cast<BomHolder<OBJECT2>*> (itHolder->second);
    }

    assert (lBomHolder_ptr != NULL);

    return *lBomHolder_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2>
  void FacBomManager::addToList (BomHolder<OBJECT2>& ioBomHolder,
                                 OBJECT1& ioObject1, OBJECT2& ioObject2) {
    ioBomHolder._bomList.push_back (&ioObject2);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2>
  void FacBomManager::addToList (OBJECT1& ioObject1, OBJECT2& ioObject2) {

    BomHolder<OBJECT2>& lBomHolder = getBomHolder<OBJECT2> (ioObject1);

    addToList<OBJECT1, OBJECT2> (lBomHolder, ioObject1, ioObject2);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2>
  void FacBomManager::addToMap (BomHolder<OBJECT2>& ioBomHolder,
                                OBJECT1& ioObject1, OBJECT2& ioObject2,
                                const MapKey_T& iKey) {

    const bool insertionSucceeded =
      ioBomHolder._bomMap.insert (typename std::map<const MapKey_T, OBJECT2*>::
                                  value_type (iKey, &ioObject2)).second;

    if (insertionSucceeded == false) {
      // Build a nice message, so that the error be fully explicit
      std::ostringstream oStr;
      oStr << "The given object ('" << iKey
           << "') can not be added to the map of '" << ioObject1.describeKey()
           << "' object. That map already contains: '";

      unsigned int idx = 0;
      for (typename std::map<const MapKey_T, OBJECT2*>::const_iterator iter =
             ioBomHolder._bomMap.begin(); 
           iter != ioBomHolder._bomMap.end(); ++iter, ++idx) {
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
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2> void FacBomManager::
  addToMap (OBJECT1& ioObject1, OBJECT2& ioObject2, const MapKey_T& iKey) {

    BomHolder<OBJECT2>& lBomHolder = getBomHolder<OBJECT2> (ioObject1);

    addToMap<OBJECT1, OBJECT2> (lBomHolder, ioObject1, ioObject2, iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2>
  void FacBomManager::addToMap (OBJECT1& ioObject1, OBJECT2& ioObject2) {
    const MapKey_T& lKey = ioObject2.describeKey();
    addToMap (ioObject1, ioObject2, lKey);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2>
  void FacBomManager::addToListAndMap (OBJECT1& ioObject1, OBJECT2& ioObject2,
                                       const MapKey_T& iKey) {

    BomHolder<OBJECT2>& lBomHolder = getBomHolder<OBJECT2> (ioObject1);

    addToList<OBJECT1, OBJECT2> (lBomHolder, ioObject1, ioObject2);
    addToMap<OBJECT1, OBJECT2> (lBomHolder, ioObject1, ioObject2, iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename OBJECT1, typename OBJECT2> void FacBomManager::
  addToListAndMap (OBJECT1& ioObject1, OBJECT2& ioObject2) {
    const MapKey_T& lKey = ioObject2.describeKey();
    addToListAndMap<OBJECT1, OBJECT2> (ioObject1, ioObject2, lKey);
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

    BomHolder<OBJECT2>& lDestHolder = getBomHolder<OBJECT2> (ioDest);
    lDestHolder._bomList = lOriginHolder._bomList;
    lDestHolder._bomMap = lOriginHolder._bomMap;
  }
  
}

#endif // __STDAIR_FAC_FACBOMMANAGER_HPP
