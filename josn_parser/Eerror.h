#pragma once
#include <stdexcept>
namespace civi
{
	namespace josn
	{
		inline void Error(const char* message)
		{
			throw std::logic_error(message);
		}
	}// namespace josn
}//namespace civi