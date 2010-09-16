// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_Period_BOM.hpp>
#include <stdair/bom/DoWStruct.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  DoWStruct_T::DoWStruct_T () {
    for (unsigned short i = 0; i < 7; ++i) {
      _dowList.push_back (false);
    }
  }
  
  // ////////////////////////////////////////////////////////////////////
  DoWStruct_T::DoWStruct_T (const std::string& iDowString) {
    const unsigned short lDowStringSize = iDowString.size();
    assert (lDowStringSize == 7);
      
    _dowList.reserve (lDowStringSize);
    for (std::string::const_iterator itChar = iDowString.begin();
         itChar != iDowString.end(); ++itChar) {
      const bool isDoWSet = (*itChar == '1')?true:false;
      _dowList.push_back (isDoWSet);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  DoWStruct_T::DoWStruct_T (const DoWStruct_T& iDowStruct) :
    _dowList (iDowStruct._dowList) {
      
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string DoWStruct_T::describeShort() const {
    std::ostringstream ostr;
    short i = 0;
    for (BooleanList_T::const_iterator itDoW = _dowList.begin();
         itDoW != _dowList.end(); ++itDoW, ++i) {
      const char lDoW = (*itDoW == true)?'1':'0';
      ostr << lDoW;
    }
    return ostr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string DoWStruct_T::describe() const {
    std::ostringstream ostr;
    short i = 0;
    for (BooleanList_T::const_iterator itDoW = _dowList.begin();
         itDoW != _dowList.end(); ++itDoW, ++i) {
      const bool lDoW = *itDoW;
      if (lDoW == true) {
        ostr << DOW_STR[i] << ".";
      }
    }
    return ostr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  bool DoWStruct_T::getDayOfWeek (const unsigned short i) const {
    return _dowList.at (i);
  }
      
  // ////////////////////////////////////////////////////////////////////
  bool DoWStruct_T::getStandardDayOfWeek (const unsigned short i) const {
    unsigned short iStd = i;
    if (iStd == 0) {
      iStd = 6;
    } else {
      --iStd;
    }
    return _dowList.at (iStd);
  }

  // ////////////////////////////////////////////////////////////////////
  void DoWStruct_T::setDayOfWeek (const unsigned short i, const bool iBool) {
    assert (i < 7);
    _dowList.at (i) = iBool;
  }

  // ////////////////////////////////////////////////////////////////////
  DoWStruct_T DoWStruct_T::shift (const long& iNbOfDays) const {
    DoWStruct_T oDoW (DEFAULT_DOW_STRING);

    for (short i = 0; i < 7; ++i) {
      const bool lDoWBool = _dowList.at (i);
      short lIndex = (i + iNbOfDays) % 7;
      if (lIndex < 0) {
        lIndex += 7;
      }
      oDoW.setDayOfWeek (lIndex, lDoWBool);
    }
    
    return oDoW;
  }

  // ////////////////////////////////////////////////////////////////////
  DoWStruct_T DoWStruct_T::intersection (const DoWStruct_T& iDoW) const {
    DoWStruct_T oDoW (DEFAULT_DOW_STRING);
    for (unsigned short i = 0; i < 7; ++i) {
      if (getDayOfWeek(i) && iDoW.getDayOfWeek(i)) {
        oDoW.setDayOfWeek (i, true);
      } else {
        oDoW.setDayOfWeek (i, false);
      }
    }
    return oDoW;
  }

  // ////////////////////////////////////////////////////////////////////
  const bool DoWStruct_T::isValid () const {
    for (unsigned short i = 0; i < 7; ++i) {
      if (getDayOfWeek(i)) {
        return true;
      }
    }
    return false;
  }

}
