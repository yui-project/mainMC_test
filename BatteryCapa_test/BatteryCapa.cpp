#include "BatteryCapa.h"
#include "Mcp3204.h"

BatteryCapa::BatteryCapa()
{
    float batteryCapa;
    // TODO 電源系にバッテリーの最大電圧を聞く
    float batteryMaxVolt;
}

float BatteryCapa::measure()
{
    batteryVolt = Mcp3204(3);
    // NOTE バッテリー電圧を最大値で割ったものを％に直す
    return batteryVolt;
}
//  NOTE:バッテリ保護を策定する関数はModeDecisionに乗っける