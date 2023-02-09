#include <iostream>
#include "Scanner.h"
#include "Parser.h"

using namespace civi::josn;

int main()
{
	auto source = R"(
		{
			"glossaty" : {
			"test" :true,
			"hello":null,
			"hello1": "miaomiao"
			}
		}
)";
	Scanner scaner(source);
	Parser parse(scaner);
	JosnElement* ele = parse.Parse();
	std::cout << ele->Dumps() << '\n';
	delete ele;
	system("pause");
	return 0;
}