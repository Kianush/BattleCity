#include "InternalWall.h"
#include "FreeSpace.h"
#include "ImplicitInternalWall.h"
#include "Bullet.h"
//===============================================================================================================
#include <QPainter>
//===============================================================================================================
InternalWall::InternalWall(const int &iColumn, const int &iRow) : StaticGameThings(iColumn, iRow)
{
    m_pImplicitStaticGameThings = new ImplicitInternalWall(iColumn, iRow);
    m_iLiveHits = 2;
}
//===============================================================================================================
InternalWall::~InternalWall()
{
    delete m_pImplicitStaticGameThings;
}
//===============================================================================================================
void InternalWall::Draw(QPainter *pPainter)
{
    m_pImplicitStaticGameThings->Draw(pPainter);
}
//===============================================================================================================
void InternalWall::PlaySoundAtBornMoment()
{
    m_pImplicitStaticGameThings->PlaySoundAtBornMoment();
}
//===============================================================================================================
void InternalWall::PlaySoundAtDeadMoment()
{
    m_pImplicitStaticGameThings->PlaySoundAtDeadMoment();
}
//===============================================================================================================
void InternalWall::BulletHitHandler(Bullet * pBullet)
{
    m_pImplicitStaticGameThings->BulletHitHandler(pBullet);
    m_iLiveHits--;
    if (m_iLiveHits < 0) {
        delete m_pImplicitStaticGameThings;
        m_pImplicitStaticGameThings = new FreeSpace(m_iColumn, m_iRow);
    }
}
//===============================================================================================================
bool InternalWall::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    return m_pImplicitStaticGameThings->CanMoveDynamicalThing(pDynamicGameThings);
}
//===============================================================================================================

