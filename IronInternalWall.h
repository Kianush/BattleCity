#ifndef IRONINTERNALWALL_H
#define IRONINTERNALWALL_H
//===============================================================================================================
#include "ImplicitInternalWall.h"
//===============================================================================================================
class QPainter;
class Bullet;
class DynamicGameThings;
//==================================================================================================================
class IronInternalWall : public ImplicitInternalWall
{
public:
    IronInternalWall(const int &iColumn, const int &iRow);
    virtual ~IronInternalWall();
    virtual void Draw(QPainter *pPainter);
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual void PlaySoundAtBornMoment() {}
    virtual void PlaySoundAtDeadMoment() {}
};
//==================================================================================================================
#endif // IRONINTERNALWALL_H
