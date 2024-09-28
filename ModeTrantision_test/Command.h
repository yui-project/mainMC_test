#pragma once
#include "Arduino.h"
#include "CommunicationWithPowerMC.h"
#include "I2cFram.h"


#define ACK 0x06

extern bool counterForAntennaDeployment;
extern uint8_t hkData[27]; // 最終HKデータ格納用配列

class Command
{
private:
    CommunicationWithPowerMC powerMC;
    I2cFram I2cFram;

    uint8_t ackOrNak;
    int masterSelectPin = 26;
    int subjectNumber = 0;

    uint8_t Fram[14];

    uint32_t mode2_endTime = 1103456;
    uint32_t mode3_endTime = 1012345;

    bool backupA_downlink_check = true;
    bool backupB_downlink_check = true;
    bool LoRaA_downlink_check = true;
    bool LoRaB_downlink_check = true;
    bool backupA_uplink_check = true;
    bool backupB_uplink_check = true;
    bool LoRaA_uplink_check = true;
    bool LoRaB_uplink_check = true;

    bool backupA_downlink_no = false;
    bool backupB_downlink_no = false;
    bool LoRaA_downlink_no = false;
    bool LoRaB_downlink_no = false;
    bool backupA_uplink_no = false;
    bool backupB_uplink_no = false;
    bool LoRaA_uplink_no = false;
    bool LoRaB_uplink_no = false;

    bool mode2_endFlag = false;
    bool mode3_endFlag = false;

    uint8_t cam_parameter = 0;
    uint8_t ad_parameter = 0;

    uint32_t TSUKUTO_time = millis();

public:
    Command();
    bool execute(int subject);
    bool sendToPowerMC(int subject);
    bool confirmationAck();
    int packetSize(int subject);
    int confirmationCommand();
};
