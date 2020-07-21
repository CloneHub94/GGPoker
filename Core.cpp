#include "Core.hpp"

namespace Green
{
	Core::Core()
	{
		auto m_AppModuleStr = skCrypt("55 8B EC 51 A1 ? ? ? ? 85 C0 74 ? 8B E5 5D C3 68 ? ? ? ?");
		auto m_AppModuleFunc = Signature(m_AppModuleStr).Scan().As<uint64_t*>();
		m_AppModuleStr.clear();

		g_Logger->Info("AppModule function %X", m_AppModuleFunc);

		typedef int(__stdcall* AppModuleUnkFunc_)(void*);
		AppModuleUnkFunc_ AppModuleFunc = (AppModuleUnkFunc_)m_AppModuleFunc;

		auto AppModule = AppModuleFunc(NULL); // Call the function

		g_Logger->Info("AppModule %X", AppModule);
	}
}