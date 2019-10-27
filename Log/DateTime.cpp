#include "DateTime.h"
#include "CharUtilities.h"
#if defined(LINUX)
#include <alloca.h>
#endif
#include <algorithm>
namespace Sys
{
    namespace Logging
    {
#define MAX_COUNT   4
        class DateTimeWrapper
        {
        public:
            DateTimeWrapper();
            DateTimeWrapper(int year, int month, int day, int hour, int minute, int second, int millisecond);
            int getYear() const;
            int getMonth() const;
            int getDay() const;
            int getHour() const;
            int getMinute() const;
            int getSecond() const;
            int getMillisecond() const;
        private:
            int y;
            int m;
            int d;
            int h;
            int M;
            int s;
            int l;
        };
        int formatToString(UTF8 *str, const int value, const int count);
        int countLetter(const UTF8 * str, const char l);
        DateTimeWrapper getTimeFromNow(const std::chrono::time_point<std::chrono::system_clock> &currentTime);
        DateTime::DateTime() :time(std::chrono::system_clock::now())
        {
        }
        DateTime::~DateTime()
        {

        }
#define CREATE_PATTERN_CASE(letter,func)\
        case letter:\
        patternCount = countLetter(pattern + 1, letter) + 1;\
        digitCount = formatToString(curTempLocation, (func), patternCount);\
        pattern += patternCount;\
        l += digitCount;\
        break;

        UTF8 * DateTime::getData(const UTF8 * pattern) const
        {
            DateTimeWrapper time = getTimeFromNow(this->time);
            int patternCount;
            int digitCount;
            int l = 0;
            int patternL = strlen(pattern);
            UTF8 * temp = (UTF8*)alloca(patternL * MAX_COUNT * sizeof(UTF8) + 1);
            int curIndex = 0;
            while (*pattern != 0)
            {
                UTF8* curTempLocation = temp + curIndex * (MAX_COUNT * sizeof(UTF8) + 1);
                switch (*pattern)
                {
                    CREATE_PATTERN_CASE('d',time.getDay());
                    CREATE_PATTERN_CASE('M',time.getMonth());
                    CREATE_PATTERN_CASE('y',time.getYear());
                    CREATE_PATTERN_CASE('h',time.getHour());
                    CREATE_PATTERN_CASE('m',time.getMinute());
                    CREATE_PATTERN_CASE('s',time.getSecond());
                    CREATE_PATTERN_CASE('l',time.getMillisecond());
                default:
                    curTempLocation[0] = *pattern;
                    curTempLocation[1] = 0;
                    pattern++;
                    l++;
                    break;
                }
                curIndex++;
            }
            l++;
            UTF8* ret = new UTF8[l];
            ret[0] = 0;
            for (int i = 0; i < curIndex; i++)
            {
                strcat(ret, temp + (i * (MAX_COUNT * sizeof(UTF8) + 1)));
            }
            return ret;
        }
        int DateTime::getNumber() const
        {
            return 3;
        }
        int countLetter(const UTF8 * str, const char l)
        {
            int count = 0;
            while ((*str == l) && (*str != 0))
            {
                count++;
                str++;
            }
            return count;
        }
        // This method take the value to print and the number of times that the letter that represent the value apper and return a string of the value according to the count
        int formatToString(UTF8* str, const int value, const int count)
        {
            if (count > MAX_COUNT)
            {
                throw "Not implement";
            }
            int t = value;
            int digitCount = 0;
            int numberDigitCount;
            char num[4];
            while (t >= 10)
            {
                num[digitCount] = (t % 10) + '0';
                t /= 10;
                digitCount++;
            }
            num[digitCount] = t + '0';
            digitCount++;
            numberDigitCount = std::max(digitCount,count);
            if (count < digitCount)
            {
                str[digitCount] = 0;
                for (digitCount--, t = 0; digitCount >= 0; digitCount--, t++)
                {
                    str[t] = num[digitCount];
                }
            }
            else
            {
                str[count] = 0;
                t = count - digitCount;
                int t1 = 0;
                while (t1 < t)
                {
                    str[t1] = '0';
                    t1++;
                }
                for (digitCount--; t1 < count; t1++, digitCount--)
                {
                    str[t1] = num[digitCount];
                }
            }
            return numberDigitCount;
        }
        DateTimeWrapper getTimeFromNow(const std::chrono::time_point<std::chrono::system_clock> &currentTime)
        {
            auto timeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch());
            auto timeInMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());
            time_t time = std::chrono::system_clock::to_time_t(currentTime);
            auto currentTimeRounded = std::chrono::system_clock::from_time_t(time);
            if (currentTimeRounded > currentTime) {
                --time;
                currentTimeRounded -= std::chrono::seconds(1);
            }
            tm *calTime = localtime(&time);
            tm& values = *calTime;
            return DateTimeWrapper(values.tm_year + 1900, values.tm_mon + 1, values.tm_mday, values.tm_hour, values.tm_min, values.tm_sec, timeInMilliseconds.count() - timeInSeconds.count() * 1000);
        }
        DateTimeWrapper::DateTimeWrapper() :y(-1)
        {
        }
        DateTimeWrapper::DateTimeWrapper(int year, int month, int day, int hour, int minute, int second, int millisecond) : y(year), m(month), d(day), h(hour), M(minute), s(second), l(millisecond)
        {
        }
        int DateTimeWrapper::getYear() const
        {
            return y;
        }
        int DateTimeWrapper::getMonth() const
        {
            return m;
        }
        int DateTimeWrapper::getDay() const
        {
            return d;
        }
        int DateTimeWrapper::getHour() const
        {
            return h;
        }
        int DateTimeWrapper::getMinute() const
        {
            return M;
        }
        int DateTimeWrapper::getSecond() const
        {
            return s;
        }
        int DateTimeWrapper::getMillisecond() const
        {
            return l;
        }
    }
}
