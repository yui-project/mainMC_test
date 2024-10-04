#pragma once
#include "Arduino.h"
class RealTimeClock{
private:

    //TODO #defineを使ってアドレスを管理したい
    const int RTC_add = 0x51;  //RTC8564NBのスレーブアドレス

    const int Control1_REG = 0x00;  ///RTC8564NBのレジスタマップ
    const int Control2_REG = 0x01;
    const int Seconds_REG = 0x02;
    const int Minites_REG = 0x03;
    const int Hours_REG = 0x04;
    const int Days_REG = 0x05;
    const int Weekdays_REG = 0x06;
    const int MonthsCentury_REG = 0x07;
    const int Years_REG = 0x08;
    const int MinuteAlarm_REG = 0x09;
    const int HourAlarm_REG = 0x0A;
    const int DayAlarm_REG = 0x0B;
    const int WeekdayAlarm_REG = 0x0C;
    const int CLKOUTfrequency_REG = 0x0D;
    const int Timercontorol_REG = 0x0E;
    const int Timer_REG = 0x0F;

    //void I2Cwrite_u8(uint8_t, uint8_t);
    //uint8_t BCDtoDec(uint8_t);//byteの方がいい？

    uint8_t RTC_data[7];  //データを格納する

    uint32_t total_minutes = 0;
    uint32_t total_minutes_hours = 0;
    uint32_t total_minutes_days = 0;
    uint32_t total_minutes_months = 0;
    uint32_t total_minutes_months_before = 0;
    uint32_t total_minutes_years = 0;
    uint32_t minute = 0;
    uint32_t day = 0;
    uint32_t month = 0;
    uint32_t year = 0;
    uint32_t months_days[12] = {0,31,28,31,30,31,30,31,31,30,31,30};//total用に一個ずつズレてる！（左から1月,2月とかではないことに注意）

public:
//NOTE:RTCを使用するためのクラス
void RTCsetup();
void I2Cwrite_u8(uint8_t reg_add, uint8_t data);
uint8_t BCDtoDec(uint8_t value);
void init();
uint32_t get();
};