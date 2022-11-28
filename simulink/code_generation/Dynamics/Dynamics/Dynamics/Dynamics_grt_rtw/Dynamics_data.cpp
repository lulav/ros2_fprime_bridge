/*
 * Dynamics_data.cpp
 *
 * Code generation for model "Dynamics".
 *
 * Model version              : 1.47
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C++ source code generated on : Mon Nov 28 10:10:28 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Dynamics.h"

/* Block parameters (default storage) */
P_Dynamics_T Dynamics::Dynamics_P{
  /* Computed Parameter: Constant2_Value
   * Referenced by: '<Root>/Constant2'
   */
  {
    0.0,                               /* r */
    0.0                                /* v */
  },

  /* Expression: params.v0.Value
   * Referenced by: '<Root>/v0'
   */
  0.0,

  /* Expression: params.r0.Value
   * Referenced by: '<Root>/r0'
   */
  -1.0,

  /* Expression: params.c.Value
   * Referenced by: '<Root>/c'
   */
  0.3,

  /* Expression: params.k.Value
   * Referenced by: '<Root>/k'
   */
  2.5,

  /* Expression: params.m.Value
   * Referenced by: '<Root>/m'
   */
  1.0
};
