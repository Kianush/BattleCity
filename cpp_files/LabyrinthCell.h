#ifndef LABYRINTHCELL_H
#define LABYRINTHCELL_H
//================================================================================================================
class GameThings;
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

    GameThings * GetStaticCellObject();
    DynamicGameThings * GetDynamicGameThings();
    void SetStaticCellObject(GameThings * pStaticGameThing);
    void SetDynamicCellObject(DynamicGameThings * pDynamicGameThings);
    void RemoveDynamicGameThings(DynamicGameThings * pDynamicGameThings);
private:
    bool IsFreeNeighbour(LabyrinthCell * pLabyrinthCell);
    void RemoveDynamicThingsFromCell(LabyrinthCell * pLabyrinthCell, DynamicGameThings * pDynamicGameThings);
    LabyrinthCell * m_pLeftCell;
    LabyrinthCell * m_pRightCell;
    LabyrinthCell * m_pUpperCell;
    LabyrinthCell * m_pLowerCell;
    GameThings * m_pStaticGameThing;
    DynamicGameThings * m_pDynamicGameThings;
};
//================================================================================================================
#endif // LABYRINTHCELL_H
