/*
 * Controller.h
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

#ifndef RTW_HEADER_Controller_h_
#define RTW_HEADER_Controller_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "Controller_types.h"

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rt_nonfinite.h"

}

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
struct B_Controller_T {
  real_T error;                        /* '<Root>/Add' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_Controller_T {
  real_T TimeStampA;                   /* '<Root>/Derivative' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative' */
  real_T TimeStampB;                   /* '<Root>/Derivative' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative' */
};

/* Continuous states (default storage) */
struct X_Controller_T {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
};

/* State derivatives (default storage) */
struct XDot_Controller_T {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
};

/* State disabled  */
struct XDis_Controller_T {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
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
struct ExtU_Controller_T {
  B_Dynamics state;                    /* '<Root>/state' */
};

/* External outputs (root outports fed by signals with default storage) */
struct ExtY_Controller_T {
  B_Controller u;                      /* '<Root>/u' */
};

/* Parameters (default storage) */
struct P_Controller_T_ {
  B_Controller Constant1_Value;        /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Constant5_Value;              /* Expression: params.r_req.Value
                                        * Referenced by: '<Root>/Constant5'
                                        */
  real_T Constant4_Value;              /* Expression: params.kp.Value
                                        * Referenced by: '<Root>/Constant4'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<Root>/Integrator'
                                        */
  real_T Constant2_Value;              /* Expression: params.ki.Value
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T Constant3_Value;              /* Expression: params.kd.Value
                                        * Referenced by: '<Root>/Constant3'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Controller_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_Controller_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_Controller_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[1];
  real_T odeF[3][1];
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
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  Controller_GetCAPIStaticMap(void);

/* Class declaration for model Controller */
class Controller final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  Controller(Controller const&) = delete;

  /* Assignment Operator */
  Controller& operator= (Controller const&) & = delete;

  /* Move Constructor */
  Controller(Controller &&) = delete;

  /* Move Assignment Operator */
  Controller& operator= (Controller &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_Controller_T * getRTM();

  /* Root inports set method */
  void setExternalInputs(const ExtU_Controller_T *pExtU_Controller_T)
  {
    Controller_U = *pExtU_Controller_T;
  }

  /* Root outports get method */
  const ExtY_Controller_T &getExternalOutputs() const
  {
    return Controller_Y;
  }

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  Controller();

  /* Destructor */
  ~Controller();

  /* private data and function members */
 private:
  /* External inputs */
  ExtU_Controller_T Controller_U;

  /* External outputs */
  ExtY_Controller_T Controller_Y;

  /* Block signals */
  B_Controller_T Controller_B;

  /* Block states */
  DW_Controller_T Controller_DW;

  /* Tunable parameters */
  static P_Controller_T Controller_P;

  /* Block continuous states */
  X_Controller_T Controller_X;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void Controller_derivatives();

  /* Real-Time Model */
  RT_MODEL_Controller_T Controller_M;
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
 * '<Root>' : 'Controller'
 */
#endif                                 /* RTW_HEADER_Controller_h_ */
