#ifndef __STDAIR_BOM_CANCELLATIONSTRUCT_HPP
#define __STDAIR_BOM_CANCELLATIONSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#include <vector>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>
#include <stdair/bom/BomIDTypes.hpp>

namespace stdair {

  /**
   * @brief Structure holding the elements of a travel solution.
   */
  struct CancellationStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get the segment path. */
    const SegmentPath_T& getSegmentPath() const {
      return _segmentPath;
    }

    /** Get the class list. */
    const ClassList_String_T& getClassList() const {
      return _classList;
    }

    /** Get the class ID list. */
    const BookingClassIDList_T& getClassIDList() const {
      return _classIDList;
    }

    /** Get the party size. */
    const PartySize_T& getPartySize() const {
      return _partySize;
    }

    /** Get the datetime. */
    const DateTime_T& getCancellationDateTime() const {
      return _datetime;
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
     * Default constructor without class ID list.
     */
    CancellationStruct (const SegmentPath_T&, const ClassList_String_T&,
                        const PartySize_T&, const DateTime_T&);
    
    /**
     * Default constructor with class ID list.
     */
    CancellationStruct (const BookingClassIDList_T&,
                        const PartySize_T&, const DateTime_T&);

    /**
     * Destructor.
     */
    ~CancellationStruct();
    

  private:
    // ///////////////////// Attributes //////////////////////
    /**
     * The list of segment-date whole keys which make the travel solution.
     */
    SegmentPath_T _segmentPath;

    /**
     * The list of availabilities for each segment-date.
     */
    ClassList_String_T _classList;

    /**
     * The list of booking class ID list.
     */
    BookingClassIDList_T _classIDList;

    /**
     * The party size of the cancellation.
     */
    PartySize_T _partySize;

    /**
     * The datetime of this cancellation.
     */
    DateTime_T _datetime;
  };

}
#endif // __STDAIR_BOM_CANCELLATIONSTRUCT_HPP
