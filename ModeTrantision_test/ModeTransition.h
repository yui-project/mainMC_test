#pragma once
#include "Arduino.h"
#include "Command.h"
#include "I2cFram.h"
#include "AntennaDeployment.h"

extern uint8_t HkData[27];
extern bool IsMode1;
extern bool IsMode2;
extern bool IsMode3;
extern bool IsMode4_1;
extern bool IsMode4_2;
extern bool IsMode4_3;
extern bool IsMode4_4;
extern bool IsMode4_5;

extern uint32_t EndTimeOfMode2;
extern bool IsDLdata;
extern int WaitingCommand;
extern bool IsShutDownedMission;



class ModeTransition
{
private:
I2cFram i2cFram;
Command command;
AntennaDeployment antennaDeployment;

#define MINUTE_30 18000

#define WEEK_1 100800
#define MONTH_1 432000

bool IsAlivePowerMc;



bool backupA_downlink_check;
bool backupB_downlink_check;
bool LoRaA_downlink_check;
bool LoRaB_downlink_check;
bool backupA_uplink_check;
bool backupB_uplink_check;
bool LoRaA_uplink_check;
bool LoRaB_uplink_check;

uint32_t EndTimeOfMode3 = 0;

bool mode2_endFlag = false;
bool mode3_endFlag = false;




//NOTE:共有Framにマイコン間グローバル変数を入れる為の変数
uint8_t Fram[14];

public:
  // NOTE:モード実行のクラス
  ModeTransition();
  void normal();
  int crisis(uint8_t modeCrisis);
};