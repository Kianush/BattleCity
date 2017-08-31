#ifndef IMPLICITINTERNALWALL_H
#define IMPLICITINTERNALWALL_H
//===============================================================================================================
#include "GameThings.h"
//===============================================================================================================
class Bullet;
class DynamicGameThings;
//class QObject;
//==================================================================================================================
class ImplicitInternalWall : public GameThings
{
public:
    ImplicitInternalWall(const int &iColumn, const int &iRow);
    virtual ~ImplicitInternalWall();
    virtual QString GetStringImage() const;
    //virtual void Draw();
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
//private:
//    QObject * m_pQmlImage;
};
//==================================================================================================================
#endif // IMPLICITINTERNALWALL_H
