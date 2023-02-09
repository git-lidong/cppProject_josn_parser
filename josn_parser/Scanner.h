#pragma once
#include <string>
#include "Eerror.h"
#include <ostream>
namespace civi
{
	namespace josn
	{
		class Scanner
		{
		public:
			Scanner(std::string source) :source_(source), current_(0) {}
			enum class JosnTokenType  //josn tokken类型
			{
				BEGIN_OBJ,     //代表 {
				END_BOJ,   //代表 }
				VALUE_SEPRATOR, //代表 ,
				NAME_SEPRATOR,//代表 :
				VALUE_STRING,//代表 "string"
				VALUE_NUMBER,//代表 1,2,2e10
				LITERAL_TRUE,//代表 true
				LITERAL_FALSE,//代表 false
				LITERAL_NULL,//代表 NULL

				BEGIN_ARRAY,//代表 [
				END_ARRAY,//代表 ]
				END_OF_SOURCE  //代表 EOF
			};
			friend std::ostream& operator<<(std::ostream& os, const JosnTokenType& type);
			
			JosnTokenType Scan(); //从当前已扫描位置开始，返回下一个token的位置
			std::string getStr()
			{
				return value_str;
			}
			double getNum()
			{
				return val_num;
			}
			void RoolBack();

		private:
			bool IsAtEnd();
			char Advance(); //获得下一个字符
			void ScanTrue();
			void ScanFalse();
			void ScanNull();
			void ScanString();
			void ScanNum();

			bool IsDigit(char c);
			char Peek();
			char PeekNext();


			std::string source_;  //< josn source
			size_t current_;//当前正在处理的位置
			size_t prev_pos;
			std::string value_str;
			double val_num;
		};
	}// namespace josn
}//namespace civi