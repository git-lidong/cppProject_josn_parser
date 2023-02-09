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
			enum class JosnTokenType  //josn tokken����
			{
				BEGIN_OBJ,     //���� {
				END_BOJ,   //���� }
				VALUE_SEPRATOR, //���� ,
				NAME_SEPRATOR,//���� :
				VALUE_STRING,//���� "string"
				VALUE_NUMBER,//���� 1,2,2e10
				LITERAL_TRUE,//���� true
				LITERAL_FALSE,//���� false
				LITERAL_NULL,//���� NULL

				BEGIN_ARRAY,//���� [
				END_ARRAY,//���� ]
				END_OF_SOURCE  //���� EOF
			};
			friend std::ostream& operator<<(std::ostream& os, const JosnTokenType& type);
			
			JosnTokenType Scan(); //�ӵ�ǰ��ɨ��λ�ÿ�ʼ��������һ��token��λ��
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
			char Advance(); //�����һ���ַ�
			void ScanTrue();
			void ScanFalse();
			void ScanNull();
			void ScanString();
			void ScanNum();

			bool IsDigit(char c);
			char Peek();
			char PeekNext();


			std::string source_;  //< josn source
			size_t current_;//��ǰ���ڴ����λ��
			size_t prev_pos;
			std::string value_str;
			double val_num;
		};
	}// namespace josn
}//namespace civi