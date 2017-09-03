#ifndef AUDIODELEGATE_H
#define AUDIODELEGATE_H
//===============================================================================================================
#include <QObject>
//===============================================================================================================
class AudioDelegate : public QObject
{
Q_OBJECT
public:
    AudioDelegate(QObject * pParent = nullptr);
    ~AudioDelegate();
    void PlayOurMove();
    void PlayOurStop();
    void PlayGetPrize();
    void PlayShot();
    void PlayRotate();
    void PlayExplosion();
    void StopGameAudio();
protected:
    virtual void customEvent(QEvent * pCustomEvent);
private:
    QObject * m_pObjectReceiver;
};
//===============================================================================================================
#endif // AUDIODELEGATE_H
