#pragma once

#include "../Interfaces/Interfaces.h"

namespace MonoLib
{
	namespace Model
	{
		class BaseDocument : IModel
		{
		public:
			std::string Name = "";
			int Id = 5;
		};
	}
}