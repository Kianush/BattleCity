#ifndef IRONINTERNALWALL_H
#define IRONINTERNALWALL_H
//===============================================================================================================
#include "ImplicitInternalWall.h"
//===============================================================================================================
class Bullet;
class DynamicGameThings;
//==================================================================================================================
class IronInternalWall : public ImplicitInternalWall
{
public:
    IronInternalWall(const int &iColumn, const int &iRow);
    virtual ~IronInternalWall();
    virtual QString GetStringImage() const;
    //virtual void Draw();
    virtual void BulletHitHandler(Bullet * pBullet);
//private:
//    QObject * m_pQmlImage;
};
//==================================================================================================================
#endif // IRONINTERNALWALL_H
