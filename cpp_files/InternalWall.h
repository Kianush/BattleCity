#ifndef INTERNALWALL_H
#define INTERNALWALL_H
//===============================================================================================================
#include "GameThings.h"
//===============================================================================================================
class Bullet;
class DynamicGameThings;
//==================================================================================================================
class InternalWall : public GameThings
{
public:
    InternalWall(const int &iColumn, const int &iRow);
    virtual ~InternalWall();
    virtual QString GetStringImage() const;
    virtual void Draw();
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
private:
    GameThings * m_pImplicitStaticGameThings;

};
//==================================================================================================================
#endif // INTERNALWALL_H
