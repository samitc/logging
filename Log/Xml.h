#ifndef _XML_H_
#define _XML_H_
#include "GlobalDefinitions.h"
namespace rapidxml
{
	template<class Ch> class xml_document;
}
namespace Sys
{
	namespace Logging
	{
		template <class T> class Node;
		template <class Z> class Xml
		{
		public:
			explicit Xml(const char *fileName);
			~Xml();
			bool open();
			template <class T> void scanAllNodes(bool node(Node<Z> *node,T *param),T *param);
			template <class T> void scanAndSons(bool node(Node<Z> *node, T *param), T *param, void(*nodeEnd)(Node<Z> *node, T *param) = NULL);
		private:
			template <class T> bool scanAndSonsRec(Node<Z> *pnode,bool node(Node<Z> *node, T *param), T *param, void(*nodeEnd)(Node<Z> *node, T *param));
			char *fileName;
			UTF8 *text;
			size_t textSize;
			rapidxml::xml_document<Z> *doc;
		};
	}
}
#include "Xml.cpp"
#endif