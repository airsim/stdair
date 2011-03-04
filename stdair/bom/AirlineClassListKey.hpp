#ifndef __STDAIR_BOM_AIRLINECLASSLISTKEY_HPP
#define __STDAIR_BOM_AIRLINECLASSLISTKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <list>
// STDAIR
#include <stdair/bom/KeyAbstract.hpp>
#include <stdair/stdair_types.hpp>

namespace stdair  {
  /** Key of airport-pair. */
  struct AirlineClassListKey : public KeyAbstract {

  private:
    // /////////// Default constructor //////////
    AirlineClassListKey () { };
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    AirlineClassListKey (const AirlineCodeList_T&,
                         const ClassList_StringList_T&);
    AirlineClassListKey (const AirlineClassListKey&);
    /** Destructor. */
    ~AirlineClassListKey ();
    
    // /////////// Getters //////////
    /** Get the airline code list. */
    const AirlineCodeList_T& getAirlineCodeList() const {
      return _airlineCodeList;
    }

    /** Get the class code list. */
    const ClassList_StringList_T& getClassCodeList() const {
      return _classCodeList;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object. */
    const std::string toString() const;

  private:
    // Attributes
    /** Airline code List. */
    AirlineCodeList_T _airlineCodeList;

    /** Classe code List. */
    ClassList_StringList_T _classCodeList;
  };

}
#endif // __STDAIR_BOM_AIRLINECLASSLISTKEY_HPP
