#include "AudioDelegate.h"
#include "AudioEvents.h"
//=================================================================================================================
#include <QCoreApplication>
//=================================================================================================================
AudioDelegate::AudioDelegate(QObject *pParent) : QObject(pParent)
{
    m_pObjectReceiver = nullptr;
}
//=================================================================================================================
AudioDelegate::~AudioDelegate()
{

}
//=================================================================================================================
void AudioDelegate::PlayOurMove()
{
    if (nullptr != m_pObjectReceiver) {
        UserMoveAudioEvent * pUserMoveAudioEvent = new UserMoveAudioEvent;
        QCoreApplication::postEvent(m_pObjectReceiver, pUserMoveAudioEvent);
    }
}
//=================================================================================================================
void AudioDelegate::PlayOurStop()
{
    if (nullptr != m_pObjectReceiver) {
        UserStopAudioEvent * pUserStopAudioEvent = new UserStopAudioEvent;
        QCoreApplication::postEvent(m_pObjectReceiver, pUserStopAudioEvent);
    }
}
//=================================================================================================================
void AudioDelegate::PlayGetPrize()
{
    if (nullptr != m_pObjectReceiver) {
        GetPrizeAudioEvent * pGetPrizeAudioEvent = new GetPrizeAudioEvent;
        QCoreApplication::postEvent(m_pObjectReceiver, pGetPrizeAudioEvent);
    }
}
//=================================================================================================================
void AudioDelegate::PlayShot()
{
    if (nullptr != m_pObjectReceiver) {
        ShotAudioEvent * pShotAudioEvent = new ShotAudioEvent;
        QCoreApplication::postEvent(m_pObjectReceiver, pShotAudioEvent);
    }
}
//=================================================================================================================
void AudioDelegate::PlayRotate()
{
    if (nullptr != m_pObjectReceiver) {
        RotateAudioEvent * pRotateAudioEvent = new RotateAudioEvent;
        QCoreApplication::postEvent(m_pObjectReceiver, pRotateAudioEvent);
    }
}
//=================================================================================================================
void AudioDelegate::PlayExplosion()
{
    if (nullptr != m_pObjectReceiver) {
        ExplosionAudioEvent * pExplosionAudioEvent = new ExplosionAudioEvent;
        QCoreApplication::postEvent(m_pObjectReceiver, pExplosionAudioEvent);
    }
}
//=================================================================================================================
void AudioDelegate::StopGameAudio()
{
    if (nullptr != m_pObjectReceiver) {
        GameStopAudioEvent * pGameStopAudioEvent = new GameStopAudioEvent;
        QCoreApplication::postEvent(m_pObjectReceiver, pGameStopAudioEvent);
    }
}

//=================================================================================================================
void AudioDelegate::customEvent(QEvent * pCustomEvent)
{
    if (int(pCustomEvent->type()) == ReadyGameAudioThreadEvent::ReadyGameAudioThreadType) {
        m_pObjectReceiver = ((ReadyGameAudioThreadEvent*)(pCustomEvent))->GetObjectTransmiter();
        PlayOurStop();
    }
    QObject::customEvent(pCustomEvent);
}
//=================================================================================================================
