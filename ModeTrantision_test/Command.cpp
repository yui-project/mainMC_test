#include "Command.h"
#include "Arduino.h"

Command::Command()
{
    // TODO 実装待ち
}

bool Command::execute(int subject)
{ // メインマイコンが受信側になった時のためのクラス
    switch (subject)
    { // 手打ちなの地味に間違えそうで怖い ★こっちがマスターで、後から下にコピペする
    case 1:
        // TODO このコマンドいる？
        return sendToPowerMC(subject);
    case 2:
        // TODO　このコマンドいる？
        return sendToPowerMC(subject);
        break;
    case 3:
        // TODO TSUKUTO時刻をメインマイコン側でどう持つかの検討と関数のそもそもの設計を見直す　冗長すぎるだろこれ

        Serial2.write(subject); // Serial2でコマンド番号を送信
        Serial2.flush();        // 送信完了待ち
        Serial2.write(0x0A);
        Serial2.flush();

        delay(1);
        digitalWrite(masterSelectPin, LOW);
        if (confirmationAck() == true)
        {
            Serial.println("SEND TSUKUTOTIME");
            // return powerMC.sendTsukutoTime(RTC.get());
            return powerMC.sendTsukutoTime(0);
        }
        else
        {
            return false;
        }
    case 4:
        // TODO TSUKUTO時刻をどう貰うか
        Serial2.write(subject); // Serial2でコマンド番号を送信
        Serial2.flush();        // 送信完了待ち
        Serial2.write(0x0A);
        Serial2.flush();

        digitalWrite(masterSelectPin, LOW);
        if (confirmationAck() == true)
        {
            Serial.println("GET TSUKUTOTIME");
            powerMC.receiveTsukutoTime();
            return true;
        }
        else
        {
            return false;
        }
    case 5:
        return sendToPowerMC(subject);
    case 6:
        return sendToPowerMC(subject);
    case 7:
        return sendToPowerMC(subject);
    case 8:
        return sendToPowerMC(subject);
    case 9:
        return sendToPowerMC(subject);
    case 10:
        return sendToPowerMC(subject);
    case 11:
        return sendToPowerMC(subject);
    case 12:
        return sendToPowerMC(subject);
    case 13:
        return sendToPowerMC(subject);
    case 14:
        return sendToPowerMC(subject);
    case 15:
        return sendToPowerMC(subject);
    case 16:
        // NOTE:メインマイコン停止予告　ACK送信だけにしとく
        digitalWrite(masterSelectPin, HIGH);
        Serial2.write(ACK);
        return true;
    case 17:
        return sendToPowerMC(subject);
    case 18:
        return sendToPowerMC(subject);
    case 19:
        Serial2.write(subject); // Serial2でコマンド番号を送信
        Serial2.flush();        // 送信完了待ち
        Serial2.write(0x0A);
        Serial2.flush();

        digitalWrite(masterSelectPin, LOW);
        if (confirmationAck() == true)
        {
            delay(1);
            // hk.getHKData();
            delay(1);
            digitalWrite(masterSelectPin, HIGH);
            Serial2.write(ACK);

            Serial.println("GEt HKdata");
            for (int i = 0; i < 27; i++)
            {
                Serial.println(hkData[i]);
            }

            return true;
        }
        else
        {
            return false;
        }

        return true;
    case 20:
        // TODO 電力監視データ　実装待ち
        break;
    case 21:
        // TODO 姿勢監視データ　実装待ち
        break;
    case 22:
        // TODO HKデータ保存　実装待ち　このコマンドいる？
        break;
    case 23:
        // TODO HKデータ読み込み　実装待ち　このコマンドいる？
        break;
    case 24:
        return sendToPowerMC(subject);
    case 25:
        return sendToPowerMC(subject);
    case 33:
        return true;
    case 34:
        return true;
    case 35:
        return true;
    case 36:
        return true;
    case 37:
        return true;
    case 38:
        return true;
    case 39:
        Serial.println("GET FRAM");
        for (int i = 0; i < 14; i++)
        {
            Fram[i] = I2cFram.read(0x56, i);
        }

        mode2_endTime = (uint32_t)((((uint32_t)Fram[0] << 16) & 0x00FF0000) | (((uint32_t)Fram[1] << 8) & 0x0000FF00) | (((uint32_t)Fram[2] << 0) & 0x000000FF));
        mode3_endTime = (uint32_t)((((uint32_t)Fram[3] << 16) & 0x00FF0000) | (((uint32_t)Fram[4] << 8) & 0x0000FF00) | (((uint32_t)Fram[5] << 0) & 0x000000FF));
        backupA_downlink_check = (bool)((Fram[6] & 0xFF) >> 7);
        backupB_downlink_check = (bool)((Fram[6] & 0x7F) >> 6);
        LoRaA_downlink_check = (bool)((Fram[6] & 0x3F) >> 5);
        LoRaB_downlink_check = (bool)((Fram[6] & 0x1F) >> 4);
        backupA_uplink_check = (bool)((Fram[6] & 0x0F) >> 3);
        backupB_uplink_check = (bool)((Fram[6] & 0x07) >> 2);
        LoRaA_uplink_check = (bool)((Fram[6] & 0x03) >> 1);
        LoRaB_uplink_check = (bool)((Fram[6] & 0x01) >> 0);
        backupA_downlink_no = (bool)((Fram[7] & 0xFF) >> 7);
        backupB_downlink_no = (bool)((Fram[7] & 0x7F) >> 6);
        LoRaA_downlink_no = (bool)((Fram[7] & 0x3F) >> 5);
        LoRaB_downlink_no = (bool)((Fram[7] & 0x1F) >> 4);
        backupA_uplink_no = (bool)((Fram[7] & 0x0F) >> 3);
        backupB_uplink_no = (bool)((Fram[7] & 0x07) >> 2);
        LoRaA_uplink_no = (bool)((Fram[7] & 0x03) >> 1);
        LoRaB_uplink_no = (bool)((Fram[7] & 0x01) >> 0);
        mode2_endFlag = (bool)((Fram[8] & 0x03) >> 1);
        mode3_endFlag = (bool)((Fram[8] & 0x01) >> 0);
        cam_parameter = Fram[9];
        ad_parameter = Fram[10];
        TSUKUTO_time = (uint32_t)((((uint32_t)Fram[11] << 16) & 0x00FF0000) | (((uint32_t)Fram[12] << 8) & 0x0000FF00) | (((uint32_t)Fram[13] << 0) & 0x000000FF));

        Serial.print(mode2_endTime);
        Serial.print(" ");
        Serial.print(mode3_endTime);
        Serial.print(" ");
        Serial.print(backupA_downlink_check);
        Serial.print(" ");
        Serial.print(backupB_downlink_check);
        Serial.print(" ");
        Serial.print(LoRaA_downlink_check);
        Serial.print(" ");
        Serial.print(LoRaB_downlink_check);
        Serial.print(" ");
        Serial.print(backupA_uplink_check);
        Serial.print(" ");
        Serial.print(backupB_uplink_check);
        Serial.print(" ");
        Serial.print(LoRaA_uplink_check);
        Serial.print(" ");
        Serial.print(LoRaB_uplink_check);
        Serial.print(" ");
        Serial.print(backupA_downlink_no);
        Serial.print(" ");
        Serial.print(backupB_downlink_no);
        Serial.print(" ");
        Serial.print(LoRaA_downlink_no);
        Serial.print(" ");
        Serial.print(LoRaB_downlink_no);
        Serial.print(" ");
        Serial.print(backupA_uplink_no);
        Serial.print(" ");
        Serial.print(backupB_uplink_no);
        Serial.print(" ");
        Serial.print(LoRaA_uplink_no);
        Serial.print(" ");
        Serial.print(LoRaB_uplink_no);
        Serial.print(" ");
        Serial.print(mode2_endFlag);
        Serial.print(" ");
        Serial.print(mode3_endFlag);
        Serial.print(" ");
        Serial.print(cam_parameter);
        Serial.print(" ");
        Serial.print(ad_parameter);
        Serial.print(" ");
        Serial.println(TSUKUTO_time);
        return true;
    case 40:

        Fram[0] = (uint8_t)((mode2_endTime & 0x00FF0000) >> 16);
        Fram[1] = (uint8_t)((mode2_endTime & 0x0000FF00) >> 8);
        Fram[2] = (uint8_t)((mode2_endTime & 0x000000FF) >> 0);
        Fram[3] = (uint8_t)((mode3_endTime & 0x00FF0000) >> 16);
        Fram[4] = (uint8_t)((mode3_endTime & 0x0000FF00) >> 8);
        Fram[5] = (uint8_t)((mode3_endTime & 0x000000FF) >> 0);
        Fram[6] = (uint8_t)((((uint8_t)backupA_downlink_check << 7) & 0xFF) | (((uint8_t)backupB_downlink_check << 6) & 0x7F) | (((uint8_t)LoRaA_downlink_check << 5) & 0x3F) | (((uint8_t)LoRaB_downlink_check << 4) & 0x1F) | (((uint8_t)backupA_uplink_check << 3) & 0x0F) | (((uint8_t)backupB_uplink_check << 2) & 0x07) | (((uint8_t)LoRaA_uplink_check << 1) & 0x03) | (((uint8_t)LoRaB_uplink_check << 0) & 0x01));
        Fram[7] = (uint8_t)((((uint8_t)backupA_downlink_no << 7) & 0xFF) | (((uint8_t)backupB_downlink_no << 6) & 0x7F) | (((uint8_t)LoRaA_downlink_no << 5) & 0x3F) | (((uint8_t)LoRaB_downlink_no << 4) & 0x1F) | (((uint8_t)backupA_uplink_no << 3) & 0x0F) | (((uint8_t)backupB_uplink_no << 2) & 0x07) | (((uint8_t)LoRaA_uplink_no << 1) & 0x03) | (((uint8_t)LoRaB_uplink_no << 0) & 0x01));
        Fram[8] = (uint8_t)(((mode2_endFlag << 1) & 0x03) | ((mode3_endFlag << 0 & 0x01)));
        Fram[9] = cam_parameter;
        Fram[10] = ad_parameter;
        Fram[11] = (uint8_t)((TSUKUTO_time & 0x00FF0000) >> 16);
        Fram[12] = (uint8_t)((TSUKUTO_time & 0x0000FF00) >> 8);
        Fram[13] = (uint8_t)((TSUKUTO_time & 0x000000FF) >> 0);

        for (int i = 0; i < 14; i++)
        {
            I2cFram.write(0x56, i, Fram[i]);
            // Serial.print(Fram[i]);Serial.print(" ");
        }
        Serial.println("TEST COMPLETE");
        delay(4000);
        return true;
    case 41:
        Serial.println("RESET FRAM");
        I2cFram.reset(0x56, 0x57, 0x00);
        return true;
        /*case 42:
            return sendToMission(subject);
        case 43:
            return sendToMission(subject);
        case 44:
            return sendToMission(subject);
        case 45:
            return sendToMission(subject);
        case 46:
            return sendToMission(subject);
        case 47:
            return sendToMission(subject);
        case 48:
            return sendToMission(subject);
        case 49:
            return sendToMission(subject);
        case 50:
            return sendToMission(subject);
        case 51:
            return sendToMission(subject);
        case 52:
            return sendToMission(subject);
        case 53:
            return sendToMission(subject);
        case 54:
            return sendToMission(subject);
        case 55:
            return sendToMission(subject);
        case 56:
            return sendToMission(subject);
        case 57:
            return sendToMission(subject);
        default:
            return mission.disposal();*/
    }
    // Serial2.write(ACK); // コマンド終わったらACKを送る？←受信側としてやること確認
}

bool Command::sendToPowerMC(int subject)
{ // メインマイコンが送信側になった時のためのクラス
    // subjectをPowerMCに送って、ACKが返ってきたらtrue、それ以外が返ってきたらfalseを返す。
    pinMode(masterSelectPin, OUTPUT);
    digitalWrite(masterSelectPin, HIGH); // mainMCをマスターに設定
    bool communicationStatus1;
    bool communicationStatus2;
    Serial2.write(subject); // Serial2でコマンド番号を送信
    Serial2.flush();        // 送信完了待ち
    Serial2.write(0x0A);
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    if (confirmationAck() == true)
        return true;
    else
        return false;
    // communicationStatus1 = confirmationAck(); // ACK1の状態確認
    Serial.println(communicationStatus1);
    if (communicationStatus1 == ACK)
    { // ACK1がACKやった時
        int packetSizeValue = packetSize(subject);
        if (packetSizeValue > 0 && packetSizeValue < 999999)
        {
            // ここにパケットの送信作業を入れる（★分割してpacketNo割り振る作業はどこでする？←誤り検出訂正やパケットNoを載せないといけない？←受信するのも合わせなきゃだし大変そう　分割されたcontentsをそれぞれ送る作業とかはpacketSizeValueを元にfor文とか組めばいい）
            return confirmationAck(); // ACK2の状態確認
        }
        else if (packetSizeValue == 999999)
        {
            return false; // packetSize()からエラーコードが吐かれた時（多分未決定コマンドが入った時や未登録の時）はfalseを返す　★これでいい？
        }
        else
        {                // packetSize(subject)==0の時
            return true; // ACK1のみのやつは、ACK2を問答無用でtrueにする
        }
    }
    else
    { // ACK1がNAKやった時
        return false;
    }
}

bool Command::confirmationAck()
{ // ACKが返ってきたらtrue,それ以外だとfalse
    /*if (Serial2.available() > 0 && Serial2.read() == ACK)
        return true;
    return false;*/
    int counter = 0;
    // TODO 脱出用の条件を作る必要あり
    while (Serial2.available() > 0)
    {
        digitalWrite(masterSelectPin, LOW);
        // Serial.println("WAITING!!!!!");
        uint8_t ackOrNck = Serial2.read();
        if (ackOrNck == ACK)
        {
            return true;
        }
        else
        {
            // return false;
        }

        counter++;

        if (counter > 100)
        {
            Serial.println("STOP WAITING!!!");
            return false;
        }

        delay(10);
    }
}

int Command::packetSize(int subject)
{ // パケットの送受信サイズを返す関数
    int pSVal = 0;
    switch (subject)
    { // 手打ちなの地味に間違えそうで怖い
    case 1:
        pSVal = 0;
        break;
    case 2:
        pSVal = 0;
        break;
    case 3:
        pSVal = 3;
        break;
    case 4:
        pSVal = 3;
        break;
    case 5:
        pSVal = 0;
        break;
    case 6:
        pSVal = 0;
        break;
    case 7:
        pSVal = 0;
        break;
    case 8:
        pSVal = 0;
        break;
    case 9:
        pSVal = 0;
        break;
    case 10:
        pSVal = 0;
        break;
    case 11:
        pSVal = 0;
        break;
    case 12:
        pSVal = 0;
        break;
    case 13:
        pSVal = 0;
        break;
    case 14:
        pSVal = 0;
        break;
    case 15:
        pSVal = 0;
        break;
    case 16:
        pSVal = 0;
        break;
    case 17:
        pSVal = 0;
        break;
    case 18:
        pSVal = 0;
        break;
    case 19:
        pSVal = 35;
        break;
    case 20:
        pSVal = 43;
        break;
    case 21:
        pSVal = 27;
        break;
    case 22:
        pSVal = 26;
        break;
    case 23:
        pSVal = 26;
        break;
    case 24:
        pSVal = 0;
        break;
    case 25:
        pSVal = 0;
        break;
    case 33:
        pSVal = 1;
        break;
    case 34:
        pSVal = 0;
        break;
    case 35:
        pSVal = 0;
        break;
    case 36:
        pSVal = 0;
        break;
    case 37:
        pSVal = 0;
        break;
    case 38:
        pSVal = 0;
        break;
    case 39:
        pSVal = 999999; // 不明（未定？）
        break;
    case 40:
        pSVal = 35;
        break;
    case 41:
        pSVal = 27;
        break;
    case 42:
        pSVal = 1;
        break;
    case 43:
        pSVal = 1;
        break;
    case 44:
        pSVal = 0;
        break;
    case 45:
        pSVal = 0;
        break;
    case 46:
        pSVal = 0;
        break;
    case 47:
        pSVal = 0;
        break;
    case 48:
        pSVal = 999999; // 不明（未定？）
        break;
    case 49:
        pSVal = 7;
        break;
    case 50:
        pSVal = 999999; // 不明（未定？）
        break;
    case 51:
        pSVal = 999999; // 不明（未定？）
        break;
    case 52:
        pSVal = 999999; // 不明（未定？）
        break;
    case 53:
        pSVal = 999999; // 不明（未定？）
        break;
    default:
        pSVal = 999999; // エラーコード的な感じで「999999」を使っていく！（ここでは未登録コマンドが入った時）
        break;
    }
    return pSVal;
}

int Command::confirmationCommand() // パソコンのシリアルモニタから送信したsubject番号を取得
{
    if (Serial.available() > 0)
    {
        String receivedString = Serial.readStringUntil('\n');
        receivedString.trim();
        if (receivedString.length() > 2)
        {
            String receivedSubject = receivedString.substring(0, 2); // 2桁の値を取得する
            subjectNumber = receivedSubject.toInt();                 // int型に変換
        }
        else
        {
            subjectNumber = receivedString.toInt();
        }
        // TODO 現状地上局からサブジェクトナンバー以外に送ろうとしているのはPMDパラメータ、ADパラメータ、（TLE）、パラメータの仕様について確認取る
        return subjectNumber;
    }
    else
    {
        return 0;
    }
}

/*
[Kurokawa's MEMO]
1.データ送信を行わない、ほとんどのコマンドがACK1のみでPacketを伴わない。それ故に流れは「SubjectNumを送信→ACK1を受信→Receiver側で処理」で終了。
*/