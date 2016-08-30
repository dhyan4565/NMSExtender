#include "NMSE_Core_1_0\ModAPI.h"
#include "NMSE_Libs\Hooking.h"
#include "HookFuncs.h"
#include <sstream>
#include <string>
#include <fstream>

HMODULE localH;
VERSION vers;
uintptr_t stack_ptr;
SizeSettings settings;

MemoryManager* gm;
MemoryManager* lm;

SizeSettings GetSettings(LPCSTR dir) {
	return {
		(int)GetPrivateProfileInt("SIZE_SETTINGS", "DEFAULT_SUBS_SIZE", 250, dir),
		(int)GetPrivateProfileInt("SIZE_SETTINGS", "DEFAULT_ITEM_SIZE", 1, dir),
		(int)GetPrivateProfileInt("SIZE_SETTINGS", "SHIP_MULT",			2, dir),
		(int)GetPrivateProfileInt("SIZE_SETTINGS", "CHARGE_VAL",		-1, dir)
	};
}

extern "C"
{
	bool OnStart(HMODULE& mHandle, ModDetails& info){
		localH = mHandle;
		info.name = "StackResize";
		vers = info.version; 

		settings = GetSettings("./NMSE/StackResize.ini");

		WriteHook(settings, gm, lm);
		return true;
	}

	void GrabVirtualMem(MemoryManager* globalMem, MemoryManager* localMem) {
		gm = globalMem;
		lm = localMem;
	}
};