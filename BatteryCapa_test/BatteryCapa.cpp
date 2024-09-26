#include "BatteryCapa.h"
#include "Mcp3204.h"

BatteryCapa::BatteryCapa()
{
}

float BatteryCapa::measure()
{
    return Mcp3204(2);
}
//  NOTE:バッテリ保護を策定する関数はModeDecisionに乗っける