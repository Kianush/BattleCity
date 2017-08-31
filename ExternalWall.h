#ifndef EXTERNALWALL_H
#define EXTERNALWALL_H
//===============================================================================================================
#include "GameThings.h"
//===============================================================================================================
class Bullet;
class DynamicGameThings;
class QObject;
//===============================================================================================================
class ExternalWall : public GameThings
{
public:
    ExternalWall(const int &iColumn, const int &iRow);
    virtual ~ExternalWall();
    //virtual void Draw();
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
    virtual QString GetStringImage() const;
//private:
//    QObject * m_pQmlImage;
};
//===============================================================================================================
#endif // EXTERNALWALL_H
