#ifndef __STDAIR_BOM_BOMCHILDRENHOLDERIMP_HPP
#define __STDAIR_BOM_BOMCHILDRENHOLDERIMP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <vector>
#include <string>
#include <map>
//STDAIR 
#include <stdair/bom/BomChildrenHolder.hpp>
#include <stdair/bom/BomIterator.hpp>

namespace stdair {
  
  /** Template class aimed at holding a list and a map of children BOM
      structure of a dedicated type. */
  template <typename CONTENT>
  class BomChildrenHolderImp : public BomChildrenHolder {
    friend class FacBomStructure;

    /** Retrieve associated bom structure type. */
    typedef typename CONTENT::Structure_T Structure_T;
    
  public:
    /** Define lists of children BOM structures. */
    typedef std::vector<const Structure_T*> BomChildrenList_T;
    /** Retrieve the map type of children BOM structures. */
    typedef typename CONTENT::Map_T BomChildrenMap_T;

    /** Define the different types of iterators. */
    typedef BomIterator_T<CONTENT,
                          typename BomChildrenList_T::const_iterator
                          > ListIterator_T;

    typedef BomIterator_T<CONTENT,
                          typename BomChildrenList_T::const_reverse_iterator
                          > ListReverseIterator_T;

    typedef BomIterator_T<CONTENT,
                          typename BomChildrenMap_T::const_iterator
                          > MapIterator_T;

    typedef BomIterator_T<CONTENT,
                          typename BomChildrenMap_T::const_reverse_iterator
                          > MapReverseIterator_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return std::string (""); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return std::string (""); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return std::string (""); }

    // /////////// Iteration methods //////////
    /** Initialise the internal iterators on bom objects:
        return the iterator at the begining of the list. */
    ListIterator_T listBegin () const {
      return ListIterator_T(_bomChildrenList.begin());
    }
    
    /** Initialise the internal iterators on bom objects:
        return the iterator past the end of the list. */
    ListIterator_T listEnd () const {
      return _bomChildrenList.end();
    }

    /** Initialise the internal reverse iterators on bom objects:
        return the reverse iterator at the rbegining of the list. */
    ListReverseIterator_T listRBegin () const {
      return _bomChildrenList.rbegin();
    }
    
    /** Initialise the internal reverse iterators on bom objects:
        return the reverse iterator past the rend of the list. */
    ListReverseIterator_T listREnd () const {
      return _bomChildrenList.rend();
    }

    /** Initialise the internal iterators on bom objects:
        return the iterator at the begining of the map. */
    MapIterator_T mapBegin () const {
      return _bomChildrenMap.begin();
    }
    
    /** Initialise the internal iterators on bom objects:
        return the iterator past the end of the map. */
    MapIterator_T mapEnd () const {
      return _bomChildrenMap.end();
    }

    /** Initialise the internal reverse iterators on bom objects:
        return the reverse iterator at the rbegining of the map. */
    MapReverseIterator_T mapRBegin () const {
      return _bomChildrenMap.rbegin();
    }
    
    /** Initialise the internal reverse iterators on bom objects:
        return the reverse iterator past the rend of the map. */
    MapReverseIterator_T mapREnd () const {
      return _bomChildrenMap.rend();
    }
    
    // /////////// Other operators /////////////
    /** Get the size of the list. */
    const unsigned int size () const {
      return _bomChildrenList.size();
    }

    /** Retrieve, if existing, the bom corresponding to the given key. */
    MapIterator_T find (const MapKey_T& iKey) const {
      return _bomChildrenMap.find (iKey);
    }

  private:
    /** Insert an element to the list and the map. */
    const bool insert (const MapKey_T& iKey, const Structure_T& iStructure) {
      const bool hasInsertionSuccessful = insert (iKey, iStructure,
                                                  _bomChildrenMap);
      if (hasInsertionSuccessful == true) {
        _bomChildrenList.push_back (&iStructure);
      }

      return hasInsertionSuccessful;
    }

    /** Internal insertion function into a map. */
    const bool insert (const MapKey_T& iKey, const Structure_T& iStructure,
                       std::map<const MapKey_T, const Structure_T*>& ioMap) {
      return ioMap.insert (typename std::map<const MapKey_T,const Structure_T*>::
                           value_type (iKey, &iStructure)).second;
    }

    /** Internal insertion function into a multimap. */
    const bool insert (const MapKey_T& iKey, const Structure_T& iStructure,
                       std::multimap<const MapKey_T, const Structure_T*>& ioMap){
      const bool hasInsertionBeenSuccessful =
        (ioMap.insert (typename std::multimap<const MapKey_T, const Structure_T*>::
                       value_type (iKey, &iStructure))) != (ioMap.end());
      
      return hasInsertionBeenSuccessful;
    }
    
  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomChildrenHolderImp () { }
    BomChildrenHolderImp (const BomChildrenHolderImp&);
    /** Destructor. */
    ~BomChildrenHolderImp() { }
    
  private:
    ///////////// Attributes //////////////
    /** List of children BOM structures. */
    BomChildrenList_T _bomChildrenList;

    /** Map of children BOM structures with their key. */
    BomChildrenMap_T _bomChildrenMap;
  };
  
}
#endif // __STDAIR_BOM_BOMCHILDRENHOLDERIMP_HPP
