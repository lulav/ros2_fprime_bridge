/*
 * Dynamics_types.h
 *
 * Code generation for model "Dynamics".
 *
 * Model version              : 1.52
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C++ source code generated on : Tue Nov 29 15:05:06 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Dynamics_types_h_
#define RTW_HEADER_Dynamics_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_B_Controller_
#define DEFINED_TYPEDEF_FOR_B_Controller_

struct B_Controller
{
  real_T u;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_B_Dynamics_
#define DEFINED_TYPEDEF_FOR_B_Dynamics_

struct B_Dynamics
{
  real_T r;
  real_T v;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_P_BUS_TYPE_
#define DEFINED_TYPEDEF_FOR_P_BUS_TYPE_

struct P_BUS_TYPE
{
  real_T m;
  real_T k;
  real_T c;
  real_T r0;
  real_T v0;
  real_T kp;
  real_T ki;
  real_T kd;
  real_T r_req;
};

#endif

/* Parameters (default storage) */
typedef struct P_Dynamics_T_ P_Dynamics_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Dynamics_T RT_MODEL_Dynamics_T;

#endif                                 /* RTW_HEADER_Dynamics_types_h_ */
