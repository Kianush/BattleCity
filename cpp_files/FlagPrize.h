#ifndef FLAGPRIZE_H
#define FLAGPRIZE_H
//================================================================================================================
#include "PrizesThings.h"
//================================================================================================================
class Labyrinth;
class Bullet;
//class QObject;
//================================================================================================================
class FlagPrize : public Prize
{
public:
    FlagPrize(const int &iColumn, const int &iRow, Labyrinth * pLabyrinth);
    virtual ~FlagPrize();
    virtual QString GetStringImage() const;
    //virtual void Draw();
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
    static void SetFlagPrizePath();
private:
    void GameOver();
    Labyrinth * m_pLabyrinth;
//    QObject * m_pQmlImage;
};
//================================================================================================================
#endif // FLAGPRIZE_H
