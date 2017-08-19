#include "SpeedAlienPanzer.h"
#include "GameStatistic.h"
//=============================================================================================================
SpeedAlienPanzer::SpeedAlienPanzer(const int &iColumn, const int &iRow) : AlienPanzer(iColumn, iRow)
{
    SetVelosity(10);
    SetCost(200);
}
//=============================================================================================================
SpeedAlienPanzer::~SpeedAlienPanzer()
{

}
//=============================================================================================================
void SpeedAlienPanzer::SetStatistic()
{
    m_psGameStatistic->AddScope(GetCost());
    m_psGameStatistic->IncrementSpeedAliensKilled();
}
//=============================================================================================================
int SpeedAlienPanzer::GetTypicalVelosity() const
{
    return 2*(AlienPanzer::GetTypicalVelosity());
}
//=============================================================================================================
