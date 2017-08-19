#include "IronInternalWall.h"
#include "Bullet.h"
//===============================================================================================================
#include <QPainter>
//===============================================================================================================
IronInternalWall::IronInternalWall(const int &iColumn, const int &iRow) : ImplicitInternalWall(iColumn, iRow)
{

}
//===============================================================================================================
IronInternalWall::~IronInternalWall()
{

}
//===============================================================================================================
void IronInternalWall::Draw(QPainter *pPainter)
{
    QBrush theBrush(QColor(150, 150, 150), Qt::NoBrush);
    pPainter->setBrush(theBrush);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    pPainter->setPen(pen);
    pPainter->drawRect(m_iColumn*40 + m_iXdiplace, m_iRow*40 + m_iYdiplace,40,40);
    theBrush.setStyle(Qt::BrushStyle::SolidPattern);
    theBrush.setColor(Qt::black);
    pPainter->drawRect(m_iColumn*40 + m_iXdiplace + 5, m_iRow*40 + m_iYdiplace + 5,30,30);
}
//===============================================================================================================
void IronInternalWall::BulletHitHandler(Bullet * pBullet)
{
    pBullet->MarkToDelete();
}
//===============================================================================================================
