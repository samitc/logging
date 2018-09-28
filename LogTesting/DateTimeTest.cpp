#include "gtest/gtest.h"
#include <thread>
#include <string>
#include "../Log/DateTime.h"
#include "../Log/LString.h"
using namespace Sys::Logging;
namespace LogTesting
{
    class DateTimeMock : public DateTime
    {
        public:
            const std::chrono::time_point<std::chrono::system_clock> getTime() const
            {
                return this->time;
            }
    };
    static tm *getLocalTime(auto time)
    {
        auto tTime = std::chrono::system_clock::to_time_t(time);
        auto localTime = localtime(&tTime);
    }
    TEST(DateTimeTest, testOnlyYear)
    {
        DateTimeMock dateTime;
        UTF8 *data = dateTime.getData("y");
        auto expected = std::to_string(getLocalTime(dateTime.getTime())->tm_year + 1900);
        EXPECT_STREQ(expected.c_str(), data);
        delete[]data;
    }
    TEST(DateTimeTest, testOnlyMonth)
    {
        DateTimeMock dateTime;
        UTF8 *data = dateTime.getData("M");
        auto expected = std::to_string(getLocalTime(dateTime.getTime())->tm_mon + 1);
        EXPECT_STREQ(expected.c_str(), data);
        delete[]data;
    }
    TEST(DateTimeTest, testOnlyDay)
    {
        DateTimeMock dateTime;
        UTF8 *data = dateTime.getData("d");
        auto expected = std::to_string(getLocalTime(dateTime.getTime())->tm_mday);
        EXPECT_STREQ(expected.c_str(), data);
        delete[]data;
    }
    TEST(DateTimeTest, testOnlyHour)
    {
        DateTimeMock dateTime;
        UTF8 *data = dateTime.getData("h");
        auto expected = std::to_string(getLocalTime(dateTime.getTime())->tm_hour);
        EXPECT_STREQ(expected.c_str(), data);
        delete[]data;
    }
    TEST(DateTimeTest, testOnlyMinute)
    {
        DateTimeMock dateTime;
        UTF8 *data = dateTime.getData("m");
        auto expected = std::to_string(getLocalTime(dateTime.getTime())->tm_min);
        EXPECT_STREQ(expected.c_str(), data);
        delete[]data;
    }
    TEST(DateTimeTest, testOnlySecond)
    {
        DateTimeMock dateTime;
        UTF8 *data = dateTime.getData("s");
        auto expected = std::to_string(getLocalTime(dateTime.getTime())->tm_sec);
        EXPECT_STREQ(expected.c_str(), data);
        delete[]data;
    }
}
