#include "AudioThread.h"
#include "AudioEvents.h"
//=================================================================================================================
#include <QCoreApplication>
#include <QSound>
#include <QDebug>
//=================================================================================================================
GameAudioPlayer::GameAudioPlayer(QObject * pParent) : QObject(pParent)
{
    //m_pMoveSound = new QSound(":/audio/our_move.wav", this);
    //m_pStopSound = new QSound(":/audio/our_stop.wav", this);
    //m_pMoveSound->setLoops(QSound::Infinite);
    //m_pStopSound->setLoops(QSound::Infinite);
    const int SIZE_PULL_SOUNDS = 5;
    for (int sound_count = 0; sound_count < SIZE_PULL_SOUNDS; ++sound_count) {
        QSound * pSound = new QSound(":/audio/shot.wav", this);
        m_qvecShotSound.push_back(pSound);

        pSound = new QSound(":/audio/rotate.wav", this);
        m_qvecRotateSound.push_back(pSound);

        pSound = new QSound(":/audio/our_move.wav", this);
        m_qvecMoveSound.push_back(pSound);

        pSound = new QSound(":/audio/explosion.wav", this);
        m_qvecExplosionSound.push_back(pSound);

        pSound = new QSound(":/audio/our_stop.wav", this);
        m_qvecStopSound.push_back(pSound);
    }
//    m_qvecStopSound[0]->setLoops(QSound::Infinite);
//    m_qvecStopSound[0]->play();
    //m_pExplosionSound = new QSound(":/audio/explosion.wav", this);
    m_pGetPrizeSound = new QSound(":/audio/get_prize.wav", this);
    m_bIsMoving = false;
}
//=================================================================================================================
GameAudioPlayer::~GameAudioPlayer()
{
    //delete m_pMoveSound;
    //delete m_pStopSound;
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
    for (sound_count = 0; sound_count < m_qvecMoveSound.size(); ++sound_count) {
        pSound = m_qvecMoveSound[sound_count];
        delete pSound;
        pSound = nullptr;
    }
    for (sound_count = 0; sound_count < m_qvecStopSound.size(); ++sound_count) {
        pSound = m_qvecStopSound[sound_count];
        delete pSound;
        pSound = nullptr;
    }
    for (sound_count = 0; sound_count < m_qvecExplosionSound.size(); ++sound_count) {
        pSound = m_qvecExplosionSound[sound_count];
        delete pSound;
        pSound = nullptr;
    }
    m_qvecShotSound.clear();
    m_qvecRotateSound.clear();
    m_qvecMoveSound.clear();
    m_qvecShotSound.clear();
    delete m_pGetPrizeSound;
}
//=================================================================================================================
void GameAudioPlayer::customEvent(QEvent *pCustomEvent)
{
    int iCustomEventType = pCustomEvent->type();
    if (iCustomEventType == UserMoveAudioEvent::UserMoveAudioType) {
//        if (m_bIsMoving != true) {
//            m_bIsMoving = true;
//            static int iCallMoveCount = 0;
//            m_qvecMoveSound[iCallMoveCount%m_qvecMoveSound.size()]->setLoops(QSound::Infinite);
//            m_qvecMoveSound[iCallMoveCount%m_qvecMoveSound.size()]->play();

//            for (int sound_count = 0; sound_count < m_qvecMoveSound.size(); ++sound_count) {
//                if ((iCallMoveCount%m_qvecMoveSound.size()) != sound_count) {
//                    m_qvecMoveSound[sound_count]->setLoops(0);
//                }
//                m_qvecStopSound[sound_count]->stop();
//            }
//            iCallMoveCount++;
//        }
    }
    if (iCustomEventType == UserStopAudioEvent::UserStopAudioType) {
//        if (m_bIsMoving != false) {
//            m_bIsMoving = false;
//            static int iCallStopCount = 0;
//            m_qvecStopSound[iCallStopCount%m_qvecMoveSound.size()]->setLoops(QSound::Infinite);
//            m_qvecStopSound[iCallStopCount%m_qvecMoveSound.size()]->play();

//            for (int sound_count = 0; sound_count < m_qvecMoveSound.size(); ++sound_count) {
//                if ((iCallStopCount%m_qvecStopSound.size()) != sound_count) {
//                    m_qvecStopSound[sound_count]->setLoops(0);
//                }
//                m_qvecMoveSound[sound_count]->stop();
//            }
//            iCallStopCount++;
//        }
    }
    if (iCustomEventType == GameStopAudioEvent::GameStopAudioType) {
//        for (int sound_count = 0; sound_count < m_qvecMoveSound.size(); ++sound_count) {
//            m_qvecMoveSound[sound_count]->stop();
//        }
//        for (int sound_count = 0; sound_count < m_qvecStopSound.size(); ++sound_count) {
//            m_qvecStopSound[sound_count]->stop();
//        }
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
        static int iCallExplosionCount = 0;
        m_qvecExplosionSound[iCallExplosionCount % m_qvecExplosionSound.size()]->play();
        iCallExplosionCount++;
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
