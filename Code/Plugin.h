#ifndef _Pnugin_h
#define _Pnugin_h

#include <thread>
#include "AEColorPicker.h"

LibExport A_Err PluginInitialize(struct SPBasicSuite*, A_long, A_long, AEGP_PluginID, AEGP_GlobalRefcon*);
void LaunchScriptWhenStartingAE();
std::string GetSelfPath();

A_Err PluginInitialize(
	struct SPBasicSuite* pica_basicP,
	A_long major_versionL,
	A_long minor_versionL,
	AEGP_PluginID aegp_plugin_id,
	AEGP_GlobalRefcon* global_refconP)
{
	Glogal_basicSuite = pica_basicP;

	LaunchScriptWhenStartingAE();

	return A_Err_NONE;
}

void LaunchScriptWhenStartingAE()
{
	std::thread thr([]{
		try {
			std::string script = (
				"void(function(){"
				"try{"
				"var n = new ExternalObject('lib:" + GetSelfPath() + "')"
				"}catch(e){"
				"return"
				"}"
				"var o = $.colorPicker;"
				"$.colorPicker ="
				"eval('@JSXBIN@ES@2.0@MyBbyBn0ABNAnAMAbyBn0ABgAbyBn0ABZAnAEXzFjBjQjQjMjZBfXzLjDjPjMjPjSiQjJjDjLjFjSCfjzBjODfRCjDfVzJjBjSjHjVjNjFjOjUjTEf4kBkWkYAffABnzBjFFnbyBn0ABZAnAEXBfjzDjPjMjEGfRCjzBhEHfXzBhQIfjEfffACzBjBJ40BhAzBjCK4B0AhAC0ACC0EzALByB')"
				"})()"
				/* JSXBIN block
				(function colorPicker(color, title){
					try{
						return n.colorPicker.apply(n, arguments);
					}catch(e){
						return o.apply($, arguments[0]);
					}
				}); */
			);
			AEGP_UtilitySuite4* UtilitySuite4 = ((AEGP_SuiteHandler)Glogal_basicSuite).UtilitySuite4();

			A_Boolean IsGUI_NotAvailable = 0;
			UtilitySuite4->AEGP_GetSuppressInteractiveUI(&IsGUI_NotAvailable);
			if (IsGUI_NotAvailable) return;

			A_Boolean IsScripting_Available = 0;
			while (true) {
				std::this_thread::yield();

				UtilitySuite4->AEGP_IsScriptingAvailable(&IsScripting_Available);
				if (!IsScripting_Available) continue;

				UtilitySuite4->AEGP_ExecuteScript(NULL, script.c_str(), TRUE, NULL, NULL);
				break;
			}
		}
		catch (A_Err&) {}
		});
	thr.detach();
}

std::string GetSelfPath()
{
#ifdef AE_OS_MAC
	Dl_info info;
	dladdr(&Glogal_basicSuite, &info);

	std::string str(info.dli_fname);
	str.resize(str.rfind(".plugin/Contents") + 7);

	return str;

#elif defined AE_OS_WIN
	HMODULE hm = nullptr;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)& GetSelfPath, &hm);

	DWORD size = MAX_PATH;
	char* buffer;
	while (true) {
		buffer = new char[size];
		const DWORD r = GetModuleFileNameA(hm, buffer, size);
		if (r < size && r != 0) break;
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			delete[] buffer;
			size *= 2;
		}
	}
	std::string str(buffer);
	for (int i = 0; i < (int)str.size(); i++) {
		if (str.compare(i, 1, "\\") == 0) {
			str.replace(i, 1, "\\\\");
			i++;
		}
	}
	return str;
#endif
}
#endif
