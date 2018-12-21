#ifndef __STDAIR_BOM_CLASSAVAILABILITYSTRUCT_HPP
#define __STDAIR_BOM_CLASSAVAILABILITYSTRUCT_HPP

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
  struct ClassAvailabilityStruct;
  typedef std::list<ClassAvailabilityStruct> ClassAvailabilityMapHolder_T;

  /**
   * @brief Structure holding the elements of a travel solution.
   */
  struct ClassAvailabilityStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    const ClassAvailabilityMap_T& getClassAvailabilityMap() const {
      return _classAvailabilityStruct;
    }

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
     * "Wrapper" contructor.
     */
    ClassAvailabilityStruct (const ClassAvailabilityMap_T&);
    
    /**
     * Default constructor.
     */
    ClassAvailabilityStruct();

    /**
     * Copy constructor.
     */
    ClassAvailabilityStruct (const ClassAvailabilityStruct&);
    
    /**
     * Destructor.
     */
    ~ClassAvailabilityStruct();
    

  private:
    // ///////////////////// Attributes //////////////////////
    /**
     * The list of availabilities for each segment-date.
     */
    ClassAvailabilityMap_T _classAvailabilityStruct;
  };

}
#endif // __STDAIR_BOM_CLASSAVAILABILITYSTRUCT_HPP
