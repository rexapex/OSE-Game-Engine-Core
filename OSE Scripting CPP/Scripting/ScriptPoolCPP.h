#pragma once
#include "OSE-Core/Scripting/ScriptPool.h"
#include "Custom Engine/CustomEngine.h"

namespace ose
{
	class CustomComponent;
}

namespace ose::scripting
{
	class ScriptPoolCPP final : public ScriptPool
	{
	public:
		ScriptPoolCPP();
		~ScriptPoolCPP();

		// Initialise the script pool
		void Init();

		// Add a custom engine component to the script pool
		void AddCustomComponent(Entity & entity, unowned_ptr<CustomComponent> comp) override;

		// Add a custom control to the script pool
		void AddCustomControl(unowned_ptr<CustomControl> control) override;

		// Get the list of custom engines
		std::vector<std::unique_ptr<CustomEngine>> const & GetCustomEngines() const { return custom_engines_; }

	private:
		std::vector<std::unique_ptr<CustomEngine>> custom_engines_;
	};
}
