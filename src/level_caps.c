#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "level_caps.h"
#include "pokemon.h"

const u16 sLevelCapFlagMap[][2] =
{
    {FLAG_BADGE01_GET, 16},
    {FLAG_DEFEATED_RIVAL_RUSTBORO, 20},
    {FLAG_BADGE02_GET, 25},
    {FLAG_BEAT_RIVAL_110, 32},
    {FLAG_DEFEATED_WALLY_MAUVILLE, 36},
    {FLAG_BADGE03_GET, 39},
    {FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, 44},
    {FLAG_BADGE04_GET, 48},
    {FLAG_BADGE05_GET, 50},
    {FLAG_RECEIVED_HM_FLY, 54},
    {FLAG_BADGE06_GET, 60},
    {FLAG_BADGE07_GET, 72},
    {FLAG_BADGE08_GET, 83},
    {FLAG_IS_CHAMPION, 100},
};

u8 GetCurrentLevelCap(void)
{
    u8 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

const u16 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
const u16 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

u16 GetSoftLevelCapExpValue(u8 level, u32 expValue)
{
    u8 levelDifference;
    u8 currentLevelCap = GetCurrentLevelCap();

    if (level >= currentLevelCap)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference >= ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[levelDifference];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
        levelDifference = currentLevelCap - level;
        if (levelDifference >= ARRAY_COUNT(sExpScalingDown))
            return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingDown) - 1]);
        else
            return expValue + (expValue / sExpScalingUp[levelDifference - 1]);
    }
}
