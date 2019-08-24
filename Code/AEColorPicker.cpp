#include "AEColorPicker.h"
#include "Plugin.h"

long  ESGetVersion() { return 0x1; };
void  ESFreeMem(void*) {};
void  ESTerminate() {};
char* ESInitialize(TaggedData*, long)
{
	InitializeSPBasicSuite();

	return "colorPicker_fs";
};

long colorPicker(TaggedData* args, long argsLength, TaggedData* pResult)
{
	pResult->type = kTypeDouble;

	PF_PixelFloat color = { 1,1,0,0 };
	if (argsLength >= 0) {
		int rgb = (int)args[0].data.fltval;
		rgb = rgb < 0 ? 0 : (rgb > 0xFFFFFF ? 0xFFFFFF : rgb);

		color.red = (PF_FpShort)((rgb & 0xFF0000) >> 16) / 0xff;
		color.green = (PF_FpShort)((rgb & 0x00FF00) >> 8) / 0xff;
		color.blue = (PF_FpShort)((rgb & 0x0000FF)) / 0xff;
	}
	const char* title = (argsLength > 1) ? args[1].data.string : "Color";

	try{
		PFAppSuite4* AppSuite4 = ((AEGP_SuiteHandler)Glogal_basicSuite).AppSuite4();
		if (AppSuite4->PF_AppColorPickerDialog(title, &color, false, &color) == PF_Interrupt_CANCEL){
			pResult->data.fltval = -1;
			return kESErrOK;
		}
	}catch (A_Err&) {
		pResult->type = kTypeScript;

		std::string script("$.colorPicker( ");
		if (argsLength > 0) {
			script.append(std::to_string((int)args[0].data.fltval));
		}
		script.append(" )");
		pResult->data.string = (char*)script.c_str();
		return kESErrOK;
	}
	#define Float2uint8_t(value) (uint8_t)(value < 0 ? 0 : value > 1 ? 0xff : round(value*0xff))    //min & max + round
	#define PixelFloat2HEX(color) Float2uint8_t(color.red) << 16 | Float2uint8_t(color.green) << 8 | Float2uint8_t(color.blue)

	pResult->data.fltval = PixelFloat2HEX(color);
	return kESErrOK;

	#undef Double2uint8_t
	#undef PixelFloat2HEX
}

void InitializeSPBasicSuite()
{
	if (Glogal_basicSuite == nullptr){
		auto GetSPBasicSuite = GetFunctionFromLib<typeGetSPBasicSuite>("PLUG", "PLUG_GetSPBasicSuite");
		if (GetSPBasicSuite == nullptr) {
			GetSPBasicSuite = GetFunctionFromLib<typeGetSPBasicSuite>("U", "U_SP_GetSPBasicSuite");
		}
		if (GetSPBasicSuite == nullptr) return;
		GetSPBasicSuite(&Glogal_basicSuite);
	}
}

template <typename T>
T GetFunctionFromLib(const char* lib, const char* func)
{
#ifdef AE_OS_WIN
	#define LibExtension ".dll"
#elif defined AE_OS_MAC
	#define LibExtension ".dylib"
	#define GetModuleHandle(l) dlopen(l, RTLD_LAZY)
	#define GetProcAddress dlsym
#endif

	std::string libbuf(lib);
	libbuf.append(LibExtension);

	auto hModule = GetModuleHandle(libbuf.c_str());
	if (hModule != nullptr) {
		return (T)GetProcAddress(hModule, func);
	}
	return nullptr;

#ifdef AE_OS_MAC
#undef GetModuleHandle
#undef GetProcAddress
#endif
}
