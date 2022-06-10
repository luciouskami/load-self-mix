#include "dll_module.h"
#include <cassert>
#include <memory>



BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
)
{


	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		UNREFERENCED_PARAMETER(lpReserved);
		model_pack::dll_module::GetInstance()->Attach();

	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		model_pack::dll_module::GetInstance()->Detach();
	}

	return TRUE;
}