#include "PrizesThings.h"
#include "OurPanzer.h"
#include "AudioDelegate.h"
//===============================================================================================================
#include <QtGlobal>
#include <QRectF>
//===============================================================================================================
Prize::Prize(const int &iColumn, const int &iRow) : GameThings(iColumn, iRow)
{
    m_bIsMarkedToDelete = false;
    m_iShowPrizeCostTime = 20;
    m_iLiveTime = 320;
    m_bIsEffect = false;
}
//===============================================================================================================
Prize::~Prize() {}
//===============================================================================================================
void Prize::SetPrizeCost(const int &iPrizeCost)
{
    m_iPrizeCost = iPrizeCost;
}
//===============================================================================================================
int Prize::GetPrizeCost() const
{
    return m_iPrizeCost;
}
//===============================================================================================================
bool Prize::IsMarkedToDelete() const
{
    return m_bIsMarkedToDelete;
}
//===============================================================================================================
void Prize::MarkToDelete()
{
    m_bIsMarkedToDelete = true;
}
//===============================================================================================================
void Prize::DecrementShowPrizeCostTime()
{
    m_iShowPrizeCostTime--;
    if (m_iShowPrizeCostTime < 0) {
        MarkToDelete();
    }
}
//===============================================================================================================
void Prize::DecrementLiveTime()
{
    m_iLiveTime--;
    if (m_iLiveTime < 0) {
         MarkToDelete();
    }
}
//===============================================================================================================
bool Prize::CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings)
{
    Q_UNUSED(pDynamicGameThings)
    return true;
}
//===============================================================================================================
void Prize::BulletHitHandler(Bullet * pBullet)
{
    Q_UNUSED(pBullet)
}
//===============================================================================================================
bool Prize::OurPanzerHanler(OurPanzer * pOurPanzer)
{
    bool bToReturn = false;
    QRectF thePrizeRect = QRectF(m_iColumn*GetCellSide(), m_iRow*GetCellSide(), GetCellSide(), GetCellSide());
    if (thePrizeRect.intersects(pOurPanzer->GetBoundingRect())) {
        bToReturn = true;
        m_bIsEffect = true;
        //QSound::play(":/audio/get_prize.wav");
        m_psAudioDelegate->PlayGetPrize();
    }
    return bToReturn;
}
//===============================================================================================================
QString Prize::GetStringImage() const
{
    return "";
}
//===============================================================================================================
bool Prize::IsEffect() const
{
    return m_bIsEffect;
}
//===============================================================================================================
