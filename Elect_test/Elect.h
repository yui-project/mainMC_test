#pragma once // NOTE:ヘッダーファイルの多重インクルードを防ぐ　HKデータクラスで使用
class Elect
{ // NOTE:メインマイコンからアクセスできるコンポーネントの消費電量を取得するためのクラス
private:
// TODO ピン番号の確認

    float volt3 = 3.3;
    int McpToAnalogNum = 4095;

    int fixMilinumber = 1000;

    // NOTE:電流センサについている抵抗値(mΩ)
    int register1 = 10;
    int register2 = 150;
    int register3 = 50;
    //TODO メインマイコンのA/DC4番ピンにはメインボード用のサーミスタがある。用途は決めてない
    int register4 = 50;

public:
    Elect();
    float getElectVolt(int CHx);
    float getElectCurrent(int CHx);
    float getElectPower(int CHx);
    int cutElect(int CHx);
};