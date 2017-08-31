#include "GameThings.h"
#include "Bullet.h"
#include "GameStatistic.h"
//=================================================================================================================
#include <QtGlobal>
#include <QGraphicsObject>
#include <QDeclarativeView>
//=================================================================================================================
int GameThings::m_siCellSizeOfSide;
GameStatistic * GameThings::m_psGameStatistic;
QDeclarativeView * GameThings::m_psMainDeclarativeView;
//=================================================================================================================
void GameThings::SetPointerGameStatistic(GameStatistic * psGameStatistic)
{
    m_psGameStatistic = psGameStatistic;
}
//=================================================================================================================
void GameThings::SetPointerMainDeclarativeView(QDeclarativeView * pMainDeclarativeView)
{
    m_psMainDeclarativeView = pMainDeclarativeView;
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
    m_iLiveHits = 0;
}
//=================================================================================================================
GameThings::~GameThings()
{
    if (nullptr != m_pQmlImage) {
        m_pQmlImage->setProperty("x", -GetCellSide());
        m_pQmlImage->setProperty("y", -GetCellSide());
        m_pQmlImage->setProperty("active", false);
    }
    m_pQmlImage = nullptr;
}
//=================================================================================================================
bool GameThings::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return true;
}
//=================================================================================================================
//QObject * GameThings::GetQmlImage()
//{
//    return m_pQmlImage;
//}
//=================================================================================================================
int GameThings::GetX() const
{
    return m_iColumn*GetCellSide() + m_iXdiplace;
}
//=================================================================================================================
int GameThings::GetY() const
{
    return m_iRow*GetCellSide() + m_iYdiplace;
}
//=================================================================================================================
void GameThings::Draw()
{
    if (nullptr != m_pQmlImage) {
        QString qstrImagePath = GetStringImage();
        if (m_pQmlImage->property("texture").toString() != qstrImagePath) {
            m_pQmlImage->setProperty("texture", qstrImagePath);
        }
        m_pQmlImage->setProperty("x", GetX());
        m_pQmlImage->setProperty("y", GetY());
        m_pQmlImage->setProperty("active", true);
    }
}
//=================================================================================================================
void GameThings::SetLiveHits(const int &iLiveHits)
{
    m_iLiveHits = iLiveHits;
}
//=================================================================================================================
int GameThings::GetLiveHits() const
{
    return m_iLiveHits;
}
//=================================================================================================================
void GameThings::DecrementLiveHits()
{
    m_iLiveHits--;
}
//=================================================================================================================
int GameThings::GetColumn() const
{
    return m_iColumn;
}
//=================================================================================================================
void GameThings::SetColumn(const int &iColumn)
{
    m_iColumn = iColumn;
}
//=================================================================================================================
int GameThings::GetRow() const
{
    return m_iRow;
}
//=================================================================================================================
void GameThings::SetRow(const int &iRow)
{
    m_iRow = iRow;
}
//=================================================================================================================
int GameThings::GetXdiplace() const
{
    return m_iXdiplace;
}
//=================================================================================================================
void GameThings::SetXdiplace(const int &iXdiplace)
{
    m_iXdiplace = iXdiplace;
}
//=================================================================================================================
int GameThings::GetYdiplace() const
{
    return m_iYdiplace;
}
//=================================================================================================================
void GameThings::SetYdiplace(const int &iYdiplace)
{
    m_iYdiplace = iYdiplace;
}
//=================================================================================================================
