#include "Xml.h"
#include <fstream>
#include <stack>
#include "rapidxml-1.13/rapidxml.hpp"
#include "Node.h"
#include "CharUtilities.h"
namespace Sys
{
	namespace Logging
	{
		template <class Z> Xml<Z>::Xml(const char *fileName):fileName(createStr(fileName)),text(nullptr),textSize(-1),doc(nullptr)
		{
		}
		template <class Z> Xml<Z>::~Xml()
		{
			delete[] this->fileName;
			delete[] this->text;
			delete this->doc;
		}
		template <class Z> bool Xml<Z>::open()
		{
			doc = new rapidxml::xml_document<Z>();
			const constexpr int FLAGS=0;
			std::ifstream file;
			file.open(this->fileName);
			if (file.is_open())
			{
				file.seekg(0, std::ios::end);
				this->textSize = file.tellg();
				file.seekg(0, std::ios::beg);
				this->text = new UTF8[this->textSize + 1];
				this->textSize = file.read(this->text, this->textSize).gcount();
				file.close();
				this->text[textSize] = 0;
				try
				{
					doc->template parse<FLAGS>(this->text);
				}
				catch (...)
				{
					return false;
				}
				return true;
			}
			return false;
		}
		template <class Z> template <class T> void Xml<Z>::scanAllNodes(bool node(Node<Z> *node, T *param), T *param)
		{
			std::stack<Node<Z>> allNodes;
			allNodes.push(this->doc->first_node());
			rapidxml::xml_node<> *cur;
			while (!allNodes.empty())
			{
				cur = allNodes.pop();
				if (!node(cur, param))
				{
					return;
				}
				for (rapidxml::xml_node<> *p = cur->first_node(); p; p = p->next_sibling())
				{
					allNodes.push(p);
				}
			}
		}
		template <class Z> template <class T> void Xml<Z>::scanAndSons(bool node(Node<Z> *node, T *param), T *param, void(*nodeEnd)(Node<Z> *node, T *param))
		{
			rapidxml::xml_node<Z> *ip = this->doc->first_node();
			Node<Z> n = Node<Z>(ip);
			if (node(&n, param))
			{
				for (rapidxml::xml_node<Z> *p = ip; p; p = p->next_sibling())
				{
					Node<Z> n{ p };
					if (!this->scanAndSonsRec(&n, node, param, nodeEnd))
					{
						break;
					}
				}
			}
			if (nodeEnd != NULL)
			{
				nodeEnd(&n, param);
			}
		}
		template <class Z> template <class T> bool Xml<Z>::scanAndSonsRec(Node<Z> *pnode, bool node(Node<Z> *node, T *param), T *param, void(*nodeEnd)(Node<Z> *node, T *param))
		{
			bool hasChildren = false;
			if (node(pnode, param))
			{
				for (rapidxml::xml_node<Z> *p = pnode->getNode()->first_node(); p; p = p->next_sibling())
				{
					hasChildren = true;
					Node<Z> n{ p };
					if (!this->scanAndSonsRec(&n, node, param, nodeEnd))
					{
						return false;
					}
				}
			}
			if (nodeEnd != NULL&&hasChildren)
			{
				nodeEnd(pnode, param);
			}
			return true;
		}
	}
}