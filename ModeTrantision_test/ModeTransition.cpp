#include "ModeTransition.h"

ModeTransition::ModeTransition()
{
}

// NOTE:各モードを処理する
void ModeTransition::normal()
{
  // NOTE:モード1
  if (IsMode1 == true)
  {
    // NOTE:RTC初期化は一回だけで良いので起動時のモード判断時に行えば良いと判断
    Serial.println("モード1");
    /*if (command.execute(24) == true)//NOTE:電源マイコン起動確認
    {
      if (command.execute(25) == true)//NOTE:モード1以降指示確認
      {
        Serial.println("モード2への移行");
        IsMode1 = false;
        IsMode2 = true;
        IsMode3 = false;
        IsMode4_1 = false;
        delay(5000);
        return 0;
      }
      else
      {
        // NOTE:モード2への移行までは30分なのでmillis関数を使えばいいのでは？
        if (millis() > 1800000)
        {
          IsMode1 = false;
          IsMode2 = true;
          IsMode3 = false;
          IsMode4_1 = false;
          return 0;
        }
        else
        {
          IsMode1 = true;
          IsMode2 = false;
          IsMode3 = false;
          IsMode4_1 = false;
          return 0;
        }
      }
    }
    else
    {*/
    IsAlivePowerMc = false;
    // TODO 電源マイコン再起動の実装
    if (millis() > MINUTE_30)
    {
      Serial.println("モード2への移行");
      delay(5000);
      IsMode1 = false;
      IsMode2 = true;
      IsMode3 = false;
      IsMode4_1 = false;
      return 0;
    }
    else
    {
      IsMode1 = true;
      IsMode2 = false;
      IsMode3 = false;
      IsMode4_1 = false;
      delay(1000);
      return 0;
    }
  }
  //  }

  // NOTE:モード2
  if (IsMode2 == true)
  {
    Serial.println("モード2");
    if (antennaDeployment.isOpen() == false) // NOTE:電源マイコンと逆で閉じていたらtrue、開いてたらfalseを出すため
    {
      Serial.println("アンテナ開く");
      antennaDeployment.startUp();
    }

    // TODO RF放射開始

    // NOTE:初回かどうかを判断する必要がある
    if (EndTimeOfMode2 == 0)
    {
      // NOTE:初めてモード２に入ったときから1週間後をモード2終了時刻に定める
      EndTimeOfMode2 = WEEK_1;

      // NOTE：共有Framに保存する
      Fram[0] = (uint8_t)((EndTimeOfMode2 & 0x00FF0000) >> 16);
      Fram[1] = (uint8_t)((EndTimeOfMode2 & 0x0000FF00) >> 8);
      Fram[2] = (uint8_t)((EndTimeOfMode2 & 0x000000FF) >> 0);
      for (int i = 0; i < 3; i++)
      {
        i2cFram.write(0x56, i, Fram[i]);
      }
    }

    // TODO 通信確認の実装 試験完了→共有FRAMのメモリをいじる形になる

    for (int i = 0; i < 14; i++)
    {
        Fram[i] = i2cFram.read(0x56, i);
    }

    backupA_downlink_check = (bool)((Fram[6] & 0xFF) >> 7);
    backupB_downlink_check = (bool)((Fram[6] & 0x7F) >> 6);
    LoRaA_downlink_check = (bool)((Fram[6] & 0x3F) >> 5);
    LoRaB_downlink_check = (bool)((Fram[6] & 0x1F) >> 4);
    backupA_uplink_check = (bool)((Fram[6] & 0x0F) >> 3);
    backupB_uplink_check = (bool)((Fram[6] & 0x07) >> 2);
    LoRaA_uplink_check = (bool)((Fram[6] & 0x03) >> 1);
    LoRaB_uplink_check = (bool)((Fram[6] & 0x01) >> 0);

    if (backupA_downlink_check == true && backupB_downlink_check == true && LoRaA_downlink_check == true && LoRaB_downlink_check == true && backupA_uplink_check == true && backupB_uplink_check == true && LoRaA_uplink_check == true && LoRaB_uplink_check == true)
    {
      // NOTE:モード3移行フラグを立てる
      Serial.println("モード3への移行");
      IsMode1 = false;
      IsMode2 = false;
      IsMode3 = true;
      IsMode4_1 = false;

      // NOTE:モード2終了フラグを立てる
      Serial.println("モード2終了");
      delay(5000);
      mode2_endFlag = true;
      mode3_endFlag = false;
      Fram[8] = (uint8_t)(((mode2_endFlag << 1) & 0x01) | ((mode3_endFlag << 0 & 0x00)));
      i2cFram.write(0x56, 8, Fram[8]);
      return 0;
    }
    else
    {
      if (millis() > EndTimeOfMode2)
      {
        // TODO モード5,6移行フラグを立てる
        Serial.println("モード3への移行");
        mode2_endFlag = true;
        mode3_endFlag = false;
        Fram[8] = (uint8_t)(((mode2_endFlag << 1) & 0x01) | ((mode3_endFlag << 0 & 0x00)));
        i2cFram.write(0x56, 8, Fram[8]);
        delay(5000);
        antennaDeployment.startUp();

        IsMode1 = false;
        IsMode2 = false;
        IsMode3 = true;
        IsMode4_1 = false;

        return 0;
      }
      else
      {
        IsMode1 = false;
        IsMode2 = true;
        IsMode3 = false;
        IsMode4_1 = false;

        return 0;
      }
    }
  }
  // NOTE:モード３
  if (IsMode3 == true)
  {
    Serial.println("モード3");
    if (EndTimeOfMode3 == 0)
    {
      // NOTE:初めてモード3に入ったときから1ヶ月をモード３終了時刻に定める
      EndTimeOfMode3 = MONTH_1;

      // NOTE：共有Framに保存する
      Fram[3] = (uint8_t)((EndTimeOfMode3 & 0x00FF0000) >> 16);
      Fram[4] = (uint8_t)((EndTimeOfMode3 & 0x0000FF00) >> 8);
      Fram[5] = (uint8_t)((EndTimeOfMode3 & 0x000000FF) >> 0);
      for (int i = 3; i < 6; i++)
      {
        i2cFram.write(0x56, i, Fram[i]);
      }
    }

    // TODO HKデータをバス部のみ取得
    // TODO HKデータの保存
    // TODO 通信確認とパラメータ設定

    if ((bool)((i2cFram.read(0x56, 8) & 0x00) >> 0) == true)
    {
      Serial.println("モード4への移行");
      delay(5000);
      IsMode1 = false;
      IsMode2 = false;
      IsMode3 = false;
      IsMode4_1 = true;
      return 0;
    }
    else
    {
      if (millis() > EndTimeOfMode3)
      {
        // NOTE:モード4移行フラグを立てる
        Serial.println("モード4への移行");
        IsMode1 = false;
        IsMode2 = false;
        IsMode3 = false;
        IsMode4_1 = true;

        // NOTE:モード3終了フラグを立てる
        Serial.println("モード3終了");
        delay(5000);
        mode2_endFlag = true;
        mode3_endFlag = true;
        Fram[8] = (uint8_t)(((mode2_endFlag << 1) & 0x01) | ((mode3_endFlag << 0 & 0x00)));
        i2cFram.write(0x56, 8, Fram[8]);

        return 0;
      }

      else
      {
        IsMode1 = false;
        IsMode2 = false;
        IsMode3 = true;
        IsMode4_1 = false;
        return 0;
      }
    }
  }

  // NOTE:モード４
  if (IsMode4_1 == true)
  {
    Serial.println("モード4");
    IsMode1 = false;
    IsMode2 = false;
    IsMode3 = false;
    IsMode4_1 = true;
    return 0;
  }
}

int ModeTransition::crisis(uint8_t modeCrisis)
{
  // TODO 実装待ち　危機モードを処理する 定常運用で使用する
}