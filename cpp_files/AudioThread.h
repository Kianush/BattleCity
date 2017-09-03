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
    QVector<QSound*> m_qvecMoveSound;
    QVector<QSound*> m_qvecStopSound;
    QVector<QSound*> m_qvecShotSound;
    QVector<QSound*> m_qvecExplosionSound;
    QVector<QSound*> m_qvecRotateSound;
    QSound * m_pGetPrizeSound;
private:
    bool m_bIsMoving;
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
