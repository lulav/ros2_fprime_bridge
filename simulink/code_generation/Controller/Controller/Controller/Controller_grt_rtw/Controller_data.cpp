/*
 * Controller_data.cpp
 *
 * Code generation for model "Controller".
 *
 * Model version              : 1.47
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C++ source code generated on : Mon Nov 28 10:12:43 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"

/* Block parameters (default storage) */
P_Controller_T Controller::Controller_P{
  /* Computed Parameter: Constant1_Value
   * Referenced by: '<Root>/Constant1'
   */
  {
    0.0                                /* u */
  },

  /* Expression: params.r_req.Value
   * Referenced by: '<Root>/r_req'
   */
  0.0,

  /* Expression: params.kp.Value
   * Referenced by: '<Root>/kp'
   */
  8.0,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator'
   */
  0.0,

  /* Expression: params.ki.Value
   * Referenced by: '<Root>/ki'
   */
  1.0,

  /* Expression: params.kd.Value
   * Referenced by: '<Root>/kd'
   */
  4.0
};
