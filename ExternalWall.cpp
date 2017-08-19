#include "ExternalWall.h"
#include "Bullet.h"
//===============================================================================================================
#include <QPainter>
//===============================================================================================================
ExternalWall::ExternalWall(const int &iColumn, const int &iRow) : StaticGameThings(iColumn, iRow)
{

}
//===============================================================================================================
ExternalWall::~ExternalWall()
{

}
//===============================================================================================================
void ExternalWall::Draw(QPainter *pPainter)
{
    QBrush theBrush(QColor(40, 40,40), Qt::SolidPattern);
    pPainter->setBrush(theBrush);
    pPainter->drawRect(m_iColumn*40 + m_iXdiplace, m_iRow*40 + m_iYdiplace,40,40);
}
//===============================================================================================================
void ExternalWall::BulletHitHandler(Bullet * pBullet)
{
    pBullet->MarkToDelete();
}
//===============================================================================================================
bool ExternalWall::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return false;
}
//===============================================================================================================
