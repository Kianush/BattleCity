//================================================================================================================
#include "AlienPanzers.h"
#include "Bullet.h"
#include "GameStatistic.h"
//================================================================================================================
#include <QPainter>
//================================================================================================================
AlienPath AlienPanzer::m_sAlienPainterPathLeft;
AlienPath AlienPanzer::m_sAlienPainterPathRight;
AlienPath AlienPanzer::m_sAlienPainterPathUp;
AlienPath AlienPanzer::m_sAlienPainterPathDown;
AlienBornPath AlienPanzer::m_sAlienBornPath;
int AlienPanzer::m_siCodeOwnerOfBullet;
int AlienPanzer::m_siQuantitySimpleAliensInGame;
//================================================================================================================
void AlienPanzer::SetQuantitySimpleAliens(const int &iQuantitySimpleAliens)
{
    m_siQuantitySimpleAliensInGame = iQuantitySimpleAliens;
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
void AlienPanzer::SetRotatedSimpleAlienPathes()
{
    QMatrix matrix;
    matrix.rotate(180);
    m_sAlienPainterPathUp.m_AlienPanzerPainterPath = matrix.map(m_sAlienPainterPathUp.m_AlienPanzerPainterPath);
    matrix.reset();
    matrix.rotate(90);
    m_sAlienPainterPathRight.m_AlienPanzerPainterPath = matrix.map(m_sAlienPainterPathUp.m_AlienPanzerPainterPath);
    matrix.rotate(90);
    m_sAlienPainterPathDown.m_AlienPanzerPainterPath = matrix.map(m_sAlienPainterPathUp.m_AlienPanzerPainterPath);
    matrix.rotate(90);
    m_sAlienPainterPathLeft.m_AlienPanzerPainterPath = matrix.map(m_sAlienPainterPathUp.m_AlienPanzerPainterPath);
}
//================================================================================================================
AlienPanzer::AlienPanzer(const int &iColumn, const int &iRow) : DynamicGameThings(iColumn, iRow, 5)
{
    m_eOrientation = Down;
    m_iLiveHits = 3;
    m_bIsMarkedToDelete = false;
    m_iShowCostTime = 20;
    m_iShowBorningTime = 2000;
    m_bIsDead = false;
    m_bIsBorning = false;
    m_iCost = 100;
}
//================================================================================================================
AlienPanzer::~AlienPanzer()
{
    m_siQuantitySimpleAliensInGame--;
}
//================================================================================================================
void AlienPanzer::Draw(QPainter *pPainter)
{
    QPoint qpointTranslatedPosition = QPoint(m_iColumn*40 + m_iXdiplace + 20, m_iRow*40 + m_iYdiplace + 20);
    pPainter->setBrush(Qt::NoBrush);
    QPen thePen;
    thePen.setWidth(1);
    pPainter->setPen(thePen);
    if (!m_bIsDead && !m_bIsBorning) {
        switch (m_eOrientation) {
            case Left:
                pPainter->drawPath(m_sAlienPainterPathLeft.
                                   m_AlienPanzerPainterPath.translated(qpointTranslatedPosition));
                break;
            case Right:
                pPainter->drawPath(m_sAlienPainterPathRight.
                                   m_AlienPanzerPainterPath.translated(qpointTranslatedPosition));
                break;
            case Up:
                pPainter->drawPath(m_sAlienPainterPathUp.
                                   m_AlienPanzerPainterPath.translated(qpointTranslatedPosition));
                break;
            case Down:
                pPainter->drawPath(m_sAlienPainterPathDown.
                                   m_AlienPanzerPainterPath.translated(qpointTranslatedPosition));
                break;
            default:
                break;
        }
    }
    else if (m_bIsDead){
        pPainter->drawText(m_iColumn*GetCellSide() + m_iXdiplace+2,
                           m_iRow*GetCellSide() + m_iYdiplace+25, "+" + QString::number(m_iCost));
    }
    else if (m_bIsBorning) {
        static int iPulseCounter = 0;
        if ((iPulseCounter/7) % 2 == 0) {
            pPainter->drawPath(m_sAlienBornPath.m_PulseFirstPainterPath.translated(qpointTranslatedPosition));
        }
        else {
            pPainter->drawPath(m_sAlienBornPath.m_PulseSecondPainterPath.translated(qpointTranslatedPosition));
        }
        iPulseCounter++;
    }
    else {}
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
    QRectF theAlienRect = thePainterPath.boundingRect();
    int x_begin = theAlienRect.left();
    int x_end = theAlienRect.left()+theAlienRect.width();
    int y_begin = theAlienRect.top();
    int y_end = theAlienRect.top() + theAlienRect.height();
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
    if (m_siCodeOwnerOfBullet != pBullet->GetCodeOwner() && bIsHitting) {

        m_iLiveHits--;
        pBullet->MarkToDelete();
        if (m_iLiveHits < 0) {
            SetStatistic();
            m_bIsDead = true;
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
