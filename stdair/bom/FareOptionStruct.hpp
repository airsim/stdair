#ifndef __STDAIR_BOM_FAREOPTIONSTRUCT_HPP
#define __STDAIR_BOM_FAREOPTIONSTRUCT_HPP

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

namespace stdair {

  /** Structure holding the elements of a fare option. */
  struct FareOptionStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get attributes. */
    const ClassList_String_T& getClassPath () const { return _classPath; }
    const Fare_T& getFare () const { return _fare; }
    const ChangeFees_T getChangeFees () const { return _changeFee; }
    const NonRefundable_T getNonRefundable () const {return _nonRefundable; }
    const SaturdayStay_T getSaturdayStay () const {return _saturdayStay; }

  public:
    // /////////// Setters ///////////////
    /** Set attributes. */
    void addClass (const ClassCode_T& iClassCode);
    void setFare (const Fare_T& iFare) { _fare = iFare; }
    void setChangeFees (const ChangeFees_T iRes) { _changeFee = iRes; }
    void setNonRefundable (const NonRefundable_T iRes) { _nonRefundable = iRes;}
    void setSaturdayStay (const SaturdayStay_T iRes) { _saturdayStay = iRes; }
        
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
    FareOptionStruct ();
    /** Destructor. */
    ~FareOptionStruct ();
    
  private:
    // ///////////////////// Attributes //////////////////////
    /** The class path. */
    ClassList_String_T _classPath;

    /** Fare. */
    Fare_T _fare;

    /** Restrictions. */
    ChangeFees_T _changeFee;
    NonRefundable_T _nonRefundable;
    SaturdayStay_T _saturdayStay;
  };

}
#endif // __STDAIR_BOM_FAREOPTIONSTRUCT_HPP
