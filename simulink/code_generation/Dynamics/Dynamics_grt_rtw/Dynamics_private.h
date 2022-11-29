/*
 * Dynamics_private.h
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

#ifndef RTW_HEADER_Dynamics_private_h_
#define RTW_HEADER_Dynamics_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "Dynamics_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetFirstInitCond
#define rtmSetFirstInitCond(rtm, val)  ((rtm)->Timing.firstInitCondFlag = (val))
#endif

#ifndef rtmIsFirstInitCond
#define rtmIsFirstInitCond(rtm)        ((rtm)->Timing.firstInitCondFlag)
#endif

#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

/* Imported (extern) block parameters */
extern P_BUS_TYPE p_bus;               /* Variable: p_bus
                                        * Referenced by: '<Root>/m'
                                        */

/* private model entry point functions */
extern void Dynamics_derivatives();

#endif                                 /* RTW_HEADER_Dynamics_private_h_ */
