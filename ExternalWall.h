#ifndef EXTERNALWALL_H
#define EXTERNALWALL_H
//===============================================================================================================
#include "StaticGameThings.h"
//===============================================================================================================
class QPainter;
class Bullet;
class DynamicGameThings;
//===============================================================================================================
class ExternalWall : public StaticGameThings
{
public:
    ExternalWall(const int &iColumn, const int &iRow);
    virtual ~ExternalWall();
    virtual void Draw(QPainter *pPainter);
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual void PlaySoundAtBornMoment() {}
    virtual void PlaySoundAtDeadMoment() {}
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
};
//===============================================================================================================
#endif // EXTERNALWALL_H
