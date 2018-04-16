#include "XmlLogger.h"
#include <iostream>
#include <algorithm>
#include "Xml.h"
#include "XmlSetting.h"
#include "CharUtilities.h"
#include "Node.h"
#include "XmlLogger.h"
#include "ConsoleWriter.h"
#include "FileWriter.h"
#include "NetworkWriter.h"
#include "LogFilter.h"
namespace Sys
{
    namespace Logging
    {
        XmlLogger::XmlLogger() :curLogger(-1)
        {
        }
        XmlLogger::~XmlLogger()
        {
        }
        bool XmlLogger::load(const char *fileName)
        {
            Xml<UTF8> xml = Xml<UTF8>(fileName);
            xml.open();
            xml.scanAndSons<XmlLogger>([](Node<UTF8> *node, XmlLogger *param)
            {
                return param->nodeScan(node);
            }, this, [](Node<UTF8> *node, XmlLogger *param)
            {
                param->nodeEnd(node);
            });
            return true;
        }
        int XmlLogger::getNumOfLoggers() const
        {
            return indexToLoggerNames.size();
        }
        std::vector<ILoggerData::CustomLevel> XmlLogger::getCustomLevel() const
        {
            return this->customLevels;
        }
        ILoggerData::StreamParam XmlLogger::getStreams(int loggerNumber) const
        {
            ILoggerData::StreamParam ret;
            ret.streamType = ILoggerData::StreamType::NONE;
            if ((int)streams[loggerNumber].streamType == 0)
            {
                return streams[getLogNumber(indexToLoggerNames[loggerNumber].appenderName)];
            }
            else
            {
                ret = streams[loggerNumber];
                const auto& appStr = streams[getLogNumber(indexToLoggerNames[loggerNumber].appenderName)];
                switch (ret.streamType)
                {
                case Sys::Logging::ILoggerData::StreamType::FILE:
                    if (ret.fileParam.maxFiles == 0)
                    {
                        ret.fileParam.maxFiles = appStr.fileParam.maxFiles;
                    }
                    if (ret.fileParam.fileName == nullptr)
                    {
                        ret.fileParam.fileName = createStr(appStr.fileParam.fileName);
                    }
                    break;
                case Sys::Logging::ILoggerData::StreamType::NETWORK:
                    if (ret.networkParam.port == 0)
                    {
                        ret.networkParam.port = appStr.networkParam.port;
                    }
                    if ((int)ret.networkParam.protocol == 0)
                    {
                        ret.networkParam.protocol = appStr.networkParam.protocol;
                    }
                    if (ret.networkParam.addr == nullptr)
                    {
                        ret.networkParam.addr = createStr(appStr.networkParam.addr);
                    }
                    break;
                }
            }
            return ret;
        }
        size_t XmlLogger::getMaxLogSize(int loggerNumber) const
        {
            size_t maxLogSize = 1024;
            if (maxLogSizeInKB[loggerNumber] != 0)
            {
                maxLogSize = maxLogSizeInKB[loggerNumber];
            }
            else if (!indexToLoggerNames[loggerNumber].logName.empty())
            {
                maxLogSize = maxLogSizeInKB[this->getLogNumber(indexToLoggerNames[loggerNumber].appenderName)];
            }
            return maxLogSize;
        }
        unsigned int XmlLogger::getMaxLogTime(int loggerNumber) const
        {
            unsigned int maxLogTime = 60 * 60 * 24;
            if (maxLogTimeInSec[loggerNumber] != 0)
            {
                maxLogTime = maxLogTimeInSec[loggerNumber];
            }
            else if (!indexToLoggerNames[loggerNumber].logName.empty())
            {
                maxLogTime = maxLogTimeInSec[this->getLogNumber(indexToLoggerNames[loggerNumber].appenderName)];
            }
            return maxLogTime;
        }
        String XmlLogger::getLoggerName(int loggerNumber) const
        {
            return !this->indexToLoggerNames[loggerNumber].logName.empty() ? indexToLoggerNames[loggerNumber].logName : indexToLoggerNames[loggerNumber].appenderName;
        }
        String XmlLogger::getPaterens(int loggerNumber) const
        {
            String patt;
            if (!pat[loggerNumber].empty())
            {
                patt = pat[loggerNumber];
            }
            else if (!indexToLoggerNames[loggerNumber].logName.empty())
            {
                patt = pat[this->getLogNumber(indexToLoggerNames[loggerNumber].appenderName)];
            }
            return patt;
        }
        bool XmlLogger::nodeScan(Node<UTF8> *node)
        {
            UTF8 *name = node->getName();
            if (strcmp(name, XML_LEVEL_CUSTOM) == 0)
            {
                if (this->xmlIner.top() != XML_ROOT)
                {
                    throw "Not implement";
                }
                CustomLevel cl;
                for (auto const &att : node->getAllAttributes())
                {
                    if (strcmp(att.getName(), "name") == 0)
                    {
                        cl.name = createStr(att.getValue());
                    }
                    if (strcmp(att.getName(), "value") == 0)
                    {
                        cl.level = strToInt(att.getValue());
                    }
                }
                this->customLevels.push_back(cl);
            }
            else if (strcmp(name, XML_ROOT) == 0)
            {
                this->xmlIner.push(XML_ROOT);
            }
            else if (strcmp(name, XML_SPECIFIC_LOGGER) == 0)
            {
                if (this->xmlIner.top() != XML_ROOT)
                {
                    throw "Not implement";
                }
                addNewLogger();
                for (auto const &att : node->getAllAttributes())
                {
                    if (strcmp(att.getName(), "name") == 0)
                    {
                        this->indexToLoggerNames[curLogger] = LogData(String(att.getValue()), String());
                    }
                }
                this->xmlIner.push(XML_SPECIFIC_LOGGER);
            }
            else if (strcmp(name, XML_LOGGER) == 0)
            {
                if (this->xmlIner.top() != XML_ROOT)
                {
                    throw "Not implement";
                }
                addNewLogger();
                String name, app;
                for (auto const &att : node->getAllAttributes())
                {
                    if (strcmp(att.getName(), "name") == 0)
                    {
                        name = att.getValue();
                    }
                    if (strcmp(att.getName(), "value") == 0)
                    {
                        app = att.getValue();
                    }
                }
                indexToLoggerNames[curLogger] = LogData(std::move(app), std::move(name));
                this->xmlIner.push(XML_LOGGER);
            }
            else if (strcmp(name, XML_OUTPUT) == 0)
            {
                if (this->xmlIner.top() != XML_SPECIFIC_LOGGER)
                {
                    throw "Not implement";
                }
                UTF8* lower = createStr(node->getAllAttributes()[0].getValue());
                if (strcmp(lower, STREAM_NAME_CONSOLE) == 0)
                {
                    this->streams[this->curLogger].streamType = StreamType::CONSOLE;
                }
                else if (strcmp(lower, STREAM_NAME_NETWORK) == 0)
                {
                    this->streams[this->curLogger].streamType = StreamType::NETWORK;
                }
                else if (strcmp(lower, STREAM_NAME_FILE) == 0)
                {
                    this->streams[this->curLogger].streamType = StreamType::FILE;
                }
                delete[] lower;
            }
            else if (strcmp(name, XML_APPEND_TO_FILE) == 0)
            {
                if (this->xmlIner.top() != XML_SPECIFIC_LOGGER || this->streams[this->curLogger].streamType != StreamType::FILE)
                {
                    throw "Not implement";
                }
                name = node->getAllAttributes()[0].getValue();
                stringToLower(name);
                if (!strcmp(name, "true"))
                {
                    this->streams[this->curLogger].fileParam.appendToFile = true;
                }
                else if (!strcmp(name, "false"))
                {
                    this->streams[this->curLogger].fileParam.appendToFile = false;
                }
            }
            else if (strcmp(name, XML_MAX_LOG_SIZE) == 0)
            {
                if (this->xmlIner.top() != XML_SPECIFIC_LOGGER)
                {
                    throw "Not implement";
                }
                this->maxLogSizeInKB[this->curLogger] = strToInt(node->getAllAttributes()[0].getValue());
            }
            else if (strcmp(name, STREAM_NETWORK_PORT) == 0)
            {
                if (this->xmlIner.top() != XML_SPECIFIC_LOGGER || this->streams[this->curLogger].streamType != StreamType::NETWORK)
                {
                    throw "Not implement";
                }
                this->streams[this->curLogger].networkParam.port = strToInt(node->getAllAttributes()[0].getValue());
            }
            else if (strcmp(name, XML_PATTERN) == 0)
            {
                if (this->xmlIner.top() != XML_SPECIFIC_LOGGER)
                {
                    throw "Not implement";
                }
                this->pat[this->curLogger] = createString(node->getValue());
            }
            else if (strcmp(name, STRRAM_NETWORK_ADDR) == 0)
            {
                if (this->xmlIner.top() != XML_SPECIFIC_LOGGER || streams[curLogger].streamType != StreamType::NETWORK)
                {
                    throw "Not implement";
                }
                this->streams[curLogger].networkParam.addr = createStr(node->getAllAttributes()[0].getValue());
            }
            else if (strcmp(name, XML_LEVEL) == 0)
            {
                if (xmlIner.top() == XML_IMMEDIATE_WRITE)
                {
                    xmlIner.push(XML_IMMEDIATE_WRITE_LEVEL);
                }
                else
                {
                    this->levels[curLogger] = createString(node->getAllAttributes()[0].getValue());
                }
            }
            else if (strcmp(name, XML_SPECIFIC_LOGGER_NAME) == 0)
            {

            }
            else if (strcmp(name, XML_FILE_LOC) == 0)
            {
                if (this->xmlIner.top() != XML_SPECIFIC_LOGGER || streams[curLogger].streamType != StreamType::FILE)
                {
                    throw "Not implement";
                }
                streams[curLogger].fileParam.fileName = createStr(node->getAllAttributes()[0].getValue());
            }
            else if (strcmp(name, XML_FILTER) == 0)
            {
                if (this->xmlIner.top() != XML_SPECIFIC_LOGGER)
                {
                    throw "Not implement";
                }
                for (const auto& att : node->getAllAttributes())
                {
                    if (strcmp(att.getName(), XML_FILTER_TYPE) == 0)
                    {
                        this->xmlIner.push(att.getValue());
                        break;
                    }
                }
            }
            else if (strcmp(name, XML_FILTER_TEXT) == 0)
            {
                if (strcmp(XML_FILTER_TYPE_TEXT, this->xmlIner.top()) != 0)
                {
                    throw "Not implement";
                }
                for (const auto& att : node->getAllAttributes())
                {
                    if (strcmp(att.getName(), XML_VAL) == 0)
                    {
                        logsFilter[curLogger].addFilterString(String(att.getValue()));
                        break;
                    }
                }
            }
            else if (strcmp(name, XML_IMMEDIATE_WRITE) == 0)
            {
                if (xmlIner.top() != XML_SPECIFIC_LOGGER)
                {
                    throw "Not implement";
                }
                xmlIner.push(XML_IMMEDIATE_WRITE);
            }
            else if (name[0] == '\0')
            {
                if (xmlIner.top() == XML_IMMEDIATE_WRITE_LEVEL)
                {
                    addImmediateWrite(node->getValue());
                }
            }
            return true;
        }
        void XmlLogger::nodeEnd(Node<UTF8>* node)
        {
            UTF8 * in = this->xmlIner.top();
            if (strcmp(in, node->getName()) != 0 && strcmp(node->getName(), XML_FILTER) != 0)
            {
                //TODO
            }
            else
            {
                this->xmlIner.pop();
            }
        }
        void XmlLogger::addImmediateWrite(UTF8 * name)
        {
            immLevels[curLogger].push_back(createString(name));
        }
        void XmlLogger::addNewLogger()
        {
            ++curLogger;
            indexToLoggerNames.resize(curLogger + 1);
            streams.resize(curLogger + 1);
            pat.resize(curLogger + 1);
            levels.resize(curLogger + 1);
            maxLogSizeInKB.resize(curLogger + 1);
            maxLogTimeInSec.resize(curLogger + 1);
            logsFilter.resize(curLogger + 1);
            immLevels.resize(curLogger + 1);
        }
        int XmlLogger::getLogNumber(const String & appender) const
        {
            int newIndex = -1;
            std::find_if(indexToLoggerNames.cbegin(), indexToLoggerNames.cend(), [&newIndex, appName = appender](const LogData& logData)
            {
                ++newIndex;
                return logData.appenderName == appName;
            });
            return newIndex;
        }
        String XmlLogger::getLevel(int loggerNumber) const
        {
            String level;
            if (!levels[loggerNumber].empty())
            {
                level = levels[loggerNumber];
            }
            else if (!indexToLoggerNames[loggerNumber].logName.empty())
            {
                level = levels[this->getLogNumber(indexToLoggerNames[loggerNumber].appenderName)];
            }
            return level;
        }
        LogFilter Sys::Logging::XmlLogger::getLogFilter(int loggerNumber) const
        {
            return logsFilter[loggerNumber];
        }
        std::vector<String> Sys::Logging::XmlLogger::getImmediateLevels(int loggerNumber) const
        {
            return immLevels[loggerNumber];
        }
        XmlLogger::LogData::LogData(const String &appender, const String &logName) :appenderName(appender), logName(logName)
        {
        }
        XmlLogger::LogData::LogData(String &&appender, String &&logName) : appenderName(appender), logName(logName)
        {
        }
    }
}