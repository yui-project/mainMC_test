#pragma once
class BatteryCapa
{ // NOTE:バッテリ容量を測定するクラス　容量値からMODEを出力する関数を作る
private:
    float batteryVolt;
    float batteryCapa;
    float batteryMaxVolt;
public:
    BatteryCapa();
    float measure();
};
