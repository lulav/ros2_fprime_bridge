/*
 * Dynamics.h
 *
 * Code generation for model "Dynamics".
 *
 * Model version              : 1.43
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C++ source code generated on : Mon Nov 28 09:35:05 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Dynamics_h_
#define RTW_HEADER_Dynamics_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "Dynamics_types.h"
#include "rtw_modelmap.h"
#include <cstring>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)    ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
struct B_Dynamics_T {
  real_T Constant5;                    /* '<Root>/Constant5' */
  real_T v;                            /* '<Root>/Integrator' */
  real_T Constant4;                    /* '<Root>/Constant4' */
  real_T Divide;                       /* '<Root>/Divide' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_Dynamics_T {
  int_T Integrator_IWORK;              /* '<Root>/Integrator' */
  int_T Integrator1_IWORK;             /* '<Root>/Integrator1' */
};

/* Continuous states (default storage) */
struct X_Dynamics_T {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
};

/* State derivatives (default storage) */
struct XDot_Dynamics_T {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
};

/* State disabled  */
struct XDis_Dynamics_T {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<Root>/Integrator1' */
};

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
struct ODE3_IntgData {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
};

#endif

/* External inputs (root inport signals with default storage) */
struct ExtU_Dynamics_T {
  B_Controller u;                      /* '<Root>/u' */
};

/* External outputs (root outports fed by signals with default storage) */
struct ExtY_Dynamics_T {
  B_Dynamics state;                    /* '<Root>/state' */
};

/* Parameters (default storage) */
struct P_Dynamics_T_ {
  B_Dynamics Constant2_Value;          /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T Constant5_Value;              /* Expression: params.v0.Value
                                        * Referenced by: '<Root>/Constant5'
                                        */
  real_T Constant4_Value;              /* Expression: params.r0.Value
                                        * Referenced by: '<Root>/Constant4'
                                        */
  real_T Constant3_Value;              /* Expression: params.c.Value
                                        * Referenced by: '<Root>/Constant3'
                                        */
  real_T Constant1_Value;              /* Expression: params.k.Value
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: params.m.Value
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Dynamics_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_Dynamics_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_Dynamics_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
  ODE3_IntgData intgData;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
    void* dataAddress[6];
    int32_T* vardimsAddress[6];
    RTWLoggingFcnPtr loggingPtrs[6];
  } DataMapInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    boolean_T firstInitCondFlag;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  Dynamics_GetCAPIStaticMap(void);

/* Class declaration for model Dynamics */
class Dynamics final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  Dynamics(Dynamics const&) = delete;

  /* Assignment Operator */
  Dynamics& operator= (Dynamics const&) & = delete;

  /* Move Constructor */
  Dynamics(Dynamics &&) = delete;

  /* Move Assignment Operator */
  Dynamics& operator= (Dynamics &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_Dynamics_T * getRTM();

  /* Root inports set method */
  void setExternalInputs(const ExtU_Dynamics_T *pExtU_Dynamics_T)
  {
    Dynamics_U = *pExtU_Dynamics_T;
  }

  /* Root outports get method */
  const ExtY_Dynamics_T &getExternalOutputs() const
  {
    return Dynamics_Y;
  }

  /* model start function */
  void start();

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  Dynamics();

  /* Destructor */
  ~Dynamics();

  /* private data and function members */
 private:
  /* External inputs */
  ExtU_Dynamics_T Dynamics_U;

  /* External outputs */
  ExtY_Dynamics_T Dynamics_Y;

  /* Block signals */
  B_Dynamics_T Dynamics_B;

  /* Block states */
  DW_Dynamics_T Dynamics_DW;

  /* Tunable parameters */
  static P_Dynamics_T Dynamics_P;

  /* Block continuous states */
  X_Dynamics_T Dynamics_X;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void Dynamics_derivatives();

  /* Real-Time Model */
  RT_MODEL_Dynamics_T Dynamics_M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Dynamics'
 */
#endif                                 /* RTW_HEADER_Dynamics_h_ */
