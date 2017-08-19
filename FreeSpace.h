#ifndef FREESPACE_H
#define FREESPACE_H
//===============================================================================================================
#include "StaticGameThings.h"
//===============================================================================================================
class QPainter;
class Bullet;
class DynamicGameThings;
//==================================================================================================================
class FreeSpace : public StaticGameThings
{
public:
    FreeSpace(const int &iColumn, const int &iRow);
    ~FreeSpace();
    virtual void Draw(QPainter *pPainter);
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual void PlaySoundAtBornMoment() {}
    virtual void PlaySoundAtDeadMoment() {}
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
};
//==================================================================================================================
#endif // FREESPACE_H
