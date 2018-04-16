#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H
namespace rapidxml
{
	template <class T> class xml_attribute;
}
namespace Sys
{
	namespace Logging
	{
		template <class T> class Attribute
		{
		public:
			explicit Attribute(rapidxml::xml_attribute<T> *att);
			~Attribute();
			T* getValue() const;
			T* getName() const;
		private:
			rapidxml::xml_attribute<T> *att;
		};
	}
}
#include "Attribute.cpp"
#endif