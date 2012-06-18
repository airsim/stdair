// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/service/Logger.hpp>
#include <stdair/bom/FFDisutilityCurveHolderStruct.hpp>

namespace stdair {
  
  // ////////////////////////////////////////////////////////////////////
  FFDisutilityCurveHolderStruct::FFDisutilityCurveHolderStruct() {
  }
    
  // ////////////////////////////////////////////////////////////////////
  FFDisutilityCurveHolderStruct::
  FFDisutilityCurveHolderStruct (const FFDisutilityCurveHolderStruct& iHolder)
    : _disutilityCurveHolder (iHolder._disutilityCurveHolder) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  FFDisutilityCurveHolderStruct::~FFDisutilityCurveHolderStruct() {
  }

  // ////////////////////////////////////////////////////////////////////
  const FFDisutilityCurve_T& FFDisutilityCurveHolderStruct::
  getFFDisutilityCurve (const std::string& iKey) const {
    FFDisutilityCurveHolder_T::const_iterator itCurve = _disutilityCurveHolder.find (iKey);
    if (itCurve == _disutilityCurveHolder.end()) {
      STDAIR_LOG_DEBUG ("Cannot find the FFDisutility curve correponding to the "
                        << "given key: " << iKey);
      assert (false);
    }

    return itCurve->second;
  }

  // ////////////////////////////////////////////////////////////////////
  void FFDisutilityCurveHolderStruct::
  addCurve (const std::string& iKey, const FFDisutilityCurve_T& iCurve) {
    bool insert = _disutilityCurveHolder.insert (FFDisutilityCurveHolder_T::value_type(iKey, iCurve)).second;
    if (insert == false) {
      STDAIR_LOG_DEBUG ("Cannot add the FFDisutility curve correponding to the "
                        << "given key: " << iKey
                        << ", the key may already exist.");
      assert (false);
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void FFDisutilityCurveHolderStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void FFDisutilityCurveHolderStruct::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string FFDisutilityCurveHolderStruct::describe() const {
    std::ostringstream oStr;
    for (FFDisutilityCurveHolder_T::const_iterator itCurve = _disutilityCurveHolder.begin();
         itCurve != _disutilityCurveHolder.end(); ++itCurve) {
      const std::string& lKey = itCurve->first;
      const FFDisutilityCurve_T& lCurve = itCurve->second;
      oStr << lKey << "; ";
      for (FFDisutilityCurve_T::const_reverse_iterator itFFDisutility =
             lCurve.rbegin();itFFDisutility != lCurve.rend(); ++itFFDisutility){
        const DTD_T& lDTD = itFFDisutility->first;
        const double& lFFDisutility = itFFDisutility->second;
        oStr << lDTD << ":" << lFFDisutility << ";";
      }
      oStr << std::endl;
    }
    return oStr.str();
  }

}
