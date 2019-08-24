#include "AEConfig.h"

#ifndef AE_OS_WIN
	#include "AE_General.r"
#endif

resource 'PiPL' (16000) {
	{	/* array properties: 7 elements */
		/* [1] */
		Kind {
			AEGP
		},
		/* [2] */
		Name {
			"AEColorPicker"
		},
		/* [3] */
		Category {
			"General Plugin"
		},
		/* [4] */
		Version {
			0x10000
		},
		/* [5] */
#ifdef AE_OS_WIN
	#ifdef AE_PROC_INTELx64
		CodeWin64X86 {"PluginInitialize"},
	#else
		CodeWin32X86 {"PluginInitialize"},
	#endif
#else
	#ifdef AE_OS_MAC
		CodeMachOPowerPC {"PluginInitialize"},
		CodeMacIntel32 {"PluginInitialize"},
		CodeMacIntel64 {"PluginInitialize"},
	#endif
#endif
	}
};

