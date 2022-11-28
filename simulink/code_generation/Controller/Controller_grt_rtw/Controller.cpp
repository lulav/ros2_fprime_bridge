/*
 * Controller.cpp
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
#include "rtwtypes.h"
#include "Controller_capi.h"
#include "Controller_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void Controller::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  int_T nXc { 1 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Controller_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  Controller_derivatives();

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
  Controller_derivatives();

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
void Controller::step()
{
  if (rtmIsMajorTimeStep((&Controller_M))) {
    /* set solver stop time */
    if (!((&Controller_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&Controller_M)->solverInfo, (((&Controller_M)
        ->Timing.clockTickH0 + 1) * (&Controller_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&Controller_M)->solverInfo, (((&Controller_M)
        ->Timing.clockTick0 + 1) * (&Controller_M)->Timing.stepSize0 +
        (&Controller_M)->Timing.clockTickH0 * (&Controller_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Controller_M))) {
    (&Controller_M)->Timing.t[0] = rtsiGetT(&(&Controller_M)->solverInfo);
  }

  {
    real_T rtb_Derivative;
    real_T *lastU;

    /* Sum: '<Root>/Add' incorporates:
     *  Constant: '<Root>/r_req'
     *  Inport: '<Root>/state'
     */
    Controller_B.error = Controller_P.r_req_Value - Controller_U.state.r;

    /* Derivative: '<Root>/Derivative' */
    rtb_Derivative = (&Controller_M)->Timing.t[0];
    if ((Controller_DW.TimeStampA >= rtb_Derivative) &&
        (Controller_DW.TimeStampB >= rtb_Derivative)) {
      rtb_Derivative = 0.0;
    } else {
      real_T lastTime;
      lastTime = Controller_DW.TimeStampA;
      lastU = &Controller_DW.LastUAtTimeA;
      if (Controller_DW.TimeStampA < Controller_DW.TimeStampB) {
        if (Controller_DW.TimeStampB < rtb_Derivative) {
          lastTime = Controller_DW.TimeStampB;
          lastU = &Controller_DW.LastUAtTimeB;
        }
      } else if (Controller_DW.TimeStampA >= rtb_Derivative) {
        lastTime = Controller_DW.TimeStampB;
        lastU = &Controller_DW.LastUAtTimeB;
      }

      rtb_Derivative = (Controller_B.error - *lastU) / (rtb_Derivative -
        lastTime);
    }

    /* End of Derivative: '<Root>/Derivative' */

    /* Outport: '<Root>/u' incorporates:
     *  Constant: '<Root>/kd'
     *  Constant: '<Root>/ki'
     *  Constant: '<Root>/kp'
     *  DotProduct: '<Root>/Dot Product'
     *  DotProduct: '<Root>/Dot Product1'
     *  DotProduct: '<Root>/Dot Product2'
     *  Integrator: '<Root>/Integrator'
     *  Sum: '<Root>/Add1'
     */
    Controller_Y.u.u = (Controller_B.error * Controller_P.kp_Value +
                        Controller_X.Integrator_CSTATE * Controller_P.ki_Value)
      + rtb_Derivative * Controller_P.kd_Value;
  }

  if (rtmIsMajorTimeStep((&Controller_M))) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative' */
    if (Controller_DW.TimeStampA == (rtInf)) {
      Controller_DW.TimeStampA = (&Controller_M)->Timing.t[0];
      lastU = &Controller_DW.LastUAtTimeA;
    } else if (Controller_DW.TimeStampB == (rtInf)) {
      Controller_DW.TimeStampB = (&Controller_M)->Timing.t[0];
      lastU = &Controller_DW.LastUAtTimeB;
    } else if (Controller_DW.TimeStampA < Controller_DW.TimeStampB) {
      Controller_DW.TimeStampA = (&Controller_M)->Timing.t[0];
      lastU = &Controller_DW.LastUAtTimeA;
    } else {
      Controller_DW.TimeStampB = (&Controller_M)->Timing.t[0];
      lastU = &Controller_DW.LastUAtTimeB;
    }

    *lastU = Controller_B.error;

    /* End of Update for Derivative: '<Root>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&Controller_M))) {
    rt_ertODEUpdateContinuousStates(&(&Controller_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&Controller_M)->Timing.clockTick0)) {
      ++(&Controller_M)->Timing.clockTickH0;
    }

    (&Controller_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&Controller_M)
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
      (&Controller_M)->Timing.clockTick1++;
      if (!(&Controller_M)->Timing.clockTick1) {
        (&Controller_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Controller::Controller_derivatives()
{
  XDot_Controller_T *_rtXdot;
  _rtXdot = ((XDot_Controller_T *) (&Controller_M)->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = Controller_B.error;
}

/* Model initialize function */
void Controller::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Controller_M)->solverInfo, &(&Controller_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&Controller_M)->solverInfo, &rtmGetTPtr((&Controller_M)));
    rtsiSetStepSizePtr(&(&Controller_M)->solverInfo, &(&Controller_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&Controller_M)->solverInfo, &(&Controller_M)->derivs);
    rtsiSetContStatesPtr(&(&Controller_M)->solverInfo, (real_T **)
                         &(&Controller_M)->contStates);
    rtsiSetNumContStatesPtr(&(&Controller_M)->solverInfo, &(&Controller_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Controller_M)->solverInfo,
      &(&Controller_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Controller_M)->solverInfo,
      &(&Controller_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Controller_M)->solverInfo,
      &(&Controller_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&Controller_M)->solverInfo, (&rtmGetErrorStatus
      ((&Controller_M))));
    rtsiSetRTModelPtr(&(&Controller_M)->solverInfo, (&Controller_M));
  }

  rtsiSetSimTimeStep(&(&Controller_M)->solverInfo, MAJOR_TIME_STEP);
  (&Controller_M)->intgData.y = (&Controller_M)->odeY;
  (&Controller_M)->intgData.f[0] = (&Controller_M)->odeF[0];
  (&Controller_M)->intgData.f[1] = (&Controller_M)->odeF[1];
  (&Controller_M)->intgData.f[2] = (&Controller_M)->odeF[2];
  (&Controller_M)->contStates = ((X_Controller_T *) &Controller_X);
  rtsiSetSolverData(&(&Controller_M)->solverInfo, static_cast<void *>
                    (&(&Controller_M)->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&Controller_M)->solverInfo, false);
  rtsiSetSolverName(&(&Controller_M)->solverInfo,"ode3");
  rtmSetTPtr((&Controller_M), &(&Controller_M)->Timing.tArray[0]);
  (&Controller_M)->Timing.stepSize0 = 0.01;

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  Controller_InitializeDataMapInfo((&Controller_M), &Controller_P);

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  Controller_X.Integrator_CSTATE = Controller_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  Controller_DW.TimeStampA = (rtInf);
  Controller_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void Controller::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Controller::Controller() :
  Controller_U(),
  Controller_Y(),
  Controller_B(),
  Controller_DW(),
  Controller_X(),
  Controller_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
Controller::~Controller()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Controller_T * Controller::getRTM()
{
  return (&Controller_M);
}
