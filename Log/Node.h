#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
namespace rapidxml
{
	template<class Ch> class xml_node;
}
namespace Sys
{
	namespace Logging
	{
		template <class T> class Attribute;
		template <class T> class Node
		{
		public:
			explicit Node(rapidxml::xml_node<T> *node);
			~Node();
			T* getValue();
			T* getName();
			std::vector<Attribute<T>> getAllAttributes();
			rapidxml::xml_node<T> * getNode();
		private:
			rapidxml::xml_node<T> *node;
		};
	}
}
#include "Node.cpp"
#endif