#pragma once
#include "ShaderVarType.h"

namespace ose::shader
{
	class ShaderNode
	{
	public:
		// NOTE - All ShaderNode derived constructors must populate inputs_ and outputs_ fields
		ShaderNode();
		~ShaderNode();

		void SetName(std::string const & name) { name_ = name; }
		std::string const & GetName() const { return name_; }

	protected:
		// Map from the name of the input to the type of the input
		std::map<std::string, ShaderVarType> inputs_;

		// Map from the name of the output to the type of the output
		std::map<std::string, ShaderVarType> outputs_;

		// The name of the shader node
		// Used in shader code generation for variable naming
		std::string name_ { "" };
	};
}
