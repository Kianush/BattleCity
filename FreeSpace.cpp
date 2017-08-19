#include "FreeSpace.h"
//==================================================================================================================
#include "Bullet.h"
//===============================================================================================================
#include <QPainter>
//===============================================================================================================
FreeSpace::FreeSpace(const int &iColumn, const int &iRow) : StaticGameThings(iColumn, iRow)
{
}
//===============================================================================================================
FreeSpace::~FreeSpace()
{

}
//===============================================================================================================
void FreeSpace::Draw(QPainter *pPainter)
{
    Q_UNUSED(pPainter)
    QPen pen;
    pen.setWidth(0);
    QBrush Brush(QColor(200, 200, 200));
    pPainter->setPen(Qt::NoPen);
    pPainter->setBrush(Brush);
    pPainter->drawRect(m_iColumn*GetCellSide(), m_iRow*GetCellSide(), GetCellSide(), GetCellSide());
}
//===============================================================================================================
void FreeSpace::BulletHitHandler(Bullet * pBullet)
{
    Q_UNUSED(pBullet)
}
//===============================================================================================================
bool FreeSpace::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return true;
}
//===============================================================================================================
