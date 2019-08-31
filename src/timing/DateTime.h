#pragma once

#include <Arduino.h>
#include <time.h>

#include "conf.h"
#include "log.h"

static time_t currentTimeOffsetTicks = 0;

struct DateTime {
  DateTime(time_t time) {
    _time = time;
    _localTime = gmtime(&_time);
  }

  DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    tm localTime;
    localTime.tm_year = year - 1900;
    localTime.tm_mon = month;
    localTime.tm_mday = day;
    localTime.tm_hour = hour;
    localTime.tm_min = min;
    localTime.tm_sec = sec;
    localTime.tm_isdst = -1;
    _time = mktime(&localTime) - TIME_ZONE_OFFSET * 60;
    _localTime = localtime(&_time);
  }

  static void configTime(DateTime time) {
    currentTimeOffsetTicks = time.gmtTime() - millis() / 1000;
  }

  static time_t now() {
    return currentTimeOffsetTicks + millis() / 1000;
  }

  int getFullYear() {
    return _localTime->tm_year + 1900;
  }

  int getMonth() {
    return _localTime->tm_mon;
  }

  int getDate() {
    return _localTime->tm_mday;
  }

  int getDay() {
    return _localTime->tm_wday;
  }

  int getHours() {
    return _localTime->tm_hour;
  }

  int getMinutes() {
    return _localTime->tm_min;
  }

  int getSeconds() {
    return _localTime->tm_sec;
  }

  time_t gmtTime() {
    return _time;
  }

  time_t _time;
  struct tm *_localTime;
};
