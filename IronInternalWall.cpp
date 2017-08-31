#include "IronInternalWall.h"
#include "Bullet.h"
//===============================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//===============================================================================================================
IronInternalWall::IronInternalWall(const int &iColumn, const int &iRow) : ImplicitInternalWall(iColumn, iRow)
{
    QString qmlObjectName = "c" + QString::number(iColumn) + "r" + QString::number(iRow);
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
}
//===============================================================================================================
IronInternalWall::~IronInternalWall()
{
}
//===============================================================================================================
QString IronInternalWall::GetStringImage() const
{
    return QString("Images/iron_wall.png");
}
//===============================================================================================================
void IronInternalWall::BulletHitHandler(Bullet * pBullet)
{
    pBullet->MarkToDelete();
}
//===============================================================================================================
