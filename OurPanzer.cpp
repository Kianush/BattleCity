#include "OurPanzer.h"
#include "Bullet.h"
#include "AudioDelegate.h"
//=================================================================================================================
#include <QDebug>
#include <math.h>
#include <QDeclarativeView>
#include <QGraphicsObject>
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
    QString qmlObjectName = "our_panzer";
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
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
        m_psAudioDelegate->PlayRotate();
    }
}
//=================================================================================================================
OurPanzer::~OurPanzer()
{
    m_siLiveCount--;
}
//=================================================================================================================
QString OurPanzer::GetStringImage() const
{
    QString qstrToReturn;
    static QString qstrArrayImages[4];
    qstrArrayImages[0] = "Images/our_panzer_nord.png";
    qstrArrayImages[1] = "Images/our_panzer_east.png";
    qstrArrayImages[2] = "Images/our_panzer_south.png";
    qstrArrayImages[3] = "Images/our_panzer_west.png";
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
    //QSound::play(":/audio/shot.wav");
    m_psAudioDelegate->PlayShot();
    return pToReturn;
}
//=================================================================================================================
void OurPanzer::BulletHitHandler(Bullet * pBullet)
{
    bool bIsHitting = false;
    bIsHitting = IsGeometrycalHitting(pBullet);
    if (this != pBullet->GetPointerParent() && bIsHitting) {
        pBullet->MarkToDelete();
    }
    if (GetMyCodeOfBullet() != pBullet->GetCodeOwner() && bIsHitting) {
        DecrementLiveHits();
        pBullet->MarkToDelete();
        if (GetLiveHits() < 0) {
            SetExplosion();
            m_psAudioDelegate->PlayExplosion();
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
    QRectF theRect;
    switch (m_eOrientation) {
        case Right:
        case Left:
            theRect = QRectF(GetColumn()*GetCellSide() + GetXdiplace(),
                             GetRow()*GetCellSide() + GetYdiplace(),
                             GetWidth(), GetHeight());
        break;
        case Up:
        case Down:
        theRect = QRectF(GetColumn()*GetCellSide() + GetXdiplace(),
                         GetRow()*GetCellSide() + GetYdiplace(),
                         GetHeight(), GetWidth());
        break;
        default:
        break;
    }
    return theRect;
}
//=================================================================================================================
//bool OurPanzer::CanMoveIntoCurrentCell() const
//{
//    bool bToReturn = false;
//    switch (m_eOrientation) {
//        case Left:
//            if (m_iXdiplace >= 0 && (m_iXdiplace - m_iVelosity) >= 0) {
//                bToReturn = true;
//            }
//            break;
//        case Right:
//            if (m_iXdiplace <= 0 && (m_iXdiplace + m_iVelosity) <= 0) {
//                bToReturn = true;
//            }
//            break;
//        case Up:
//            if (m_iYdiplace >= 0 && (m_iYdiplace - m_iVelosity) >= 0) {
//                bToReturn = true;
//            }
//            break;
//        case Down:
//            if (m_iYdiplace <= 0 && (m_iYdiplace + m_iVelosity) <= 0) {
//                bToReturn = true;
//            }
//            break;
//        default:
//            break;
//    }
//    return bToReturn;
//}
//=================================================================================================================
