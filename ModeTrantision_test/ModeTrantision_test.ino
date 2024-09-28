// NOTE:9/2インテグレーションに向けて髙橋が書いたメインマイコンのコードである。いくらでも修正、編集おｋ

#include "Arduino.h"
#include "MP.h"

#include "AntennaDeployment.h"
#include "I2cFram.h"
#include "SPI.h"
#include "ModeTransition.h"
#include "IoExpander.h"
#include "Decoder.h"
#include "Command.h"

// NOTE:グローバル変数　メインマイコンフローチャートに準ずる 書き方気持ち悪かったら修正お願い
// TODO サブコア用に共有メモリにいれてもいいかもしれない
uint8_t hkData[27] = {0b00000000};
bool IsMode1;
bool IsMode2;
bool IsMode3;
bool IsMode4_1;
bool IsMode4_2;
bool IsMode4_3;
bool IsMode4_4;
bool IsMode4_5;
uint32_t EndTimeOfMode2 = 0;
uint32_t RadioSwitchTimeOfMode5_2 = 0;
uint32_t SwitchTimeToMode7_2 = 0;
uint32_t SwitchTimeToMode7_3 = 0;
uint32_t PreviousTimeOfSaveHKdata = 0;
uint32_t PreviousTimeOfGetHKdata = 0;
// TODO 前回実行されたモード用の変数を作る
bool IsDLdata;
int WaitingCommand;
bool IsShutDownedMission;
bool DlRadio = 1; // NOTE:1だったらLoRa、０だったらBackUpを使用している
bool UlRadio = 1;
bool InitialBatteryProtect = 0;
bool MediumBatteryProtect = 0;
bool LastBatteryProtect = 0;
bool PowerMCUncontrolled; // NOTE：電源マイコン通信断絶フラグ
bool MissionUncontrolled; // NOTE：ミッション部通信断絶フラグ

// NOTE:初回起動かどうかを判断するための変数
bool counterForInitialStartUp = false;

AntennaDeployment antennaDeployment;
I2cFram i2cFram;
ModeTransition modeTransition;
Command command;
IoExpander ex;

#define CS_A 19
#define CS_B 25
#define CS_C 22

#define LTCswitch 26
#define radioCore 1

void setup()
{
    Serial.begin(115200);
    Serial2.begin(57600, SERIAL_8E1);

    // NOTE サブコアの起動
    /*int ret = MP.begin(radioCore);
    if(ret < 0){
        Serial.println("radioCore begin fail!");
    }*/
    SPI5.begin();
    // NOTE:SPIの初期設定
    SPI5.setBitOrder(MSBFIRST);
    SPI5.setDataMode(SPI_MODE0);
    SPI5.setClockDivider(SPI_CLOCK_DIV128);

    // NOTE:トランシーバICに繋がっているピン
    pinMode(LTCswitch, OUTPUT);

    // NOTE:デコーダ用のピン
    pinMode(CS_A, OUTPUT);
    pinMode(CS_B, OUTPUT);
    pinMode(CS_C, OUTPUT);
    digitalWrite(CS_A, HIGH);
    digitalWrite(CS_B, HIGH);
    digitalWrite(CS_C, HIGH);

    //FIXME
    i2cFram.begin();
}

void loop()
{
    // NOTE:loop関数をモードマスターとみなす

    // NOTE:起動最初にディプロイメントスイッチの状態を確認→開放しているかどうかでMODEの値を変える
    // NOTE:マイコンに書き込む前にFRAMの初期化を別枠で済ませる必要がある
    if (counterForInitialStartUp == false)
    {
        //FIXME 代入になってる
        if (antennaDeployment.isOpen() == false) // NOTE:電源マイコンと逆で閉じていたらtrue、開いてたらfalseを出すため
        {
            // NOTE:送受信モード終了フラグの確認
            bool counterForConfirmationOfDelivery = (bool)((i2cFram.read(0x56, 8) & 0x01) >> 1);
            if (counterForConfirmationOfDelivery == true)
            {
                // NOTE:バス稼働モード終了フラグの確認
                bool counterForBusOperation = (bool)((i2cFram.read(0x56, 8) & 0x00) >> 0);
                if (counterForBusOperation == true)
                {
                    IsMode1 = false;
                    IsMode2 = false;
                    IsMode3 = false;
                    IsMode4_1 = true;
                    Serial.println("IN TO 4-1");
                }
                else
                {
                    IsMode1 = false;
                    IsMode2 = false;
                    IsMode3 = true;
                    IsMode4_1 = false;
                    Serial.println("IN TO 3");
                }
            }
            else
            {
                IsMode1 = false;
                IsMode2 = true;
                IsMode3 = false;
                IsMode4_1 = false;
                Serial.println("IN TO 2");
            }
        }
        else
        {
            IsMode1 = true;
            IsMode2 = false;
            IsMode3 = false;
            IsMode4_1 = false;
            Serial.println("IN TO 1");
        }
        counterForInitialStartUp = true;
    }

    // NOTE:モード遷移 ModeTransitionに実装
    modeTransition.normal();

    // NOTE:インテグレーション用 将来的には無線機で行う　この処理をサブコアで回したい
    digitalWrite(LTCswitch, HIGH);
    if (Serial2.available() > 0)
    {

        int subject = Serial2.read();
        Serial.println(subject);
    }
    int subject = command.confirmationCommand();
    if (subject > 0)
    {
        Serial.println(subject);
        if (command.execute(subject) == true)
        {
            Serial.println("Hello");
        }
        else
        {
            Serial.println("NO!!!");
        }
        subject = 0;
    }
}