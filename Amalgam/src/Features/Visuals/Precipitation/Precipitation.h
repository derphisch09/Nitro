#pragma once

#include "../../../SDK/SDK.h"

class CPrecipitation
{
private:
    int m_iRainEntityIndex = -1;
    ClientClass* GetPrecipitationClass();

public:
    void Run();
    void Update();
    void Cleanup();

    bool IsRaining() const 
    { 
        return m_iRainEntityIndex != -1; 
    }

    friend class CVisuals;
};

ADD_FEATURE(CPrecipitation, Precipitation)