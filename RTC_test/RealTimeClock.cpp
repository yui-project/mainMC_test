#include "RealTimeClock.h"
#include <Wire.h>
#include "Arduino.h"

void RealTimeClock::RTCsetup(){
  I2Cwrite_u8(Control1_REG, 0x00);  //STOP。時刻合わせをするときは、最初に時計を停止させる

  I2Cwrite_u8(Seconds_REG, 0x00);               //秒
  I2Cwrite_u8(Minites_REG, 0x00);               //分
  I2Cwrite_u8(Hours_REG, 0x00);                 //時
  I2Cwrite_u8(Days_REG, 0x01);                  //日
  I2Cwrite_u8(Weekdays_REG, 0x07);              //曜日
  I2Cwrite_u8(MonthsCentury_REG, 0x01 | 0x80);  //月。0x80は21世紀に設定するため
  I2Cwrite_u8(Years_REG, 0x01);                 //年

  I2Cwrite_u8(Control1_REG, 0x00);  //start.時刻合わせができたら時計をスタート
}

void RealTimeClock::I2Cwrite_u8(uint8_t reg_add, uint8_t data){
  Wire.beginTransmission(RTC_add);
  Wire.write(reg_add);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t RealTimeClock::BCDtoDec(uint8_t value){
  return ((value >> 4) * 10) + (value & 0x0F);
}

void RealTimeClock::init(){
  //NOTE:RTCの初期化
  Wire.begin();
  RTCsetup();
}

uint32_t RealTimeClock::get(){
  //NOTE:RTCから現在TSUKUTO時刻を取得
  Wire.beginTransmission(RTC_add);
  Wire.write(Seconds_REG);
  Wire.endTransmission();

  Wire.requestFrom(RTC_add, 7);
  for (int i = 0; i < 7; i++) {
    while (Wire.available() == 0) {}
    RTC_data[i] = Wire.read();
  }

  minute = BCDtoDec(RTC_data[1] & 0x7F);
  day = BCDtoDec(RTC_data[3] & 0x3F) - 1;
  month = BCDtoDec(RTC_data[5] & 0x1F);//ここだけ-1がないのは、month_daysをずらしているから。←そうしないと、月毎に日数違うのがややこしい
  year = BCDtoDec(RTC_data[6])-1;
  total_minutes_hours = (int)BCDtoDec(RTC_data[2] & 0x3F) * 60;
  total_minutes_days = day * 60 * 24;

  total_minutes_months_before = 0;

  for (int k = 0; k < month; k++){
    total_minutes_months_before += months_days[k];
  }

  total_minutes_months = (uint32_t) total_minutes_months_before * 24 * 60;
  total_minutes_years = year * 365 * 60 * 24;
  total_minutes = minute + total_minutes_hours + total_minutes_days + total_minutes_months + total_minutes_years;

  //delay(1000);

  return total_minutes;
}