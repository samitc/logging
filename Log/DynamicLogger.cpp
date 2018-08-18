#include "DynamicLogger.h"
#include <iostream>
#include "CharUtilities.h"
#if defined(WINDOWS)
#elif defined(LINUX)
#include <sys/inotify.h>
#include <unistd.h>
#include <aio.h>
#include <string.h>
#endif
namespace Sys
{
	namespace Logging
	{
		DynamicLogger::DynamicLogger(const char * fileName, ConcurrencyLevel level) : scanTh(&scanThread,this), Logger(level), name(fileName), xml(loadXml(fileName))
		{
			isExit.test_and_set(std::memory_order_relaxed);
			this->reloadConfig(xml, 0);
		}
        DynamicLogger::DynamicLogger(const char * fileName, int concurrencyLevel) : scanTh(&scanThread, this), Logger(concurrencyLevel), name(fileName), xml(loadXml(fileName))
        {
            isExit.test_and_set(std::memory_order_relaxed);
            this->reloadConfig(xml, 0);
        }
		DynamicLogger::~DynamicLogger()
		{
			isExit.clear(std::memory_order_relaxed);
			if (scanTh.joinable())
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
#if defined(WINDOWS)
				SetEvent(exitHandle);
#elif defined(LINUX)
#endif
				scanTh.join();
			}
		}
		XmlLogger DynamicLogger::loadXml(const char *fileName)
		{
			XmlLogger ret;
			ret.load(fileName);
			return ret;
		}
		bool comparechar(const char* p1, const char* p2, int n)
		{
			while (n-- >= 0 && *(p1++) == *(p2++));
			return n == -1;
		}
		String cs2s(const wchar_t* str)
		{
			int len = wcslen(str);
			char *ret = new char[len];
			wcstombs(ret, str, len);
			return String(ret, len);
		}
		void DynamicLogger::scanThread(DynamicLogger *logger)
		{
			const char* fileName = logger->name.c_str();
			const int sizeOfFileName = strlen(fileName);
			const char* p = fileName + sizeOfFileName - 1;
			while (*(--p) != '\\'&& p != fileName);
			char* folder;
			if (p == fileName)
			{
				folder = (char*)alloca((1024) * sizeof(char));
#if defined(WINDOWS)
				GetCurrentDirectoryA(1024 * sizeof(char), folder);
#elif defined(LINUX)
				getcwd(folder, 1024 * sizeof(char));
#endif
			}
			else
			{
				folder = (char*)alloca((p - fileName + 1) * sizeof(char));
				strcpy(folder, fileName, p - fileName);
			}
#if defined(WINDOWS)
			FILE_NOTIFY_INFORMATION strFileNotifyInfo[1024];
			OVERLAPPED overlapped;
			HANDLE hDirectory = CreateFileA(folder,
				FILE_LIST_DIRECTORY | GENERIC_READ,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				0,
				OPEN_EXISTING,
				FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
				0
			);
			ZeroMemory(&overlapped, sizeof overlapped);
			overlapped.hEvent = CreateEvent(NULL, true, false, "test");
			logger->exitHandle = overlapped.hEvent;
			do
			{
				ReadDirectoryChangesW(hDirectory, (LPVOID)&strFileNotifyInfo, sizeof(strFileNotifyInfo), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE, NULL, &overlapped, NULL);
				WaitForSingleObject(overlapped.hEvent, INFINITE);
				ResetEvent(overlapped.hEvent);
				if (!logger->isExit.test_and_set(std::memory_order_relaxed))
				{
					break;
				}
				FILE_NOTIFY_INFORMATION *info = strFileNotifyInfo;
				do
				{
					if (sizeOfFileName * 2 == info->FileNameLength&&comparechar(fileName, cs2s(info->FileName).c_str(), sizeOfFileName))
					{
						logger->reloadConfig(logger->loadXml(logger->name.c_str()), 0);
						break;
					}
					info = (FILE_NOTIFY_INFORMATION *)(((char*)info) + info->NextEntryOffset);
				} while (info->NextEntryOffset != 0);
			} while (logger->isExit.test_and_set(std::memory_order_relaxed));
			CloseHandle(hDirectory);
			CloseHandle(overlapped.hEvent);
#elif defined(LINUX)
			int notifyD = inotify_init();
			const int EVENT_SIZE = sizeof(inotify_event);
			const int EVENT_BUF_LEN = 1024 * (EVENT_SIZE + 16);
			char buffer[EVENT_BUF_LEN];
			aiocb cb;
			do
			{
				int folderD = inotify_add_watch(notifyD, logger->name.c_str(), IN_MODIFY);
				memset(&cb, 0, sizeof(cb));
				cb.aio_nbytes = EVENT_BUF_LEN;
				cb.aio_fildes = notifyD;
				cb.aio_offset = 0;
				cb.aio_buf = buffer;
				int i = 0;
				aio_read(&cb);
				bool isFinish = false;
				while (!isFinish)
				{
					if (!logger->isExit.test_and_set(std::memory_order_relaxed))
					{
						aio_cancel(notifyD, &cb);
						isFinish = true;
						break;
					}
					if (aio_error(&cb) != EINPROGRESS)
					{
						break;
					}
					std::this_thread::sleep_for(std::chrono::duration<int, std::ratio<1>>(1));
				}
				if (isFinish)
				{
					break;
				}
				int length = aio_return(&cb);
				while (i < length)
				{
					inotify_event *event = (inotify_event *)&buffer[i];
					logger->reloadConfig(logger->loadXml(logger->name.c_str()), 0);
					i += EVENT_SIZE + event->len;
				}
				inotify_rm_watch(notifyD, folderD);
			} while (logger->isExit.test_and_set(std::memory_order_relaxed));
			close(notifyD);
#endif
		}
	}
}