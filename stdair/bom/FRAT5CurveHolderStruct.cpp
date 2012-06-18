// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/service/Logger.hpp>
#include <stdair/bom/FRAT5CurveHolderStruct.hpp>

namespace stdair {
  
  // ////////////////////////////////////////////////////////////////////
  FRAT5CurveHolderStruct::FRAT5CurveHolderStruct() {
  }
    
  // ////////////////////////////////////////////////////////////////////
  FRAT5CurveHolderStruct::
  FRAT5CurveHolderStruct (const FRAT5CurveHolderStruct& iHolder)
    : _frat5CurveHolder (iHolder._frat5CurveHolder) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  FRAT5CurveHolderStruct::~FRAT5CurveHolderStruct() {
  }

  // ////////////////////////////////////////////////////////////////////
  const FRAT5Curve_T& FRAT5CurveHolderStruct::
  getFRAT5Curve (const std::string& iKey) const {
    FRAT5CurveHolder_T::const_iterator itCurve = _frat5CurveHolder.find (iKey);
    if (itCurve == _frat5CurveHolder.end()) {
      STDAIR_LOG_DEBUG ("Cannot find the FRAT5 curve correponding to the "
                        << "given key: " << iKey);
      assert (false);
    }

    return itCurve->second;
  }

  // ////////////////////////////////////////////////////////////////////
  void FRAT5CurveHolderStruct::
  addCurve (const std::string& iKey, const FRAT5Curve_T& iCurve) {
    bool insert = _frat5CurveHolder.insert (FRAT5CurveHolder_T::value_type(iKey, iCurve)).second;
    if (insert == false) {
      STDAIR_LOG_DEBUG ("Cannot add the FRAT5 curve correponding to the "
                        << "given key: " << iKey
                        << ", the key may already exist.");
      assert (false);
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  void FRAT5CurveHolderStruct::toStream (std::ostream& ioOut) const {
    ioOut << describe();
  }

  // ////////////////////////////////////////////////////////////////////
  void FRAT5CurveHolderStruct::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  const std::string FRAT5CurveHolderStruct::describe() const {
    std::ostringstream oStr;
    for (FRAT5CurveHolder_T::const_iterator itCurve = _frat5CurveHolder.begin();
         itCurve != _frat5CurveHolder.end(); ++itCurve) {
      const std::string& lKey = itCurve->first;
      const FRAT5Curve_T& lCurve = itCurve->second;
      oStr << lKey << "; ";
      for (FRAT5Curve_T::const_reverse_iterator itFRAT5 = lCurve.rbegin();
           itFRAT5 != lCurve.rend(); ++itFRAT5) {
        const DTD_T& lDTD = itFRAT5->first;
        const double& lFRAT5 = itFRAT5->second;
        oStr << lDTD << ":" << lFRAT5 << ";";
      }
      oStr << std::endl;
    }
    return oStr.str();
  }

}
