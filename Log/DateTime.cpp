#include "DateTime.h"
#include <chrono>
namespace Sys
{
    namespace Logging
    {
        int countLetter(const UTF8 * str, const char l);
        DateTime::DateTime() :time(createTimeData::getTimeNow())
        {
        }
        DateTime::~DateTime()
        {

        }
        UTF8 * DateTime::getData(const UTF8 * pattern) const
        {
            int count;
            int l = 0;
            std::list<UTF8 *> str;
            UTF8* t;
            while (*pattern != 0)
            {
                switch (*pattern)
                {
                case 'd':
                    count = handlePattern(pattern + 1, str, time.getDay(), 'd');
                    pattern += count;
                    l += count;
                    break;
                case 'M':
                    count = handlePattern(pattern + 1, str, time.getMonth(), 'M');
                    pattern += count;
                    l += count;
                    break;
                case 'y':
                    count = handlePattern(pattern + 1, str, time.getYear(), 'y');
                    pattern += count;
                    l += count;
                    break;
                case 'h':
                    count = handlePattern(pattern + 1, str, time.getHour(), 'h');
                    pattern += count;
                    l += count;
                    break;
                case 'm':
                    count = handlePattern(pattern + 1, str, time.getMinute(), 'm');
                    pattern += count;
                    l += count;
                    break;
                case 's':
                    count = handlePattern(pattern + 1, str, time.getSecond(), 's');
                    pattern += count;
                    l += count;
                    break;
                case 'l':
                    count = handlePattern(pattern + 1, str, time.getMillisecond(), 'l');
                    pattern += count;
                    l += count;
                    break;
                default:
                    t = new UTF8[2];
                    t[0] = *pattern;
                    t[1] = 0;
                    str.push_back(t);
                    pattern++;
                    l++;
                    break;
                }
            }
            std::list<UTF8*>::iterator s = str.begin(), e = str.end();
            l++;
            UTF8* ret = new UTF8[l];
            ret[0] = 0;
            while (s != e)
            {
                strcat(ret, *s);
                delete[](*s);
                ++s;
            }
            return ret;
        }
        int DateTime::getNumber() const
        {
            return 3;
        }
        int DateTime::handlePattern(const UTF8 *pat, std::list<UTF8 *> &str, const int value, char letter) const
        {
            int count = countLetter(pat, letter) + 1;
            str.push_back(this->formatToString(value, count));
            return count;
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
        UTF8 * DateTime::formatToString(const int value, const int count) const
        {
            int t = value;
            int digitCount = 0;
            char num[4];
            while (t >= 10)
            {
                num[digitCount] = (t % 10) + '0';
                t /= 10;
                digitCount++;
            }
            num[digitCount] = t + '0';
            digitCount++;
            UTF8 * ret;
            if (count < digitCount)
            {
                ret = new UTF8[digitCount + 1];
                ret[digitCount] = 0;
                for (digitCount--, t = 0; digitCount >= 0; digitCount--, t++)
                {
                    ret[t] = num[digitCount];
                }
            }
            else
            {
                ret = new UTF8[count + 1];
                ret[count] = 0;
                t = count - digitCount;
                int t1 = 0;
                while (t1 < t)
                {
                    ret[t1] = '0';
                    t1++;
                }
                for (digitCount--; t1 < count; t1++, digitCount--)
                {
                    ret[t1] = num[digitCount];
                }
            }
            return ret;
        }
        DateTime::DateTimeWrapper DateTime::createTimeData::getTimeNow()
        {
            const auto currentTime = std::chrono::system_clock::now();
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
            return DateTimeWrapper(values.tm_year + 1900, values.tm_mon + 1, values.tm_mday, values.tm_hour, values.tm_min, values.tm_sec,timeInMilliseconds.count() - timeInSeconds.count() * 1000);
        }
        DateTime::DateTimeWrapper::DateTimeWrapper() :y(-1)
        {
        }
        DateTime::DateTimeWrapper::DateTimeWrapper(int year, int month, int day, int hour, int minute, int second, int millisecond) : y(year), m(month), d(day), h(hour), M(minute), s(second), l(millisecond)
        {
        }
        int DateTime::DateTimeWrapper::getYear() const
        {
            return y;
        }
        int DateTime::DateTimeWrapper::getMonth() const
        {
            return m;
        }
        int DateTime::DateTimeWrapper::getDay() const
        {
            return d;
        }
        int DateTime::DateTimeWrapper::getHour() const
        {
            return h;
        }
        int DateTime::DateTimeWrapper::getMinute() const
        {
            return M;
        }
        int DateTime::DateTimeWrapper::getSecond() const
        {
            return s;
        }
        int DateTime::DateTimeWrapper::getMillisecond() const
        {
            return l;
        }
    }
}
