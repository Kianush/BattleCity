#ifndef AUDIOEVENTS_H
#define AUDIOEVENTS_H
//=================================================================================================================
#include <QEvent>
//=================================================================================================================
class ReadyGameAudioThreadEvent : public QEvent
{
public:
    enum {ReadyGameAudioThreadType = User + 1};
    ReadyGameAudioThreadEvent() : QEvent((Type)ReadyGameAudioThreadType) {}
    void SetObjectTransmiter(QObject * pTransmiterObject) {m_pTransmiterObject = pTransmiterObject;}
    QObject * GetObjectTransmiter() {return m_pTransmiterObject;}
private:
    QObject * m_pTransmiterObject;
};
//=================================================================================================================
class UserMoveAudioEvent : public QEvent
{
public:
    enum {UserMoveAudioType = User + 2};
    UserMoveAudioEvent() : QEvent((Type)UserMoveAudioType) {}
};
//=================================================================================================================
class UserStopAudioEvent : public QEvent
{
public:
    enum {UserStopAudioType = User + 3};
    UserStopAudioEvent() : QEvent((Type)UserStopAudioType) {}
};
//=================================================================================================================
class GameStopAudioEvent : public QEvent
{
public:
    enum {GameStopAudioType = User + 4};
    GameStopAudioEvent() : QEvent((Type)GameStopAudioType) {}
};
//=================================================================================================================
class ExplosionAudioEvent : public QEvent
{
public:
    enum {ExplosionAudioType = User + 5};
    ExplosionAudioEvent() : QEvent((Type)ExplosionAudioType) {}
};
//=================================================================================================================
class RotateAudioEvent : public QEvent
{
public:
    enum {RotateAudioType = User + 6};
    RotateAudioEvent() : QEvent((Type)RotateAudioType) {}
};
//=================================================================================================================
class ShotAudioEvent : public QEvent
{
public:
    enum {ShotAudioType = User + 7};
    ShotAudioEvent() : QEvent((Type)ShotAudioType) {}
};
//=================================================================================================================
class GetPrizeAudioEvent : public QEvent
{
public:
    enum {GetPrizeAudioType = User + 8};
    GetPrizeAudioEvent() : QEvent((Type)GetPrizeAudioType) {}
};
//=================================================================================================================
#endif // AUDIOEVENTS_H
