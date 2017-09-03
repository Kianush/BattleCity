//================================================================================================================
#include "AlienPanzers.h"
#include "Bullet.h"
#include "GameStatistic.h"
#include "AudioDelegate.h"
//================================================================================================================
#include <QDeclarativeView>
#include <QGraphicsObject>
//================================================================================================================
int AlienPanzer::m_siCodeOwnerOfBullet;
int AlienPanzer::m_siQuantitySimpleAliensInGame;
int AlienPanzer::m_siNumberOfTheAlien = 0;
int AlienPanzer::m_siWidthOfMainImage;
int AlienPanzer::m_siHeightOfMainImage;
//================================================================================================================
void AlienPanzer::SetDimensionsOfMainImage(const int &iWidth, const int iHeight)
{
   m_siWidthOfMainImage = iWidth;
   m_siHeightOfMainImage = iHeight;
}
//================================================================================================================
void AlienPanzer::ResetAliensInGame(const int &iQuantityAliensInGame)
{
    m_siNumberOfTheAlien = iQuantityAliensInGame;
}
//================================================================================================================
void AlienPanzer::SetQuantitySimpleAliens(const int &iQuantitySimpleAliens)
{
    m_siQuantitySimpleAliensInGame = iQuantitySimpleAliens;
}
//================================================================================================================
void AlienPanzer::DecrementQuantityAliens()
{
    m_siQuantitySimpleAliensInGame--;
}
//================================================================================================================
int AlienPanzer::GetQuantitySimpleAliens()
{
    return m_siQuantitySimpleAliensInGame;
}
//================================================================================================================
void AlienPanzer::SetCodeOwnerOfBullets(const int &iCodeOwner)
{
    m_siCodeOwnerOfBullet = iCodeOwner;
}
//================================================================================================================
AlienPanzer::AlienPanzer(const int &iColumn, const int &iRow) : DynamicGameThings(iColumn, iRow, 5)
{
    m_eOrientation = Down;
    SetLiveHits(3);
    m_bIsMarkedToDelete = false;
    m_iShowCostTime = 20;
    m_iShowBorningTime = 2000;
    m_bIsDead = false;
    m_bIsBorning = false;
    m_iCost = 100;
    QString qmlObjectName = "alien_"+QString::number(m_siNumberOfTheAlien);
    m_siNumberOfTheAlien++;
    m_pQmlImage = m_psMainDeclarativeView->rootObject()->findChild<QObject*>(qmlObjectName);
}
//================================================================================================================
AlienPanzer::~AlienPanzer()
{
}
//================================================================================================================
QString AlienPanzer::GetStringImage() const
{
    QString qstrToReturn;
    static QString qstrArrayImages[7];
    qstrArrayImages[0] = "Images/alien_panzer_nord.png";
    qstrArrayImages[1] = "Images/alien_panzer_east.png";
    qstrArrayImages[2] = "Images/alien_panzer_south.png";
    qstrArrayImages[3] = "Images/alien_panzer_west.png";
    qstrArrayImages[4] = "Images/pulse_1.png";
    qstrArrayImages[5] = "Images/pulse_2.png";
    qstrArrayImages[6] = "Images/plus_100.png";
    if (!m_bIsDead && !m_bIsBorning) {
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
    }
    else if (m_bIsBorning) {
        static int iPulseCounter = 0;
        if ((iPulseCounter/7) % 2 == 0) {
            qstrToReturn = qstrArrayImages[4];
        }
        else {
            qstrToReturn = qstrArrayImages[5];
        }
        iPulseCounter++;
    }
    else if (m_bIsDead) {
        qstrToReturn = qstrArrayImages[6];
    }
    else {}
    return qstrToReturn;
}
//================================================================================================================
bool AlienPanzer::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    bool bToReturn = false;
    if (IsDead()) {
        bToReturn = true;
    }
    return bToReturn;
}
//================================================================================================================
void AlienPanzer::SetOrientation(const DynamicGameThings::Orientation &eOrientation)
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
//================================================================================================================
void AlienPanzer::Move(bool &bCellChange)
{
    bCellChange = false;
    if (m_bIsBorning) {
        return;
    }
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
//================================================================================================================
void AlienPanzer::DummyRotate()
{
    int iRandResult = rand() % 2;
//    int iRandResult = rand() % 4;
//    if (m_eOrientation == Down || m_eOrientation == Up) {
//        if (iRandResult) {
//            if (iRandResult % 2) {
//                SetOrientation(Left);
//            }
//            else {
//                SetOrientation(Right);
//            }
//        }
//        else {
//            SetOrientation(Orientation(((int)m_eOrientation + 1) % 4));
//        }
//    }
//    else {
//        if (iRandResult) {
//            if (iRandResult % 2) {
//                SetOrientation(Up);
//            }
//            else {
//                SetOrientation(Down);
//            }
//        }
//        else {
//            SetOrientation(Orientation(((int)m_eOrientation + 3) % 4));
//        }
//    }
    if (!iRandResult) {
        SetOrientation(Orientation(((int)m_eOrientation + 1) % 4));
    }
    else {
        SetOrientation(Orientation(((int)m_eOrientation + 3) % 4));
    }
}
//================================================================================================================
Bullet * AlienPanzer::Shoot()
{
    int iColumnBullet, iRowBullet, iXdiplaceBullet, iYdiplaceBullet;
    RecalculatePosition(iColumnBullet, iRowBullet, iXdiplaceBullet, iYdiplaceBullet);

    Bullet * pToReturn = new Bullet(iColumnBullet, iRowBullet, iXdiplaceBullet, iYdiplaceBullet, 20, m_eOrientation);
    pToReturn->SetCodeOwner(m_siCodeOwnerOfBullet);
    pToReturn->SetParent(this);
    return pToReturn;
}
//================================================================================================================
void AlienPanzer::BulletHitHandler(Bullet * pBullet)
{
    if (IsDead()) {
        return;
    }
    if (m_bIsBorning) {
        return;
    }
    bool bIsGeometrycallyHitting = IsGeometrycalHitting(pBullet);
    if (this != pBullet->GetPointerParent() && bIsGeometrycallyHitting) {
        pBullet->MarkToDelete();
    }
    if (m_siCodeOwnerOfBullet != pBullet->GetCodeOwner() && bIsGeometrycallyHitting) {

        DecrementLiveHits();
        pBullet->MarkToDelete();
        if (GetLiveHits() < 0) {
            SetStatistic();
            m_bIsDead = true;
            SetExplosion();
            m_psAudioDelegate->PlayExplosion();
        }
    }
}
//================================================================================================================
void AlienPanzer::SetStatistic()
{
    m_psGameStatistic->AddScope(GetCost());
    m_psGameStatistic->IncrementSimpleAliensKilled();
}
//================================================================================================================
int AlienPanzer::GetTypicalVelosity() const
{
    const int TYPICAL_VELOSITY = 5;
    return TYPICAL_VELOSITY;
}
//================================================================================================================
bool AlienPanzer::IsMarkedToDelete() const
{
    return m_bIsMarkedToDelete;
}
//================================================================================================================
void AlienPanzer::MarkToDelete()
{
    m_bIsMarkedToDelete = true;
}
//================================================================================================================
bool AlienPanzer::IsDead() const
{
    return m_bIsDead;
}
//================================================================================================================
void AlienPanzer::DecrementShowCostTime()
{
    m_iShowCostTime--;
    if (m_iShowCostTime < 0) {
        MarkToDelete();
    }
}
//================================================================================================================
void AlienPanzer::DecreaseBornTime(const int &iTick)
{
    m_iShowBorningTime -= iTick;
    if (m_iShowBorningTime <= 0) {
        m_bIsBorning = false;
    }
}
//================================================================================================================
void AlienPanzer::SetBorning()
{
    m_bIsBorning = true;
}
//================================================================================================================
bool AlienPanzer::IsBorning() const
{
    return m_bIsBorning;
}
//================================================================================================================
void AlienPanzer::SetCost(const int &iCost)
{
    m_iCost = iCost;
}
//================================================================================================================
int AlienPanzer::GetCost() const
{
    return m_iCost;
}
//================================================================================================================
void AlienPanzer::SetTypicalVelosity()
{
    SetVelosity(GetTypicalVelosity());
}
//================================================================================================================
int AlienPanzer::GetWidth() const
{
    if (m_eOrientation == Up || m_eOrientation == Down) {
        return m_siWidthOfMainImage;
    }
    else {
        return m_siHeightOfMainImage;
    }
}
//================================================================================================================
int AlienPanzer::GetHeight() const
{
    if (m_eOrientation == Up || m_eOrientation == Down) {
        return m_siHeightOfMainImage;
    }
    else {
        return m_siWidthOfMainImage;
    }
}
//================================================================================================================
bool AlienPanzer::CanMoveIntoCurrentCell() const
{
    bool bToReturn = false;
    switch (m_eOrientation) {
        case Left:
            if (m_iXdiplace >= 0 && (m_iXdiplace - m_iVelosity) >= 0) {
                bToReturn = true;
            }
            break;
        case Right:
            if (m_iXdiplace <= 0 && (m_iXdiplace + m_iVelosity) <= 0) {
                bToReturn = true;
            }
            break;
        case Up:
            if (m_iYdiplace >= 0 && (m_iYdiplace - m_iVelosity) >= 0) {
                bToReturn = true;
            }
            break;
        case Down:
            if (m_iYdiplace <= 0 && (m_iYdiplace + m_iVelosity) <= 0) {
                bToReturn = true;
            }
            break;
        default:
            break;
    }
    return bToReturn;
}
