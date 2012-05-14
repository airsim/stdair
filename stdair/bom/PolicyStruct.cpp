// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <cassert>
#include <iomanip>
#include <iostream>
//STDAIR
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/PolicyStruct.hpp>

namespace stdair {
    
  // ////////////////////////////////////////////////////////////////////
  PolicyStruct::PolicyStruct () : 
    _demand (0.0), _yield (0.0), _stdDev(0.0) {
    assert(false);
  }

  // ////////////////////////////////////////////////////////////////////
  PolicyStruct::PolicyStruct (const BookingClassList_T& iBookingClassList, 
                  const NbOfBookings_T& iDemand,
                  const Yield_T& iYield,
                  const StdDevValue_T& iStdDev) :
    _bookingClassList(iBookingClassList), _demand(iDemand),
    _yield (iYield), _stdDev(iStdDev) {
  }
    
  // ////////////////////////////////////////////////////////////////////
  PolicyStruct::PolicyStruct 
  (const PolicyStruct& iPolicyStruct) :
    _bookingClassList(iPolicyStruct.getBookingClasses()), 
    _demand(iPolicyStruct.getDemand()),
    _yield (iPolicyStruct.getYield()),
    _stdDev(iPolicyStruct.getStdDev()) {
  }
    
  // ////////////////////////////////////////////////////////////////////
  PolicyStruct::~PolicyStruct() {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string PolicyStruct::describe() const {
    std::ostringstream ostr;
    toStream(ostr);
     
    return ostr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  void PolicyStruct::toStream (std::ostream& ioOut) const {
    const Revenue_T& lRevenue = getRevenue();
    BookingClassList_T::const_iterator itBC = _bookingClassList.begin();
    if (itBC != _bookingClassList.end()) {
      const BookingClass* lBookingClass = *itBC;
      assert(lBookingClass != NULL);
      ioOut << lBookingClass->describeKey();
    }
    itBC++;
    for (; itBC != _bookingClassList.end(); itBC++) {
      const BookingClass* lBookingClass = *itBC;
      assert(lBookingClass != NULL);
      ioOut << ", ";
      ioOut << lBookingClass->describeKey();
    }
    ioOut << std::fixed << std::setprecision (2)
          << "; " << _demand 
          << "; " << _yield 
          << "; " << lRevenue 
          << "; " << _stdDev << std::endl;
  }
    
  // ////////////////////////////////////////////////////////////////////
  void PolicyStruct::display () const {
    toStream (std::cout);
  }
}
