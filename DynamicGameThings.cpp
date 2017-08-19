//=================================================================================================================
#include "DynamicGameThings.h"
#include "LabyrinthCell.h"
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
    return pToReturn;
}
//=================================================================================================================
LabyrinthCell * DynamicGameThings::CanMoveToTheNextCell(LabyrinthCell * pCurrentLabyrinthCell)
{
    LabyrinthCell * pToReturn = nullptr;
    switch (m_eOrientation) {
    case Left:
        if (pCurrentLabyrinthCell->IsFreeCellAtLeft()) {
            pToReturn = CheckDynamicThingInCell(pCurrentLabyrinthCell->GetLeft());
        }
        break;
    case Right:
        if (pCurrentLabyrinthCell->IsFreeCellAtRight()) {
            pToReturn = CheckDynamicThingInCell(pCurrentLabyrinthCell->GetRight());
        }
        break;
    case Up:
        if (pCurrentLabyrinthCell->IsFreeCellAtUp()) {
            pToReturn = CheckDynamicThingInCell(pCurrentLabyrinthCell->GetUpper());
        }
        break;
    case Down:
        if (pCurrentLabyrinthCell->IsFreeCellAtDown()) {
            pToReturn = CheckDynamicThingInCell(pCurrentLabyrinthCell->GetLower());
        }
        break;
    default:
        break;
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
