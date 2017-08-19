#include "OurPanzer.h"
#include "Bullet.h"
//=================================================================================================================
#include <QPainter>
#include <QDebug>
#include <math.h>
//=================================================================================================================
int OurPanzer::m_siLiveCount;
//=================================================================================================================
void OurPanzer::SetLiveCount(const int &iLiveCount)
{
    m_siLiveCount = iLiveCount;
}
//=================================================================================================================
int OurPanzer::GetLiveCount()
{
    return m_siLiveCount;
}
//=================================================================================================================
OurPanzer::OurPanzer(const int &iColumn, const int &iRow) :
    AlienPanzer(iColumn, iRow)
{
    m_eOrientation = Up;
    m_iVelosity = 0;
    m_bStoping = false;
    m_bIsShooting = false;
}
//=================================================================================================================
void OurPanzer::SetOrientation(const DynamicGameThings::Orientation &eOrientation)
{
    if (eOrientation != m_eOrientation) {
        m_eOrientation = eOrientation;
        int iColumn, iRow, iXdiplace, iYdiplace;
        RecalculatePosition(iColumn, iRow, iXdiplace, iYdiplace);
        if (!(m_iColumn == iColumn && iRow != m_iRow)) {
            switch (m_eOrientation) {
                case Left:
                case Right:
                    m_iYdiplace = 0;
                break;
                case Up:
                case Down:
                    m_iXdiplace = 0;
                break;
            default:
                break;
            }
        }
    }
}
//=================================================================================================================
OurPanzer::~OurPanzer()
{
    m_siLiveCount--;
}
//=================================================================================================================
void OurPanzer::Draw(QPainter *pPainter)
{
    QPen thePen;
    thePen.setWidth(2);
    thePen.setColor(Qt::darkGreen);
    pPainter->setPen(thePen);
    QPoint qpointTranslatedPosition = QPoint(m_iColumn*40 + m_iXdiplace + 20, m_iRow*40 + m_iYdiplace + 20);
    pPainter->setBrush(Qt::NoBrush);
    switch (m_eOrientation) {
        case Left:
            pPainter->drawPath(m_sAlienPainterPathLeft.m_AlienPanzerPainterPath.translated(qpointTranslatedPosition));
            break;
        case Right:
            pPainter->drawPath(m_sAlienPainterPathRight.m_AlienPanzerPainterPath.translated(qpointTranslatedPosition));
            break;
        case Up:
            pPainter->drawPath(m_sAlienPainterPathUp.m_AlienPanzerPainterPath.translated(qpointTranslatedPosition));
            break;
        case Down:
            pPainter->drawPath(m_sAlienPainterPathDown.m_AlienPanzerPainterPath.translated(qpointTranslatedPosition));
            break;
        default:
            break;
    }
}
//=================================================================================================================
int OurPanzer::GetMyCodeOfBullet() const
{
    return (m_siCodeOwnerOfBullet - 1);
}
//=================================================================================================================
Bullet * OurPanzer::Shoot()
{
    int iColumnBullet, iRowBullet, iXdiplaceBullet, iYdiplaceBullet;
    RecalculatePosition(iColumnBullet, iRowBullet, iXdiplaceBullet, iYdiplaceBullet);
    Bullet * pToReturn = new Bullet(iColumnBullet, iRowBullet, iXdiplaceBullet, iYdiplaceBullet, 20, m_eOrientation);
    pToReturn->SetCodeOwner(GetMyCodeOfBullet());
    pToReturn->SetParent(this);
    m_bIsShooting = true;
    return pToReturn;
}
//=================================================================================================================
void OurPanzer::BulletHitHandler(Bullet * pBullet)
{
    QPoint qpointTranslatedPosition = QPoint(m_iColumn*40 + m_iXdiplace + 20, m_iRow*40 + m_iYdiplace + 20);
    QPainterPath thePainterPath;
    switch (m_eOrientation) {
        case Left:
            thePainterPath = m_sAlienPainterPathLeft.m_AlienPanzerPainterPath.translated(qpointTranslatedPosition);
            break;
        case Right:
            thePainterPath = m_sAlienPainterPathRight.m_AlienPanzerPainterPath.translated(qpointTranslatedPosition);
            break;
        case Up:
            thePainterPath = m_sAlienPainterPathUp.m_AlienPanzerPainterPath.translated(qpointTranslatedPosition);
            break;
        case Down:
            thePainterPath = m_sAlienPainterPathDown.m_AlienPanzerPainterPath.translated(qpointTranslatedPosition);
            break;
        default:
            break;
    }
    QRectF theRect = thePainterPath.boundingRect();
    int x_begin = theRect.left();
    int x_end = theRect.left()+theRect.width();
    int y_begin = theRect.top();
    int y_end = theRect.top() + theRect.height();
    int x_bullet_begin = pBullet->GetColumn()*GetCellSide() + pBullet->GetXdiplace() + GetCellSide()/2;
    int x_bullet_end = x_bullet_begin + 5;
    int y_bullet_begin = pBullet->GetRow()*GetCellSide() + pBullet->GetYdiplace() + GetCellSide()/2;
    int y_bullet_end = y_bullet_begin +5;
    bool bIsHitting = false;
    switch (pBullet->GetMoveOrientation()) {
    case Left:
    case Right:
        if ((y_bullet_begin >= y_begin && y_bullet_begin <= y_end) ||
            (y_bullet_end >= y_begin && y_bullet_end <= y_end)) {
            bIsHitting = true;
        }
        break;
    case Up:
    case Down:
        if ((x_bullet_begin >= x_begin && x_bullet_begin <= x_end) ||
            (x_bullet_end >= x_begin && x_bullet_end <= x_end)) {
            bIsHitting = true;
        }
        break;
    default:
        break;
    }

    if (this != pBullet->GetPointerParent() && bIsHitting) {
        pBullet->MarkToDelete();
    }
    if (GetMyCodeOfBullet() != pBullet->GetCodeOwner() && bIsHitting) {
        m_iLiveHits--;
        pBullet->MarkToDelete();
        if (m_iLiveHits < 0) {
            MarkToDelete();
        }
    }
}
//=================================================================================================================
void OurPanzer::Move(bool &bCellChange)
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

    int iColumn, iRow, iXdiplace, iYdiplace;
    RecalculatePosition(iColumn, iRow, iXdiplace, iYdiplace);
    if (!(iColumn == m_iColumn && iRow == m_iRow)) {
        m_iColumn = iColumn;
        m_iRow = iRow;
        m_iXdiplace = iXdiplace;
        m_iYdiplace = iYdiplace;
        bCellChange = true;
    }
}
//=================================================================================================================
bool OurPanzer::IsShooting() const
{
    return m_bIsShooting;
}
//=================================================================================================================
void OurPanzer::UnsetShootingSign()
{
    m_bIsShooting = false;
}
//=================================================================================================================
QRectF OurPanzer::GetBoundingRect()
{
    QPoint qpointTranslatedPosition = QPoint(m_iColumn*GetCellSide() + m_iXdiplace + GetCellSide()/2,
                                             m_iRow*GetCellSide() + m_iYdiplace + GetCellSide()/2);
    QRectF theRect;
    switch (m_eOrientation) {
        case Left:
            theRect = m_sAlienPainterPathLeft.m_AlienPanzerPainterPath.boundingRect();
            break;
        case Right:
            theRect = m_sAlienPainterPathRight.m_AlienPanzerPainterPath.boundingRect();
            break;
        case Up:
            theRect = m_sAlienPainterPathUp.m_AlienPanzerPainterPath.boundingRect();
            break;
        case Down:
            theRect = m_sAlienPainterPathDown.m_AlienPanzerPainterPath.boundingRect();
            break;
        default:
            break;
    }
    theRect = theRect.translated(qpointTranslatedPosition);
    return theRect;
}
//=================================================================================================================
