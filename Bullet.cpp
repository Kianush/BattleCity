#include "Bullet.h"
//==================================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//==================================================================================================================
int Bullet::m_siNumberOfBullet = 0;
int Bullet::m_siBulletWidth;
int Bullet::m_siBulletHeight;
//==================================================================================================================
void Bullet::SetDimensionsOfBullet(const int &iWidth, const int &iHeight)
{
    m_siBulletWidth = iWidth;
    m_siBulletHeight = iHeight;
}
//==================================================================================================================
Bullet::Bullet(const int &iColumn, const int &iRow, const int &iXDiplace, const int &iYdiplace,
               const int &iVelosity, const Orientation &eOrientation) :
    DynamicGameThings(iColumn, iRow, iVelosity)
{
    m_iXdiplace = iXDiplace;
    m_iYdiplace = iYdiplace;
    m_eOrientation = eOrientation;
    m_bMarkToDelete = false;
    m_pParent = nullptr;
    QString qmlObjectName = "bullet_" + QString::number(m_siNumberOfBullet);
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
    m_siNumberOfBullet++;
    if (m_siNumberOfBullet > 255) {
        m_siNumberOfBullet = 0;
    }
}
//==================================================================================================================
Bullet::~Bullet()
{
}
//==================================================================================================================
void Bullet::Move(bool &bCellChange)
{
    bCellChange = false;
    switch (m_eOrientation) {
    case Left:
        m_iXdiplace -= m_iVelosity;
        break;
    case Right:
        m_iXdiplace += m_iVelosity;
        break;
    case Up:
        m_iYdiplace -= m_iVelosity;
        break;
    case Down:
        m_iYdiplace += m_iVelosity;
    default:
        break;
    }
    const int SIDE_SIZE = 40;
    if (m_iXdiplace >= SIDE_SIZE) {
        m_iColumn++;
        m_iXdiplace = m_iXdiplace % SIDE_SIZE;
        bCellChange = true;
        return;
    }
    if (m_iXdiplace <= -SIDE_SIZE) {
        m_iColumn--;
        m_iXdiplace = m_iXdiplace % SIDE_SIZE;
        bCellChange = true;
        return;
    }
    if (m_iYdiplace >= SIDE_SIZE) {
        m_iRow++;
        m_iYdiplace = m_iYdiplace % SIDE_SIZE;
        bCellChange = true;
        return;
    }
    if (m_iYdiplace <= -SIDE_SIZE) {
        m_iRow--;
        m_iYdiplace = m_iYdiplace % SIDE_SIZE;
        bCellChange = true;
        return;
    }
}
//==================================================================================================================
void Bullet::BulletHitHandler(Bullet * pBullet)
{
    Q_UNUSED(pBullet)
}
//==================================================================================================================
QString Bullet::GetStringImage() const
{
    QString qstrToReturn;
    static QString qstrArrayImages[4];
    qstrArrayImages[0] = "Images/bullet_nord.png";
    qstrArrayImages[1] = "Images/bullet_east.png";
    qstrArrayImages[2] = "Images/bullet_south.png";
    qstrArrayImages[3] = "Images/bullet_west.png";
    switch (m_eOrientation) {
        case Up:
            qstrToReturn = qstrArrayImages[0];
        break;
        case Right:
            qstrToReturn = qstrArrayImages[1];
        break;
        case Down:
            qstrToReturn = qstrArrayImages[2];
        break;
        case Left:
            qstrToReturn = qstrArrayImages[3];
        break;
        default:
        break;
    }
    return qstrToReturn;
}
//==================================================================================================================
int Bullet::GetX() const
{
    return m_iColumn*GetCellSide() + m_iXdiplace + GetCellSide()/2 - GetWidth()/2;
}
//==================================================================================================================
int Bullet::GetY() const
{
    return m_iRow*GetCellSide() + m_iYdiplace + + GetCellSide()/2 - GetHeight()/2;
}
//==================================================================================================================
bool Bullet::IsMarkedToDelete() const
{
    return m_bMarkToDelete;
}
//==================================================================================================================
void Bullet::MarkToDelete()
{
    m_bMarkToDelete = true;
}
//==================================================================================================================
void Bullet::SetParent(DynamicGameThings * pParent)
{
    m_pParent = pParent;
}
//==================================================================================================================
DynamicGameThings::Orientation Bullet::GetMoveOrientation() const
{
    return m_eOrientation;
}
//==================================================================================================================
int Bullet::GetWidth() const
{
    return m_siBulletWidth;
}
//==================================================================================================================
int Bullet::GetHeight() const
{
    return m_siBulletHeight;
}
//==================================================================================================================
