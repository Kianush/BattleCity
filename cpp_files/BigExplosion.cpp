#include "BigExplosion.h"
//=================================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//=================================================================================================================
int BigExplosion::m_siNumberOfBigExplosion = 0;
//=================================================================================================================
BigExplosion::BigExplosion(const int &iColumn, const int &iRow) : GameThings(iColumn, iRow)
{
    m_iTick = 11;
    m_siNumberOfBigExplosion++;
    if (m_siNumberOfBigExplosion > 32) {
        m_siNumberOfBigExplosion = 0;
    }
    QString qmlObjectName = "big_explosion_" + QString::number(m_siNumberOfBigExplosion);
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
}
//=================================================================================================================
BigExplosion::~BigExplosion()
{

}
//=================================================================================================================
QString BigExplosion::GetStringImage() const
{
    QString qstrToReturn = "Images/big_explosion_11.png";
    if (m_iTick > 0 && m_iTick < 12) {
        qstrToReturn = "Images/bullet_explosion_" + QString::number(12 - m_iTick) + ".png";
    }
    return qstrToReturn;
}
//=================================================================================================================
void BigExplosion::BulletHitHandler(Bullet * pBullet)
{
    Q_UNUSED(pBullet)
}
//=================================================================================================================
int BigExplosion::GetWidth() const
{
    return 50;
}
//=================================================================================================================
int BigExplosion::GetHeight() const
{
    return 50;
}
//=================================================================================================================
void BigExplosion::DecrementTick()
{
    m_iTick--;
}
//=================================================================================================================
int BigExplosion::GetTick() const
{
    return m_iTick;
}
//=================================================================================================================
