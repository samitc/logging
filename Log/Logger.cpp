#include "Logger.h"
#include <algorithm>
#include "LogStatement.h"
#include "PreMessage.h"
#include "ILogStatement.h"
#include "LoggerData.h"
#include "ILoggerWriter.h"
#include "LogData.h"
#include "Configuration.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
#define MAX_LEVEL   255
        void Logger::log(const char * level, const UTF8 * msg, const UTF8* name, bool writeImmediately) const
        {
            String levelS(level);
            Configuration* config = this->config.load(std::memory_order_acquire)->addRef();
            this->plog(config->getLevels().at(levelS), msg, level, name, writeImmediately);
            config->removeRef();
        }
        void Logger::plog(unsigned int level, const UTF8* msg, const UTF8* sLevel, const UTF8* name, bool writeIm) const
        {
            if (checkLevel(level))
            {
                Configuration* config = this->config.load(std::memory_order_acquire)->addRef();
                writeIm |= std::find_if(config->getImmLevels().cbegin(), config->getImmLevels().cend(), [&sLevel](const String str)
                {
                    return !strcmp(sLevel, str.c_str());
                }) != config->getImmLevels().cend();
                loggerManager.log(config, sLevel, createStr(msg), name, writeIm);
            }
        }
        void Logger::log(unsigned short level, const UTF8 * msg) const
        {
            if (checkLevel(level))
            {
                int maxDis = 0x7fffffff;
                const char* lv;
                Configuration* config = this->config.load(std::memory_order_acquire)->addRef();
                auto str = std::find_if(config->getLevels().cbegin(), config->getLevels().cend(), [level, &maxDis, &lv](const auto& lev)
                {
                    int dis;
                    if (lev.second == level)
                    {
                        lv = lev.first.c_str();
                        return true;
                    }
                    else if (lev.second > level)
                    {
                        dis = lev.second - level;
                    }
                    else
                    {
                        dis = level - lev.second;
                    }
                    if (maxDis > dis)
                    {
                        maxDis = dis;
                        lv = lev.first.c_str();
                    }
                    return false;
                });
                this->log(lv, msg);
                config->removeRef();
            }
        }
        void Logger::log(const UTF8* level, const UTF8* msg) const
        {
            Configuration* config = this->config.load(std::memory_order_acquire)->addRef();
            this->plog(config->getLevels().at(String(level)), msg, level, name, false);
            config->removeRef();
        }
        void Logger::log(const UTF8* level, const UTF8 * msg, const UTF8* name) const
        {
            Configuration* config = this->config.load(std::memory_order_acquire)->addRef();
            this->plog(config->getLevels().at(String(level)), msg, level, name, false);
            config->removeRef();
        }
        void Logger::log(const UTF8* level, const UTF8 * msg, bool writeImmediately) const
        {
            Configuration* config = this->config.load(std::memory_order_acquire)->addRef();
            this->plog(config->getLevels().at(String(level)), msg, level, name, writeImmediately);
            config->removeRef();
        }
        void Logger::log(unsigned short level, const std::function<const UTF8*()>& msg) const
        {
            this->log(level, msg());
        }
        void Logger::log(const UTF8* level, const std::function<const UTF8*()>& msg) const
        {
            this->log(level, msg());
        }
        void Logger::log(const UTF8* level, const std::function<const UTF8*()>& msg, const UTF8* name) const
        {
            this->log(level, msg(), name);
        }
        void Logger::log(const UTF8* level, const std::function<const UTF8* ()>&msg, bool writeImmediately) const
        {
            this->log(level, msg(), writeImmediately);
        }
        void Logger::debug(const UTF8 * msg) const
        {
            this->log("debug", msg);
        }
        void Logger::fatal(const UTF8 * msg) const
        {
            this->log("fatal", msg);
        }
        void Logger::error(const UTF8 * msg) const
        {
            this->log("error", msg);
        }
        void Logger::info(const UTF8 * msg) const
        {
            this->log("info", msg);
        }
        void Logger::warn(const UTF8 * msg) const
        {
            this->log("warn", msg);
        }
        void Logger::trace(const UTF8 * msg) const
        {
            this->log("trace", msg);
        }
        void Logger::debug(const UTF8 * msg, bool writeImmediately) const
        {
            this->log("debug", msg, writeImmediately);
        }
        void Logger::fatal(const UTF8 * msg, bool writeImmediately) const
        {
            this->log("fatal", msg, writeImmediately);
        }
        void Logger::error(const UTF8 * msg, bool writeImmediately) const
        {
            this->log("error", msg, writeImmediately);
        }
        void Logger::info(const UTF8 * msg, bool writeImmediately) const
        {
            this->log("info", msg, writeImmediately);
        }
        void Logger::warn(const UTF8 * msg, bool writeImmediately) const
        {
            this->log("warn", msg, writeImmediately);
        }
        void Logger::trace(const UTF8 * msg, bool writeImmediately) const
        {
            this->log("trace", msg, writeImmediately);
        }
        void Logger::debug(const UTF8 * msg, const UTF8* name) const
        {
            this->log("debug", msg, name);
        }
        void Logger::fatal(const UTF8 * msg, const UTF8* name) const
        {
            this->log("fatal", msg, name);
        }
        void Logger::error(const UTF8 * msg, const UTF8* name) const
        {
            this->log("error", msg, name);
        }
        void Logger::info(const UTF8 * msg, const UTF8* name) const
        {
            this->log("info", msg, name);
        }
        void Logger::warn(const UTF8 * msg, const UTF8* name) const
        {
            this->log("warn", msg, name);
        }
        void Logger::trace(const UTF8 * msg, const UTF8* name) const
        {
            this->log("trace", msg, name);
        }
        void Logger::setLogFilter(const LogFilter & logFilter)
        {
            Configuration* config = this->config.load(std::memory_order_acquire)->addRef();
            config->setFilter(logFilter);
            config->removeRef();
        }
        bool Logger::checkLevel(unsigned int level) const
        {
            Configuration* config = this->config.load(std::memory_order_acquire)->addRef();
            unsigned char l = config->getLevel();
            config->removeRef();
            return l >= level;
        }
        void Logger::reloadConfig(const ILoggerData& logger, int loggerNumber)
        {
            Configuration* conf;
            bool removeWriter = true;
            {
                std::vector<String> immLevels = std::move(logger.getImmediateLevels(loggerNumber));
                std::map<String, int> levels;
                levels[String("debug")] = 170;
                levels[String("trace")] = 200;
                levels[String("info")] = 140;
                levels[String("warn")] = 100;
                levels[String("error")] = 50;
                levels[String("fatal")] = 20;
                std::vector<ILoggerData::CustomLevel> customs = logger.getCustomLevel();
                for (const auto& levelCustom : customs)
                {
                    levels[levelCustom.name] = levelCustom.level;
                }
                ILoggerWriter* writer = nullptr;
                const auto& stream = logger.getStreams(loggerNumber);
                Configuration* curConf = config.load(std::memory_order_acquire);
                if (curConf!=nullptr)
                {
                    curConf->addRef();
                }
                if (curConf != nullptr && !curConf->getLoggerWriter()->compare(stream))
                {
                    writer = const_cast<ILoggerWriter*>(curConf->getLoggerWriter());
                    removeWriter = false;
                }
                else
                {
                    writer = const_cast<ILoggerWriter*>(stream.getLoggerWriter());
                }
                if (curConf!=nullptr)
                {
                    curConf->removeRef();
                }
                String lev = logger.getLevel(loggerNumber);
                const auto& lvl = levels.find(lev);
                unsigned char level;
                if (lvl == levels.cend())
                {
                    level = atoi(lev.c_str());
                }
                else
                {
                    level = (*lvl).second;
                }
                if (level > MAX_LEVEL)
                {
                    level = MAX_LEVEL;
                }
                PreMessage* p = new PreMessage(logger.getPaterens(loggerNumber).c_str(), logger.getLoggerName(loggerNumber).c_str());
                LogFilter f = logger.getLogFilter(loggerNumber);
                conf = new Configuration(p, writer, level, std::move(levels), std::move(immLevels), std::move(f), logger.getMaxWaitingLogs(loggerNumber));
                conf = config.exchange(conf, std::memory_order_release);
            }
            if (conf != nullptr)
            {
                if (!removeWriter)
                {
                    conf->clearRemoveWriter();
                }
                conf->removeRef();
            }
        }
        LogFilter Logger::getLogFilter() const
        {
            Configuration* config = this->config.load(std::memory_order_acquire)->addRef();
            LogFilter ret = config->startUsingFilter();
            config->endUsingFilter();
            config->removeRef();
            return ret;
        }
        UTF8* createOrNull(const UTF8* str)
        {
            if (str==nullptr)
            {
                return nullptr;
            }
            else
            {
                return createStr(str);
            }
        }
        Logger::Logger(const ILoggerData& logger, int loggerNumber, ConcurrencyLevel level) : Logger(logger, loggerNumber, nullptr, level)
        {
        }
        Logger::Logger(const ILoggerData& logger, int loggerNumber, const UTF8* name, ConcurrencyLevel level) : name(createOrNull(name)), logNumber(0), config(), loggerManager(level)
        {
            reloadConfig(logger, loggerNumber);
        }
        Logger::Logger(const ILoggerData& logger, int loggerNumber, int concurrencyLevel) : Logger(logger, loggerNumber, nullptr, concurrencyLevel)
        {
        }
        Logger::Logger(const ILoggerData& logger, int loggerNumber, const UTF8* name, int concurrencyLevel) : name(createOrNull(name)), logNumber(0), config(), loggerManager(concurrencyLevel)
        {
            reloadConfig(logger, loggerNumber);
        }
        Logger::Logger(Logger &&copy) : config(copy.config.load(std::memory_order_acquire)), name(std::move(copy.name)), loggerManager(std::move(copy.loggerManager))
        {
            copy.config.store(nullptr, std::memory_order_relaxed);
        }
        Logger::Logger(ConcurrencyLevel level) : loggerManager(level)
        {
        }
        Logger::Logger(int concurrencyLevel) : loggerManager(concurrencyLevel)
        {
        }
        Logger::~Logger()
        {
            config.load()->removeRef();
        }
    }
}