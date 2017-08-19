#include "FlagPrize.h"
#include "Labyrinth.h"
#include "Bullet.h"
//================================================================================================================
#include <QPainter>
//================================================================================================================
FlagPrizePath FlagPrize::m_sFlagPrizePath;
//================================================================================================================
void FlagPrize::SetFlagPrizePath()
{
    QMatrix matrix;
    matrix.rotate(180);
    m_sFlagPrizePath.m_FlagPrizePath = matrix.map(m_sFlagPrizePath.m_FlagPrizePath);
}
//================================================================================================================
FlagPrize::FlagPrize(const int &iColumn, const int &iRow, Labyrinth * pLabyrinth) : Prize(iColumn, iRow)
{
    m_pLabyrinth = pLabyrinth;
}
//================================================================================================================
void FlagPrize::Draw(QPainter *pPainter)
{
    QPoint qpointTranslatedPosition = QPoint(m_iColumn*GetCellSide() + m_iXdiplace + GetCellSide()/2,
                                             m_iRow*GetCellSide() + m_iYdiplace + GetCellSide()/2);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    pPainter->setPen(pen);
    pPainter->setBrush(Qt::NoBrush);
    pPainter->drawPath(m_sFlagPrizePath.m_FlagPrizePath.translated(qpointTranslatedPosition));
}
//================================================================================================================
bool FlagPrize::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return false;
}
//================================================================================================================
void FlagPrize::BulletHitHandler(Bullet * pBullet)
{
    pBullet->MarkToDelete();
    MarkToDelete();
    GameOver();
}
//================================================================================================================
void FlagPrize::GameOver()
{
    m_pLabyrinth->DoGameOver();
}
//================================================================================================================
