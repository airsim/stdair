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
  extern const FRAT5Curve_T FRAT5_CURVE_D;

  /** Disutility curves for fare families. */
  extern const FFDisutilityCurve_T FF_DISUTILITY_CURVE_A;
  extern const FFDisutilityCurve_T FF_DISUTILITY_CURVE_B;
  extern const FFDisutilityCurve_T FF_DISUTILITY_CURVE_C;
  extern const FFDisutilityCurve_T FF_DISUTILITY_CURVE_D;
  extern const FFDisutilityCurve_T FF_DISUTILITY_CURVE_E;
  extern const FFDisutilityCurve_T FF_DISUTILITY_CURVE_F;

  /** FRAT5 curves. */
  struct DefaultMap {
    static FRAT5Curve_T createFRAT5CurveA();
    static FRAT5Curve_T createFRAT5CurveB();
    static FRAT5Curve_T createFRAT5CurveC();
    static FRAT5Curve_T createFRAT5CurveD();
    static FFDisutilityCurve_T createFFDisutilityCurveA();
    static FFDisutilityCurve_T createFFDisutilityCurveB();
    static FFDisutilityCurve_T createFFDisutilityCurveC();
    static FFDisutilityCurve_T createFFDisutilityCurveD();
    static FFDisutilityCurve_T createFFDisutilityCurveE();
    static FFDisutilityCurve_T createFFDisutilityCurveF();
  };
}
#endif // __STDAIR_BAS_BASCONST_SELLUPCURVES_HPP
