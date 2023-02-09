#include "Scanner.h"

namespace civi
{
	namespace josn
	{
		void Scanner::RoolBack()
		{
			current_ = prev_pos;
		}
		bool Scanner::IsAtEnd()
		{
			return current_ >= source_.size();
		}
		char Scanner::Advance()
		{
			return source_[current_++];
		}
		void Scanner::ScanTrue()
		{
			if (source_.compare(current_, 3, "rue") == 0)
			{
				current_ += 3;
			}
			else {
				Error("Scan 'true' error");
			}
		}
		void Scanner::ScanFalse()
		{
			if (source_.compare(current_, 4, "alse") == 0)
			{
				current_ += 4;
			}
			else {
				Error("Scan 'false' error");
			}
		}
		void Scanner::ScanNull()
		{
			if (source_.compare(current_, 3, "ull") == 0)
			{
				current_ += 3;
			}
			else {
				Error("Scan 'null' error");
			}
		}
		void Scanner::ScanString()
		{
			size_t pos = current_;
			while (Peek() != '\"' && !IsAtEnd())
			{
				Advance();
			}
			if (IsAtEnd())
			{
				Error("Invalid string:missing closing quote!");
			}
			Advance();
			value_str = source_.substr(pos, current_ - pos - 1);
		}
		void Scanner::ScanNum()
		{
			size_t pos = current_-1;
			while (IsDigit(Peek()))
			{
				Advance();
			}
			if (Peek() == '.' && IsDigit(PeekNext()))
			{
				Advance();
				while (IsDigit(Peek()))
				{
					Advance();
				}
			}
			val_num = std::atof(source_.substr(pos, current_ - pos).c_str());
		}
		bool Scanner::IsDigit(char c)
		{
			return c>='0' && c<=9;
		}
		char Scanner::Peek()
		{
			if (IsAtEnd()) return '\0';
			return source_[current_];
		}
		char Scanner::PeekNext()
		{
			if (current_ + 1 >= source_.size()) return '\0';
			return source_[current_];
		}
		Scanner::JosnTokenType Scanner::Scan()
		{
			if (IsAtEnd())
			{
				return JosnTokenType::END_OF_SOURCE;
			}
			prev_pos = current_;
			char c = Advance();
			switch (c)
			{
			case '{':
				return JosnTokenType::BEGIN_OBJ;
			case '}':
				return JosnTokenType::END_BOJ;
			case '[':
				return JosnTokenType::BEGIN_ARRAY;
			case ']':
				return JosnTokenType::END_ARRAY;
			case ':':
				return JosnTokenType::NAME_SEPRATOR;
			case ',':
				return JosnTokenType::VALUE_SEPRATOR;
			case 't':
				ScanTrue();
				return JosnTokenType::LITERAL_TRUE;
			case 'f':
				ScanFalse();
				return JosnTokenType::LITERAL_FALSE;
			case 'n':
				ScanNull();
				return JosnTokenType::LITERAL_NULL;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				return Scan();
			case '\"':
				ScanString();
				return JosnTokenType::VALUE_STRING;
			case '-':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				ScanNum();
				return JosnTokenType::VALUE_NUMBER;
			default:
				Error("²»Ö§³ÖToken:" + c);

			}
			return JosnTokenType();
		}
		std::ostream& operator<<(std::ostream& os, const Scanner::JosnTokenType& type)
		{
			switch (type)
			{
			case Scanner::JosnTokenType::BEGIN_ARRAY:
				os << "[";
				break;
			case Scanner::JosnTokenType::END_ARRAY:
				os << "]";
				break;
			case Scanner::JosnTokenType::BEGIN_OBJ:
				os << "{";
				break;
			case Scanner::JosnTokenType::END_BOJ:
				os << "}";
				break;
			case Scanner::JosnTokenType::NAME_SEPRATOR:
				os << ":";
				break;
			case Scanner::JosnTokenType::VALUE_NUMBER:
				os << "number";
				break;
			case Scanner::JosnTokenType::VALUE_SEPRATOR:
				os << ",";
				break;
			case Scanner::JosnTokenType::VALUE_STRING:
				os << "string";
				break;
			case Scanner::JosnTokenType::LITERAL_NULL:
				os << "null";
				break;
			case Scanner::JosnTokenType::LITERAL_TRUE:
				os << "true";
				break;
			case Scanner::JosnTokenType::LITERAL_FALSE:
				os << "false";
				break;
			case Scanner::JosnTokenType::END_OF_SOURCE:
				os << "EOF";
				break;
			default:
				break;
			}
			return os;
		}
}// namespace josn
}//namespace civi