#ifndef __STDAIR_BOM_SEGMENTDATE_HPP
#define __STDAIR_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Fusion
#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
#include <boost/fusion/include/map.hpp>
#else // BOOST_VERSION >= 103500
#include <boost/mpl/map.hpp>
#endif // BOOST_VERSION >= 103500
// StdAir 
#include <stdair/bom/SegmentDateContent.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/LegDateTypes.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>

namespace stdair {
  // Forward declarations
  class FlightDate;
  class LegDate;
  class SegmentCabin;
  
  /** Class representing the actual functional/business content for a
      segment-date. */
  class SegmentDate : public SegmentDateContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef SegmentDateStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef FlightDate Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;

    /** Define the list of children holder types. */
#if BOOST_VERSION >= 103500
    typedef boost::fusion::map<
      boost::fusion::pair<SegmentCabin, SegmentCabinHolder_T*>,
      boost::fusion::pair<LegDate, LegDateHolder_T*>
      > ChildrenHolderMap_T;
#else // BOOST_VERSION >= 103500
    typedef boost::mpl::map< > ChildrenHolderMap_T;
#endif // BOOST_VERSION >= 103500
    // //////////////////////////////////////////////////////////////////
        
  public:
    // /////////// Getters /////////////
    /** Get a list or map of a children type for iteration methods. */
    SegmentCabinList_T getSegmentCabinList () const;
    SegmentCabinMap_T getSegmentCabinMap () const;
    LegDateList_T getLegDateList () const;
    LegDateMap_T getLegDateMap () const;

    /** Get the flight number of the segment. */
    const FlightNumber_T& getFlightNumber () const;
    
    /** Get the airline code of the segment. */
    const AirlineCode_T& getAirlineCode () const;

    /** Retrieve, if existing, the SegmentCabin corresponding to the
        given cabin code.
        <br>If not existing, return the NULL pointer. */
    SegmentCabin* getSegmentCabin (const CabinCode_T&) const;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    SegmentDate (const Key_T&, Structure_T&);
    /** Destructor. */
    ~SegmentDate();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    SegmentDate ();
    SegmentDate (const SegmentDate&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
    
  };

}
#endif // __STDAIR_BOM_SEGMENTDATE_HPP
