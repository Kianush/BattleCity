#include "AudioThread.h"
#include "AudioEvents.h"
//=================================================================================================================
#include <QCoreApplication>
#include <QSound>
#include <QDebug>
//=================================================================================================================
GameAudioPlayer::GameAudioPlayer(QObject * pParent) : QObject(pParent)
{
    m_pMoveSound = new QSound(":/audio/our_move.wav", this);
    m_pStopSound = new QSound(":/audio/our_stop.wav", this);
    m_pMoveSound->setLoops(QSound::Infinite);
    m_pStopSound->setLoops(QSound::Infinite);
    const int SIZE_PULL_SOUNDS = 5;
    for (int sound_count = 0; sound_count < SIZE_PULL_SOUNDS; ++sound_count) {
        QSound * pSound = new QSound(":/audio/shot.wav", this);
        m_qvecShotSound.push_back(pSound);
        pSound = new QSound(":/audio/rotate.wav", this);
        m_qvecRotateSound.push_back(pSound);
    }

    m_pExplosionSound = new QSound(":/audio/explosion.wav", this);
    m_pGetPrizeSound = new QSound(":/audio/get_prize.wav", this);
}
//=================================================================================================================
GameAudioPlayer::~GameAudioPlayer()
{
    delete m_pMoveSound;
    delete m_pStopSound;
    QSound * pSound;
    int sound_count;
    for (sound_count = 0; sound_count < m_qvecShotSound.size(); ++sound_count) {
        pSound = m_qvecShotSound[sound_count];
        delete pSound;
        pSound = nullptr;
    }
    for (sound_count = 0; sound_count < m_qvecRotateSound.size(); ++sound_count) {
        pSound = m_qvecRotateSound[sound_count];
        delete pSound;
        pSound = nullptr;
    }
    m_qvecShotSound.clear();
    m_qvecRotateSound.clear();
    delete m_pExplosionSound;
    delete m_pGetPrizeSound;
}
//=================================================================================================================
void GameAudioPlayer::customEvent(QEvent *pCustomEvent)
{
    int iCustomEventType = pCustomEvent->type();
    if (iCustomEventType == UserMoveAudioEvent::UserMoveAudioType) {
        m_pStopSound->stop();
        m_pMoveSound->play();
    }
    if (iCustomEventType == UserStopAudioEvent::UserStopAudioType) {
        m_pStopSound->play();
        m_pMoveSound->stop();
    }
    if (iCustomEventType == GameStopAudioEvent::GameStopAudioType) {
        m_pStopSound->stop();
        m_pMoveSound->stop();
    }
    if (iCustomEventType == GetPrizeAudioEvent::GetPrizeAudioType) {
        //QSound::play(":/audio/get_prize.wav");
        m_pGetPrizeSound->play();
    }
    if (iCustomEventType == ShotAudioEvent::ShotAudioType) {
        static int iCallShotCount = 0;
        m_qvecShotSound[iCallShotCount % m_qvecShotSound.size()]->play();
        iCallShotCount++;
    }
    if (iCustomEventType == RotateAudioEvent::RotateAudioType) {
        static int iCallRotateCount = 0;
        m_qvecRotateSound[iCallRotateCount % m_qvecRotateSound.size()]->play();
        iCallRotateCount++;
    }
    if (iCustomEventType == ExplosionAudioEvent::ExplosionAudioType) {
        //QSound::play(":/audio/explosion.wav");
        m_pExplosionSound->play();
    }
    QObject::customEvent(pCustomEvent);
}
//=================================================================================================================
GameAudioThread::GameAudioThread(QObject * pObjectReceiver, QObject * pParent) : QThread(pParent)
{
    m_pObjectReceiver = pObjectReceiver;
}
//=================================================================================================================
GameAudioThread::~GameAudioThread()
{
    if (m_pGameAudioPlayer != nullptr) {
        delete m_pGameAudioPlayer;
    }
}
//=================================================================================================================
void GameAudioThread::run()
{
    m_pGameAudioPlayer = new GameAudioPlayer;
    if (nullptr != m_pObjectReceiver) {
        ReadyGameAudioThreadEvent * pReadyGameAudioThreadEvent = new ReadyGameAudioThreadEvent;
        pReadyGameAudioThreadEvent->SetObjectTransmiter(m_pGameAudioPlayer);
        QCoreApplication::postEvent(m_pObjectReceiver, pReadyGameAudioThreadEvent);
    }
    exec();
}
//=================================================================================================================
