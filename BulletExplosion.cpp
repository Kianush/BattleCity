#include "BulletExplosion.h"
//=================================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//=================================================================================================================
int BulletExplosion::m_siNumberOfBulletExplosion = 0;
//=================================================================================================================
BulletExplosion::BulletExplosion(const int &iColumn, const int &iRow,
                                 const int &iXDiplace, const int &iYdiplace) : GameThings(iColumn, iRow)
{
    SetXdiplace(iXDiplace);
    SetYdiplace(iYdiplace);
    m_iTick = 11;
    m_siNumberOfBulletExplosion++;
    if (m_siNumberOfBulletExplosion > 255) {
        m_siNumberOfBulletExplosion = 0;
    }
    QString qmlObjectName = "bullet_explosion_" + QString::number(m_siNumberOfBulletExplosion);
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
}
//=================================================================================================================
BulletExplosion::~BulletExplosion()
{

}
//=================================================================================================================
QString BulletExplosion::GetStringImage() const
{
    QString qstrToReturn = "Images/bullet_explosion_11.png";
    if (m_iTick > 0 && m_iTick < 12) {
        qstrToReturn = "Images/bullet_explosion_" + QString::number(12 - m_iTick) + ".png";
    }
    return qstrToReturn;
}
//=================================================================================================================
void BulletExplosion::BulletHitHandler(Bullet * pBullet)
{
    Q_UNUSED(pBullet)
}
//=================================================================================================================
void BulletExplosion::DecrementTick()
{
    m_iTick--;
}
//=================================================================================================================
int BulletExplosion::GetTick() const
{
    return m_iTick;
}
//=================================================================================================================
int BulletExplosion::GetWidth() const
{
    return 21;
}
//=================================================================================================================
int BulletExplosion::GetHeight() const
{
    return 21;
}
//=================================================================================================================
