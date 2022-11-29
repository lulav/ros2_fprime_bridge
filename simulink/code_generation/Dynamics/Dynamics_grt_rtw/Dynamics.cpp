/*
 * Dynamics.cpp
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

#include "Dynamics.h"
#include "Dynamics_types.h"
#include "Dynamics_private.h"

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void Dynamics::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3]{
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3]{
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE3_IntgData *id { static_cast<ODE3_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T hB[3];
  int_T i;
  int_T nXc { 2 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Dynamics_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  Dynamics_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  Dynamics_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Dynamics::step()
{
  if (rtmIsMajorTimeStep((&Dynamics_M))) {
    /* set solver stop time */
    if (!((&Dynamics_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&Dynamics_M)->solverInfo, (((&Dynamics_M)
        ->Timing.clockTickH0 + 1) * (&Dynamics_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&Dynamics_M)->solverInfo, (((&Dynamics_M)
        ->Timing.clockTick0 + 1) * (&Dynamics_M)->Timing.stepSize0 +
        (&Dynamics_M)->Timing.clockTickH0 * (&Dynamics_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Dynamics_M))) {
    (&Dynamics_M)->Timing.t[0] = rtsiGetT(&(&Dynamics_M)->solverInfo);
  }

  if (rtmIsMajorTimeStep((&Dynamics_M))) {
    /* Constant: '<Root>/m' */
    Dynamics_B.m = p_bus;
  }

  /* Integrator: '<Root>/integrator_v' */
  if (Dynamics_DW.integrator_v_IWORK != 0) {
    Dynamics_X.integrator_v_CSTATE = Dynamics_B.m.v0;
  }

  /* Integrator: '<Root>/integrator_v' */
  Dynamics_B.v = Dynamics_X.integrator_v_CSTATE;

  /* Integrator: '<Root>/integrator_r' */
  if (Dynamics_DW.integrator_r_IWORK != 0) {
    Dynamics_X.integrator_r_CSTATE = Dynamics_B.m.r0;
  }

  /* Outport: '<Root>/state' incorporates:
   *  BusAssignment: '<Root>/Bus Assignment'
   *  Integrator: '<Root>/integrator_r'
   */
  Dynamics_Y.state.r = Dynamics_X.integrator_r_CSTATE;
  Dynamics_Y.state.v = Dynamics_B.v;

  /* Product: '<Root>/Divide' incorporates:
   *  DotProduct: '<Root>/Dot Product'
   *  DotProduct: '<Root>/Dot Product1'
   *  Inport: '<Root>/u'
   *  Integrator: '<Root>/integrator_r'
   *  Sum: '<Root>/Add'
   */
  Dynamics_B.Divide = ((Dynamics_U.u.u - Dynamics_B.m.c * Dynamics_B.v) -
                       Dynamics_X.integrator_r_CSTATE * Dynamics_B.m.k) /
    Dynamics_B.m.m;
  if (rtmIsMajorTimeStep((&Dynamics_M))) {
    /* Update for Integrator: '<Root>/integrator_v' */
    Dynamics_DW.integrator_v_IWORK = 0;

    /* Update for Integrator: '<Root>/integrator_r' */
    Dynamics_DW.integrator_r_IWORK = 0;
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&Dynamics_M))) {
    rt_ertODEUpdateContinuousStates(&(&Dynamics_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&Dynamics_M)->Timing.clockTick0)) {
      ++(&Dynamics_M)->Timing.clockTickH0;
    }

    (&Dynamics_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&Dynamics_M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&Dynamics_M)->Timing.clockTick1++;
      if (!(&Dynamics_M)->Timing.clockTick1) {
        (&Dynamics_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Dynamics::Dynamics_derivatives()
{
  XDot_Dynamics_T *_rtXdot;
  _rtXdot = ((XDot_Dynamics_T *) (&Dynamics_M)->derivs);

  /* Derivatives for Integrator: '<Root>/integrator_v' */
  _rtXdot->integrator_v_CSTATE = Dynamics_B.Divide;

  /* Derivatives for Integrator: '<Root>/integrator_r' */
  _rtXdot->integrator_r_CSTATE = Dynamics_B.v;
}

/* Model initialize function */
void Dynamics::initialize()
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Dynamics_M)->solverInfo, &(&Dynamics_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&Dynamics_M)->solverInfo, &rtmGetTPtr((&Dynamics_M)));
    rtsiSetStepSizePtr(&(&Dynamics_M)->solverInfo, &(&Dynamics_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&Dynamics_M)->solverInfo, &(&Dynamics_M)->derivs);
    rtsiSetContStatesPtr(&(&Dynamics_M)->solverInfo, (real_T **) &(&Dynamics_M
                         )->contStates);
    rtsiSetNumContStatesPtr(&(&Dynamics_M)->solverInfo, &(&Dynamics_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Dynamics_M)->solverInfo, &(&Dynamics_M)
      ->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Dynamics_M)->solverInfo, &(&Dynamics_M)
      ->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Dynamics_M)->solverInfo, &(&Dynamics_M
      )->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&Dynamics_M)->solverInfo, (&rtmGetErrorStatus
      ((&Dynamics_M))));
    rtsiSetRTModelPtr(&(&Dynamics_M)->solverInfo, (&Dynamics_M));
  }

  rtsiSetSimTimeStep(&(&Dynamics_M)->solverInfo, MAJOR_TIME_STEP);
  (&Dynamics_M)->intgData.y = (&Dynamics_M)->odeY;
  (&Dynamics_M)->intgData.f[0] = (&Dynamics_M)->odeF[0];
  (&Dynamics_M)->intgData.f[1] = (&Dynamics_M)->odeF[1];
  (&Dynamics_M)->intgData.f[2] = (&Dynamics_M)->odeF[2];
  (&Dynamics_M)->contStates = ((X_Dynamics_T *) &Dynamics_X);
  rtsiSetSolverData(&(&Dynamics_M)->solverInfo, static_cast<void *>
                    (&(&Dynamics_M)->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&Dynamics_M)->solverInfo, false);
  rtsiSetSolverName(&(&Dynamics_M)->solverInfo,"ode3");
  rtmSetTPtr((&Dynamics_M), &(&Dynamics_M)->Timing.tArray[0]);
  (&Dynamics_M)->Timing.stepSize0 = 0.01;
  rtmSetFirstInitCond((&Dynamics_M), 1);

  /* Start for Constant: '<Root>/m' */
  Dynamics_B.m = p_bus;

  /* InitializeConditions for Integrator: '<Root>/integrator_v' incorporates:
   *  Integrator: '<Root>/integrator_r'
   */
  if (rtmIsFirstInitCond((&Dynamics_M))) {
    Dynamics_X.integrator_v_CSTATE = 0.0;
    Dynamics_X.integrator_r_CSTATE = 0.0;
  }

  Dynamics_DW.integrator_v_IWORK = 1;

  /* End of InitializeConditions for Integrator: '<Root>/integrator_v' */

  /* InitializeConditions for Integrator: '<Root>/integrator_r' */
  Dynamics_DW.integrator_r_IWORK = 1;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond((&Dynamics_M))) {
    rtmSetFirstInitCond((&Dynamics_M), 0);
  }
}

/* Model terminate function */
void Dynamics::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Dynamics::Dynamics() :
  Dynamics_U(),
  Dynamics_Y(),
  Dynamics_B(),
  Dynamics_DW(),
  Dynamics_X(),
  Dynamics_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
Dynamics::~Dynamics()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Dynamics_T * Dynamics::getRTM()
{
  return (&Dynamics_M);
}
