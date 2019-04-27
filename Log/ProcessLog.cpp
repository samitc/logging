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
        bool ProcessLog::processLog(const LogData& ld, String& res) const
        {
            Configuration* config = ld.getConfig();
            if (config->startUsingFilter().filter(String(ld.getMsg())))
            {
                config->endUsingFilter();
                LogStatement ls = LogStatement(config->getSysData(), ld.getMsg(), ld.getLevel());
                res = ls.getMessage(ld.getDatas(), ld.getDatasSize());
                res += ld.getName();
                return true;
            }
            else
            {
                config->endUsingFilter();
                return false;
            }
        }
    }
}