#pragma once
#include <string>
#include <map>
#include <sstream>
#include <vector>

namespace civi
{
	namespace josn
	{
		class JosnElement;
		using JosnObj = std::map<std::string, JosnElement*>;//±£´æjoan type
		using JosnArr = std::vector<JosnElement*>;
		class JosnElement
		{
		public:

			enum Type
			{
				JOSN_OBJ,
				JOSN_ARRAY,
				JOSN_STRING,
				JOSN_BOOL,
				JOSN_NULL,
				JOSN_NUM
			};
			union Value
			{
				JosnObj* val_obj;
				JosnArr* val_arr;
				std::string* val_str;
				double val_num;
				bool val_bool;

			};
			JosnElement() :type_(Type::JOSN_NULL) {}
			JosnElement(JosnObj* value_obj) { value(value_obj); }
			JosnElement(JosnArr* value_arr) { value(value_arr); }
			JosnElement(std::string* value_str) { value(value_str); }
			JosnElement(float value_num) { value(value_num); }
			JosnElement(bool value_bool) { value(value_bool); }
			~JosnElement()
			{
				if (type_ == Type::JOSN_OBJ)
				{
					JosnObj* obj = value_.val_obj;
					for (auto& item : *obj) {
						delete item.second;
					}
					delete obj;
				}
				else if (type_ == Type::JOSN_ARRAY)
				{
					JosnArr* arr = value_.val_arr;
					for (auto& item : *arr)
					{
						delete item;
					}
					delete arr;
				}
				else if (type_ == Type::JOSN_STRING)
				{
					std::string* str = value_.val_str;
					delete str;
				}
			}
			void value(JosnObj* value_obj) {
				type_ = Type::JOSN_OBJ;
				value_.val_obj = value_obj;
			}
			void value(JosnArr* value_arr)
			{
				type_ = Type::JOSN_ARRAY;
				value_.val_arr = value_arr;
			}
			void value(std::string* value_str)
			{
				type_ = Type::JOSN_STRING;
				value_.val_str = value_str;
			}
			void value(double value_num)
			{
				type_ = Type::JOSN_NUM;
				value_.val_num = value_num;
			}
			void value(bool value_bool) {
				type_ = Type::JOSN_BOOL;
				value_.val_bool = value_bool;
			}



			JosnObj* AsObj() {
				if (type_ == Type::JOSN_OBJ)
				{
					return value_.val_obj;
				}
				Error("Type of JosnElement isn't JosnObject!");		
			}
			JosnArr* AsArr()
			{
				if (type_ == Type::JOSN_ARRAY)
				{
					return value_.val_arr;
				}
				Error("Type of JosnElement isn't JosnArray!");
			}
			std::string* AsStr()
			{
				if (type_ == Type::JOSN_STRING)
				{
					return value_.val_str;
				}
				Error("Type of JosnElement isn't String!");
			}
			double AsNum()
			{
				if (type_ == Type::JOSN_NUM)
				{
					return value_.val_num;
				}
				Error("Type of JosnElement isn't Number!");
			}
			bool AsBool()
			{
				if (type_ == Type::JOSN_BOOL)
				{
					return value_.val_bool;
				}
				Error("Type of JosnElement isn't Boolean!");
			}

			std::string Dumps()  //×ª³Éjosn×Ö·û´®
			{
				std::stringstream ss;
				switch (type_)
				{
				case civi::josn::JosnElement::JOSN_OBJ:
					ss << *value_.val_obj;
					break;
				case civi::josn::JosnElement::JOSN_ARRAY:
					ss << *value_.val_arr;
					break;
				case civi::josn::JosnElement::JOSN_STRING:
					ss << '\"' << *(value_.val_str) << '\"';
					break;
				case civi::josn::JosnElement::JOSN_BOOL:
					ss << (value_.val_bool  ? "true" : "false");
					break;
				case civi::josn::JosnElement::JOSN_NULL:
					ss << "null";
					break;
				case civi::josn::JosnElement::JOSN_NUM:
					ss << value_.val_num;
					break;
				default:
					break;
				}
				return ss.str();
			}
			friend std::ostream& operator<<(std::ostream& os, const JosnObj& obj)
			{
				os << "{";
				for (auto iter = obj.begin(); iter != obj.end(); iter++) {
					os << '\"' << iter->first << '\"' << ": " << iter->second->Dumps();
					if (iter != --obj.end())
					{
						os << ", ";
					}
				}
				os << "}";
				return os;
			}
			friend std::ostream& operator<<(std::ostream& os, const JosnArr& arr)
			{
				os << "[";
				for (size_t i = 0; i<arr.size(); i++) {
					os << arr[i]->Dumps();
					if (i!=arr.size()-1)
					{
						os << ", ";
					}
				}
				os << "]";
				return os;
			}

		private:
			Type type_;
			Value value_;
		};
	}// namespace josn
}//namespace civi