//this file setting the keyword for the xml
#ifndef _XMLSETTING_H_
#define _XMLSETTING_H_
#define XML_VAL				"value"
#define XML_ROOT			"Log"
#define XML_LEVEL_CUSTOM	"level_custom"
#define	XML_SPECIFIC_LOGGER	"appender"
#define		XML_OUTPUT			"OutPutStream"//file//conole

#define		XML_FILE_LOC		"LoggerFile"
#define		XML_APPEND_TO_FILE	"AppendToFile"//true false
#define		XML_MAX_FILES		"maxFiles"
#define     XML_MAX_WAITING_LOGS    "maxWaitingLogs"
#define		STRRAM_NETWORK_ADDR	"address"
#define		STREAM_NETWORK_PORT	"port"
#define STREAM_NETWORK_PROTOCOL	"protocol"


#define		XML_MAX_LOG_SIZE	"maximumLogSize"//"10MB"
#define		XML_MAX_LOG_TIME	"maximumLogTime"//1s;m;h;d
#define		XML_PATTERN			"pattern"
#define		XML_FILTER				"filter"
#define				XML_FILTER_TYPE	"type"
#define				XML_FILTER_TYPE_TEXT	"contain text"
#define			XML_FILTER_MIN				"min level"
#define			XML_FILTER_MAX				"max level"
#define			XML_FILTER_TEXT			"text"
#define		XML_IMMEDIATE_WRITE	"ImmediateLogWrite"
#define			XML_IMMEDIATE_WRITE_LEVEL	"level"
#define		XML_LEVEL			"level"
#define	XML_LOGGER		"logger"
#define		XML_LEVEL					"level"
#define		XML_SPECIFIC_LOGGER_NAME	"appender name"

//XML_OUTPUT
#define STREAM_NAME_CONSOLE		"console"
#define STREAM_NAME_FILE		"file"
#define STREAM_NAME_NETWORK		"network"
#endif