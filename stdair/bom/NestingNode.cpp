// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <cassert>
#include <iomanip>
#include <iostream>
//STDAIR
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp> 
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/NestingNode.hpp>

namespace stdair {
    
  // ////////////////////////////////////////////////////////////////////
  NestingNode::NestingNode () : 
    _key (DEFAULT_NESTING_NODE_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  NestingNode::NestingNode (const NestingNode& iNestingNode)
  : _key (DEFAULT_NESTING_NODE_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  NestingNode::NestingNode (const Key_T& iKey) : _key (iKey), _parent (NULL) {
  }
    
  // ////////////////////////////////////////////////////////////////////
  NestingNode::~NestingNode() {
  }
    
  // ////////////////////////////////////////////////////////////////////
  std::string NestingNode::toString () const {
    std::ostringstream oStr;
    oStr << describeKey();
    
    oStr << _yield << std::endl;
    
    return oStr.str();
  }
  
}
