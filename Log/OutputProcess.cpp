#include "OutputProcess.h"
#include <queue>
#include "Logger.h"
#include "ILoggerWriter.h"
#include "Configuration.h"
#include "CharUtilities.h"
#include "LString.h"
namespace Sys
{
    namespace Logging
    {
        void writeToOutput(const LogOutput& msg);
        OutputProcess::OutputProcess() : curPrinted(0)
        {
        }
        OutputProcess::~OutputProcess()
        {
            printAllData();
        }
        void OutputProcess::outputLog(LogOutput&& logOutput) const
        {
            if (logOutput.shouldWriteInstantly)
            {
                writeToOutput(logOutput);
            }
            else
            {
                data.insert(std::move(logOutput));
                printAllData();
            }
        }
        void OutputProcess::printAllData() const
        {
            auto s = data.cbegin(), e = data.cend();
            while (s != e && s->logNumber == curPrinted)
            {
                writeToOutput(*s);
                s = data.erase(s);
                curPrinted++;
            }
        }
        void writeToOutput(const LogOutput& msg)
        {
            Configuration* config = msg.config;
            config->getLoggerWriter()->write(msg.msg.c_str());
        }
        LogOutput::LogOutput(const LogOutput& copy) :LogOutput(copy.config, String(copy.msg), copy.shouldWriteInstantly, copy.logNumber)
        {
            config->addRef();
        }
        LogOutput::LogOutput(Configuration* config, String&& msg, bool shouldWriteInstantly, uint64_t logNumber) : msg(msg), config(config), logNumber(logNumber), shouldWriteInstantly(shouldWriteInstantly)
        {
        }
        LogOutput::LogOutput(LogOutput&& o) : LogOutput(o.config, std::move(o.msg), o.shouldWriteInstantly, o.logNumber)
        {
            o.msg = nullptr;
            o.config = nullptr;
        }
        LogOutput::~LogOutput()
        {
            if (config != nullptr)
            {
                config->removeRef();
            }
        }
    }
}