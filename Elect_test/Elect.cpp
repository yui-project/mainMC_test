#include "Elect.h"
#include "Mcp3204.h"
#include "Arduino.h"

Elect::Elect()
{
}
// TODO ピン番号が一致しているかを確認する
// TODO A/DCのアナログ値の修正用の値を電源マイコンからもらう？
float Elect::getElectVolt(int CHx)
{
    return Mcp3204(CHx - 1) * volt3 / McpToAnalogNum;
}
float Elect::getElectCurrent(int CHx)
{ // 電流、消費電力の測定　ADCの電圧*ずれの比/抵抗値＊1000 電流センサ合計2個
    switch (CHx)
    {
    case 1:
        return getElectVolt(1) / register1 * fixMilinumber; // CH0
    case 2:
        return getElectVolt(2) / register2 * fixMilinumber; // CH1
    }
    return 0;
}
float Elect::getElectPower(int CHx)
{
    return getElectVolt(CHx - 1) * getElectCurrent(CHx - 1);
}

int Elect::cutElect(int CHx)
{
    // TODO 実装待ち
    // NOTE:電流大きすぎた箇所をシャットダウンする
    // NOTE:具体的な方法はコンポーネントごとに繋がっているMOSFETを制御する→システムブロック図に書いてある
}