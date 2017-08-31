#include "ExternalWall.h"
#include "Bullet.h"
//===============================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//===============================================================================================================
ExternalWall::ExternalWall(const int &iColumn, const int &iRow) : GameThings(iColumn, iRow)
{
    QString qmlObjectName = "c" + QString::number(iColumn) + "r" + QString::number(iRow);
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
}
//===============================================================================================================
QString ExternalWall::GetStringImage() const
{
    return QString("Images/external_wall.png");
}
//===============================================================================================================
ExternalWall::~ExternalWall()
{
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
