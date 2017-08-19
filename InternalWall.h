#ifndef INTERNALWALL_H
#define INTERNALWALL_H
//===============================================================================================================
#include "StaticGameThings.h"
//===============================================================================================================
class QPainter;
class Bullet;
class DynamicGameThings;
//==================================================================================================================
class InternalWall : public StaticGameThings
{
public:
    InternalWall(const int &iColumn, const int &iRow);
    virtual ~InternalWall();
    virtual void Draw(QPainter *pPainter);
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual void PlaySoundAtBornMoment();
    virtual void PlaySoundAtDeadMoment();
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
private:
    StaticGameThings * m_pImplicitStaticGameThings;
    int m_iLiveHits;
};
//==================================================================================================================
#endif // INTERNALWALL_H
