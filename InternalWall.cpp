#include "InternalWall.h"
#include "FreeSpace.h"
#include "ImplicitInternalWall.h"
#include "Bullet.h"
#include "AudioDelegate.h"
//===============================================================================================================
InternalWall::InternalWall(const int &iColumn, const int &iRow) : GameThings(iColumn, iRow)
{
    m_pImplicitStaticGameThings = new ImplicitInternalWall(iColumn, iRow);
    SetLiveHits(2);
    m_pQmlImage = nullptr;
}
//===============================================================================================================
InternalWall::~InternalWall()
{
    delete m_pImplicitStaticGameThings;
}
//===============================================================================================================
void InternalWall::Draw()
{
    m_pImplicitStaticGameThings->Draw();
}
//===============================================================================================================
QString InternalWall::GetStringImage() const
{
    return m_pImplicitStaticGameThings->GetStringImage();
}
//===============================================================================================================
void InternalWall::BulletHitHandler(Bullet * pBullet)
{
    m_pImplicitStaticGameThings->BulletHitHandler(pBullet);
    SetExplosion(m_pImplicitStaticGameThings->IsExplosion());
    if (m_pImplicitStaticGameThings->GetLiveHits() < 0) {
        SetExplosion();
        m_psAudioDelegate->PlayExplosion();
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

