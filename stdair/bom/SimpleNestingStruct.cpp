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
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/SimpleNestingStruct.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {
    
  // ////////////////////////////////////////////////////////////////////
  SimpleNestingStruct::SimpleNestingStruct () : 
    _nestingNodeMap() {
  }

  // ////////////////////////////////////////////////////////////////////
  SimpleNestingStruct::
  SimpleNestingStruct (const NestingNodeMap_T& iNestingNodeMap) :
    _nestingNodeMap(iNestingNodeMap) {
  }
    
  // ////////////////////////////////////////////////////////////////////
  SimpleNestingStruct::SimpleNestingStruct 
  (const SimpleNestingStruct& iSimpleNestingStruct) :
    _nestingNodeMap(iSimpleNestingStruct.getNestingNodeMap()) {
  }
    
  // ////////////////////////////////////////////////////////////////////
  SimpleNestingStruct::~SimpleNestingStruct() {
  }
  // ////////////////////////////////////////////////////////////////////
  const bool SimpleNestingStruct::insertBookingClassList(const Yield_T& iYield,
                                    const BookingClassList_T& iBookingClassList) {
    const bool isBookinClassListEmpty = iBookingClassList.empty();
    if (isBookinClassListEmpty == true) {
      std::ostringstream ostr;
      ostr << "The booking class list is empty and it should not be. "
        "No insertion done in the nesting structure (";
      toStream(ostr);
      ostr << ").";
      STDAIR_LOG_DEBUG(ostr.str());
      throw BookingClassListEmptyInNestingStructException(ostr.str());
    }
    assert(isBookinClassListEmpty == false);
    NestingNodeMap_T::iterator itNestingNode = _nestingNodeMap.find (iYield);
    bool insertionSucceeded = false;
    // Search a node with the same yield and add the
    // booking classes to the booking class list of the node.
    // If there is not a node with the same yield, create it.
    if (itNestingNode == _nestingNodeMap.end()) {
      NestingNode_T lNode (iYield, iBookingClassList);
      insertionSucceeded = _nestingNodeMap.insert(lNode).second;
    } else {
      NestingNode_T& lNode = *itNestingNode;
      const Yield_T& lYield = lNode.first;
      assert(lYield == iYield);
      BookingClassList_T& lBCList = lNode.second;
      for (BookingClassList_T::const_iterator itBC = iBookingClassList.begin(); 
           itBC != iBookingClassList.end(); ++itBC) {
        BookingClass* lBC_ptr = *itBC;
        assert(lBC_ptr != NULL);
        lBCList.push_back(lBC_ptr);
      }
      insertionSucceeded = true;
    }

    return insertionSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  const bool SimpleNestingStruct::
  alreadyInNestingStruct(const ClassCode_T& iClassCode) const {
    bool isAlreadyInTheMap = false;
    NestingNodeMap_T::const_iterator itMap = _nestingNodeMap.begin();
    for(; itMap != _nestingNodeMap.end(); ++itMap) {
      const NestingNode_T& lNestingNode = *itMap;
      const BookingClassList_T& lBCList = lNestingNode.second;
      BookingClassList_T::const_iterator itBC = lBCList.begin();
      for (;itBC != lBCList.end(); ++itBC) {
        BookingClass* lBC_ptr = *itBC;
        assert(lBC_ptr != NULL);
        const BookingClassKey& lBookingClassKey = lBC_ptr->getKey();
        const ClassCode_T& lClassCode = lBookingClassKey.getClassCode();
        if (lClassCode == iClassCode) {
          isAlreadyInTheMap = true;
          return isAlreadyInTheMap;
        }
      }
    }
    return isAlreadyInTheMap;
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string SimpleNestingStruct::describe() const {
    std::ostringstream ostr;
    ostr << "Struct of nesting node map." << std::endl;
    toStream(ostr);
    return ostr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  void SimpleNestingStruct::toStream (std::ostream& ioOut) const {
    NestingNodeMap_T::const_iterator itMap = _nestingNodeMap.begin();
    for(; itMap != _nestingNodeMap.end(); ++itMap) {
      const NestingNode_T& lNestingNode = *itMap;
      const Yield_T& lYield = lNestingNode.first;
      const BookingClassList_T& lBCList = lNestingNode.second;
      ioOut << lYield << ": ";
      BookingClassList_T::const_iterator itBC = lBCList.begin();
      for(unsigned int idx = 0; itBC != lBCList.end(); ++itBC, ++idx) {
        if (idx != 0) {
          ioOut << ", ";
        }
        ioOut << (*itBC)->describeKey();
      }
    }
  }
    
  // ////////////////////////////////////////////////////////////////////
  void SimpleNestingStruct::display () const {
    toStream (std::cout);
  }
}
