#ifndef _Color_Picker_h
#define _Color_Picker_h

#include <string>
#include "AEConfig.h"
#include "AEGP_SuiteHandler.h"
#include "SoSharedLibDefs.h"

#ifdef AE_OS_WIN
	#include <windows.h>
	#define LibExport extern "C" __declspec(dllexport)
	#define strdup _strdup
#elif defined AE_OS_MAC
	#include <dlfcn.h>
	#define LibExport extern "C" __attribute__ ((visibility ("default")))
#endif
 
static struct SPBasicSuite* Glogal_basicSuite = nullptr;

LibExport long  colorPicker(TaggedData*, long, TaggedData*);

LibExport char* ESInitialize(TaggedData*, long);
LibExport long  ESGetVersion();
LibExport void  ESFreeMem(void*);
LibExport void  ESTerminate();

void InitializeSPBasicSuite();
template <typename T>T GetFunctionFromLib(const char* lib, const char* func);
typedef void (*typeGetSPBasicSuite) (SPBasicSuite**);

#endif
