#ifndef __STDAIR_BOM_SIMPLENESTINGSTRUCT_HPP
#define __STDAIR_BOM_SIMPLENESTINGSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL

// StdAir
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/NestingTypes.hpp>

namespace stdair {    

  /**
   * Structure holding a nesting node map according to the yield.
   */
  struct SimpleNestingStruct : public StructAbstract {
      
  public:
    // /////////////////// Getters ////////////////////////
    /**
     * Get the nesting node map
     */
    const NestingNodeMap_T& getNestingNodeMap() const {
      return _nestingNodeMap;
    }   
    
  public:
    // ///////////////////// Modifiers /////////////////////
    /**
     * Insert a list of booking class in the nesting node map
     */
    const bool insertBookingClassList(const Yield_T&,
                                      const BookingClassList_T&);

    /**
     * Clear all elements of the nesting node map
     */
    void clear() {
      _nestingNodeMap.clear();
    }

  public:
    // ///////////////////// Management map methods /////////////////////
    /**
     * Search if a booking class is already in the nesting structure
     */
    const bool alreadyInNestingStruct(const ClassCode_T&) const;

  public:
    // ///////// Display Methods //////////
    /**
     * Dump a Business Object into an output stream.
     * @param ostream& the output stream
     * @return ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;
    
    /**
     * Give a description of the structure (for display purposes).
     */
    const std::string describe() const;
      
    /**
     * Display on standard output.
     */
    void display () const;
      
  public:
    // /////////// Constructors and destructor. ////////////
    /**
     * Default constructor.
     */
    SimpleNestingStruct();

    /**
     * Main constructor.
     */
    SimpleNestingStruct (const NestingNodeMap_T&);

    /**
     * Copy constructor.
     */
    SimpleNestingStruct (const SimpleNestingStruct&);
      
    /**
     * Destructor.
     */
    virtual ~SimpleNestingStruct();
     
  private:
    // //////////// Attributes ////////////
    /**
     * The nesting node map.
     */
    NestingNodeMap_T _nestingNodeMap;

  };
}
#endif // __STDAIR_BOM_SIMPLENESTINGSTRUCT_HPP
