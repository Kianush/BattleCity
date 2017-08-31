//=================================================================================================================
#include "DynamicGameThings.h"
#include "LabyrinthCell.h"
#include "Bullet.h"
//=================================================================================================================
#include <math.h>
//=================================================================================================================
DynamicGameThings::DynamicGameThings(const int &iColumn, const int &iRow, const int &iVelosity) :
    GameThings(iColumn, iRow)
{
    m_iVelosity = iVelosity;
    m_iXdiplace = 0;
    m_iYdiplace = 0;
}
//=================================================================================================================
DynamicGameThings::~DynamicGameThings() {}
//=================================================================================================================
LabyrinthCell * DynamicGameThings::CheckDynamicThingInCell(LabyrinthCell * pCell)
{
    LabyrinthCell * pToReturn = nullptr;
    DynamicGameThings * pDynamicGameThings = pCell->GetDynamicGameThings();
    if (nullptr == pDynamicGameThings || this == pDynamicGameThings) {
        pToReturn = pCell;
    }
    else {
        if (pDynamicGameThings->CanMoveDynamicalThing(this)) {
            pToReturn = pCell;
        }
    }
    if (nullptr == pDynamicGameThings) {
        bool bCanIMove = true;
        DynamicGameThings * pDynamicalThingUpper = pCell->GetUpper()->GetDynamicGameThings();
        DynamicGameThings * pDynamicalThingLower = pCell->GetLower()->GetDynamicGameThings();
        DynamicGameThings * pDynamicalThingLeft = pCell->GetLeft()->GetDynamicGameThings();
        DynamicGameThings * pDynamicalThingRight = pCell->GetRight()->GetDynamicGameThings();
        switch (m_eOrientation) {
            case Right:
            case Left:
                if (!((nullptr == pDynamicalThingUpper) && (nullptr == pDynamicalThingLower))) {
                    if (pDynamicalThingUpper) {
                        if(pDynamicalThingUpper->GetYdiplace() > 0) {
                            bCanIMove = false;
                        }
                    }
                    if (pDynamicalThingLower) {
                        if (pDynamicalThingLower->GetYdiplace() < 0) {
                            bCanIMove = false;
                        }
                    }
                }
            break;
            case Up:
            case Down:
                if (!((nullptr == pDynamicalThingLeft) && (nullptr == pDynamicalThingRight))) {
                    if (pDynamicalThingLeft) {
                        if(pDynamicalThingLeft->GetXdiplace() > 0) {
                            bCanIMove = false;
                        }
                    }
                    if (pDynamicalThingRight) {
                        if (pDynamicalThingRight->GetXdiplace() < 0) {
                            bCanIMove = false;
                        }
                    }
                }
            break;
            default:
            break;
        }
        if (!bCanIMove) {
            pToReturn = nullptr;
        }
    }
    return pToReturn;
}
//=================================================================================================================
LabyrinthCell * DynamicGameThings::CanMoveToTheNextCell(LabyrinthCell * pCurrentLabyrinthCell)
{
    LabyrinthCell * pToReturn = nullptr;
    LabyrinthCell * pNextCell = nullptr;
    switch (m_eOrientation) {
    case Left:
        if (pCurrentLabyrinthCell->IsFreeCellAtLeft()) {
            pNextCell = CheckDynamicThingInCell(pCurrentLabyrinthCell->GetLeft());
        }
        break;
    case Right:
        if (pCurrentLabyrinthCell->IsFreeCellAtRight()) {
            pNextCell = CheckDynamicThingInCell(pCurrentLabyrinthCell->GetRight());
        }
        break;
    case Up:
        if (pCurrentLabyrinthCell->IsFreeCellAtUp()) {
            pNextCell = CheckDynamicThingInCell(pCurrentLabyrinthCell->GetUpper());
        }
        break;
    case Down:
        if (pCurrentLabyrinthCell->IsFreeCellAtDown()) {
            pNextCell = CheckDynamicThingInCell(pCurrentLabyrinthCell->GetLower());
        }
        break;
    default:
        break;
    }
    if (nullptr != pNextCell) {
        pToReturn = CheckDynamicThingInCell(pNextCell);
    }
    return pToReturn;
}
//=================================================================================================================
void DynamicGameThings::SetOrientation(const DynamicGameThings::Orientation &eOrientation)
{
    m_eOrientation = eOrientation;
}
//=================================================================================================================
void DynamicGameThings::SetVelosity(const int &iVelosity)
{
    m_iVelosity = iVelosity;
}
//=================================================================================================================
int DynamicGameThings::GetVelosity() const
{
    return m_iVelosity;
}
//=================================================================================================================
bool DynamicGameThings::IsGeometrycalHitting(Bullet * pBullet) const
{
    bool bIsHitting = false;

    int x_begin = GetColumn()*GetCellSide() + GetXdiplace();
    int y_begin = GetRow()*GetCellSide() + GetYdiplace();
    int x_end = x_begin + GetWidth();
    int y_end = y_begin + GetHeight();
    int x_bullet_begin = pBullet->GetColumn()*GetCellSide() + pBullet->GetXdiplace() + GetCellSide()/2;
    int x_bullet_end = x_bullet_begin + pBullet->GetWidth();
    int y_bullet_begin = pBullet->GetRow()*GetCellSide() + pBullet->GetYdiplace() + GetCellSide()/2;
    int y_bullet_end = y_bullet_begin + pBullet->GetHeight();

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
    return bIsHitting;
}
//================================================================================================================
void DynamicGameThings::RecalculatePosition(int &iColumn, int &iRow, int &iXdiplace, int &iYdiplace)
{
    double dXcentr = double(m_iColumn*GetCellSide() + m_iXdiplace) + double(GetCellSide())/2.0;
    double dYcentr = double(m_iRow*GetCellSide() + m_iYdiplace) + double(GetCellSide())/2.0;
    int iXcentr = int(floor(dXcentr +0.5));
    int iYcentr = int(floor(dYcentr +0.5));
    iColumn = iXcentr/GetCellSide();
    iRow = iYcentr/GetCellSide();
    iXdiplace = (iXcentr - GetCellSide()/2) - iColumn*GetCellSide();
    iYdiplace = (iYcentr - GetCellSide()/2) - iRow*GetCellSide();
}
//=================================================================================================================
