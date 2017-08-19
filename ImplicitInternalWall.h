#ifndef IMPLICITINTERNALWALL_H
#define IMPLICITINTERNALWALL_H
//===============================================================================================================
#include "StaticGameThings.h"
//===============================================================================================================
class QPainter;
class Bullet;
class DynamicGameThings;
//==================================================================================================================
class ImplicitInternalWall : public StaticGameThings
{
public:
    ImplicitInternalWall(const int &iColumn, const int &iRow);
    virtual ~ImplicitInternalWall();
    virtual void Draw(QPainter *pPainter);
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual void PlaySoundAtBornMoment() {}
    virtual void PlaySoundAtDeadMoment() {}
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
private:
    int m_iLiveHits;
};
//==================================================================================================================
#endif // IMPLICITINTERNALWALL_H
