#ifndef __STDAIR_BOM_POSCHANNELKEY_HPP
#define __STDAIR_BOM_POSCHANNELKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// SIMFQT
#include <stdair/bom/KeyAbstract.hpp>
#include <stdair/stdair_types.hpp>

namespace stdair  {
  /** Key of fare point of sale and channel. */
  struct PosChannelKey : public KeyAbstract {

  private:
    // /////////// Default constructor //////////
    PosChannelKey () { };
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    PosChannelKey (const CityCode_T&, const ChannelLabel_T&);
    PosChannelKey (const PosChannelKey&);
    /** Destructor. */
    ~PosChannelKey ();
    
    // /////////// Getter //////////
    /** Get the point of sale. */
    const CityCode_T& getPos() const {
      return _pos;
    }
   
    /** Get the channel. */
    const ChannelLabel_T& getChannel() const {
      return _channel;
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
       when among children of a given parent Business Object.*/
    const std::string toString() const;

  private:
    // Attributes
    /** City code point of sale. */
    CityCode_T _pos;

    /** Booking channel
        (D=direct, I=indirect, N=oNline, F=oFfline). */
    ChannelLabel_T _channel;

  };

}
#endif // __STDAIR_BOM_POSCHANNELKEY_HPP
