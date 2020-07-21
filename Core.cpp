#include "Core.hpp"

namespace Green
{
	Core::Core()
	{
		auto AppModuleStr = skCrypt("55 8B EC 51 A1 ? ? ? ? 85 C0 74 ? 8B E5 5D C3 68 ? ? ? ?");
		auto AppModuleFuncAddress = Signature(AppModuleStr).Scan().As<uint64_t*>();
		AppModuleStr.clear();

		g_Logger->Info("AppModule function %X", AppModuleFuncAddress);

		typedef int(__stdcall* AppModuleUnkFunc_)(void*);
		AppModuleUnkFunc_ AppModuleFunc = (AppModuleUnkFunc_)AppModuleFuncAddress;

		auto AppModule = AppModuleFunc(NULL); // Call the function which returns AppModule pointer

		g_Logger->Info("AppModule %X", AppModule);
	}
}