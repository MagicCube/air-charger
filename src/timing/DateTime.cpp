#include "DateTime.h"

#include "conf.h"
#include "log.h"

static time_t __currentTimeOffsetTicks = 0;

DateTime::DateTime(time_t time) {
  _time = time;
  _localTime = localtime(&_time);
}

DateTime::DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min,
                   uint8_t sec) {
  tm localTime;
  localTime.tm_year = year - 1900;
  localTime.tm_mon = month;
  localTime.tm_mday = day;
  localTime.tm_hour = hour;
  localTime.tm_min = min;
  localTime.tm_sec = sec;
  localTime.tm_isdst = -1;
  _time = mktime(&localTime);
  _localTime = localtime(&_time);
}

void DateTime::configTime(DateTime time) {
  __currentTimeOffsetTicks = time.gmtTime() - millis() / 1000;
}

time_t DateTime::now() {
  return __currentTimeOffsetTicks + millis() / 1000;
}

int DateTime::fullYear() {
  return _localTime->tm_year + 1900;
}

int DateTime::month() {
  return _localTime->tm_mon;
}

int DateTime::date() {
  return _localTime->tm_mday;
}

int DateTime::day() {
  return _localTime->tm_wday;
}

int DateTime::hours() {
  return _localTime->tm_hour;
}

int DateTime::minutes() {
  return _localTime->tm_min;
}

int DateTime::seconds() {
  return _localTime->tm_sec;
}

time_t DateTime::gmtTime() {
  return _time;
}
