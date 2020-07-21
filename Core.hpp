#pragma once

#define InRange(val) (val >= dwGameBase && val <= dwGameBase + 0x9000000)

namespace Green
{
	class Core
	{
	public:
		explicit Core();
		~Core() noexcept = default;
		Core(Core const&) = delete;
		Core(Core&&) = delete;
		Core& operator=(Core const&) = delete;
		Core& operator=(Core&&) = delete;
	private:
	};

	inline std::unique_ptr<Core> g_Core;
}