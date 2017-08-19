#ifndef SPEEDALIENPANZER_H
#define SPEEDALIENPANZER_H
//===============================================================================================================
#include "AlienPanzers.h"
//===============================================================================================================
class SpeedAlienPanzer : public AlienPanzer
{
public:
    SpeedAlienPanzer(const int &iColumn, const int &iRow);
    ~SpeedAlienPanzer();
protected:
    virtual void SetStatistic();
    virtual int GetTypicalVelosity() const;
};
//===============================================================================================================
#endif // SPEEDALIENPANZER_H
