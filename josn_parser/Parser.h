#pragma once
#include "Scanner.h"
#include "JosnElement.h"

namespace civi
{
	namespace josn
	{
		class Parser
		{
		public:
			Parser(Scanner scanner) :scanner_(scanner) {}
			JosnElement* Parse();
		private:
			JosnObj* ParseObj();
			JosnArr* ParseArr();
			Scanner scanner_;
		};
	}// namespace josn
}//namespace civi
