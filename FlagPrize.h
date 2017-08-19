#ifndef FLAGPRIZE_H
#define FLAGPRIZE_H
//================================================================================================================
#include "PrizesThings.h"
#include "PrizesPathes.h"
//================================================================================================================
class Labyrinth;
class Bullet;
//================================================================================================================
class FlagPrize : public Prize
{
public:
    FlagPrize(const int &iColumn, const int &iRow, Labyrinth * pLabyrinth);
    virtual ~FlagPrize(){}
    virtual void Draw(QPainter *pPainter);
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
    static void SetFlagPrizePath();
private:
    void GameOver();
    Labyrinth * m_pLabyrinth;
    static FlagPrizePath m_sFlagPrizePath;
};
//================================================================================================================
#endif // FLAGPRIZE_H
