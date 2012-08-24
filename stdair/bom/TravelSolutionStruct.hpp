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
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/FareOptionStruct.hpp>
#include <stdair/bom/FareOptionTypes.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>

namespace stdair {

  /**
   * @brief Structure holding the elements of a travel solution.
   */
  struct TravelSolutionStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get the segment path. */
    const SegmentPath_T& getSegmentPath() const {
      return _segmentPath;
    }

    /** Get the holder of avalabilities. */
    const ClassAvailabilityMapHolder_T& getClassAvailabilityMapHolder() const {
      return _classAvailabilityMapHolder;
    }

    /** Get the holder of object ID's. */
    const ClassObjectIDMapHolder_T& getClassObjectIDMapHolder() const {
      return _classObjectIDMapHolder;
    }

    /** Get the holder of yields. */
    const ClassYieldMapHolder_T& getClassYieldMapHolder() const {
      return _classYieldMapHolder;
    }

    /** Get the holder of bid price vectors. */
    const BidPriceVectorHolder_T& getBidPriceVectorHolder() const {
      return _bidPriceVectorHolder;
    }
    
    /** Get the holder of class - bid price reference. */
    const ClassBpvMapHolder_T& getClassBpvMapHolder() const {
      return _classBpvMapHolder;
    }

    /** Get the list of fare options. */
    const FareOptionList_T& getFareOptionList() const {
      return _fareOptionList;
    }

    /** Get the non-const list of fare options. */
    FareOptionList_T& getFareOptionListRef() {
      return _fareOptionList;
    }

    /** Get the chosen fare option. */
    const FareOptionStruct& getChosenFareOption() const {
      assert (_chosenFareOption != NULL);
      return *_chosenFareOption;
    }
    
  public:
    // /////////// Setters ///////////////
    /** Add a segment key to the segment path. */
    void addSegment (const std::string&);

    /** Add a class availability map. */
    void addClassAvailabilityMap (const ClassAvailabilityMap_T&);

    /** Add a class object ID map. */
    void addClassObjectIDMap (const ClassObjectIDMap_T&);

    /** Add a class yield map. */
    void addClassYieldMap (const ClassYieldMap_T&);

    /** Add a bid price vector. */
    void addBidPriceVector (const BidPriceVector_T&);

    /** Add a class bpv reference map. */
    void addClassBpvMap (const ClassBpvMap_T&);

    /** Add a fare option. */
    void addFareOption (const FareOptionStruct&);

    /** Set the chosen fare option. */
    void setChosenFareOption (const FareOptionStruct& iChosenFO) {
      _chosenFareOption = &iChosenFO;
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

    /**
     * Display only the segment path.
     */
    const std::string describeSegmentPath() const;
  

  public:
    // //////////// Constructors & Destructor ///////////////
    /**
     * Default constructor.
     */
    TravelSolutionStruct();

    /**
     * Destructor.
     */
    ~TravelSolutionStruct();
    

  private:
    // ///////////////////// Attributes //////////////////////
    /**
     * The list of segment-date whole keys which make the travel solution.
     */
    SegmentPath_T _segmentPath;

    /**
     * The list of availabilities for each segment-date.
     */
    ClassAvailabilityMapHolder_T _classAvailabilityMapHolder;

    /**
     * The list of class ID for each segment-date.
     */
    ClassObjectIDMapHolder_T _classObjectIDMapHolder;
    
    /**
     * The list of yields for each segment-date.
     */
    ClassYieldMapHolder_T _classYieldMapHolder;
    
    /**
     * The list of BP vectors of all cabins.
     */
    BidPriceVectorHolder_T _bidPriceVectorHolder;
    
    /**
     * The list of BP vector references for each class.
     */
    ClassBpvMapHolder_T _classBpvMapHolder;

    /**
     * The list of fare options.
     */
    FareOptionList_T _fareOptionList;

    /**
     * The chosen fare option.
     */
    const FareOptionStruct* _chosenFareOption;
  };

}
#endif // __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP
