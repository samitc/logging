#include "Node.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "Attribute.h"
namespace Sys
{
	namespace Logging
	{
		template <class T> Node<T>::Node(rapidxml::xml_node<T> *node):node(node)
		{
		}
		template <class T> Node<T>::~Node()
		{

		}
		template <class T> T* Node<T>::getValue()
		{
			return this->node->value();
		}
		template <class T> T* Node<T>::getName()
		{
			return this->node->name();
		}
		template <class T> std::vector<Attribute<T>> Node<T>::getAllAttributes()
		{
			std::vector<Attribute<T>> ret;
			for (rapidxml::xml_attribute<T> *p = this->node->first_attribute();p; p=p->next_attribute())
			{
				ret.push_back(Attribute<T>(p));
			}
			return ret;
		}
		template <class T> rapidxml::xml_node<T> * Node<T>::getNode()
		{
			return this->node;
		}
	}
}