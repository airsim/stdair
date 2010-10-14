// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/YieldStore.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  YieldStore::YieldStore (const Key_T& iKey) : _key (iKey), _parent (NULL) {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldStore::~YieldStore () {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string YieldStore::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }

}

