#ifndef GAMESTATISTIC_H
#define GAMESTATISTIC_H
//=================================================================================================================
class GameStatistic
{
public:
    GameStatistic();
    ~GameStatistic();
    void AddScope(const int &iCost);
    void IncrementSimpleAliensKilled();
    void IncrementSpeedAliensKilled();
    int GetSimpleAliensKilled() const;
    int GetSpeedAliensKilled() const;
    int GetTotalKilled() const;
    int GetScope() const;
    int GetHiScope() const;
    bool IsGameVictory() const;
    void SetGameResult(const bool &bGameResult);
    void SetHiScope(const int &iHiScope);
    void Reset();

private:
   int m_iSimpleAliensKilled;
   int m_iSpeedAliensKilled;
   int m_iScope;
   int m_iHiScope;
   bool m_bGameResult;
};
//=================================================================================================================
#endif // GAMESTATISTIC_H
