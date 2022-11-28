/*
 * Controller_capi.cpp
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

#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "Controller_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "Controller.h"
#include "Controller_capi.h"
#include "Controller_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((nullptr))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

static rtwCAPI_BlockParameters rtBlockParameters[]{
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  { 0, TARGET_STRING("Controller/Constant1"),
    TARGET_STRING("Value"), 1, 0, 0 },

  { 1, TARGET_STRING("Controller/Constant2"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 2, TARGET_STRING("Controller/Constant3"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 3, TARGET_STRING("Controller/Constant4"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 4, TARGET_STRING("Controller/Constant5"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 5, TARGET_STRING("Controller/Integrator"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  {
    0, (nullptr), (nullptr), 0, 0, 0
  }
};

/* Tunable variable parameters */
static rtwCAPI_ModelParameters rtModelParameters[]{
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 0, (nullptr), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

/* Initialize Data Address */
static void Controller_InitializeDataAddr(void* dataAddr[], P_Controller_T
  *Controller_P)
{
  dataAddr[0] = (void*) (&Controller_P->Constant1_Value);
  dataAddr[1] = (void*) (&Controller_P->Constant2_Value);
  dataAddr[2] = (void*) (&Controller_P->Constant3_Value);
  dataAddr[3] = (void*) (&Controller_P->Constant4_Value);
  dataAddr[4] = (void*) (&Controller_P->Constant5_Value);
  dataAddr[5] = (void*) (&Controller_P->Integrator_IC);
}

#endif

/* Initialize Data Run-Time Dimension Buffer Address */
#ifndef HOST_CAPI_BUILD

static void Controller_InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (nullptr);
}

#endif

#ifndef HOST_CAPI_BUILD

/* Initialize logging function pointers */
static void Controller_InitializeLoggingFunctions(RTWLoggingFcnPtr loggingPtrs[])
{
  loggingPtrs[0] = (nullptr);
  loggingPtrs[1] = (nullptr);
  loggingPtrs[2] = (nullptr);
  loggingPtrs[3] = (nullptr);
  loggingPtrs[4] = (nullptr);
  loggingPtrs[5] = (nullptr);
}

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[]{
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer, enumStorageType */
  { "double", "real_T", 0, 0, sizeof(real_T), (uint8_T)SS_DOUBLE, 0, 0, 0 },

  { "struct", "B_Controller", 1, 1, sizeof(B_Controller), (uint8_T)SS_STRUCT, 0,
    0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[]{
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { (nullptr), 0, 0, 0, 0 },

  { "u", rt_offsetof(B_Controller, u), 0, 0, 0 }
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static rtwCAPI_DimensionMap rtDimensionMap[]{
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_SCALAR, 0, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static uint_T rtDimensionArray[]{
  1,                                   /* 0 */
  1                                    /* 1 */
};

/* Fixed Point Map */
static rtwCAPI_FixPtMap rtFixPtMap[]{
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { (nullptr), (nullptr), rtwCAPI_FIX_RESERVED, 0, 0, (boolean_T)0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static rtwCAPI_SampleTimeMap rtSampleTimeMap[]{
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  {
    (nullptr), (nullptr), 0, 0
  }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic{
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { (nullptr), 0,
    (nullptr), 0,
    (nullptr), 0 },

  { rtBlockParameters, 6,
    rtModelParameters, 0 },

  { (nullptr), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 3689049103U,
    745901375U,
    2608973738U,
    2046352288U },
  (nullptr), 0,
  (boolean_T)0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  Controller_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void Controller_InitializeDataMapInfo(RT_MODEL_Controller_T *const Controller_M,
  P_Controller_T *Controller_P)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(Controller_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(Controller_M->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(Controller_M->DataMapInfo.mmi, (nullptr));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  Controller_InitializeDataAddr(Controller_M->DataMapInfo.dataAddress,
    Controller_P);
  rtwCAPI_SetDataAddressMap(Controller_M->DataMapInfo.mmi,
    Controller_M->DataMapInfo.dataAddress);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  Controller_InitializeVarDimsAddr(Controller_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(Controller_M->DataMapInfo.mmi,
    Controller_M->DataMapInfo.vardimsAddress);

  /* Set Instance specific path */
  rtwCAPI_SetPath(Controller_M->DataMapInfo.mmi, (nullptr));
  rtwCAPI_SetFullPath(Controller_M->DataMapInfo.mmi, (nullptr));

  /* Cache C-API logging function pointers into the Real-Time Model Data structure */
  Controller_InitializeLoggingFunctions(Controller_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(Controller_M->DataMapInfo.mmi,
    Controller_M->DataMapInfo.loggingPtrs);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(Controller_M->DataMapInfo.mmi, (nullptr));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(Controller_M->DataMapInfo.mmi, (nullptr));
  rtwCAPI_SetChildMMIArrayLen(Controller_M->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C"
{

#endif

  void Controller_host_InitializeDataMapInfo(Controller_host_DataMapInfo_T
    *dataMap, const char *path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, (nullptr));

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, (nullptr));

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, (nullptr));

    /* Set reference to submodels */
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (nullptr));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */

/* EOF: Controller_capi.cpp */
