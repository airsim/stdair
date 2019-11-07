#ifndef __STDAIR_BAS_PROGRESSSTATUS_HPP
#define __STDAIR_BAS_PROGRESSSTATUS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/BasConst_Event.hpp>
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  /**
   * Structure holding the details of a progress status.
   *
   * The progress status is given by the ratio between the "current"
   * and the "expected" (or "actual") numbers. For instance, when the
   * expected/actual number is 1000 and the current number is 200,
   * then the progress status is 20% (= 200 / 1000).
   */
  struct ProgressStatus : public StructAbstract {
  public:
    // //////////////// Getters /////////////////
    /** Get the current number. */
    const Count_T& count() const {
      return _currentNb;
    }

    /** Get the current number. */
    const Count_T& getCurrentNb() const {
      return _currentNb;
    }

    /** Get the expected number. */
    const Count_T& getExpectedNb() const {
      return _expectedNb;
    }

    /** Get the actual number. */
    const Count_T& getActualNb() const {
      return _actualNb;
    }

    /** Get the progress as a percentage. */
    const ProgressPercentage_T progress() const {
      if (_actualNb == 0) {
        return 0;
      } 
      Percentage_T lPercentage = 
	(static_cast<Percentage_T> (_currentNb)
	 / static_cast<Percentage_T> (_actualNb));
      lPercentage *= MAXIMUM_PROGRESS_STATUS;
      return lPercentage;
    }
    

    // //////////////// Setters /////////////////
    /** Set the current number. */
    void setCurrentNb (const Count_T& iCurrentNb) {
      _currentNb = iCurrentNb;
    }

    /** Set the expected number. */
    void setExpectedNb (const Count_T& iExpectedNb) {
      _expectedNb = iExpectedNb;
    } 

    /** Set the actual number. */
    void setActualNb (const Count_T& iActualNb) {
      _actualNb = iActualNb;  
    }

    /** Reset the current number (to 0). */
    void reset();

    /** Increment the current number. */
    Count_T operator+= (Count_T iIncrement) {
      _currentNb += iIncrement;
      return _currentNb;
    }

    /** Increment the current number. */
    Count_T operator++() {
      ++_currentNb;
      return _currentNb;
    }


  public:
    // //////////////// Display Support Methods /////////////////
    /** Give a description of the structure (e.g., "1 {99, 100}"). */
    const std::string describe() const;   

    /** Give a description of the structure (e.g., "1% (1/ 100)"). */
    const std::string toString() const;

    
  public:
    /**
     * Constructor.
     *
     * @param const Count_T& The current number.
     * @param const Count_T& The expected number.
     * @param const Count_T& The actual number.
     */
    ProgressStatus (const Count_T& iCurrentNb, const Count_T& iExpectedNb,
                    const Count_T& iActualNb);

    /**
     * Constructor.
     *
     * As no current number is given, it is set to 0.
     *
     * @param const Count_T& The expected number.
     * @param const Count_T& The actual number.
     */
    ProgressStatus (const Count_T& iExpectedNb, const Count_T& iActualNb);

    /**
     * Constructor.
     *
     * As no expected number is given, it is assumed to be equal to
     * the actual one. The current number is set to 0.
     *
     * @param const Count_T& The actual number.
     */
    ProgressStatus (const Count_T& iActualNb);

    /**
     * Constructor.
     *
     * All the numbers are set to 0.
     */
    ProgressStatus();

    /**
     * Copy Constructor.
     */
    ProgressStatus (const ProgressStatus&);
    
  private:
    // //////////////// Attributes /////////////////
    /** Current number. */
    Count_T _currentNb;

    /** Expected number. */
    Count_T _expectedNb;

    /** Actual number. */
    Count_T _actualNb;
  };

}
#endif // __STDAIR_BAS_PROGRESSSTATUS_HPP
