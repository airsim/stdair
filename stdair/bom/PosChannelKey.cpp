// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// STDAIR
#include <stdair/bom/PosChannelKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  PosChannelKey::PosChannelKey (const CityCode_T& iPos,
                                const ChannelLabel_T& iChannel)
    : _pos (iPos), _channel(iChannel) {
  }

  // ////////////////////////////////////////////////////////////////////
  PosChannelKey::PosChannelKey (const PosChannelKey& iKey)
    : _pos (iKey._pos), _channel (iKey._channel) {
  }

  // ////////////////////////////////////////////////////////////////////
  PosChannelKey::~PosChannelKey () {
  }

  // ////////////////////////////////////////////////////////////////////
  void PosChannelKey::toStream (std::ostream& ioOut) const {
    ioOut << "PosChannelKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void PosChannelKey::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string PosChannelKey::toString() const {
    std::ostringstream oStr;
    oStr << _pos << "," << _channel << std::endl; 
    return oStr.str();
  }

}
