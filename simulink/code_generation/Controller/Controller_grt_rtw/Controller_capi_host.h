#ifndef RTW_HEADER_Controller_cap_host_h__
#define RTW_HEADER_Controller_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

struct Controller_host_DataMapInfo_T {
  rtwCAPI_ModelMappingInfo mmi;
};

#ifdef __cplusplus

extern "C"
{

#endif

  void Controller_host_InitializeDataMapInfo(Controller_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                 /* RTW_HEADER_Controller_cap_host_h__ */

/* EOF: Controller_capi_host.h */
