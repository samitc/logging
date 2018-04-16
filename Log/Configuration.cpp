#include "Configuration.h"
namespace Sys
{
    namespace Logging
    {
        Configuration::Configuration() :sysData(nullptr), loggerWriter(nullptr), level(-1), numOfRef(1), removeWriter(true)
        {
        }
        Configuration::Configuration(Configuration &&c) : Configuration(c.sysData, c.loggerWriter, c.level, std::move(c.levels), std::move(c.immLevels), std::move(c.filter))
        {
            c.loggerWriter = nullptr;
            c.sysData = nullptr;
        }
        Configuration::Configuration(PreMessage *p, ILoggerWriter *l, unsigned char level, std::map<String, int>&&cl, std::vector<String>&&iml, LogFilter &&f) :
            sysData(p), loggerWriter(l), level(level), levels(std::move(cl)), immLevels(std::move(iml)), filter(std::move(f)), numOfRef(1), removeWriter(true)
        {
        }
        Configuration::~Configuration()
        {
            if (removeWriter)
            {
                delete loggerWriter;
            }
            delete sysData;
        }
        const PreMessage * Configuration::getSysData() const
        {
            return sysData;
        }
        const ILoggerWriter * Configuration::getLoggerWriter() const
        {
            return loggerWriter;
        }
        unsigned char Configuration::getLevel() const
        {
            return level;
        }
        const std::map<String, int>& Configuration::getLevels() const
        {
            return levels;
        }
        const std::vector<String>& Configuration::getImmLevels() const
        {
            return immLevels;
        }
        const LogFilter & Configuration::startUsingFilter() const
        {
            filterRWL.startRead();
            return filter;
        }
        void Configuration::endUsingFilter() const
        {
            filterRWL.endRead();
        }
        void Configuration::setFilter(const LogFilter & filter)
        {
            filterRWL.startWrite();
            this->filter = filter;
            filterRWL.endWrite();
        }
        Configuration* Configuration::addRef()
        {
            ++numOfRef;
            return this;
        }
        void Configuration::removeRef()
        {
            if (--numOfRef == 0)
            {
                delete this;
            }
        }
        void Configuration::clearRemoveWriter()
        {
            removeWriter = false;
        }
    }
}