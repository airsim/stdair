// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/PosChannel.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  PosChannel::PosChannel()
    : _key (DEFAULT_POS,
            DEFAULT_CHANNEL),
      _parent (NULL)  {
    // That constructor is used by the serialisation process
  }

  // ////////////////////////////////////////////////////////////////////
  PosChannel::PosChannel (const PosChannel& iPosChannel)
    : _key (iPosChannel.getKey()), _parent (NULL)  {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  PosChannel::PosChannel (const Key_T& iKey)
    : _key (iKey), _parent (NULL)  {
  }

  // ////////////////////////////////////////////////////////////////////
  PosChannel::~PosChannel () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string PosChannel::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }
}
