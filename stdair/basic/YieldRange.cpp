// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <limits>
#include <sstream>
// StdAir
#include <stdair/basic/YieldRange.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange() :
    _upperYield (std::numeric_limits<Yield_T>::max()),
    _averageYield (std::numeric_limits<Yield_T>::max()),
    _lowerYield (std::numeric_limits<Yield_T>::min()) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange (const YieldRange& iYieldRange) :
    _upperYield (iYieldRange.getUpperYield()),
    _averageYield (iYieldRange.getAverageYield()),
    _lowerYield (std::numeric_limits<Yield_T>::min()) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange (const Yield_T iUpperYield) :
    _upperYield (iUpperYield), _averageYield (iUpperYield),
    _lowerYield (iUpperYield) {
  }

  // ////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange (const Yield_T iUpperYield,
                                const Yield_T iAverageYield) :
    _upperYield (iUpperYield), _averageYield (iAverageYield),
    _lowerYield (std::numeric_limits<Yield_T>::min()) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  YieldRange::YieldRange (const Yield_T iUpperYield,
                                const Yield_T iAverageYield,
                                const Yield_T iLowerYield) :
    _upperYield (iUpperYield), _averageYield (iAverageYield),
    _lowerYield (iLowerYield) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  YieldRange::~YieldRange() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void YieldRange::toStream (std::ostream& ioOut) const {
    ioOut << _averageYield << "([" << _lowerYield << ", "
          << _upperYield << "])";
  }
  
  // ////////////////////////////////////////////////////////////////////
  void YieldRange::fromStream (std::istream& ioIn) {
  } 
  
  // ////////////////////////////////////////////////////////////////////
  const std::string YieldRange::describe() const {
    std::ostringstream oStr;
    
    return oStr.str();
  }
  
}
