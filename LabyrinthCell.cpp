#include "LabyrinthCell.h"
#include "StaticGameThings.h"
//================================================================================================================
#include <QDebug>
//================================================================================================================
LabyrinthCell::LabyrinthCell()
{
    m_pStaticGameThing = nullptr;
    m_pDynamicGameThings = nullptr;
}
//================================================================================================================
LabyrinthCell::~LabyrinthCell()
{
    if (m_pStaticGameThing != nullptr) {
        delete m_pStaticGameThing;
    }
}
//================================================================================================================
void LabyrinthCell::SetNeighbours(LabyrinthCell * pLeftCell,
                                  LabyrinthCell * pRightCell,
                                  LabyrinthCell * pUpperCell,
                                  LabyrinthCell * pLowerCell)
{
    m_pLeftCell = pLeftCell;
    m_pRightCell = pRightCell;
    m_pUpperCell = pUpperCell;
    m_pLowerCell = pLowerCell;
    m_pStaticGameThing = nullptr;
}
//================================================================================================================
bool LabyrinthCell::IsFreeNeighbour(LabyrinthCell * pLabyrinthCell)
{
    bool bToReturn = false;
    if (pLabyrinthCell != nullptr) {
        if (nullptr != pLabyrinthCell->GetStaticCellObject()) {
            bToReturn = pLabyrinthCell->GetStaticCellObject()->CanMoveDynamicalThing(nullptr);
        }
    }
    return bToReturn;
}
//================================================================================================================
bool LabyrinthCell::IsFreeCellAtLeft()
{
    return IsFreeNeighbour(m_pLeftCell);
}
//================================================================================================================
bool LabyrinthCell::IsFreeCellAtRight()
{
    return IsFreeNeighbour(m_pRightCell);
}
//================================================================================================================
bool LabyrinthCell::IsFreeCellAtUp()
{
    return IsFreeNeighbour(m_pUpperCell);
}
//================================================================================================================
bool LabyrinthCell::IsFreeCellAtDown()
{
    return IsFreeNeighbour(m_pLowerCell);
}
//================================================================================================================
LabyrinthCell * LabyrinthCell::GetLeft()
{
    return m_pLeftCell;
}
//================================================================================================================
LabyrinthCell * LabyrinthCell::GetRight()
{
    return m_pRightCell;
}
//================================================================================================================
LabyrinthCell * LabyrinthCell::GetUpper()
{
    return m_pUpperCell;
}
//================================================================================================================
LabyrinthCell * LabyrinthCell::GetLower()
{
    return m_pLowerCell;
}
//================================================================================================================
void LabyrinthCell::SetStaticCellObject(StaticGameThings * pStaticGameThing)
{
    m_pStaticGameThing = pStaticGameThing;
}
//================================================================================================================
StaticGameThings * LabyrinthCell::GetStaticCellObject()
{
    return m_pStaticGameThing;
}
//================================================================================================================
void LabyrinthCell::SetDynamicCellObject(DynamicGameThings * pDynamicGameThings)
{
    m_pDynamicGameThings = pDynamicGameThings;
}
//================================================================================================================
DynamicGameThings * LabyrinthCell::GetDynamicGameThings()
{
    return m_pDynamicGameThings;
}
//================================================================================================================
void LabyrinthCell::RemoveDynamicGameThings(DynamicGameThings * pDynamicGameThings)
{
    RemoveDynamicThingsFromCell(m_pLeftCell, pDynamicGameThings);
    RemoveDynamicThingsFromCell(m_pRightCell, pDynamicGameThings);
    RemoveDynamicThingsFromCell(m_pUpperCell, pDynamicGameThings);
    RemoveDynamicThingsFromCell(m_pLowerCell, pDynamicGameThings);
    if (m_pDynamicGameThings == pDynamicGameThings) {
        m_pDynamicGameThings = nullptr;
    }
}
//================================================================================================================
void LabyrinthCell::RemoveDynamicThingsFromCell(LabyrinthCell * pLabyrinthCell,
                                                DynamicGameThings * pDynamicGameThings)
{
    if (nullptr == pLabyrinthCell) return;
    if (pLabyrinthCell->GetDynamicGameThings() == pDynamicGameThings) {
        pLabyrinthCell->SetDynamicCellObject(nullptr);
    }
}
//================================================================================================================
