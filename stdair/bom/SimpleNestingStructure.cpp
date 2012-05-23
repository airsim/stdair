// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <cassert>
#include <iomanip>
#include <iostream>
//STDAIR
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/SimpleNestingStructure.hpp>
#include <stdair/bom/NestingNode.hpp>
#include <stdair/bom/NestingNodeTypes.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {
    
  // ////////////////////////////////////////////////////////////////////
  SimpleNestingStructure::SimpleNestingStructure () : 
    _key (DEFAULT_NESTING_STRUCTURE_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SimpleNestingStructure::
  SimpleNestingStructure (const SimpleNestingStructure& iSimpleNestingStructure)
  : _key (DEFAULT_NESTING_STRUCTURE_CODE), _parent (NULL) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SimpleNestingStructure::SimpleNestingStructure (const Key_T& iKey)
  : _key (iKey), _parent (NULL) {
  }
    
  // ////////////////////////////////////////////////////////////////////
  SimpleNestingStructure::~SimpleNestingStructure() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  // const bool SimpleNestingStructure::insertBookingClassList(const Yield_T& iYield,
  //                                   const BookingClassList_T& iBookingClassList) {
  //   const bool isBookinClassListEmpty = iBookingClassList.empty();
  //   if (isBookinClassListEmpty == true) {
  //     std::ostringstream ostr;
  //     ostr << "The booking class list is empty and it should not be. "
  //       "No insertion done in the nesting structure (";
  //     toStream(ostr);
  //     ostr << ").";
  //     STDAIR_LOG_DEBUG(ostr.str());
  //     throw BookingClassListEmptyInNestingStructException(ostr.str());
  //   }
  //   assert(isBookinClassListEmpty == false);
  //   NestingNodeMap_T::iterator itNestingNode = _nestingNodeMap.find (iYield);
  //   bool insertionSucceeded = false;
  //   // Search a node with the same yield and add the
  //   // booking classes to the booking class list of the node.
  //   // If there is not a node with the same yield, create it.
  //   if (itNestingNode == _nestingNodeMap.end()) {
  //     NestingNode_T lNode (iYield, iBookingClassList);
  //     insertionSucceeded = _nestingNodeMap.insert(lNode).second;
  //   } else {
  //     NestingNode_T& lNode = *itNestingNode;
  //     const Yield_T& lYield = lNode.first;
  //     assert(lYield == iYield);
  //     BookingClassList_T& lBCList = lNode.second;
  //     for (BookingClassList_T::const_iterator itBC = iBookingClassList.begin(); 
  //          itBC != iBookingClassList.end(); ++itBC) {
  //       BookingClass* lBC_ptr = *itBC;
  //       assert(lBC_ptr != NULL);
  //       lBCList.push_back(lBC_ptr);
  //     }
  //     insertionSucceeded = true;
  //   }

  //   return insertionSucceeded;
  // }

  // ////////////////////////////////////////////////////////////////////
  // const bool SimpleNestingStructure::
  // alreadyInNestingStructure(const ClassCode_T& iClassCode) const {
  //   bool isAlreadyInTheMap = false;
  //   NestingNodeMap_T::const_iterator itMap = _nestingNodeMap.begin();
  //   for(; itMap != _nestingNodeMap.end(); ++itMap) {
  //     const NestingNode_T& lNestingNode = *itMap;
  //     const BookingClassList_T& lBCList = lNestingNode.second;
  //     BookingClassList_T::const_iterator itBC = lBCList.begin();
  //     for (;itBC != lBCList.end(); ++itBC) {
  //       BookingClass* lBC_ptr = *itBC;
  //       assert(lBC_ptr != NULL);
  //       const BookingClassKey& lBookingClassKey = lBC_ptr->getKey();
  //       const ClassCode_T& lClassCode = lBookingClassKey.getClassCode();
  //       if (lClassCode == iClassCode) {
  //         isAlreadyInTheMap = true;
  //         return isAlreadyInTheMap;
  //       }
  //     }
  //   }
  //   return isAlreadyInTheMap;
  // }
    
  // ////////////////////////////////////////////////////////////////////
  std::string SimpleNestingStructure::toString () const {
    std::ostringstream oStr;
    oStr << describeKey();
 
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const NestingNodeList_T& SimpleNestingStructure::getNestingNodeList() const {
    return BomManager::getList<NestingNode> (*this);
  }
  
}
