// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <sstream>
// STDAIR
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/bom/PosChannelKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  PosChannelKey::PosChannelKey()
    : _pos (DEFAULT_POS),
      _channel (DEFAULT_CHANNEL) {
    assert (false);
  }

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
    oStr << _pos << DEFAULT_KEY_SUB_FLD_DELIMITER
         << " " << _channel; 
    return oStr.str();
  }

}
