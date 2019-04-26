#include "ProcessLog.h"
#include <queue>
#include "LogData.h"
#include "Logger.h"
#include "LogStatement.h"
#include "Configuration.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
        UTF8* ProcessLog::processLog(const LogData& ld) const
        {
            Configuration* config = ld.getConfig();
            if (config->startUsingFilter().filter(String(ld.getMsg())))
            {
                config->endUsingFilter();
                LogStatement ls = LogStatement(config->getSysData(), ld.getMsg(), ld.getLevel());
                String str = ls.getMessage(ld.getDatas(), ld.getDatasSize());
                str += ld.getName();
                return createStr(str.c_str());
            }
            else
            {
                config->endUsingFilter();
                return nullptr;
            }
        }
    }
}