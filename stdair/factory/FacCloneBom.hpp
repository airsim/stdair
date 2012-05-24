#ifndef __STDAIR_FAC_FACCLONEBOM_HPP
#define __STDAIR_FAC_FACCLONEBOM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <list>
// StdAir 
#include <stdair/factory/FacAbstract.hpp>
#include <stdair/service/FacSupervisor.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {  

  /**
   * @brief Base class for Factory layer.
   */
  template <typename BOM>
  class FacCloneBom : public FacAbstract {

    /// Internal type definitions.
    typedef std::list<BOM*> BomPool_T;
    typedef typename BOM::Key_T Key_T;


  public:
    // ///////////// Business methods ////////////
    /**
     * Provide the unique instance.
     *
     * The singleton is instantiated when first used.
     * @return FacCloneBom&
     */
    static FacCloneBom& instance();

    /**
     * Clone a BOM object.
     */
    BOM& clone (const BOM&);
    
  protected:
    /**
     * Default Constructor.
     */
    FacCloneBom() {}

  public:
    /**
     * Destructor.
     */
    ~FacCloneBom() {
      clean();
    }

    /**
     * Destroyed all the object instantiated by this factory.
     */
    void clean();
    

  private:
    // ///////////////////// Attributes //////////////////
    /**
     * The unique instance.
     */
    static FacCloneBom* _instance;

    /**
     * List of instantiated Business Objects.
     */
    BomPool_T _pool;
  };


  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> FacCloneBom<BOM>* FacCloneBom<BOM>::_instance = NULL;
  
  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> FacCloneBom<BOM>& FacCloneBom<BOM>::instance () {
    if (_instance == NULL) {
      _instance = new FacCloneBom ();
      assert (_instance != NULL);

      FacSupervisor::instance().registerCloneBomFactory (_instance);
    }
    return *_instance;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> void FacCloneBom<BOM>::clean () {
    // Destroy all the objects
    for (typename BomPool_T::iterator itBom = _pool.begin();
         itBom != _pool.end(); ++itBom) {
      BOM* currentBom_ptr = *itBom;
      assert (currentBom_ptr != NULL);
      delete currentBom_ptr; currentBom_ptr = NULL;
    }

    // Empty the pool.
    _pool.clear();

    // Reset the static instance.
    _instance = NULL;
  }
  
  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> BOM& FacCloneBom<BOM>::clone (const BOM& iBom) {
    BOM* oBom_ptr = new BOM (iBom);
    assert (oBom_ptr != NULL);
    _pool.push_back (oBom_ptr);
    return *oBom_ptr;
  }
  
}
#endif // __STDAIR_FAC_FACCLONEBOM_HPP
