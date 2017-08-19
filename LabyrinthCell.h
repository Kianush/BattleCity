#ifndef LABYRINTHCELL_H
#define LABYRINTHCELL_H
//================================================================================================================
class StaticGameThings;
class DynamicGameThings;
//================================================================================================================
class LabyrinthCell
{
public:
    LabyrinthCell();
    ~LabyrinthCell();
    void SetNeighbours(LabyrinthCell * pLeftCell,
                       LabyrinthCell * pRightCell,
                       LabyrinthCell * pUpperCell,
                       LabyrinthCell * pLowerCell);
    bool IsFreeCellAtLeft();
    bool IsFreeCellAtRight();
    bool IsFreeCellAtUp();
    bool IsFreeCellAtDown();
    LabyrinthCell * GetLeft();
    LabyrinthCell * GetRight();
    LabyrinthCell * GetUpper();
    LabyrinthCell * GetLower();
    void SetStaticCellObject(StaticGameThings * pStaticGameThing);
    StaticGameThings * GetStaticCellObject();
    void SetDynamicCellObject(DynamicGameThings * pDynamicGameThings);
    void RemoveDynamicGameThings(DynamicGameThings * pDynamicGameThings);
    DynamicGameThings * GetDynamicGameThings();
private:
    bool IsFreeNeighbour(LabyrinthCell * pLabyrinthCell);
    void RemoveDynamicThingsFromCell(LabyrinthCell * pLabyrinthCell, DynamicGameThings * pDynamicGameThings);
    LabyrinthCell * m_pLeftCell;
    LabyrinthCell * m_pRightCell;
    LabyrinthCell * m_pUpperCell;
    LabyrinthCell * m_pLowerCell;
    StaticGameThings * m_pStaticGameThing;
    DynamicGameThings * m_pDynamicGameThings;
};
//================================================================================================================
#endif // LABYRINTHCELL_H
