#include "GameThings.h"
#include "Bullet.h"
#include "GameStatistic.h"
//=================================================================================================================
#include <QtGlobal>
//=================================================================================================================
int GameThings::m_siCellSizeOfSide;
GameStatistic * GameThings::m_psGameStatistic;
//=================================================================================================================
void GameThings::SetPointerGameStatistic(GameStatistic * psGameStatistic)
{
    m_psGameStatistic = psGameStatistic;
}
//=================================================================================================================
GameStatistic * GameThings::GetPointerGameStatistic()
{
    return m_psGameStatistic;
}
//=================================================================================================================
int GameThings::GetCellSide()
{
    return m_siCellSizeOfSide;
}
//=================================================================================================================
void GameThings::SetCellSizeOfSide(const int &iCellSizeOfSide)
{
    m_siCellSizeOfSide = iCellSizeOfSide;
}
//=================================================================================================================
GameThings::GameThings(const int &iColumn, const int &iRow)
{
    m_iColumn = iColumn; m_iRow = iRow;
    m_iXdiplace = 0; m_iYdiplace = 0;
}
//=================================================================================================================
GameThings::~GameThings(){}
//=================================================================================================================
bool GameThings::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return true;
}
//=================================================================================================================
