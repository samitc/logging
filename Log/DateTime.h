#ifndef _DATETIME_H_
#define _DATETIME_H_
#include "IData.h"
#include <list>
namespace Sys
{
    namespace Logging
    {
        class PatternData;
        class DateTime :public IData
        {
        private:
            class DateTimeWrapper
            {
            public:
                DateTimeWrapper();
                DateTimeWrapper(int year, int month, int day, int hour, int minute, int second);
                int getYear() const;
                int getMonth() const;
                int getDay() const;
                int getHour() const;
                int getMinute() const;
                int getSecond() const;
            private:
                int y;
                int m;
                int d;
                int h;
                int M;
                int s;
            };
        public:
            DateTime();
            virtual ~DateTime();
            virtual UTF8 * getData(const UTF8 * pattern) const;
            int getNumber() const override;
        protected:
            DateTimeWrapper time;
        private:
            // This method take the value to print and the number of times that the letter that represent the value apper and return a string of the value according to the count
            UTF8 * formatToString(const int value, const int count) const;
            int handlePattern(const UTF8 *pat, std::list<UTF8 *> &str, const int value, char letter) const;
        public:
            class createTimeData
            {
            private:
            public:
                static DateTimeWrapper getTimeNow();
            };
        };
    }
}
#endif