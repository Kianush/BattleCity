#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H
//=================================================================================================================
#include <QObject>
#include <QThread>
#include <QVector>
//=================================================================================================================
class QSound;
//=================================================================================================================
class GameAudioPlayer : public QObject
{
Q_OBJECT
public:
    GameAudioPlayer(QObject * pParent = nullptr);
    ~GameAudioPlayer();
protected:
    virtual void customEvent(QEvent * pCustomEvent);
    QSound * m_pMoveSound;
    QSound * m_pStopSound;
    QVector<QSound*> m_qvecShotSound;
    QSound * m_pExplosionSound;
    QVector<QSound*> m_qvecRotateSound;
    //QSound * m_pRotateSound;
    QSound * m_pGetPrizeSound;
};
//=================================================================================================================
class GameAudioThread : public QThread
{
Q_OBJECT
public:
    GameAudioThread(QObject * pObjectReceiver, QObject *pParent = Q_NULLPTR);
    virtual ~GameAudioThread();
    void SetObjectReceiver(QObject * m_pObjectReceiver);
    QObject * GetObjectTransmiter();
protected:
    virtual void run();
private:
    GameAudioPlayer * m_pGameAudioPlayer;
    QObject * m_pObjectReceiver;
};
//=================================================================================================================
#endif // AUDIOTHREAD_H
