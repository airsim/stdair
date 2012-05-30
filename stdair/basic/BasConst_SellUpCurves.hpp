#ifndef __STDAIR_BAS_BASCONST_SELLUPCURVES_HPP
#define __STDAIR_BAS_BASCONST_SELLUPCURVES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/stdair_types.hpp>

namespace stdair {

  /** FRAT5 curves for forecasting and optimisation. */
  extern const FRAT5Curve_T FRAT5_CURVE_A;
  extern const FRAT5Curve_T FRAT5_CURVE_B;
  extern const FRAT5Curve_T FRAT5_CURVE_C;

  /** Disutility curves for fare families. */
  extern const FFDisutilityCurve_T FF_DISUTILITY_CURVE_A;
  extern const FFDisutilityCurve_T FF_DISUTILITY_CURVE_B;

  /** FRAT5 curves. */
  struct DefaultMap {
    static FRAT5Curve_T createFRAT5CurveA();
    static FRAT5Curve_T createFRAT5CurveB();
    static FRAT5Curve_T createFRAT5CurveC();
    static FFDisutilityCurve_T createFFDisutilityCurveA();
    static FFDisutilityCurve_T createFFDisutilityCurveB();
  };
}
#endif // __STDAIR_BAS_BASCONST_SELLUPCURVES_HPP
