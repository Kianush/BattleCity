#include "GameStatistic.h"
#include <QDebug>
//=================================================================================================================
GameStatistic::GameStatistic()
{
   m_iSimpleAliensKilled = 0;
   m_iSpeedAliensKilled = 0;
   m_iScope = 0;
   m_iHiScope = 0;
   m_bGameResult = false;
}
//=================================================================================================================
void GameStatistic::Reset()
{
    m_iSimpleAliensKilled = 0;
    m_iSpeedAliensKilled = 0;
    m_iScope = 0;
    m_bGameResult = false;
}
//=================================================================================================================
GameStatistic::~GameStatistic()
{

}
//=================================================================================================================
void GameStatistic::AddScope(const int &iCost)
{
    m_iScope += iCost;
//qDebug()<<"m_iScope="<<m_iScope;
}
//=================================================================================================================
void GameStatistic::IncrementSimpleAliensKilled()
{
    m_iSimpleAliensKilled++;
}
//=================================================================================================================
void GameStatistic::IncrementSpeedAliensKilled()
{
    m_iSpeedAliensKilled++;
}
//=================================================================================================================
int GameStatistic::GetSimpleAliensKilled() const
{
    return m_iSimpleAliensKilled;
}
//=================================================================================================================
int GameStatistic::GetSpeedAliensKilled() const
{
    return m_iSpeedAliensKilled;
}
//=================================================================================================================
int GameStatistic::GetTotalKilled() const
{
    return (GetSimpleAliensKilled()+ GetSpeedAliensKilled());
}
//=================================================================================================================
int GameStatistic::GetScope() const
{
    return m_iScope;
}
//=================================================================================================================
int GameStatistic::GetHiScope() const
{
    return m_iHiScope;
}
//=================================================================================================================
void GameStatistic::SetHiScope(const int &iHiScope)
{
    if (iHiScope > m_iHiScope) {
        m_iHiScope = iHiScope;
    }
}
//=================================================================================================================
bool GameStatistic::IsGameVictory() const
{
    return m_bGameResult;
}
//=================================================================================================================
void GameStatistic::SetGameResult(const bool &bGameResult)
{
    m_bGameResult = bGameResult;
}
//=================================================================================================================
