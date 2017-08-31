#ifndef FREESPACE_H
#define FREESPACE_H
//===============================================================================================================
#include "GameThings.h"
//===============================================================================================================
class Bullet;
class DynamicGameThings;
//class QObject;
//==================================================================================================================
class FreeSpace : public GameThings
{
public:
    FreeSpace(const int &iColumn, const int &iRow);
    virtual ~FreeSpace();
    virtual QString GetStringImage() const;
    //virtual void Draw();
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
//private:
//    QObject * m_pQmlImage;
};
//==================================================================================================================
#endif // FREESPACE_H
