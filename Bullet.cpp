#include "Bullet.h"
//==================================================================================================================
#include <QPainter>
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
}
//==================================================================================================================
Bullet::~Bullet() {}
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
void Bullet::Draw(QPainter *pPainter)
{
    pPainter->setBrush(Qt::SolidPattern);
    pPainter->drawRect(m_iColumn*40 + m_iXdiplace + 20, m_iRow*40 + m_iYdiplace + 20, 5 ,5);
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
