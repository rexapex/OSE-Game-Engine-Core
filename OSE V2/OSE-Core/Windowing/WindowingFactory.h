#pragma once

namespace ose
{
	class WindowManager;

	class WindowingFactory
	{
	public:
		constexpr WindowingFactory() {}
		virtual ~WindowingFactory() {}
		WindowingFactory(WindowingFactory &) = delete;
		WindowingFactory & operator=(WindowingFactory &) = delete;
		WindowingFactory(WindowingFactory &&) = default;
		WindowingFactory & operator=(WindowingFactory &&) = default;

		virtual uptr<WindowManager> NewWindowManager() = 0;
	};
}
