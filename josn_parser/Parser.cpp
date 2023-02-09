#include "Parser.h"

namespace civi {
	namespace josn {
		using JosnTokenType = Scanner::JosnTokenType;
		JosnElement* Parser::Parse()
		{
			JosnElement* element = new JosnElement;
			JosnTokenType token_type = scanner_.Scan();
			switch (token_type)
			{
			case JosnTokenType::END_OF_SOURCE:
			{
				break;
			}
			case JosnTokenType::BEGIN_OBJ:
			{
				JosnObj* obj = ParseObj();
				element->value(obj);
				break;
			}
			case JosnTokenType::BEGIN_ARRAY:
			{
				JosnArr* arr = ParseArr();
				element->value(arr);
				break;
			}
			case JosnTokenType::VALUE_STRING:
			{
				std::string* str = new std::string(scanner_.getStr());
				element->value(str);
				break;
			}
			case JosnTokenType::VALUE_NUMBER:
			{
				double num = scanner_.getNum();
				element->value(num);
			}
			case JosnTokenType::LITERAL_TRUE:
			{
				element->value(true);
				break;
			}
			case JosnTokenType::LITERAL_FALSE:
			{
				element->value(false);
				break;
			}
			case JosnTokenType::LITERAL_NULL:
			{
				break;
			}
			}
			return element;
		}
		JosnObj* Parser::ParseObj()
		{
			JosnObj* res = new JosnObj();
			JosnTokenType next = scanner_.Scan();
			if (next == JosnTokenType::END_BOJ)
			{
				return res;
			}
			scanner_.RoolBack();
			while (true)
			{
				next = scanner_.Scan();
				if (next != JosnTokenType::VALUE_STRING)
				{
					Error("key must be string");
				}
				std::string key = scanner_.getStr();
				next = scanner_.Scan();
				if (next != JosnTokenType::NAME_SEPRATOR)
				{
					Error("Expected ':'!");
				}
				(*res)[key] = Parse();
				next = scanner_.Scan();
				if (next == JosnTokenType::END_BOJ)
				{
					break;
				}
				if (next != JosnTokenType::VALUE_SEPRATOR) {
					Error("Expected ','!");
				}
			}
			return res;
		}
		JosnArr* Parser::ParseArr()
		{
			JosnArr* res = new JosnArr();
			JosnTokenType next = scanner_.Scan();
			if (next == JosnTokenType::END_ARRAY)
			{
				return res;
			}
			scanner_.RoolBack();
			while (true)
			{
				res->push_back(Parse());
				next = scanner_.Scan();
				if (next == JosnTokenType::END_ARRAY) break;
				if (next != JosnTokenType::VALUE_SEPRATOR) Error("Expected ','!");

			}
			return res;
		}
	} //namespace josn
} //namespace civi