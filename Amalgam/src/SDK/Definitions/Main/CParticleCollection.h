#pragma once

#include "../Misc/UtlObjectReference.h"

class CSheet;
typedef __m128 fltx4;

class CParticleSystemDefinition
{
public:
    byte pad0[12];
    int m_nInitialParticles;
    int m_nPerParticleUpdatedAttributeMask;
    int m_nPerParticleInitializedAttributeMask;
    int m_nInitialAttributeReadMask;
    int m_nAttributeReadMask;
    uint64 m_nControlPointReadMask;
    Vector m_BoundingBoxMin;
    Vector m_BoundingBoxMax;
    char m_pszMaterialName[MAX_PATH];
};

class CParticleCollection
{
public:
    CUtlReference<CSheet> m_Sheet;
    fltx4 m_fl4CurTime;
    int m_nPaddedActiveParticles;
    float m_flCurTime;
    int m_nActiveParticles;
    float m_flDt;
    float m_flPreviousDt;
    float m_flNextSleepTime;
    CUtlReference<CParticleSystemDefinition> m_pDef;
};

struct SpriteRenderInfo_t
{
    size_t m_nXYZStride{};
    fltx4* m_pXYZ{};
    size_t m_nRotStride{};
    fltx4* m_pRot{};
    size_t m_nYawStride{};
    fltx4* m_pYaw{};
    size_t m_nRGBStride{};
    fltx4* m_pRGB{};
    size_t m_nCreationTimeStride{};
    fltx4* m_pCreationTimeStamp{};
    size_t m_nSequenceStride{};
    fltx4* m_pSequenceNumber{};
    size_t m_nSequence1Stride{};
    fltx4* m_pSequence1Number{};
    float m_flAgeScale{};
    float m_flAgeScale2{};
    void* m_pSheet{};
    int m_nVertexOffset{};
    CParticleCollection* m_pParticles{};
};

struct ParticleRenderData_t
{
    float m_flSortKey;
    int   m_nIndex;
    float m_flRadius;
    uint8 m_nAlpha;
    uint8 m_nAlphaPad[3];
};