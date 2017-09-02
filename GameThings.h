#ifndef GAMETHINGS_H
#define GAMETHINGS_H
//=================================================================================================================
class Bullet;
class DynamicGameThings;
class GameStatistic;
class QDeclarativeView;
class QString;
class QObject;
class AudioDelegate;
class BigExplosion;
//=================================================================================================================
class GameThings
{
public:
    GameThings(const int &iColumn, const int &iRow);
    virtual ~GameThings();
    virtual void Draw();
    virtual QString GetStringImage() const = 0;
    virtual void BulletHitHandler(Bullet * pBullet);
    virtual bool CanMoveDynamicalThing(DynamicGameThings * pDynamicGameThings);
    void SetColumn(const int &iColumn);
    void SetXdiplace(const int &iXdiplace);
    void SetYdiplace(const int &iYdiplace);
    void SetRow(const int &iRow);
    int GetColumn() const;
    int GetRow() const;
    int GetXdiplace() const;
    int GetYdiplace() const;
    int GetLiveHits() const;
    bool IsExplosion();
    void SetExplosion(const bool bExplosion = true);
    BigExplosion * CreateBigExplosion() const;
    static void SetCellSizeOfSide(const int &iCellSizeOfSide);
    static void SetPointerGameStatistic(GameStatistic * psGameStatistic);
    static void SetAudioDelegate(AudioDelegate * pAudioDelegate);
    static void SetPointerMainDeclarativeView(QDeclarativeView *pMainDeclarativeView);
    static GameStatistic * GetPointerGameStatistic();
protected:
    int m_iColumn;
    int m_iRow;
    int m_iXdiplace;
    int m_iYdiplace;
    void SetLiveHits(const int &iLiveHits);
    void DecrementLiveHits();
    static int GetCellSide();
    QObject * m_pQmlImage;
    static GameStatistic * m_psGameStatistic;
    static QDeclarativeView * m_psMainDeclarativeView;
    static AudioDelegate * m_psAudioDelegate;
    virtual int GetX() const;
    virtual int GetY() const;
private:
    static int m_siCellSizeOfSide;
    int m_iLiveHits;
    bool m_bIsExplosion;
};
//=================================================================================================================
#endif // GAMETHINGS_H
