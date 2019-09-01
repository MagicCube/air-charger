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

int DateTime::getFullYear() {
  return _localTime->tm_year + 1900;
}

int DateTime::getMonth() {
  return _localTime->tm_mon;
}

int DateTime::getDate() {
  return _localTime->tm_mday;
}

int DateTime::getDay() {
  return _localTime->tm_wday;
}

int DateTime::getHours() {
  return _localTime->tm_hour;
}

int DateTime::getMinutes() {
  return _localTime->tm_min;
}

int DateTime::getSeconds() {
  return _localTime->tm_sec;
}

time_t DateTime::gmtTime() {
  return _time;
}
