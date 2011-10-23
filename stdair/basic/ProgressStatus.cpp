// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/BasConst_Event.hpp>
#include <stdair/basic/ProgressStatus.hpp>

namespace stdair {
  
  // //////////////////////////////////////////////////////////////////////
  ProgressStatus::ProgressStatus (const Count_T& iCurrentNb,
                                  const Count_T& iExpectedNb,
                                  const Count_T& iActualNb)
    : _currentNb (iCurrentNb),
      _expectedNb (iExpectedNb), _actualNb (iActualNb) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  ProgressStatus::ProgressStatus (const Count_T& iExpectedNb,
                                  const Count_T& iActualNb)
    : _currentNb (DEFAULT_PROGRESS_STATUS),
      _expectedNb (iExpectedNb), _actualNb (iActualNb) {
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressStatus::ProgressStatus (const Count_T& iActualNb)
    : _currentNb (DEFAULT_PROGRESS_STATUS),
      _expectedNb (iActualNb), _actualNb (iActualNb) {
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressStatus::ProgressStatus()
    : _currentNb (DEFAULT_PROGRESS_STATUS),
      _expectedNb (DEFAULT_PROGRESS_STATUS),
      _actualNb (DEFAULT_PROGRESS_STATUS) {
  }

  // //////////////////////////////////////////////////////////////////////
  ProgressStatus::ProgressStatus (const ProgressStatus& iProgressStatus)
    : _currentNb (iProgressStatus._currentNb),
      _expectedNb (iProgressStatus._expectedNb),
      _actualNb (iProgressStatus._actualNb) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void ProgressStatus::reset() {
    _currentNb = DEFAULT_PROGRESS_STATUS;
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string ProgressStatus::describe() const {
    std::ostringstream oStr;
    oStr << _currentNb << " / {" << _expectedNb << ", " << _actualNb << "}";
    return oStr.str();
  }
  
}
