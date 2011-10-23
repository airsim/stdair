#ifndef __STDAIR_SVC_FACSTDAIRSERVICECONTEXT_HPP
#define __STDAIR_SVC_FACSTDAIRSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/service/FacServiceAbstract.hpp>

namespace stdair {

  //// Forward declarations
  class STDAIR_ServiceContext;

  /**
   * @brief Factory for Bucket.
   */
  class FacSTDAIRServiceContext : public FacServiceAbstract {
  public:

    /**
     * Provide the unique instance.
     *
     * The singleton is instantiated when first used.
     *
     * @return FacSTDAIRServiceContext&
     */
    static FacSTDAIRServiceContext& instance();

    /**
     * Destructor.
     *
     * The Destruction put the _instance to NULL
     * in order to be clean for the next FacSTDAIRServiceContext::instance().
     */
    ~FacSTDAIRServiceContext();

    /**
     * Create a new STDAIR_ServiceContext object.
     *
     * This new object is added to the list of instantiated objects.
     *
     * @return STDAIR_ServiceContext& The newly created object.
     */
    STDAIR_ServiceContext& create();

    
  protected:
    /**
     * Default Constructor.
     *
     * This constructor is protected in order to ensure the singleton pattern.
     */
    FacSTDAIRServiceContext() {}

  private:
    /**
     * The unique instance.
     */
    static FacSTDAIRServiceContext* _instance;
  };

}
#endif // __STDAIR_SVC_FACSTDAIRSERVICECONTEXT_HPP
