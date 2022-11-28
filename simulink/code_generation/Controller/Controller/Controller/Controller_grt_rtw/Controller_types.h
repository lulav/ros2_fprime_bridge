/*
 * Controller_types.h
 *
 * Code generation for model "Controller".
 *
 * Model version              : 1.45
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C++ source code generated on : Mon Nov 28 09:32:43 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Controller_types_h_
#define RTW_HEADER_Controller_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_B_Dynamics_
#define DEFINED_TYPEDEF_FOR_B_Dynamics_

struct B_Dynamics
{
  real_T r;
  real_T v;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_B_Controller_
#define DEFINED_TYPEDEF_FOR_B_Controller_

struct B_Controller
{
  real_T u;
};

#endif

/* Parameters (default storage) */
typedef struct P_Controller_T_ P_Controller_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Controller_T RT_MODEL_Controller_T;

#endif                                 /* RTW_HEADER_Controller_types_h_ */
