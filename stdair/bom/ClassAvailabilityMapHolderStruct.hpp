#ifndef __STDAIR_BOM_CLASSAVAILABILITYMAPHOLDERSTRUCT_HPP
#define __STDAIR_BOM_CLASSAVAILABILITYMAPHOLDERSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#include <list>
#include <map>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /**
   * Define (booking class, availability) map.
   */
  typedef std::map<const ClassCode_T, Availability_T> ClassAvailabilityMap_T;

  /**
   * Define list of (booking class, availability) maps.
   */
  typedef std::list<ClassAvailabilityMap_T> ClassAvailabilityMapHolder_T;

  /**
   * @brief Structure holding the elements of a travel solution.
   */
  struct ClassAvailabilityMapHolderStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get the holder of avalabilities. */
    const ClassAvailabilityMapHolder_T& getClassAvailabilityMapHolder() const {
      return _classAvailabilityMapHolder;
    }

  public:
    // /////////// Setters ///////////////
    /** Add a class availability map. */
    void addClassAvailabilityMap (const ClassAvailabilityMap_T&);


  public:
    // /////////// Display support method /////////////
    /**
     * Dump a Business Object into an output stream.
     *
     * @param ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;

    /**
     * Read a Business Object from an input stream.
     * @param istream& the input stream.
     */
    void fromStream (std::istream& ioIn);

    /**
     * Display of the structure.
     */
    const std::string describe() const;
  
    /**
     * Display of the structure.
     */
    const std::string display() const;


  public:
    // //////////// Constructors & Destructor ///////////////
    /**
     * Default constructor.
     */
    ClassAvailabilityMapHolderStruct();

    /**
     * Copy constructor.
     */
    ClassAvailabilityMapHolderStruct (const ClassAvailabilityMapHolderStruct&);
    
    /**
     * Destructor.
     */
    ~ClassAvailabilityMapHolderStruct();
    

  private:
    // ///////////////////// Attributes //////////////////////
    /**
     * The list of availabilities for each segment-date.
     */
    ClassAvailabilityMapHolder_T _classAvailabilityMapHolder;
  };

}
#endif // __STDAIR_BOM_CLASSAVAILABILITYMAPHOLDERSTRUCT_HPP
