#include "ConsoleWriter.h"
#include <iostream>
namespace Sys
{
	namespace Logging
	{
		void ConsoleWriter::write(const char* text) const
		{
			std::cout << text << std::endl;
		}
        bool ConsoleWriter::compare(const StreamParam&) const
        {
            return true;
        }
	}
}