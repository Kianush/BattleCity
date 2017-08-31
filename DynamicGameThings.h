#ifndef DYNAMICGAMETHINGS_H
#define DYNAMICGAMETHINGS_H
//=================================================================================================================
#include "GameThings.h"
//=================================================================================================================
class LabyrinthCell;
class QString;
class Bullet;
//=================================================================================================================
class DynamicGameThings : public GameThings
{
public:
    enum Orientation {
        Left = 0,
        Right = 1,
        Up = 2,
        Down = 3
    };
public:
    DynamicGameThings(const int &iColumn, const int &iRow, const int &iVelosity);
    virtual ~DynamicGameThings();
    virtual LabyrinthCell * CanMoveToTheNextCell(LabyrinthCell * pCurrentLabyrinthCell);
    virtual void Move(bool &bCellChange) = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const  = 0;
    virtual void SetOrientation(const DynamicGameThings::Orientation &eOrientation);

    void SetVelosity(const int &iVelosity);
    int GetVelosity() const;
protected:
    bool IsGeometrycalHitting(Bullet * pBullet) const;
    void RecalculatePosition(int &iColumn, int &iRow, int &iXdiplace, int &iYdiplace);
    Orientation m_eOrientation;
    int m_iVelosity;
private:
    LabyrinthCell * CheckDynamicThingInCell(LabyrinthCell * pCell);
};
//=================================================================================================================
#endif // DYNAMICGAMETHINGS_H
