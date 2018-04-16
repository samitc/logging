#include "Attribute.h"
#include "rapidxml-1.13/rapidxml.hpp"
namespace Sys
{
	namespace Logging
	{
		template <class T> Attribute<T>::Attribute(rapidxml::xml_attribute<T> *att):att(att)
		{
		}
		template <class T> Attribute<T>::~Attribute()
		{

		}
		template <class T> T* Attribute<T>::getValue() const
		{
			return this->att->value();
		}
		template <class T> T* Attribute<T>::getName() const
		{
			return this->att->name();
		}
	}
}