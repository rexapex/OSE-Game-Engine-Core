// NOTE - No #pragma once or include guards
// If a script file includes another script file, macros should be redefined s.t. NAME is set correctly

#include "Custom Engine/CustomEngine.h"

namespace ose
{
	class Entity;
	class CustomComponent;
}

#ifdef CAT
#	undef CAT
#endif
#ifdef XCAT
#	undef XCAT
#endif
#ifdef NAME
#	undef NAME
#endif
#ifdef DATA
#	undef DATA
#endif
#ifdef ENGINE
#	undef ENGINE
#endif

#define CAT(a, b) a ## b
#define XCAT(a, b) CAT(a, b)

#define TOSTR(x) #x
#define STR(x) TOSTR(x)

#define DATA(code) \
	struct XCAT(NAME, Data) { \
		XCAT(NAME, Data) (unowned_ptr<CustomComponent> comp) : READONLY_CUSTOM_COMPONENT(comp) {} \
		XCAT(NAME, Data) (XCAT(NAME, Data) const &) = default; \
		XCAT(NAME, Data) (XCAT(NAME, Data) &&) = default; \
		XCAT(NAME, Data) & operator=(XCAT(NAME, Data) const &) = default; \
		XCAT(NAME, Data) & operator=(XCAT(NAME, Data) &&) = default; \
		unowned_ptr<CustomComponent> READONLY_CUSTOM_COMPONENT; \
		code \
	};

#define ENGINE(code) \
	class XCAT(NAME, Engine) : public ose::scripting::CustomEngine { \
	public: \
		XCAT(NAME, Engine)() : ose::scripting::CustomEngine() {} \
		std::string GetComponentTypeName() const override { return STR(NAME); } \
		void AddCustomComponent(unowned_ptr<Entity> entity, unowned_ptr<CustomComponent> comp) { \
			data_array_.emplace_back(comp); \
			InitComponent(entity, data_array_.back()); \
		} \
		void RemoveCustomComponent(unowned_ptr<CustomComponent> comp) { \
			data_array_.erase(std::remove_if(data_array_.begin(), data_array_.end(), [comp](auto & data) { \
				return data.READONLY_CUSTOM_COMPONENT == comp; \
			})); \
		} \
	private: \
		std::vector<XCAT(NAME, Data)> data_array_; \
	public: \
		code \
	};\
	std::unique_ptr<ose::scripting::CustomEngine> XCAT(New, XCAT(NAME, Engine))() { \
		return std::make_unique<XCAT(NAME, Engine)>(); \
	} \
	auto XCAT(NAME, AddFactoryToMap) = [] { \
		CustomEngine::GetSetCustomEngineFactory(STR(New) STR(NAME) STR(Engine), XCAT(New, XCAT(NAME, Engine))); \
		return 0; \
	}();

// Prevents needing to include these in every custom engine script
using namespace ose;
using namespace ose::scripting;
