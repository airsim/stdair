#ifndef __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP
#define __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#include <vector>
// StdAir
#include <stdair/stdair_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/FareOptionStruct.hpp>
#include <stdair/bom/FareOptionTypes.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>

namespace stdair {

  /** Structure holding the elements of a travel solution. */
  struct TravelSolutionStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get the segment path. */
    const SegmentPath_T& getSegmentPath () const {
      return _segmentPath;
    }

    /** Get the holder of avalabilities. */
    const ClassAvailabilityMapHolder_T& getClassAvailabilityMapHolder () const {
      return _classAvailabilityMapHolder;
    }

    /** Get the list of fare options. */
    const FareOptionList_T& getFareOptionList () const {
      return _fareOptionList;
    }
    
  public:
    // /////////// Setters ///////////////
    /** Add a segment key to the segment path. */
    void addSegment (const std::string&);

    /** Add a class availability map. */
    void addClassAvailabilityMap (const ClassAvailabilityMap_T&);

    /** Add a fare option. */
    void addFareOption (const FareOptionStruct&);

  public:
    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;
  
  public:
    // //////////// Constructors & Destructor ///////////////
    /** Main constructor. */
    TravelSolutionStruct ();
    /** Destructor. */
    ~TravelSolutionStruct ();
    
  private:
    // ///////////////////// Attributes //////////////////////
    /** The list of segment-date whole keys which make the travel solution. */
    SegmentPath_T _segmentPath;

    /** The list of availabilities for each segment-date. */
    ClassAvailabilityMapHolder_T _classAvailabilityMapHolder;

    /** The list of fare options. */
    FareOptionList_T _fareOptionList;
  };

}
#endif // __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP
