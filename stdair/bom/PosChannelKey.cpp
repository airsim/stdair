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
  PosChannelKey::PosChannelKey (const CityCode_T& iPosition,
                                const ChannelLabel_T& iChannel)
    : _position (iPosition), _channel(iChannel) {
  }

  // ////////////////////////////////////////////////////////////////////
  PosChannelKey::PosChannelKey (const PosChannelKey& iKey)
    : _position (iKey._position), _channel (iKey._channel) {
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
    oStr << _position << "," << _channel << std::endl; 
    return oStr.str();
  }

}
