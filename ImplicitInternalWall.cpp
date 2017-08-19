#include "ImplicitInternalWall.h"
#include "Bullet.h"
//===============================================================================================================
#include <QPainter>
//===============================================================================================================
ImplicitInternalWall::ImplicitInternalWall(const int &iColumn, const int &iRow) : StaticGameThings(iColumn, iRow)
{
    m_iLiveHits = 2;
}
//===============================================================================================================
ImplicitInternalWall::~ImplicitInternalWall()
{

}
//===============================================================================================================
void ImplicitInternalWall::Draw(QPainter *pPainter)
{
    QBrush theBrush;
    switch (m_iLiveHits) {
    case 2:
        theBrush = (QColor(200, 200, 200), Qt::SolidPattern);
        break;
    case 1:
        theBrush = (QColor(200, 200, 200), Qt::Dense1Pattern);
        break;
    case 0:
        theBrush = (QColor(200, 200, 200), Qt::Dense2Pattern);
        break;
    default:
        break;
    }
    pPainter->setBrush(theBrush);
    pPainter->drawRect(m_iColumn*40 + m_iXdiplace, m_iRow*40 + m_iYdiplace,40,40);
}
//===============================================================================================================
void ImplicitInternalWall::BulletHitHandler(Bullet * pBullet)
{
    pBullet->MarkToDelete();
    m_iLiveHits--;
}
//===============================================================================================================
bool ImplicitInternalWall::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return false;
}
//===============================================================================================================
